from re import M
from site import USER_BASE
from flask import (
    Flask,
    render_template,
    redirect,
    request,
    url_for,
    make_response,
    send_from_directory,
    url_for,
)
from functools import wraps
import firebase_admin
from firebase_admin import credentials, auth, storage, firestore
import json
import pyrebase
import multiprocessing
import time
import smtplib, ssl
from email.mime.text import MIMEText
import requests
from utils.recaptcha import ReCaptcha
from utils.database import Database
from flask_uploads import UploadSet, IMAGES, configure_uploads
from flask_wtf import FlaskForm
from flask_wtf.file import FileField, FileRequired, FileAllowed
from wtforms import SubmitField
from utils.plantID import PlantID
import base64
import requests
from flask import request
import wikipedia

cred = credentials.Certificate(
    "./firebase/tupabotanical-firebase-adminsdk-g7pnk-9e9bc7cc2c.json"
)
firebase_admin.initialize_app(cred)
pb = pyrebase.initialize_app(json.load(open("./firebase/fbconfig.json")))
db = firestore.client()
db = Database(db)
pd = PlantID()

# email configs ###########################

smtp_server = "smtp.gmail.com"
port = 587
sender_email = ""
password = ""
context = ssl.create_default_context()

app = Flask(__name__)

# Upload Configs
app.config["SECRET_KEY"] = ""
app.config["UPLOADED_PHOTOS_DEST"] = "images"
photos = UploadSet("photos", IMAGES)
configure_uploads(app, photos)

# Recaptcha configs
app.config.from_object(ReCaptcha)
recaptcha_pub_key = ReCaptcha.RC_PubK
recaptcha_priv_key = ReCaptcha.RC_PrivK

# Utils ###########################
def send_email_with_link(email, reason, link):
    try:
        server = smtplib.SMTP(smtp_server, port)
        server.ehlo()
        server.starttls(context=context)
        server.ehlo()
        server.login(sender_email, password)

        email_message = MIMEText(f"{link}")

        email_message["Subject"] = f"[TUPÃ BOTANICAL] {reason} Account Link"

        server.sendmail(sender_email, email, email_message.as_string())

    except Exception as e:
        return {"error": e}
    finally:
        server.quit()


class UploadForm(FlaskForm):
    photo = FileField(
        validators=[
            FileAllowed(photos, "Only images are allowed"),
            FileRequired("File field should not be empty"),
        ]
    )
    submit = SubmitField("Upload")


def get_email_jwt():
    jwt = str(request.cookies.get("access_token"))
    payload = jwt.split(".")[1]
    payload = json.loads(base64.b64decode(payload + "==").decode("utf-8"))
    return payload["email"]


# Middlewares ###########################
def check_token(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        access_token = request.cookies.get("access_token")
        try:
            user = auth.verify_id_token(access_token)
        except:
            return {"message": "Missing Authorization Token"}, 403
        return f(*args, **kwargs)

    return wrap


def is_human(captcha_response):
    payload = {"response": captcha_response, "secret": recaptcha_priv_key}
    response = requests.post(
        "https://www.google.com/recaptcha/api/siteverify", data=payload
    )
    response_text = json.loads(response.text)
    if response_text == None:
        return "Something's wrong"
    elif response_text["success"] == False:
        return "Error! Try again later…"
    else:
        return True


def check_email_verification(email):
    user = auth.get_user_by_email(email)
    return user.email_verified


# Routes ###########################
@app.route("/")
def index():
    return render_template("index.html")


@app.route("/signin")
def signin():
    return render_template("signin.html", pub_key=recaptcha_pub_key)


@app.route("/register")
def register():
    return render_template("register.html", pub_key=recaptcha_pub_key)


@app.route("/signup", methods=["POST"])
def signup():
    if request.method == "POST":  # Only listen to POST
        result = request.form  # Get the data submitted
        email = result["email"]
        password = result["password"]
        try:

            captcha_response = request.form["g-recaptcha-response"]
            captcha_treatmeant = is_human(captcha_response)
            if captcha_treatmeant == True:

                user = auth.create_user(email=email, password=password)
                link = auth.generate_email_verification_link(email)
                reason = "Activation Account"

                # Avoid wait email sending delay using multiprocessing (threads) to continue html render.
                # Daemons are allocated like a subprocess in OS to continue executing tasks
                # I reccomend read about async/thread functions in python

                process = multiprocessing.Process(
                    target=send_email_with_link, args=(email, reason, link)
                )
                process.daemon = True
                process.start()

                db.create_user_collection(email)

                return redirect(url_for("signin"))

            else:
                return redirect(url_for("signup"))

        except Exception as e:
            return render_template("register.html", error=e)


@app.route("/login", methods=["POST"])
def login():
    if request.method == "POST":  # Only if data has been posted
        result = request.form  # Get the data
        email = result["email"]
        password = result["password"]
        username = str(email)
        print(username)
        try:
            if check_email_verification(email):

                captcha_response = request.form["g-recaptcha-response"]
                captcha_treatmeant = is_human(captcha_response)
                if captcha_treatmeant == True:
                    user = pb.auth().sign_in_with_email_and_password(email, password)
                    jwt = user["idToken"]
                    response = make_response(redirect("dashboard"))
                    response.set_cookie(
                        "access_token",
                        jwt,
                        httponly=True,
                        samesite="Strict",
                        secure=True,
                    )
                    return response

                else:
                    return redirect("signin")
            else:
                return redirect("signin")

        except Exception as e:
            return redirect("signin")


@app.route("/passwordReset")
def passwordReset():
    return render_template("password_reset.html", pub_key=recaptcha_pub_key)


@app.route("/passwordChange")
@check_token
def passwordChange():
    return render_template("password_change.html", pub_key=recaptcha_pub_key)


@app.route("/images/<filename>")
def get_file(filename):
    return send_from_directory(app.config["UPLOADED_PHOTOS_DEST"], filename)


@app.route("/dashboard", methods=["GET", "POST"])
@check_token
def dashboard():

    username = get_email_jwt()

    try:
        form = UploadForm()
        if form.validate_on_submit():
            filename = photos.save(form.photo.data)
            file_url = url_for("get_file", filename=filename)
            db.upload_image(file_url, username)
        else:
            file_url = None

        images_name = db.get_usernames_images(username)

        images_url = [db.get_image_link(i) for i in images_name]
        images_title = [db.get_image_name(i) for i in images_name]
        images_description = [db.get_image_description(i) for i in images_name]
        images_upload = [db.get_image_date(i) for i in images_name]
        images_id = [db.get_image_id(i) for i in images_name]

        return render_template(
            "dashboard.html",
            form=form,
            file_urls=images_url,
            images_description=images_description,
            images_name=images_title,
            images_upload=images_upload,
            images_id=images_id,
        )
    except Exception as e:
        return render_template("dashboard.html", form=form)


@app.route("/resetpassword", methods=["POST"])
def resetpassword():
    try:
        captcha_response = request.form["g-recaptcha-response"]
        captcha_treatmeant = is_human(captcha_response)
        if captcha_treatmeant == True:
            result = request.form
            email = result["email"]
            reason = "Reset Password"
            link = auth.generate_password_reset_link(email)
            send_email_with_link(email, reason, link)
            return render_template(
                "password_reset.html",
                error="We send a reset password link to your email!",
            )
        else:
            return render_template("password_reset.html", error=captcha_treatmeant)
    except Exception as e:
        return render_template("password_reset.html", error=e)


@app.route("/passwordchange", methods=["POST"])
@check_token
def passwordchange():
    try:
        captcha_response = request.form["g-recaptcha-response"]
        captcha_treatmeant = is_human(captcha_response)
        if captcha_treatmeant == True:
            result = request.form
            email = result["email"]
            p1 = result["password"]
            p2 = result["password2"]
            user_uid = auth.get_user_by_email(email).uid
            auth.update_user(uid=user_uid, password=p1)
            return render_template("password_change.html", error="Password Changed!")
        else:
            return render_template("password_reset.html", error=captcha_treatmeant)
    except Exception as e:
        return render_template("password_change.html", error=e)


@app.route("/delete")
@check_token
def delete():
    return render_template("delete.html")


@app.route("/deleteAccount", methods=["POST"])
@check_token
def deleteAccount():
    try:
        result = request.form
        email = result["email"]
        password = result["password"]
        user_uid = pb.auth().sign_in_with_email_and_password(email, password).uid
        auth.delete_user(user_uid)
        return redirect(url_for("index"), code=200)
    except Exception as e:
        return render_template("delete.html", error="Error! Try again later…")


@app.route("/analyzeImage/<imageName>")
@check_token
def analyzeImage(imageName):
    try:
        image_url = db.get_image_link(imageName)
        encoded_image = []
        encoded_image.append(
            base64.b64encode(requests.get(image_url).content).decode("utf-8")
        )
        image_datas = json.loads(pd.identify(encoded_image)[0])
        suggestions = image_datas["suggestions"]

        scientific_name = suggestions[0]["plant_details"]["scientific_name"]
        db.set_image_name(imageName, scientific_name)
        description = wikipedia.page(scientific_name).summary
        db.set_image_description(imageName, description)
        db.set_image_id(imageName, imageName)
        return redirect(url_for("dashboard"))
    except:
        return redirect(url_for("dashboard"))


@app.route("/deleteImage/<imageName>")
@check_token
def deleteImage(imageName):
    try:
        db.delete_image(imageName)
        return redirect(url_for("dashboard"))
    except:
        return redirect(url_for("dashboard"))


if __name__ == "__main__":
    app.run(debug=True)
