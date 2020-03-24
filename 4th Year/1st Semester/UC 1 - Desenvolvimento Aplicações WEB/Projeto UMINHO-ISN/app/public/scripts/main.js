require.config({
    "baseUrl": '/scripts',
    "paths": {

        /**
         * Application External Libraries
         */
        // jQuery & Plguins
        "jquery": "external/jQuery/jquery-3.4.1.min",
        "jquery-confirm": "external/jQuery/plugins/jquery-confirm/jquery-confirm",

        // Bootstrap
        "bootstrap": "external/bootstrap/bootstrap.bundle",
        // "popper": "external/bootstrap/popper",

        // Tagify
        "tagify": "external/tagify/tagify",


        // QuillJS
        "quill": "external/quill/quill",

        // Dropzone
        "dropzone": "external/dropzone/dropzone",


        /**
         * Application Utils
         */
        // Notification Alerts
        "alert": "modules/utils/alerts",
        // Composer
        "composer": "modules/utils/composer",
        // Tagify Configuration
        "tagifyWrapper": "modules/utils/tagify-configuration",

        /**
         * Common Logic Scripts
         */
        "common": "modules/utils/common",

        /**
         * Application Modules
         */
        // Settings
        "settings": "modules/settings/main-settings",
        // Messages
        "messages": "modules/messages/main-messages",

        // Feed
        "feed": "modules/feed/main-feed"




    },

    /**
     * Shim Libraries
     */
    "jquery-confirm": {
        deps: ['jquery'],
        exports: 'confirm'
    },

    "dropzone": {
        deps: ['jquery'],
        exports: 'dropzone'
    },

    "bootstrap": {
        "deps": [
            'jquery'
            // 'popper'
        ]
    },
    scriptType: 'text/javascript'

});

require([
    'composer',
    'alert',
    'common',
    'tagifyWrapper'
], () => {
    console.clear();
    console.log("Common modules loaded");
});