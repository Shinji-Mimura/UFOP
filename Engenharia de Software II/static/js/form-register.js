$("#register-form").submit(function (event) {
    var p1 = document.getElementById("password-one");
    var p2 = document.getElementById("password-two");
    var email = document.getElementById("email-address");

    var re = /^\S+@\S+$/; // regex for email front-end validation

    if (!re.test(email.value)) {
        event.preventDefault();
        $("body").toast({
            class: "error",
            position: "bottom center",
            message: `Your email is not valid!`,
        });
    }

    if (p1.value != p2.value) {
        event.preventDefault();
        $("body").toast({
            class: "error",
            position: "bottom center",
            message: `The passwords don't match!`,
        });
    }

    if (p1.value.length < 6) {
        event.preventDefault();
        $("body").toast({
            class: "error",
            position: "bottom center",
            message: `The password need at least six characters!`,
        });
    }

});
