const mongoose = require('mongoose');

const messageSchema = new mongoose.Schema({
    by: String,
    date: Date,
    text: String
});

const chatSchema = new mongoose.Schema({
    _id: { type: mongoose.Types.ObjectId, auto: true },
    name: String,
    participants: [ String ],
    messages: [messageSchema],
    publicRoom: {
        type: Boolean,
        default: false,
    }
});

const Chatroom = mongoose.model('chatrooms', chatSchema, 'chatrooms');

module.exports = Chatroom;