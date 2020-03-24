define(['jquery', 'tagify', 'composer', 'dropzone', 'bootstrap'], (
    $,
    Tagify,
    composer,
    dropzone
) => {
    'use strict';

    $(document).ready(() => {
        let input = document.querySelector('input[name=courses]');
        new Tagify(input);

        // Triggers
        // Edit Profile Picture Sidebar
        $('#edit-profile').on('click', event => {
            $('#editProfile').modal('show');
        });
        // Edit Password
        $('#change-password').on('click', event => {
            $('#changePasswordForm').modal('show');
        });

        // Perform Put Actions
        $('#changePasswordButton').on('click', event => {
            let newPassword = $('#password').val();

            $.ajax({
                type: 'PUT',
                url: 'http://localhost:3030/settings/change-password',
                data: `password=${newPassword}`,
                success: result => {
                    console.log(result);
                },
                error: result => {
                    console.log(result);
                    alert(result);
                }
            });
        });

        // Submit Changes
        const $infoForm = $('#update-user-info');
        $infoForm.on('submit', handler => {
            handler.preventDefault();

            let dataArray = $infoForm.serializeArray();

            let content = $('.quill-composer .ql-editor').html();

            let dataJson = composer.parseData(dataArray, '#bio', 'value');
            dataJson.bio = content;

            console.log(dataJson);
            $.ajax({
                url: `/api/settings/update`,
                type: 'put',
                data: dataJson,
                success: response => {
                    console.log(response);
                    $('#update-user-info').click();
                },
                error: response => console.log(response)
            });
        });

        // Settings Dropzone
        // let t = new dropzone.Dropzone("#settings-dropzone", { url: "/file/post"});
        $('#settings-dropzone').dropzone({
            url: '/settings/picture-update',
            uploadMultiple: false,
            acceptedFiles: 'image/*',
            success: function(file, res) {
                console.log('Upload success.');
                console.log(res);
            },
            error: function(file, res) {
                console.log('Upload error.');
                console.log(res);
            }
        });
    });

    $('#save-profile-picture').on('click', () => {
        $(location).attr('href', '/settings');
    });

    $('#update-user-info-social').on('submit', () => {
        let instagram = $('#instagram').val();
        let twitter = $('#twitter').val();
        let linkedIn = $('#linkedIn').val();
        let github = $('#github').val();
        let facebook = $('#facebook').val();

        $.ajax({
            method: 'PUT',
            url: `/api/settings/updatesocial`,
            data: {
                instagram: instagram,
                twitter: twitter,
                linkedIn: linkedIn,
                github: github,
                facebook: facebook
            },
            success: response => {
                console.log(response);
                $(location).attr('href', '/settings');
            },
            error: response => console.log(response)
        });
    });
});
