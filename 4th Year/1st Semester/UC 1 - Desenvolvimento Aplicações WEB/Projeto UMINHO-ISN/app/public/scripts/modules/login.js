$(document).ready(() => {
    $('#call-register').click(() => {
        $('#register-form-container').show();
        $('#login-form-container').hide(750);
    });
    $('#call-login').click(() => {
        $('#register-form-container').hide(750);
        $('#login-form-container').show();
    });
});