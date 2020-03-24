const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const checkAuth = require('../../middleware/check-auth');
const fs = require('fs');
const path = require('path');

const multer = require('multer');
const upload = multer({
    dest: 'app/public/uploads'
});

const User = require('../../controllers/users');

router.get('/', checkAuth, (req, res) => {
    let user = req.decodedUser;

    User.searchUser(user)
        .then(data => res.jsonp(data))
        .catch(err => res.jsonp(err));
});

router.post('/picture-update', checkAuth, upload.single("file"), (req, res) => {
    let user = req.decodedUser;

    // let uploadedFile = path.join(__dirname, `../public/uploads/${req.file.path}`);
    let uploadedFile = req.file.path;

    let userPorfilePath = path.join(__dirname, `../public/uploads/${user}/${req.file.originalname}`);

    fs.rename(uploadedFile, userPorfilePath, err => {
        if (err) throw err;
    });

    let pictureUpdate = {
        username: user,
        avatar: `/uploads/${user}/${req.file.originalname}`
    };

    console.table(pictureUpdate);

    User.updateAvatar(pictureUpdate)
        .then(result => console.log(result))
        .catch(err => console.log(err));

});

router.put('/update', checkAuth, (req, res) => {
    let user = req.decodedUser;
    console.log(`UPDATING ${user}`);

    console.log(req.body);
    console.log(req.body.courses.length);

    let courses = [];

    if (req.body.courses.length > 0) {
        let coursesJson = JSON.parse(req.body.courses);
        coursesJson.forEach(course => courses.push(course.value));

    }
    let info = {
        bio: req.body.bio,
        courses: courses,

    };
    User.updateInfo(user, info)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

router.put('/updatesocial', checkAuth, (req, res) => {
    let user = req.decodedUser;

    console.log(req.body);

    User.updateInfoSocial(user, req.body).then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

router.put('/change-password', checkAuth, (req, res) => {
    console.log(req.decodedUser);

    bcrypt.hash(req.body.password, 10, (err, hash) => {
        if (err) console.log(err);
        else {
            console.log(hash);
            User.updatePassword(req.decodedUser, hash)
                .then(result => console.log(result))
                .catch(err => console.log(err));
        }
    });

    res.redirect('/settings');
});

module.exports = router;