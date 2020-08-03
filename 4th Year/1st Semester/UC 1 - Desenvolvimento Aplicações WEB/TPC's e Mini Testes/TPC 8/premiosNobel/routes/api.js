var express = require("express");
var router = express.Router();

var controlador = require("../controllers/premio");

// GET da página que permite obter toda a lista de Prémios.
router.get("/premios", function (req, res) {

    // Caso exista a query "categoria" e "data" no URL.
    if("categoria" in req.query) {

        // Ter "categoria" apenas.
        if(req.query.data && req.query.categoria) {
            controlador.listaPremios({category: req.query.categoria, year: {$gt: req.query.data}})
                .then(premios => res.jsonp(premios))
                .catch(erro => res.status(500).jsonp(erro));
        }
        // Ter "categoria" apenas.
        else {
            controlador.listaPremios({category: req.query.categoria})
                .then(premios => res.jsonp(premios))
                .catch(erro => res.status(500).jsonp(erro));
        }
    }
    // Caso não exista nem "categoria" nem "data".
    else {
        controlador.listaPremios({}, {_id: 1, year: 1, category: 1})
            .then(premios => res.jsonp(premios))
            .catch(erro => res.status(500).jsonp(erro));
    }
});

// GET da página que permite obter toda a lista de Laureados.
router.get("/laureados", function (req, res) {
    controlador.listaLaureados()
        .then(dados => res.jsonp(dados))
        .catch(erro => res.status(500).jsonp(erro));
});

// GET da página que permite obter toda a lista de categorias.
router.get("/categorias", function (req, res) {
    controlador.listaCategorias()
        .then(categorias => res.jsonp(categorias))
        .catch(erro => res.status(500).jsonp(erro));
});

// GET da página que mostra as informações de um Prémio consoante o seu ID.
router.get("/premios/:idPremio", function (req, res) {
    var idPremio = req.params.idPremio;

    controlador.consultarID(idPremio)
        .then(premio => res.jsonp(premio))
        .catch(erro => res.status(500).jsonp(erro));
});

// Adicionar um novo Prémio.
// Ainda não está a funcionar.
router.post("/premios", function (req, res) {

})

// Eliminar um Prémio.
router.delete("/premios/:idPremio", function (req, res) {
    controlador.eliminarID(req.params.idPremio)
        .then(premio => {
            console.log("Prémio eliminado da Base de Dados.")
            res.sendStatus(200);
        })
        .catch(erro => res.status(500).jsonp(erro));
});

router.all("*", function (req, res) {
    res.status(404).render("paginaErro", {mensagemErro: "Pedido HTTP não existente."});
});

module.exports = router;