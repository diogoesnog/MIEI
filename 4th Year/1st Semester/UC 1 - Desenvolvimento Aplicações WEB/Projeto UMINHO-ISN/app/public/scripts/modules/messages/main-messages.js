define([
    'jquery',
    'alert',
    'tagifyWrapper',
    'jquery-confirm',
    'bootstrap'
], ($, alert, tagify) => {
    "use strict";

    const addMessage = (message) => {
        let loginUser = $("#loginUser").attr('data-value');
        
        if(loginUser == message.by) { 
            $("#messages-wrapper").append(`
            <li class="list-group-item border-0 float-right">
                <div class="d-inline-flex p-2 borderChatMe float-right">
                    ${message.text}
                </div>
            </li>
            `);
        }

        else {
            $("#messages-wrapper").append(`

                <li class="list-group-item border-0">
                    <div class="row">
                        <div class="col-0 p-2">
                            <a href="/profile/${message.by}" target="_blank">
                                <div title="${message.InfoUser[0].fullName}" class="circle-avatar" style="background-image:url(${message.InfoUser[0].photo})"></div>
                            </a>
                        </div>
                        <div class="d-inline-flex p-2 m-2 borderChat">
                            ${message.text}
                        </div>

                    </div>
                </li>
            `);
        }

        console.log("Adding message...");
        console.table(message);
    };


    $(document).ready( () => {
        $("#chat-selected").hide();
        let previousConversation;

        /**
         * Create a new Conversation Modal
         */
        $('#new-chat').on('click', event => {
            $("#new-chatroom-modal").modal();
        });

        /**
         * Open a Given Conversation
         */
        $(document).on('click', '.open-conversation', event => {
            let id = $(event.currentTarget).attr('id');

            if(previousConversation !== undefined) {
                console.log(`Previous: ${previousConversation}`);
                $(`#${previousConversation}`).removeClass('active');
            }

            event.currentTarget.className += " active";

            previousConversation = id;

            console.log(id);

            $.ajax({
                type: 'GET',
                url: `/api/messenger/${id}`,
                success: response => {
                    $("#messages-wrapper").html("");
                    $("#no-chat-selected").hide();
                    $("#chat-selected").show();

                    $("#chatName").text(response[0].name);
                    $('input[name=chatId]').val(response[0]._id);
                    $("#leave-conversation").attr('value', response[0]._id);

                    response[0].Messages.forEach(message => {
                        if(message.InfoUser.length > 0)
                            addMessage(message);
                    });
                    // messages-wrapper

                },
                error: response => {
                    console.log(response);
                }
            });
        });


        /**
         * Send a Message
         */
        $("#send-message-button").on('click', event => {
            console.log("Sending message...");

            let msg = $("#message-body-form").val();
            let chatId = $('input[name=chatId]').val();

            let body = {
                text: msg,
                chatId: chatId
            };

            $.ajax({
                type: 'put',
                url: `/api/messenger`,
                contentType: 'application/json',
                data: JSON.stringify(body),
                success: response => {
                    body.by = "me";
                    addMessage(body);
                },
                error: response => {
                    // Oops...
                    console.log(response);
                }
            });
        });

        /**
         * Remove myself from conversation
         */
        $(document).on('click', '#leave-conversation', event => {
            let id = $(event.currentTarget).attr('value');

            $.confirm({
                title: 'Leave Conversation',
                content: 'Are you sure?',
                buttons: {
                    confirm: () => {
                        $.ajax({
                            type: 'delete',
                            url: `/api/messenger/${id}`,
                            success: response => {
                                console.log("Left the Chat");
                                let message = {
                                    title: "You've just left the conversation",
                                };

                                alert.warningAlert(message);

                                $(`#${response._id}`).remove();
                                $('#chat-selected').hide();
                                $('#no-chat-selected').show();

                                console.log(response);
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


        let options = {
            selector: "input[name=participants]",
            api: "/api/user/match",
            field: "username",
            enforce: true,
            autocomplete: true
        };
        tagify.config( options );

    });


});


