const UserPost = require('../models/userPost');
const mongoose = require('mongoose');


// get all users posts
exports.getAllPosts = () => {
    return UserPost.find({})
};

// get post by id
exports.getPostId = (id) => {
    return UserPost.findOne({
        _id: id
    });
};

// add new post
module.exports.addNew = ({
    createdBy,
    content
}) => {
    let newData = new UserPost({
        createdBy: createdBy,
        content: content
    });

    return newData.save();
};

// get user posts
module.exports.userPosts = (username) => {
    return UserPost.aggregate([{
        '$match': {
            'createdBy': username
        }
    }, {
        '$lookup': {
            'from': 'users',
            'localField': 'createdBy',
            'foreignField': 'username',
            'as': 'InfoUser'
        }
    }, {
        '$project': {
            'createdBy': 1,
            'content': 1,
            'createdAt': 1,
            'InfoUser.photo': 1,
            'InfoUser.fullName': 1
        }
    }, {
        '$sort': {
            'createdAt': -1
        }
    }])
};

// get all posts ordered by created date
module.exports.postsDate = () => {
    return UserPost.find({}).sort({
        createdAt: 'desc'
    });
};

module.exports.getComments = (id) => {
    return UserPost.aggregate([{
        '$match': {
            '_id': mongoose.Types.ObjectId(id)
        }
    }, {
        '$unwind': {
            'path': '$comments',
            'preserveNullAndEmptyArrays': false
        }
    }, {
        '$lookup': {
            'from': 'users',
            'localField': 'comments.createdBy',
            'foreignField': 'username',
            'as': 'comments.InfoComment'
        }
    }, {
        '$group': {
            '_id': '$_id',
            'Comments': {
                '$push': '$comments'
            }
        }
    }, {
        '$project': {
            'Comments._id': 1,
            'Comments.createdBy': 1,
            'Comments.text': 1,
            'Comments.createdAt': 1,
            'Comments.InfoComment.fullName': 1,
            'Comments.InfoComment.photo': 1
        }
    }, {
        '$sort': { 'Comments.createdAt': -1 }
    }
])
};

module.exports.infoUserPost = () => {
    return UserPost.aggregate([{
        '$lookup': {
            'from': 'users',
            'localField': 'createdBy',
            'foreignField': 'username',
            'as': 'InfoUser'
        }
    }, {
        '$project': {
            'createdBy': 1,
            'content': 1,
            'createdAt': 1,
            'InfoUser.photo': 1,
            'InfoUser.fullName': 1
        }
    }, {
        '$sort': {
            'createdAt': -1
        }
    }])
};

// pesquisa de posts pelo texto
module.exports.postsSearch = (word) => {
    return UserPost.find({
        "content.text": {
            "$regex": word,
            "$options": "i"
        }
    }).sort({
        createdAt: 'desc'
    });
};

// delete post --> na route verificar primeiro se existe
module.exports.deletePost = (postId) => {
    return UserPost.findByIdAndRemove({
        _id: postId
    });
};

// update post
module.exports.updatePost = (postId, data) => {
    return UserPost.updateOne(
        {'_id': postId },
        {'content.text': data.content.text}
    ).exec();
};

// add comment
module.exports.addComment = (postId, comment) => {
    return UserPost.findOneAndUpdate({
        _id: postId
    }, {
        $push: {
            comments: comment
        }
    }, {
        new: true,
        runValidators: true
    });
};

// remove comment 
module.exports.removeComment = (postId, commentId) => {
    return UserPost.update({
        _id: postId
    }, {
        "$pull": {
            "comments": {
                _id: commentId
            }
        }
    }, {
        safe: true,
        multi: true
    });
};

// update comment 
module.exports.updateComment = (postId, commentId, text) => {
    return UserPost.updateOne({
        "_id": postId,
        "comments._id": commentId
    }, {
        $set: {
            "comments.$.text": text,
        }
    }, {
        new: true,
    });
};

// find by comment id
module.exports.postByCommentId = (commentId) => {

    let id = mongoose.Types.ObjectId(commentId);
    return UserPost.aggregate([{
        $unwind: "$comments"
    }, {
        $match: {
            "comments._id": id
        }
    }, {
        $project: {
            _id: 0,
            comments: 1
        }
    }]);
};