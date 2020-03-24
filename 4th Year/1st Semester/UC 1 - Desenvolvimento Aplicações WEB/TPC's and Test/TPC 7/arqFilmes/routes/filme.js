const express = require("express");
var router = express.Router();

var modelo = require("../models/filme");
var controlador = require("../controllers/filme");

/* GET da Home Page. */
router.get("/", function(req, res, next) {
    
    controlador.listaFilmes()
        .then(listaFilmes => res.render("indice.pug", {filmes: listaFilmes}))
        .catch(erro => res.render("paginaErro.pug", {erro: erro}));
});

/* GET da página para adicionar uma novo Filme ao Arquivo de Filmes. */
/* Apenas renderiza a página de adicionar um Novo. */
router.get("/adicionarFilme", function(req, res, next) {
    res.render("adicionarFilme.pug");
})

/* GET da página que mostra as informações de um Filme consoante o seu ID. */
router.get("/id/:idFilme", function (req, res, next) {

    controlador.consultarID(req.params.idFilme)
        .then(filme => res.render("consultarFilme.pug", {filme: filme}))
        .catch(erro => res.render("paginaErro.pug", {erro: "Filme com ID " + req.params.idFilme + " não encontrado na Base de Dados."}));
})

/* GET da página que mostra as informações de um Filme consoante o seu Title. */
router.get("/titulo/:tituloFilme", (req, res) => {

    controlador.consultarTitulo(req.params.tituloFilme)
        .then(filme => res.render("consultarFilme.pug", {filme: filme}))
        .catch(erro => res.render("paginaErro.pug", {erro: "Filme com ID " + req.params.tituloFilme + " não encontrado na Base de Dados."}));
})

/* GET da página que permite editar um Filme. */
router.get("/editar/:idFilme", function (req, res, next) {

    controlador.consultarID(req.params.idFilme)
        .then(filme => res.render("editarFilme.pug", {filme: filme}))
        .catch(erro => res.render("paginaErro.pug", {erro: "Filme com ID " + idFilme + " não encontrado na Base de Dados."}));
})

/* POST de um Filme na Base de Dados. */
router.post("/", function(req, res, next) {

    // Não consigo fazer o parse de vários inputs, transformando num array.
    // Ver depois.
    // Para já fica a vazio.
    req.body.cast = [];
    req.body.genres = [];

    // Schema de um Filme.
    var novoFilme = new modelo({
        title: req.body.title,
        year: req.body.year,
        cast: req.body.cast,
        genres: req.body.genres
    });

    controlador.inserirFilme(novoFilme)
        .then(filme => {
            console.log("Filme com ID " + filme._id + " adicionado à Base de Dados.");
            res.redirect("/filmes/id/" + filme._id);
        })
        .catch(erro => {
            console.log("Filme com ID " + filme._id + " não adicionado à Base de Dados.");
            res.render("paginaErro.pug", {erro: erro});
        })
})

/* DELETE de um Filme. */
router.delete("/:idFilme", function (req, res, next) {
    
    controlador.eliminarFilme(req.params.idFilme)
        .then((data) => {
            console.log("Filme com ID " + req.params.idFilme + " eliminado da Base de Dados.");
            res.jsonp(data);
        })
        .catch(erro => {
            console.log("Filme com ID " + req.params.idFilme + " não eliminado da Base de Dados.");
            res.render("paginaErro.pug", {erro: erro});
        })
})

/* PUT para quando se atualiza um Filme. */
router.put("/:idFilme", function (req, res, next) {

    controlador.atualizarFilme(req.params.idFilme, req.body)
        .then(data => {
            console.log("Filme com ID " + req.params.idFilme + " atualizado da Base de Dados.");
            res.jsonp(data);
        })
        .catch(erro => {
            console.log("Filme com ID " + req.params.idFilme + " não atualizado da Base de Dados.");
            res.render("paginaErro.pug", {erro: erro});
        })
})

module.exports = router;