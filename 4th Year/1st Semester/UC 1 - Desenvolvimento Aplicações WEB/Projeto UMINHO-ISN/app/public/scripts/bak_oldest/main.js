require.config({
    "paths": {
        // External
        "jquery": "external/jquery",
        "bootstrap": "external/bootstrap",

        // Angular
        // Translations
        // "i18n": "external/jQuery-i18n/jquery.i18n",
        // "i18n-messagestore": "external/jQuery-i18n/jquery.i18n.messagestore",
        // "i18n-fallbacks": "external/jQuery-i18n/jquery.i18n.fallbacks",
        // "i18n-parser": "external/jQuery-i18n/jquery.i18n.parser",
        // "i18n-emitter": "external/jQuery-i18n/jquery.i18n.emitter",
        // "i18n-language": "external/jQuery-i18n/jquery.i18n.language",


        // i18next
        // "i18next": "external/i18next",

        // Modules
        // "app-translations": 'app-translations',

        // Modules
        "loginPage": "modules/loginPage"
        // "translations": "modules/translations"
    },
    "bootstrap": {
        "deps": [
            'jquery'
        ]
    },
    "shim": {
        'i18n': [ 'jquery' ],
        'i18next': ['jquery']
    }
});

require([
    'loginPage',
], () => {
    console.log("RequireJS Modules Loaded")
});