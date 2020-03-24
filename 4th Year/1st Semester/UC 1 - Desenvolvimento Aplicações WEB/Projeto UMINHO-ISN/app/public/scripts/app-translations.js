let app = angular.module('ISN', ['pascalprecht.translate']);

app.run(['$rootScope', function($rootScope) {
    if(localStorage.getItem('language') !== null )
        $rootScope.lang = localStorage.getItem('language');
    else
        $rootScope.lang = "en-US";

}]);

app.config(function ($translateProvider) {
    $translateProvider
        .useStaticFilesLoader({
            prefix: './i18n/',
            suffix: '.json'
        })
        .useSanitizeValueStrategy('sanitizeParameters')
        .preferredLanguage(
            localStorage.getItem('language') || 'en-US'
        );
    console.dir($translateProvider)
});

app.controller('multiLang', ($scope, $rootScope, $translate) => {
    $scope.changeLanguage = function (key) {
        $rootScope.lang = key;
        $translate.use(key);
    };
});