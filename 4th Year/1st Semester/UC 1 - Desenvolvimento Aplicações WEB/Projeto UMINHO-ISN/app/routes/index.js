// Server Routes
const express = require('express');
const router = express.Router();
const axios = require('axios');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const sendEmail = require('../utils/sendEmail');
const crypto = require('crypto');
const fs = require('fs');
const path = require('path');

const user = require('../controllers/users');

/**
 * Login Root Route
 */
router.get('/', (req, res) => {
    if (req.cookies.userToken !== undefined)
        res.redirect('/feed');
    else
        res.render('login', {
            message: req.flash("message")
        });
});

/**
 * User Login
 */
router.post('/login', (req, res) => {
    console.log(req.body);
    console.log('login requested');

    // fazer aqui verificação se username e password estão vazios?

    user.searchUser(req.body.username)
        .then(data => {
            if (data !== null) {
                bcrypt
                    .compare(req.body.password, data.password)
                    .then(result => {
                        if (!result) {
                            req.flash("message", "Wrong Password or Username!");
                            res.redirect('/')
                        } else {
                            console.log('Valid Password');
                            const token = jwt.sign({
                                    username: data.username
                                },
                                process.env.JWT_KEY, {
                                    expiresIn: process.env.JWT_EXPIRE
                                }, {
                                    algorithm: 'RS256'
                                }
                            );

                            const cookieOptions = {
                                expires: new Date(
                                    Date.now() +
                                    process.env.JWT_COOKIE_EXPIRE * 24 * 60 * 60 * 1000
                                ),
                                httpOnly: false
                            };
                            res.cookie('userToken', token, cookieOptions);
                            res.redirect('/feed');
                        }
                    })
                    .catch(err => console.log(err));
            } else {
                req.flash("message", `User with username ${req.body.username} does not exist`);
                console.log(`User with username ${req.body.username} does not exist`);
                res.redirect('/');
            }
        })
        .catch(err => console.log(err));
});

// @desc    Register user
// @route   POST /register
// @access  Public
router.post('/register', (req, res) => {
    user.searchUser(req.body.username)
        .then(data => {
            if (data === null) {
                const newUser = {
                    username: req.body.username,
                    fullName: req.body.name,
                    password: req.body.password,
                    email: req.body.email
                };

                console.log(newUser);

                user.addNew(newUser)
                    .then(result => console.log(result))
                    .catch(err => console.log(err));

                let userDir = path.join(__dirname, `../public/uploads/users/${newUser.username}`);
                fs.mkdir(userDir, err => {
                    if (err) console.log(err);
                });

                const token = jwt.sign({
                        username: newUser.username
                    },
                    process.env.JWT_KEY, {
                        expiresIn: process.env.JWT_EXPIRE
                    }, {
                        algorithm: 'RS256'
                    }
                );

                const cookieOptions = {
                    expires: new Date(
                        Date.now() +
                        process.env.JWT_COOKIE_EXPIRE * 24 * 60 * 60 * 1000
                    ),
                    httpOnly: false
                };
                res.cookie('userToken', token, cookieOptions);
                res.redirect('/feed');
            } else {
                req.flash("message", `User ${req.body.username} already exists`);
                res.redirect('/');
            }
        })
        .catch(err => {
            console.log(err);
        });
});

router.post('/forgotpassword', (req, res) => {
    user
        .searchUserEmail(req.body.email)
        .then(data => {
            if (!data) {
                console.log("Invalid Email");
                res.jsonp({
                    title: 'Invalid Email',
                    body: ''
                })
            } else {
                // criar o token de reset
                const resetToken = data.getResetPasswordToken();

                data
                    .save({
                        validateBeforeSave: false
                    })
                    .then(() => {
                        // criar o url de reset da password
                        // Create reset url
                        const resetUrl = `${req.protocol}://${req.get(
                            'host'
                        )}/resetpassword/${resetToken}`;

                        const message = ``;

                        const html = `<p>Este email foi enviado porque foi requirido um reset da password.\nO limite de tempo para poderes realizar é de 20 minutos.\nSe não realizar esta operação neste intervalo de tempo, terá de realizar novo pedido de reset.\nPara completar o processo de reset visite o seguinte link:</p>
                        <a href="${resetUrl}">Click here</a>`
                        
                        try {
                            sendEmail({
                                    email: data.email,
                                    subject: 'Password reset Token',
                                    message,
                                    html
                                })
                                .then(() => {
                                    res.jsonp({
                                        title: 'Check your Email',
                                        body: ''
                                    })
                                })
                                .catch();
                        } catch (err) {
                            console.log(err);
                            //caso corra mal, estes campos voltam a undefined
                            data.resetPasswordToken = undefined;
                            data.resetPasswordExpire = undefined;

                            data
                                .save({
                                    validateBeforeSave: false
                                })
                                .then()
                                .catch();

                            console.log('O Email não pode ser enviado');
                        }
                    });
            }
        })
        .catch(err => {
            console.log(err);
        });
});


router.get('/resetpassword/:resettoken', (req, res) => {
    res.render('resetpassword', {
        token: req.params.resettoken
    });
});


router.put('/resetpassword/:resettoken', (req, res) => {

    console.log(req.body);
    // get hashed token
    const resetPasswordToken = crypto
        .createHash('sha256')
        .update(req.params.resettoken)
        .digest('hex');

    user
        .searchUserQuery({
            resetPasswordToken,
            resetPasswordExpire: {
                $gt: Date.now()
            }
        })
        .then(user => {
            if (!user) {
                console.log('Token inválido');
                res.jsonp({
                    title: 'Invalid Token, make request again',
                    body: ''
                })
            } else {
                // dar update da password
                user.password = req.body.password;
                user.resetPasswordToken = undefined;
                user.resetPasswordExpire = undefined;

                user.save().then(() => {
                    console.log('password atualizada com sucesso');
                    res.jsonp({
                        title: 'Password updated with success',
                        body: ''
                    })
                });
            }
        })
        .catch(err => {
            console.log(err);
        });
});


router.get('/forgotpasswordpage', (req, res) => {
    res.render('insertemail');
});



// Export Routes for Index
module.exports = router;