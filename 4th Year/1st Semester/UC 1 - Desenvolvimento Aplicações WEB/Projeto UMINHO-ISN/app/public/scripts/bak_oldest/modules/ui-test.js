define([
    'jquery',
    'User'
], function($, User) {
    "use strict";

    let about = new User("Miguel Solans", "Braga");

    $(document).ready( () => {

        $("#about").append(about.overrideUser());

    });
});