const UserPosts = require('../controllers/userPosts');

module.exports = (req, res, next) => {
    try {
        UserPosts.postByCommentId(req.body.idComment).then(data => {
            if (data != undefined) {
                if (data[0].comments.createdBy == req.decodedUser) {
                    next()
                } else {
                    console.log("O user autenticado não é dono do comentário");
                }
            } else {
                console.log("Não existe comment com o id passado");
            }
        })



    } catch (error) {
        console.log(error);
        // console.log(error)
        res.redirect('/');
    }
};