var mongoose = require("mongoose");
var Obra = require("../models/obra");

// Lista de todas as Obras consoante uma dada Query.
module.exports.listaObras = (query) => {
    return Obra.find(query).exec();
}

// Lista de todos os Compositores.
module.exports.listaDistinta = (queryDistinta) => {
    return Obra.distinct(queryDistinta).exec();
}