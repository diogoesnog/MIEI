var express = require("express");
var axios = require("axios");

var router = express.Router();

var key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE1Nzg4NjAwNTQsImV4cCI6MTU4MTQ1MjA1NH0.HIlH4_Ao6504qaLhhbZ2_OtDzaZaG5FeYy-Yc2d9lwQ"

router.get("/", function(req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades?apikey=" + key)
    .then(entidades => res.render("index", {entidades: entidades.data}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });

    
});

router.get("/:idEntidade", function (req, res) {

    axios.get("http://clav-api.dglab.gov.pt/api/entidades/"+ req.params.id + "?apikey=" + key)
    .then(entidades => res.render("index", {entidades: entidades.data}))
    .catch(erro => {
        console.log(erro);
        res.render("paginaErro", {mensagemErro: erro});
    });
});

module.exports = router;