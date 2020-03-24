const express = require("express");

const {
    getPosts
} = require("../controllers/posts");

const Post = require('../models/userPost');
const post = require('../controllers/posts');

const checkAuth = require('../middleware/check-auth');

const pagination = require('../middleware/pagination');



const router = express.Router();



router.route("/").get(pagination(Post), getPosts);

router.post('/', checkAuth, (req, res) => {

    const newPost = {
        createdBy: req.decodedUser,
        //other stuff
    };

    console.log(newPost);

    post.addNew(newPost)
        .then(result => console.log(result))
        .catch(err => console.log(err));

});







module.exports = router;