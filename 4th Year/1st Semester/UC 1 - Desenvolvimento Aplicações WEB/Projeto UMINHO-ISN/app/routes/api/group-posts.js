const express = require('express');
const router = express.Router();
const Groups = require('../../controllers/groups');
const Posts = require('../../controllers/groupPosts');
const checkAuth = require('../../middleware/check-auth');


router.get('/:id', (req, res) => {
    // Group Post
    Posts.getAllGroupPosts(req.params.id)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});


router.post('/', (req, res) => {

    let files = undefined;

    if(req.body.files !== undefined)
        files = req.body.files;

    let post = {
        groupId: req.body.groupId,
        createdBy: req.body.createdBy,
        content: {
            text: req.body.text,
            files: files
        }
    };

    Posts.addNewGroupPost(post)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

router.delete('/:id', (req, res) => {
    // Deletes a Post
});



module.exports = router;




// get posts por data de um grupo--> talvez com paginação

// criar post -> middleware pra verificar se é membro do grupo

// editar post -> post owner

// remover post -> user owner

// adicionar comentário -> membro

// remover comentário -> post owner ou comment owner

// atualizar comment -> comment owner