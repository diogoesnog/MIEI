var express = require('express');
var router = express.Router();
var Utilizadores = require('../controllers/utilizadores')
var passport = require ('passport')

/* GET users listing. */
router.get('/', passport.authenticate('jwt', {session: false}), function(req, res) {
  Utilizadores.listar()
    .then(dados => res.jsonp(dados))
    .catch(e => res.status(500).jsonp(e))
});

router.get('/:email', passport.authenticate('jwt', {session: false}), function(req, res) {
  Utilizadores.consultar(req.params.email)
    .then(dados => res.jsonp(dados))
    .catch(e => res.status(500).jsonp(e))
});

router.post('/', function(req,res){
  Utilizadores.inserir(req.body)
    .then(dados => res.jsonp(dados))
    .catch(e => res.status(500).jsonp(e))
})

module.exports = router;
