const UserPosts = require('../controllers/userPosts');

module.exports = (req, res, next) => {
    try {
        //verificar se é owner do comentário
        UserPosts.postByCommentId(req.body.idComment).then(data => {
            if (data != undefined) {
                if (data[0].comments.createdBy == req.decodedUser) {
                    next()
                } else {
                    // verificar se é owner do post
                    UserPosts.getPostId(req.params.postId).then(data1 => {
                        if (data1 != undefined) {
                            if (data1.createdBy == req.decodedUser) {
                                next()
                            } else {
                                console.log("O user autenticado não é dono da publicação nem do comentário");
                            }
                        } else {

                            console.log("Não existe post com o id passado");
                        }
                    })
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