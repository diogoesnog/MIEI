const jwt = require('jsonwebtoken');

module.exports = (req, res, next)=> {
    try{

        const token = req.cookies.userToken;
        const decodedToken = jwt.verify(token, process.env.JWT_KEY, { algorithm: 'RS256' });
        req.decodedUser = decodedToken.username;

        next();
    } catch(error){
        res.redirect('/');
    }
};