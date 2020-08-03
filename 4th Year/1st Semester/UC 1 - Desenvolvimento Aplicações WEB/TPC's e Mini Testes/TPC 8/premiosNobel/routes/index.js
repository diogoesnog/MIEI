var express = require("express");
var router = express.Router();

var axios = require("axios");

// Esta parte trata de enviar a solicitação em si para a API.
// API é que trata de fazer as operações.

// GET da Home Page.
// A ideia é reencaminhar para uma página WEB que terá um conjunto de opções principais.
router.get("/", function (req, res) {
    res.render("paginaPrincipal");
});

// GET da página para adicionar um novo Prémio.
router.get('/premios/adicionarPremio', function (req, res) {
    res.render('adicionarPremio');
});

// GET da página que permite obter toda a lista de Prémios.
router.get("/premios", function (req, res) {
    // Importante para fazer o parse do que é dado no URL.
    axios.get("http://localhost:3000/api/premios",{
        params: {
            categoria: req.query.categoria,
            data: req.query.data
        }
    })
        .then(premios => res.render("paginaPremios", {premios: premios.data}))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

// GET da página que permite obter toda a lista de Laureados.
router.get("/laureados", function (req, res) {

    axios.get("http://localhost:3000/api/laureados")
        .then(laureados => res.render("paginaLaureados", {laureados: laureados.data}))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

// GET da página que permite obter toda a lista de categorias.
router.get("/categorias", function (req, res) {

    axios.get("http://localhost:3000/api/categorias")
        .then(premios => res.render("paginaCategorias", {categorias: premios.data}))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

// GET da página que mostra as informações de um Prémio consoante o seu ID.
router.get("/premios/:idPremio", function (req, res) {

    axios.get("http://localhost:3000/api/premios/" + req.params.idPremio)
        .then(premio => res.render("paginaPremio", {premio: premio.data}))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

// Adicionar um novo Prémio.
// Ainda não está a funcionar.
router.post("/premios", function (req, res) {
    axios.post("http://localhost:3000/api/premios/" + req.params.idPremio)
        .then(res.render("paginaPrincipal"))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

// Eliminar um Prémio.
// Quando o Prémio é efetivamente eliminado, reencaminha-se para a Página Principal.
router.delete("/premios/:idPremio", function (req, res) {
    axios.delete("http://localhost:3000/api/premios/" + req.params.idPremio)
        .then(res.render("paginaPrincipal"))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

router.all("*", function (req, res)  {
    res.status(404).render("paginaErro", {mensagemErro: "Pedido HTTP não existente."});
})

module.exports = router;