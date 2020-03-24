const express = require('express');
const router = express.Router();
const checkAuth = require('../middleware/check-auth');
const axios = require('axios');

function timeMinutes(d1, d2) {
    var diff = Math.abs(d1 - d2)
    return Math.floor((diff / 1000) / 60);
}

function timeHours(d1, d2) {
    return parseInt(Math.abs(d1 - d2) / (60 * 60 * 1000));
}

function timeDays(d1, d2) {
    var t2 = d2.getTime();
    var t1 = d1.getTime();

    return parseInt((t2 - t1) / (24 * 3600 * 1000));
}

function timeWeeks(d1, d2) {
    var t2 = d2.getTime();
    var t1 = d1.getTime();

    return parseInt((t2 - t1) / (24 * 3600 * 1000 * 7));
}

function timeMonth(d1, d2) {
    var d1Y = d1.getFullYear();
    var d2Y = d2.getFullYear();
    var d1M = d1.getMonth();
    var d2M = d2.getMonth();

    return (d2M + 12 * d2Y) - (d1M + 12 * d1Y);
}

function timeYears(d1, d2) {
    return d2.getFullYear() - d1.getFullYear();
}

router.get('/', checkAuth, (req, res) => {
    let one = `${process.env.APP_URL}/api/user/${req.decodedUser}`;
    let two = `${process.env.APP_URL}/api/userpost/feed/${req.decodedUser}`;
    
    let loginUser = req.decodedUser;

    const requestOne = axios.get(one, {
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        }
    });
    const requestTwo = axios.get(two, {
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        }
    });

    axios
        .all([requestOne, requestTwo])
        .then(
            axios.spread((...responses) => {
                const infoFeed = responses[0].data;
                const postsUser = responses[1].data;

                let now = new Date()

                for (var i in postsUser) {
                    let date = new Date(postsUser[i].createdAt)

                    const timeyears = timeYears(date, now)
                    const timemonth = timeMonth(date, now);
                    const timeweeks = timeWeeks(date, now);
                    const timedays = timeDays(date, now);
                    const timehours = timeHours(date, now);
                    const timeminutes = timeMinutes(date, now);
                    if (timeyears > 0) {
                        postsUser[i].createdAt = '' + timeyears + ' year' + (timeyears === 1 ? "" : "s")
                    } else if (timemonth > 0) {
                        postsUser[i].createdAt = '' + timemonth + ' month' + (timemonth === 1 ? "" : "s")
                    } else if (timeweeks > 0) {
                        postsUser[i].createdAt = '' + timeweeks + ' week' + (timeweeks === 1 ? "" : "s")
                    } else if (timedays > 0) {
                        postsUser[i].createdAt = '' + timedays + ' day' + (timedays === 1 ? "" : "s")
                    } else if (timehours > 0) {
                        postsUser[i].createdAt = '' + timehours + ' hour' + (timehours === 1 ? "" : "s")
                    } else if (timeminutes > 0) {
                        postsUser[i].createdAt = '' + timeminutes + ' minute' + (timeminutes === 1 ? "" : "s")
                    } else {
                        postsUser[i].createdAt = "Right Now"
                    }

                }

                res.render('profile', {
                    infoFeed: infoFeed,
                    postsUser: postsUser,
                    loginUser: loginUser
                });
            })
        )
        .catch(error => console.log(error));
});

router.get('/:username', checkAuth, function (req, res, next) {
    let one = `${process.env.APP_URL}/api/user/${req.params.username}`;
    let two = `${process.env.APP_URL}/api/userpost/feed/${req.params.username}`;

    let loginUser = req.decodedUser;

    const requestOne = axios.get(one, {
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        }
    });
    const requestTwo = axios.get(two, {
        headers: {
            Cookie: `userToken=${req.cookies.userToken}`
        }
    });

    axios
        .all([requestOne, requestTwo])
        .then(
            axios.spread((...responses) => {
                const infoFeed = responses[0].data;
                const postsUser = responses[1].data;

                let now = new Date()

                for (var i in postsUser) {
                    let date = new Date(postsUser[i].createdAt)

                    const timeyears = timeYears(date, now)
                    const timemonth = timeMonth(date, now);
                    const timeweeks = timeWeeks(date, now);
                    const timedays = timeDays(date, now);
                    const timehours = timeHours(date, now);
                    const timeminutes = timeMinutes(date, now);
                    if (timeyears > 0) {
                        postsUser[i].createdAt = '' + timeyears + ' year' + (timeyears === 1 ? "" : "s")
                    } else if (timemonth > 0) {
                        postsUser[i].createdAt = '' + timemonth + ' month' + (timemonth === 1 ? "" : "s")
                    } else if (timeweeks > 0) {
                        postsUser[i].createdAt = '' + timeweeks + ' week' + (timeweeks === 1 ? "" : "s")
                    } else if (timedays > 0) {
                        postsUser[i].createdAt = '' + timedays + ' day' + (timedays === 1 ? "" : "s")
                    } else if (timehours > 0) {
                        postsUser[i].createdAt = '' + timehours + ' hour' + (timehours === 1 ? "" : "s")
                    } else if (timeminutes > 0) {
                        postsUser[i].createdAt = '' + timeminutes + ' minute' + (timeminutes === 1 ? "" : "s")
                    } else {
                        postsUser[i].createdAt = "Right Now"
                    }

                }
                console.log(loginUser)
                console.log(postsUser)
                res.render('profile', {
                    infoFeed: infoFeed,
                    postsUser: postsUser,
                    loginUser: loginUser
                });
            })
        )
        .catch(error => console.log(error));
});

module.exports = router;