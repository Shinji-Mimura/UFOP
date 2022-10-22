from firebase_admin import credentials, auth, storage, firestore
import os
from datetime import date


class Database:
    def __init__(self, db):
        self.bucket = storage.bucket("")
        self.db = db

    def rename_image(self, filename, username):
        doc = self.db.collection("users").document(username).get()
        if doc.exists:
            user = doc.to_dict()
            user_images = len(user["images"])
            name = filename.split("/")
            rest = name[-1].split(".")
            new = username + "_" + str(user_images + 1) + "." + rest[1]
            return new

        else:
            return username + "_0"

    def upload_image(self, filename, username):
        path = os.path.abspath("./" + filename)
        imageName = self.rename_image(filename, username)
        blob = self.bucket.blob(imageName)
        blob.upload_from_filename(path)
        blob.make_public()
        link = blob.public_url
        self.db.collection("users").document(username).update(
            {"images": firestore.ArrayUnion([imageName])}
        )
        today = date.today()
        todayT = today.strftime("%d/%m/%Y")
        self.db.collection("images").document(imageName).set(
            {
                "link": link,
                "description": "",
                "name": imageName,
                "date": todayT,
                "id": imageName,
            }
        )

        self.remove_image_local(path)

    def get_usernames_images(self, username):
        doc = self.db.collection("users").document(username).get()
        if doc.exists:
            user = doc.to_dict()
            images = user["images"]
            return images
        else:
            return []

    def get_image_id(self, image):
        doc = self.db.collection("images").document(image).get()
        if doc.exists:
            im = doc.to_dict()
            return im["id"]
        else:
            return ""

    def get_image_description(self, image):
        doc = self.db.collection("images").document(image).get()
        if doc.exists:
            im = doc.to_dict()
            description = im["description"]
            return description
        else:
            return ""

    def get_image_link(self, image):
        doc = self.db.collection("images").document(image).get()
        if doc.exists:
            im = doc.to_dict()
            return im["link"]
        else:
            return ""

    def get_image_name(self, image):
        doc = self.db.collection("images").document(image).get()
        if doc.exists:
            im = doc.to_dict()
            return im["name"]
        else:
            return ""

    def get_image_date(self, image):
        doc = self.db.collection("images").document(image).get()
        if doc.exists:
            im = doc.to_dict()
            return im["date"]
        else:
            return ""

    def create_user_collection(self, email):
        self.db.collection("users").document(email).set({"images": []})

    def remove_image_local(self, path):
        try:
            os.remove(path)
        except Exception as e:
            print(e)

    def set_image_description(self, image, description):
        today = date.today()
        todayT = today.strftime("%d/%m/%Y")
        doc = (
            self.db.collection("images")
            .document(image)
            .set(
                {
                    "link": self.get_image_link(image),
                    "description": description,
                    "name": self.get_image_name(image),
                    "date": todayT,
                    "id": self.get_image_id(image),
                }
            )
        )

    def set_image_name(self, image, name):
        today = date.today()
        todayT = today.strftime("%d/%m/%Y")
        doc = (
            self.db.collection("images")
            .document(image)
            .set(
                {
                    "link": self.get_image_link(image),
                    "description": self.get_image_description(image),
                    "name": name,
                    "date": todayT,
                    "id": self.get_image_id(image),
                }
            )
        )

    def delete_image(self, image):
        self.db.collection("images").document(image).delete()

    def set_image_id(self, image, idd):
        today = date.today()
        todayT = today.strftime("%d/%m/%Y")
        doc = (
            self.db.collection("images")
            .document(image)
            .set(
                {
                    "link": self.get_image_link(image),
                    "description": self.get_image_description(image),
                    "name": name,
                    "date": todayT,
                    "id": idd,
                }
            )
        )
