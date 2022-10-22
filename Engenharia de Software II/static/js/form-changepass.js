$("#register-form").submit(function (event) {
    var p1 = document.getElementById("password-one");
    var p2 = document.getElementById("password-two");


    if (p1.value != p2.value) {
        event.preventDefault();
        $("body").toast({
            class: "error",
            position: "bottom center",
            message: `The passwords don't match!`,
        });
    }

});
