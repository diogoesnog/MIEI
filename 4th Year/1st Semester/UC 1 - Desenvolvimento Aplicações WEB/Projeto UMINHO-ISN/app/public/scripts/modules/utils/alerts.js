define([
    'jquery'
], ($) => {
    "use strict";

    return {

        successAlert: ({title, body}) => {

        },



        primaryAlert: ({title, body}) => {

        },

        infoAlert: ({title, body}) => {

        },

        warningAlert: ({title, body})  => {
        $('#alerts-container').append(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
                                        <h4 class="alert-heading">${title}</h4><p>${body}</p>
                                        <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                                            <span aria-hidden="true">&times;</span>
                                        </button>
                                   </div>`);
        },

        dangerAlert: ({title, body}) => {

        },

        darkAlert: ({title, body}) => {

        }

    }
});


function successAlert({title, body}) {

}
