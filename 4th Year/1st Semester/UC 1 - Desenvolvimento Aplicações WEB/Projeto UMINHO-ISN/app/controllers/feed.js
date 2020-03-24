const Feed = require('../models/userPost');


module.exports.getUserFeed = (username) => {
    return Feed.aggregate([{
            $unwind: "$posts"
        },
        {
            $match: {
                username: username
            }
        },
        {
            $project: {
                fullName: 1,
                posts: 1,
                username: 1
            }
        }]);
};

module.exports.getFeed = () => {
    return Feed.aggregate([{
        $unwind: "$posts"
    }, {
        $project: {
            fullName: 1,
            username: 1,
            posts: 1
        }
    }]);
};

module.exports.addToFeed = ({createdBy, content}) => {

    let newPost = new userPost({
        createdBy: createdBy,
        content: content
    });

    return newPost.save();
};