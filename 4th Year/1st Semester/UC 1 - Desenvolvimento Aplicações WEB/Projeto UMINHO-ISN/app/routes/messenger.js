const express = require('express');
const router = express.Router();
const checkAuth = require('../middleware/check-auth');
const dotenv = require('dotenv');
const axios = require('axios');

router.get('/', checkAuth, (req, res ) => {
   
    let loginUser = req.decodedUser;

    axios.get(`${process.env.API_URL}/messenger`, {
        headers:  {
            Cookie: `userToken=${req.cookies.userToken}`
        }
    })
        .then(response => res.render('messenger', { data: response.data, loginUser: loginUser }))
        .catch(err => console.log(err));
});

router.get('/:id', checkAuth, (req, res) => {
    let id = req.params.id;

    axios.get(`${process.env}/messenger/${id}`, {
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        }})
        .then(response => res.render('messenger'))
        .catch(err => res.render('messenger'));
});

router.post('/new', checkAuth, (req, res) => {
    let newRoom = req.body;


    console.log(newRoom);


    let participantsJson = JSON.parse(newRoom.participants);


    console.log(participantsJson);

    let participants = [];

    participantsJson.forEach(participant => participants.push(participant.value));

    participants.push(req.decodedUser);

    let parsedNewRoom = {
        name: newRoom.name,
        participants: participants
    };

    axios(`${process.env.API_URL}/messenger`, {
        method: "post",
        data: parsedNewRoom,
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        },
    }).then(response => res.redirect('/messenger'))
        .catch(err => console.log(err));
});

module.exports = router;