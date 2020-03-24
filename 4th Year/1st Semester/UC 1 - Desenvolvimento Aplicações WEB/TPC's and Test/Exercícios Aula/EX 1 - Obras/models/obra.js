var mongoose = require("mongoose")
var Schema = mongoose.Schema;

// Schema de um Prémio.
var obraSchema = new mongoose.Schema({
        _id: mongoose.Schema.Types.ObjectId,
        nome: String,
        desc: String,
        anoCriacao: String,
        periodo: String,
        compositor: String,
        duracao: String
});

module.exports = mongoose.model("obras", obraSchema, "obras")
