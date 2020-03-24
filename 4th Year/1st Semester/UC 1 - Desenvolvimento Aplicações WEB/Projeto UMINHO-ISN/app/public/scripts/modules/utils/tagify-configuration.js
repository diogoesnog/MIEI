define([
    'jquery',
    'tagify'
], ($, Tagify) => {
    "use strict";

    return {
        config: ({selector, api, field, id, enforce, autocomplete}) => {
            let tagifyInput = document.querySelector(selector);
            let tagifyObj;
            let onInput = e => {
                let value = e.detail.value;
                tagifyObj.settings.whitelist.length = 0;

                $.ajax({
                    method: "GET",
                    url: `${api}/${value}`,
                    success: response => {
                        response.forEach(data => {
                            let entry = {
                                value: data[field],
                                id: data[id]
                            };
                            tagifyObj.settings.whitelist.push(entry);
                            // tagifyObj.settings.whitelist.push(data[field])
                        });
                    },
                    error: response => {
                        console.log(response);
                    }
                });
                console.log(value);
            };


            tagifyObj = new Tagify(tagifyInput, {
                enforceWhitelist: enforce,
                autocomplete: autocomplete,
                whitelist: []
            });
            tagifyObj.on('input', onInput);

            return tagifyObj;
        }
    }
});