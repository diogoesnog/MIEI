var express = require("express");
var router = express.Router();

var obras = require("../controllers/obra");

// GET da página que permite obter toda a lista de Obras.
router.get("/obras", function (req, res) {

    if("compositor" in req.query && "duracao" in req.query){
        
        obras.listaObras({compositor: req.query.compositor, duracao: req.query.duracao})
            .then(obras => res.jsonp(obras))
            .catch(erro => {
                console.log(erro);
                res.status(500).jsonp(erro);
            });
    }
    else if("ano" in req.query) {

        obras.listaObras({anoCriacao: req.query.ano})
            .then(obras => res.jsonp(obras))
            .catch(erro => {
                console.log(erro);
                res.status(500).jsonp(erro);
            });
    }
    else if("periodo" in req.query){
        
        obras.listaObras({periodo: req.query.periodo})
            .then(obras => res.jsonp(obras))
            .catch(erro => {
                console.log(erro);
                res.status(500).jsonp(erro);
            });
    }
    else {
        
        obras.listaObras()
            .then(obras => res.jsonp(obras))
            .catch(erro => {
                console.log(erro);
                res.status(500).jsonp(erro);
            });
    }
});

router.get("/obras/:idObra", function (req, res) {
    
    obras.listaObras({_id: req.params.idObra})
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
});

router.get("/compositores", function (req, res) {

    obras.listaDistinta("compositor")
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
});

router.get("/periodos", function (req, res) {
    
    obras.listaDistinta('periodo')
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
});

module.exports = router;