define([
    // Nothing
], function () {
    "use strict";

    function User(name, city) {
        this.name = name;
        this.city = city;

        this.overrideUser = () => {
            return `HelloWorld! I'm ${this.name} from ${this.city}`;
        }
    }

    return User;

});