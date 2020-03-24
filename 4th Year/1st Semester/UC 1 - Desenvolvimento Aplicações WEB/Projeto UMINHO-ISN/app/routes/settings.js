const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const checkAuth = require('../middleware/check-auth');
const fs = require('fs');
const path = require('path');
const axios = require('axios');

const multer = require('multer');
const upload = multer({
    dest: 'app/public/uploads'
});

const User = require('../controllers/users');

router.get('/', checkAuth, (req, res) => {
    axios.get(`${process.env.API_URL}/settings`, {
            headers: {
                Cookie: `userToken=${req.cookies.userToken}`
            }
        }).then(response => res.render('settings', {
            data: response.data
        }))
        .catch(err => res.render('error', err));

});

router.post('/picture-update', checkAuth, upload.single("file"), (req, res) => {
    let user = req.decodedUser;

    let uploadedFile = req.file.path;

    let userPorfilePath = path.join(__dirname, `../public/uploads/users/${user}/${req.file.originalname}`);

    fs.rename(uploadedFile, userPorfilePath, err => {
        if (err) console.log(err);
    });

    let pictureUpdate = {
        username: user,
        avatar: `/uploads/users/${user}/${req.file.originalname}`
    };

    console.table(pictureUpdate);

    User.updateAvatar(pictureUpdate)
        .then(result => console.log(result))
        .catch(err => console.log(err));

});



router.post('/update', checkAuth, (req, res) => {

    axios(`${process.env.API_URL}/settings/update`, {
            method: "put",
            data: req.body,
            headers: {
                Cookie: `userToken=${req.cookies.userToken}`
            },
        }).then(response => res.redirect('/settings'))
        .catch(err => console.log(err));
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