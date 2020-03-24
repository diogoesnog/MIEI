var express = require('express');
var router = express.Router();
var jsonfile = require('jsonfile')

var myBD = __dirname + "/../compras.json"
console.log(myBD)

/* GET home page. */
router.get('/', function(req, res, next) {
  jsonfile.readFile(myBD, (erro, compras) => {
    if(!erro){
      res.render('index', {lista: compras})
    }
    else{
      res.render('error', {error: erro})
    }
  })
})

router.post('/', function(req, res) {
  jsonfile.readFile(myBD, (erro, compras)=>{
    if(!erro){
      compras.push(req.body)
      jsonfile.writeFile(myBD, compras, erro => {
        if(erro) console.log(erro)
        else console.log('Registo gravado com sucesso.')
      })
    }
  })
  res.redirect('/')
})

module.exports = router
