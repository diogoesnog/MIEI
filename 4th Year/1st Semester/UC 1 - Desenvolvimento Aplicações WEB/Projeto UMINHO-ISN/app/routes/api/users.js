const express = require('express');
const router = express.Router();
const Users = require('../../controllers/users');
const checkAuth = require('../../middleware/check-auth');



router.get('/groups', checkAuth, (req, res) => {
    Users.getGroups(req.decodedUser)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err))
})

router.get('/infofeed', checkAuth, (req, res) => {
    Users.getInfoFeed(req.decodedUser).then(result => res.jsonp(result)).catch(err => res.jsonp(err))
})

router.put('/groups', checkAuth, (req, res) => {
    console.log(req.body.groups);
    Users.updateInfo(req.decodedUser, req.body).then(result => res.jsonp(result)).catch(err => res.jsonp(err))
})

router.get('/:username', checkAuth, (req, res) => {
    Users.searchUser(req.params.username).then(result => res.jsonp(result)).catch(err => res.jsonp(err))
})


router.get('/match/:id', checkAuth, (req, res) => {
    let id = req.params.id;

    Users.usernameMatch(id)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

module.exports = router;