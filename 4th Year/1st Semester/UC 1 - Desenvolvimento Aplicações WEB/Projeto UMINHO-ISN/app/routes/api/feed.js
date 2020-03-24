const express = require('express');
const router = express.Router();
const checkAuth = require('../../middleware/check-auth');
const feed = require('../../controllers/feed');

router.get('/', (req, res) => {
    console.log(`From Middleware: ${req.decodedUser}`);
    feed.getFeed()
        .then(data => res.jsonp(data))
        .catch(error => res.jsonp(error));
});

// Publicar no feed
router.put('/', checkAuth, (req, res) => {
    feed.addToFeed(req.decodedUser)
        .then(data => res.jsonp(data))
        .catch(error => res.jsonp(error));
    res.redirect('/feed');
});

router.put('/:id', (req, res) => {
});

module.exports = router;