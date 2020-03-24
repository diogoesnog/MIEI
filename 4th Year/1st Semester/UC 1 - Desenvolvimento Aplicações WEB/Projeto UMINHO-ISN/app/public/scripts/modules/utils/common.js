define([
    'jquery',
    'tagifyWrapper'
], ($, tagify) => {
    /**
     * User Logout
     */
    $('#signout').on('click', () => {
        document.cookie = "userToken" +'=; Path=/; Expires=Thu, 01 Jan 1970 00:00:01 GMT;';

        window.location.href = '/';
    });

    /**
     * Tagify Initialization
     */
    let options = {
        selector: "input[name=groupnames]",
        api: "/api/group/match",
        field: "name",
        id: "_id",
        enforce: true,
        autocomplete: true
    };
    tagify.config( options );
});