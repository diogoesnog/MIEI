var express = require('express');
var passport = require('passport');

var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
  console.log('Na CB da HomePage...');
  console.log(req.sessionID);
  res.render('index');
});

router.get('/login', function(req, res) {
  console.log('Na CB do GET Login...');
  console.log(req.sessionID);
  res.render('login');
})

function verificaAutenticacao(req, res, next){
  if(req.isAuthenticated()) next();
  else res.redirect('/login');
}
router.get('/protegida', verificaAutenticacao, function(req, res) {
    res.send('Atingiste a Área Protegida' + JSON.stringify(req.user));
})


// O servidor dos Users é outro. Neste caso na porta 5026.
// Estamos a trabalhar com dois servidores. 
// Um é o servidor em si que está em contacto direto com a WEB.
// Outro é o que trata da API de Dados.


router.post('/login', passport.authenticate('local', 
  {
    sucessRedirect: '/protegida',
    sucessFlash: 'Utilizador Autenticado com sucesso.',
    failureRedirect: '/login',
    failureFlash: 'Utilizador ou Password inválido(s).'

  })
)

module.exports = router;
