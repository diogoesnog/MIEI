var express = require("express");
var axios = require("axios");

var router = express.Router();

var key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE1Nzg4NjAwNTQsImV4cCI6MTU4MTQ1MjA1NH0.HIlH4_Ao6504qaLhhbZ2_OtDzaZaG5FeYy-Yc2d9lwQ"

// GET http://clav-api.dglab.gov.pt/api/entidades
router.get("/", function(req, res) {

    if("sigla" in req.query){

        axios.get("http://clav-api.dglab.gov.pt/api/entidades?sigla=" + req.params.sigla + "&apikey=" + key)
        .then(entidade => res.render("paginaEntidade", {entidade: entidade.data}))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
    }
    else if("sioe" in req.query){
        
        axios.get("http://clav-api.dglab.gov.pt/api/entidades?sioe=" + req.params.sioe + "&apikey=" + key)
        .then(entidade => res.render("paginaEntidade", {entidade: entidade.data}))
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
    }
   
});

// GET http://clav-api.dglab.gov.pt/api/entidades/{id}
router.get("/:id", function(req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.id + "?apikey=" + key)
    .then(entidade => res.render("paginaEntidade", {entidade: entidade.data, idEntidade: req.params.id}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });
});

// GET http://clav-api.dglab.gov.pt/api/entidades/{id}/tipologias
router.get("/:id/tipologias", function (req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.id + "/tipologias?apikey=" + key)
    .then(tipologias => res.render("tipologiasEntidade", {tipologias: tipologias.data, idEntidade: req.params.id}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });
});

// GET http://clav-api.dglab.gov.pt/api/entidades/{id}/intervencao/dono
router.get("/:id/intervencao/dono", function (req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.id + "/intervencao/dono?apikey=" + key)
    .then(processos => res.render("processosDona", {processos: processos.data, idEntidade: req.params.id}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });
});

// GET GET http://clav-api.dglab.gov.pt/api/entidades/{id}/intervencao/participante
router.get("/:id/intervencao/participante", function (req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.id + "/intervencao/participante?apikey=" + key)
    .then(processos => res.render("processosParticipante", {processos: processos.data, idEntidade: req.params.id}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });
});

module.exports = router;