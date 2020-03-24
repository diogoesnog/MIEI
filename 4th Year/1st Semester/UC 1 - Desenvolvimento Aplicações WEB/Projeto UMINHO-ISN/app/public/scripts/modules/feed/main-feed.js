define([
    'jquery',
    'alert',
    'composer',
    'tagifyWrapper',
    'jquery-confirm',
    'bootstrap'
], function ($, alert, composer, tagify) {
    'use strict';

    function formatComment(content) {
        let info = `<div class="post-info border-bottom px-3">
        <div class="row">
            <div class="col-2 p-2">
                <div class="circle-avatar" style="background-image:url(${content.InfoComment[0].photo})"></div>
            </div>
            <div class="col-8 p-3">
                <t class="font-weight-bold">
                    ${content.InfoComment[0].fullName}
                </t>
                <a href="/profile/${content.createdBy}" class="text-muted">
                    @${content.createdBy}
                </a>
                <br>
                <div class="text-justify">
                   ${content.text}
                </div>
            </div>
        </div>
    </div>`;

        $('#comments-container').append(info);

    }

    // update-post-button
    $('#update-post-button').on('click', () => {
        let text = $('#edit-post-text').val();
        let id = $('#edit-post-id').attr('value');

        $.ajax({
            method: "PUT",
            url: `/api/userpost/${id}`,
            data: {
                content: {
                    text: text
                }
            },
            success: response => {
                console.log(response);
                $(location).attr('href', '/feed');
            },
            error: response => console.log(response)
        });
    });

    $(document).ready(() => {
        /**
         * View Comments Modal
         */
        $(document).on("click", ".view-comments", event => {
            let id = $(event.currentTarget).attr('data-value');
            $.ajax({
                type: "get",
                url: `/api/userpost/comments/${id}`,
                success: response => {
                    $('#comments-container').html("");

                    $('#submit-post-comment').attr('action', `api/userpost/comment/${id}`);

                    if (response.length > 0) {
                        response[0].Comments.forEach(content => formatComment(content));
                    }
                    $('#comments-modal').modal();
                },
                error: response => {
                    console.log(response);
                }
            })
        });
        /**
         * Edit a post
         */
        $(document).on('click', '.edit-post', event => {

            let id = $(event.currentTarget).attr("data-value");

            $.ajax({
                method: "GET",
                url: `/api/userpost/${id}`,
                success: response => {

                    $('#edit-post-id').attr('value', response._id);
                    $(".quill-editor .ql-editor").append(response.content.text);
                    $('#edit-post-modal').modal()
                },
                error: response => console.log(response)
            });
        });

        // update-post-button
        $('#update-post-button').on('click', () => {
            let content = $(".quill-editor .ql-editor").html();
            // $('#edit-post-text').val(content);

            let id = $('#edit-post-id').attr('value');
            // quill-editor
            $.ajax({
                method: "PUT",
                url: `/api/userpost/${id}`,
                data: {
                    content: {
                        text: content
                    }
                },
                success: response => {
                    console.log(response);
                    $(location).attr('href', '/feed');
                },
                error: response => console.log(response)
            });
        });

        /**
         * Delete a Given Post
         */
        $(document).on("click", ".delete-post", event => {
            let id = $(event.currentTarget).attr('data-value');
            $.confirm({
                title: 'Remove Post',
                content: 'Are you sure?',
                buttons: {
                    confirm: () => {

                        $.ajax({
                            type: "delete",
                            url: `/api/userpost/${id}`,
                            success: response => {
                                alert.warningAlert({title: "Post Deleted", body: ""});
                                console.log(response);
                                $(`#${response._id}`).remove();
                            },
                            error: response => {
                                console.log(response);
                            }
                        });
                    },
                    cancel: () => {
                    },
                }
            });
        });

        $('.manage-my-groups').on('click', () => {
            $.ajax({
                method: "GET",
                url: '/api/group/registered',
                success: response => {
                    $('#group-feed').html("");
                    // /group/
                    response.forEach(group => {
                        $('#group-list').append(`<p><a class="text-muted2" href="/group/${group._id}">${group.name}</a></p>`);
                    });
                    $('#manage-my-groups').modal();
                    console.log(response);
                }, error: response => console.log(response)
            });
        });

        /**
         * Create a new Post
         */
        const $postForm = $('#feed-post-form');

        $postForm.on('submit', (e) => {

            let content = $(".quill-composer .ql-editor").html();
            $('#user-post-text').attr('value', content);

            $postForm.unbind('submit').submit();

        });
    });
});