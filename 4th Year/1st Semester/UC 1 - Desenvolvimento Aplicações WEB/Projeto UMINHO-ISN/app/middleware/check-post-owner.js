const UserPosts = require('../controllers/userPosts');

module.exports = (req, res, next) => {
    try {

        UserPosts.getPostId(req.params.id).then(data => {
            if (data != undefined) {
                if (data.createdBy == req.decodedUser) {
                    next()
                } else {
                    console.log("O user autenticado não é dono do post");
                }
            } else {
                console.log("Não existe post com o id passado");
            }
        })

    } catch (error) {
        console.log(error);
        // console.log(error)
        res.redirect('/');
    }
};