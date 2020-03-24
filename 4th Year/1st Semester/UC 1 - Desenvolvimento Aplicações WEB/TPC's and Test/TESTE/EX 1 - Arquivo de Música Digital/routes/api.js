var express = require("express");
var router = express.Router();

var obras = require("../controllers/obras");

// GET da Lista de Obras Musicais.
router.get("/obras", function (req, res) {

    // Lista de Obras que tenham o campo Compositor com o valor passado na Query.
    if("compositor" in req.query){
 
        obras.listaObrasQuery({"compositor": req.query.compositor})
            .then(obras => res.jsonp(obras))
            .catch(erro => {
                console.log(erro);
                res.status(500).jsonp(erro);
            });
    }
    // Lista de Obras que tenham uma ou mais partituras para o Instrumento com o valor passado na Query.
    else if("instrumento" in req.query){

        obras.listarObrasInstrumento(req.query.instrumento)
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
    }
    // Lista de Obras.
    // Devolvemos apenas os campos id, titulo, tipo e compositor.
    else{

        obras.listaObras()
            .then(obras => res.jsonp(obras))
            .catch(erro => {
                console.log(erro);
                res.status(500).jsonp(erro);
            });
    }

});

// GET da Informação (completa) de uma Obra.
router.get("/obras/:id", function (req, res) {
    
    obras.infoObra(req.params.id)
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
});

router.get("/tipos", function (req, res) {
    
    obras.listaTipos()
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
});

router.get("/obrasQuant", function (req, res) {
    
    obras.listaObrasQuant()
        .then(obras => res.jsonp(obras))
        .catch(erro => {
            console.log(erro);
            res.status(500).jsonp(erro);
        });
});

module.exports = router;