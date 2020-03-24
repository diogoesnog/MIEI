/**
 * User Post Schema
 * Contributors: Diogo Nogueira, Mateus Silva, Miguel R. Solans
 */

const mongoose = require('mongoose');

const commentSchema = new mongoose.Schema({
    _id: {
        type: mongoose.Types.ObjectId,
        auto: true
    },
    text: {
        type: String,
        required: true
    },
    createdBy: {
        type: String,
        required: true
    },
    createdAt: {
        type: Date,
        default: Date.now
    }
});

const postContentSchema = new mongoose.Schema({
    files: [String],
    text: String
});
const userPostSchema = new mongoose.Schema({
    _id: {
        type: mongoose.Types.ObjectId,
        auto: true
    },
    createdBy: {
        type: String,
        required: true
    },
    content: postContentSchema,
    comments: {
        type: [commentSchema],
        default: []
    },
    createdAt: {
        type: Date,
        default: Date.now
    }
});

const UserPost = mongoose.model('userPosts', userPostSchema, 'userPosts');

module.exports = UserPost;