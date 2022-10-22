$("#signin-form").submit(function (event) {
    var email = document.getElementById("email-address");

    var re = /^\S+@\S+$/;

    if (!re.test(email.value)) {
        event.preventDefault();
        $("body").toast({
            class: "error",
            position: "bottom center",
            message: `Your email is not valid!`,
        });
    }
});
