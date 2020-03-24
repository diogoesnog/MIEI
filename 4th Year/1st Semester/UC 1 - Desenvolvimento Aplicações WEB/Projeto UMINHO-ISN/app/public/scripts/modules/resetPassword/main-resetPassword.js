define(['jquery', 'alert', 'bootstrap'], (
    $,
    alert
) => {
    'use strict';

    $('#sendemail').on('click', event => {
        let email = $('#email').val();
        event.preventDefault();
        console.log(email);
        $.ajax({
            type: 'POST',
            dataType: 'json',
            url: '/forgotpassword',
            data: {
                email: email
            },
            success: result => {
                alert.warningAlert(result);

            },
            error: result => {
                console.log(results);
            }
        });
    });



    $('#newpasswordbtn').on('click', event => {
        let newpassword = $('#newpassword').val();
        let token = $('#token').attr('value');
        event.preventDefault();
        $.ajax({
            type: 'PUT',
            url: `/resetpassword/${token}`,
            data: {
                password: newpassword
            },
            success: result => {
                alert.warningAlert(result);
            },
            error: result => {
                console.log(results);
            }
        });
    });

});