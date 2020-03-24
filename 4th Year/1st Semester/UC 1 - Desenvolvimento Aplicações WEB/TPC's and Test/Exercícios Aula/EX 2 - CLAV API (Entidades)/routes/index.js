var express = require("express");
var axios = require("axios");

var router = express.Router();

var key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE1NzM0ODgwMDgsImV4cCI6MTU3NjA4MDAwOH0.UD0UdMrzKcWDop8HlwqdeOuK_ZzZxHvOMOP2DMkIjUQ"

router.get("/", function(req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades?apikey=" + key)
    .then(entidades => res.render("listaEntidades", {entidades: entidades.data}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });
});

router.get("/:idEntidade", function (req, res) {

    Promise
        .all([
            axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.idEntidade + "?apikey=" + key),
            axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.idEntidade + "/tipologias/?apikey=" + key),
            axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.idEntidade + "/intervencao/dono/?apikey=" + key),
            axios.get("http://clav-api.dglab.gov.pt/api/entidades/" + req.params.idEntidade + "/intervencao/participante/?apikey=" + key),
        ])
        .then(([entidadesAPI, tipologiasAPI, donoAPI, participantesAPI]) => {
            res.render('paginaEntidade', {
                entidade: entidadesAPI.data,
                tipologias: tipologiasAPI.data,
                donos: donoAPI.data,
                participantes: participantesAPI.data
            });
        })
        .catch(erro => {
            console.log(erro);
            res.render("paginaErro", {mensagemErro: erro});
        });
});

module.exports = router;