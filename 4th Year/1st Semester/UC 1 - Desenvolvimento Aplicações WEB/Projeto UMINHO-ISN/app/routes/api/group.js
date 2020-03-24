const express   = require('express');
const router    = express.Router();
const group     = require('../../controllers/groups');
const checkAuth = require('../../middleware/check-auth');
const groupPost = require('../../controllers/groupPosts');
const parseTag  = require('../../utils/parseTag');

/*********************************************************************
 * Group Basic Operations
 *********************************************************************/


/**
 * Join a Group
 */
router.post('/join', checkAuth, (req, res) => {
    let user = req.decodedUser;

    group.joinMany(req.body, user)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));

});


/**
 * List public routes
 */
router.get('/public', checkAuth, (req, res) => {

    group.listAvailableGroups({audience: true}, {_id: 1, name: 1, description: 1})
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

/**
 * List groups owned by me
 */
router.get('/own', checkAuth, (req, res) => {
    group.listAvailableGroups({ creator: req.decodedUser })
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

/**
 * Groups I take part of
 */
router.get('/registered', checkAuth, (req, res) => {

    if(req.query.limit !== undefined) {
        group.listTopGroups({members: req.decodedUser}, parseInt(req.query.limit) )
            .then(data => res.jsonp(data))
            .catch(err => res.jsonp(err));

    } else {
        group.listAvailableGroups({ members: req.decodedUser }, { _id: 1, name: 1, description: 1})
            .then(data => res.jsonp(data))
            .catch(err => res.jsonp(err));
    }
});


/**
 * Add user to a group
 */
router.put('/:id/add', checkAuth, (req, res) => {
    let users = req.body.users;

    group.creator(req.params.id)
        .then(data => {
            if(data.creator === req.decodedUser && !data.audience) {
                group.registerMembers(req.params.id, users)
                    .then(result => res.jsonp(result))
                    .catch(err => res.jsonp(err));

            } else if (result.audience) {
                group.registerMembers(req.params.id, users)
                    .then(result => res.jsonp(result))
                    .catch(err => res.jsonp(err));
            } else {
                res.jsonp({title: "No Permission", message: "You don't have enough permissions to add users"});
            }
        })
        .catch(err => res.jsonp(err));
});

/**
 * New Group
 */
router.post('/new', checkAuth, (req, res) => {
    console.log("/API new Requested");

    let audience = req.body.audience;


    let t = audience === 'true';

    let newGroup = {
        name: req.body.name,
        description: req.body.description,
        members: [req.decodedUser],
        creator: req.decodedUser,
        audience: t
    };

    console.log(newGroup);

    group.createGroup(newGroup)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));

});


/*********************************************************************
 * Post Operations
 *********************************************************************/
/**
 * Create a Group Post
 */
router.post('/:id/post', checkAuth, (req, res) => {
    console.log("/api New Group Post");
    let newPost = {
        groupId: req.params.id,
        createdBy: req.decodedUser,
        content: {
            text: req.body.content.text,
            files: req.body.content.files
        }
    };
    groupPost.addNewGroupPost(newPost)
        .then(result => res.redirect(req.headers.referer))
        .catch(err => res.jsonp(err));

});

/**
 * Get a Group posts
 */
router.get('/:id/posts', (req, res) => {
    groupPost.infoGroupPost(req.params.id)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

/**
 * Change Form Settings
 */
router.put('/:id/update', checkAuth, (req, res) => {

    group.updateGroup(req.params.id, req.body)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

/**
 * Delete a Group Post
 */
router.delete('/post/:id', checkAuth, (req, res) => {
    let id = req.params.id;

    console.log(`DELETING POST ${id}`);

    groupPost.deletePost(id)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

/**
 * Update a Group post
 */
router.put('/post/:id', checkAuth, (req, res) => {
    let id = req.params.id;
    console.log(`UPDATING POST ${id}`);

    groupPost.updatePost(id, req.body)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));

});

/**
 * Group Comments Routes
 */
/**
 * Get a Group Post Comments
 */
router.get('/post/:id/comments', checkAuth, (req, res) => {
    console.log("Getting Group Posts...");

    let post = req.params.id;

    groupPost.getComments(post)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));

});

/**
 * Leave a given group
 */
router.delete('/:id/leave', checkAuth, (req, res) => {
    let id = req.params.id,
        user = req.decodedUser;

    group.leaveGroup(id, user)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

router.get('/post/single/:id', checkAuth, (req, res ) => {

    let post = req.params.id;

    groupPost.getSinglePost(post)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));

});

/**
 * Add a new comment to a post
 */
router.post('/post/:id/comment', checkAuth, (req, res) => {
    let postId = req.params.id;

    let comment = {
        text: req.body.text,
        createdBy: req.decodedUser
    };

    groupPost.addComment(postId, comment)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));

});

router.get('/match/:str', checkAuth, (req, res) => {
    let str = req.params.str;

    group.groupMatch(str)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});
/**
 * Get a Single Group
 */
router.get('/:id', checkAuth, (req, res) => {
    console.log("API GET GROUP");
    group.searchGroupById(req.params.id)
        .then(result => res.jsonp(result))
        .catch(err => res.jsonp(err));
});

module.exports = router;