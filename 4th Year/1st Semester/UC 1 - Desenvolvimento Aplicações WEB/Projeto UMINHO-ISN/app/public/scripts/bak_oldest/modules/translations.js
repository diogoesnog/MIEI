define([
    'jquery',
    'i18next'
], ($, i18next) => {
    console.dir(i18next);

    let lang = localStorage.getItem('language');

    i18next.init({
        resGetPath: localStorage.getItem('language') === null ? 'i18n/en-US.json' : lang,
        getAsync: false
    }, () => {
        $("[data-i18n]").i18n()
    });

    console.log("Translations Loaded");
});