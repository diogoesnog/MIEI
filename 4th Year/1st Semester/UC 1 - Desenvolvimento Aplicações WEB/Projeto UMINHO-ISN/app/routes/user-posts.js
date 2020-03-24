const express = require('express');
const router = express.Router();
const Post = require('../controllers/userPosts');
const checkAuth = require('../middleware/check-auth');
const fs = require('fs');
const multer = require('multer');
const path = require('path');
const axios = require('axios');

const upload = multer({
    dest: 'app/public/uploads'
});

router.post('/', checkAuth, upload.array('files', 12), (req, res) => {
    let user = req.decodedUser;

    let uploadedFiles = req.files;
    let fileNames = [];

    // let userPorfilePath = path.join(__dirname, `../public/uploads/users/${user}/${req.file.originalname}`);
    //
    //     fs.rename(uploadedFile, userPorfilePath, err => {
    //         if (err) console.log(err);
    //     });
    //
    //     let pictureUpdate = {
    //         username: user,
    //         avatar: `/uploads/users/${user}/${req.file.originalname}`
    //     };

    uploadedFiles.forEach(file => {
        let fileUpload = path.join(__dirname, `../public/uploads/files/${file.originalname}`);

        fs.rename(file.path, fileUpload, err => console.log(err));

        fileNames.push(`/uploads/files/${file.originalname}`);
    });

    let newPost = {
        createdBy: user,
        content: {
            files: fileNames,
            text: req.body.text
        }
    };

    Post.addNew(newPost)
        .then(result => res.redirect('/feed'))
        .catch(err => res.jsonp(err));

});


router.post('/comment/:postId', checkAuth, (req, res) => {
    console.log("Requested Comment Post");

    axios(`${process.env.API_URL}/userpost/comment/${req.params.postId}`, {
        method: "post",
        data: req.body,
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        },
    }).then(response => res.redirect('/feed'))
        .catch(err => console.log(err));

});


module.exports = router;