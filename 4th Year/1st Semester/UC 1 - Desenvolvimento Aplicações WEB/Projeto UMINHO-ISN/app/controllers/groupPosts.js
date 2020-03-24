const mongoose = require('mongoose');
const GroupPosts = require('../models/groupPost');

module.exports.getSinglePost = (id) => {
    return GroupPosts.findById(id);
};

// get post by id
exports.getGroupPostId = (id) => {
    return GroupPosts.find({ groupId: id})
        .sort({
            createdAt: 'desc'
        });
};

// add new post
module.exports.addNewGroupPost = (post) => {
    let newData = new GroupPosts(post);

    return newData.save();
};

// pesquisa de posts pelo texto
module.exports.postsSearch = (word) => {
    return GroupPosts.find({
        "content.text": {
            "$regex": word,
            "$options": "i"
        }
    }).sort({
        createdAt: 'desc'
    })
};

// update post
module.exports.updatePost = (postId, data) => {
    return GroupPosts.findByIdAndUpdate(postId, data, {
        new: true,
        runValidators: true
    })
};

// remover post
module.exports.deletePost = (postId) => {
    return GroupPosts.findByIdAndRemove({
        _id: postId
    })
};

// add comment
module.exports.addComment = (postId, comment) => {
    return GroupPosts.findByIdAndUpdate( postId, {
        $push: {
            comments: comment
        }
    }, {
        new: true,
        runValidators: true
    });
};

// Get Comments
module.exports.getComments = (id) => {
    return GroupPosts.aggregate([{
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

// remove comment
module.exports.removeComment = (postId, commentId) => {
    return GroupPosts.findByIdAndUpdate( postId, {
        "$pull": {
            "comments": {
                _id: commentId
            }
        }
    }, {
        safe: true,
        multi: true
    })
};

// update comment 
module.exports.updateComment = (postId, commentId, text) => {
    return GroupPosts.findByIdAndUpdate(commentId, {
        $set: {
            "comments.$.text": text,
        }
    }, {
        new: true,
    })
};

// find by comment id
module.exports.postByCommentId = (commentId) => {

    let id = mongoose.Types.ObjectId(commentId);
    return GroupPosts.aggregate([{
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
        }])
};

module.exports.infoGroupPost = (groupId) => {
    return GroupPosts.aggregate([{
        "$match": {
            "groupId": groupId
        }
    },{
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