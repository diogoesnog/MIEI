const express = require('express');
const router = express.Router();
const checkAuth = require('../../middleware/check-auth');
const messenger = require('../../controllers/messenger');


router.get('/', checkAuth, (req, res) => {
    let user = req.decodedUser;
    console.log(`MESSENGER: ${user}`);
    messenger.getChatBox(user)
        .then(data => res.jsonp(data))
        .catch(err => res.jsonp(err));
});

router.get('/:id', checkAuth, (req, res) => {
    let id = req.params.id;
    messenger.getMessages1(id)
        .then(data => {
            console.log(data[0])
            res.jsonp(data)})
        .catch(err => res.jsonp(err));
});


router.post('/', checkAuth, (req, res) => {
    let newRoom = req.body;

    messenger.newRoom(newRoom)
        .then(data => res.jsonp(data))
        .catch(err => res.jsonp(err));

});

router.put('/', checkAuth, (req, res) => {
    let message = req.body;
    let user = req.decodedUser;

    console.log(message);

    let msg = {
        chatId: message.chatId,
        text: message.text,
        date: Date.now(),
        by: user
    };

    messenger.sendMessage(msg)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

router.delete('/:id', checkAuth, (req, res) => {
    let username = req.decodedUser;
    let chatId = req.params.id;

    console.log(`REMOVING ${username} FROM ${chatId}`);

    messenger.removeFromConversation({chatId, username})
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

module.exports = router;