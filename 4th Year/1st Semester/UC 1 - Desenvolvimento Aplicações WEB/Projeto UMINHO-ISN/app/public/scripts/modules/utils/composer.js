define([
    'jquery',
    'quill'
], ($, Quill) => {
    "use strict";
    const options = {
        theme: 'snow',
        formats: [
            'bold',
            'header',
            'italic',
            'link',
            'list',
            'blockquote',
            'indent',
            'video',
            'code-block'
        ],
        modules: {
            toolbar: [
                ['bold', 'italic', 'link', 'underline', 'strike'],
                ['blockquote', {'list': 'ordered'}, {'list': 'bullet'}, 'code-block'],
                [ 'video' ]
            ],
            clipboard: {
                matchVisual: false // https://quilljs.com/docs/modules/clipboard/#matchvisual
            }
        },
        placeholder: 'Write something...'
    };
    /**
     * QuillJS Configuration
     */
    const quill = new Quill('.quill-composer', options);

    const editor = new Quill('.quill-editor', options);
    return {
        quill: this.quill,
        parseData: (data, id, attr) => {
            let content = $(".quill-composer .ql-editor").html();

            $(id).attr(attr, content);

            let dataJson = {};
            data.forEach(entry => {
                dataJson[entry.name] = entry.value;
            });
            return dataJson;
        }
    }
});

