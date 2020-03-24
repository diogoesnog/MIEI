var mongoose = require("mongoose")
var Schema = mongoose.Schema;

// Schema de um Laureado.
var laureadoSchema = new mongoose.Schema({
    id: String,
    firstname: String,
    surname: String,
    motivation: String,
    share: String,
});

// Schema de um Prémio.
var premioSchema = new mongoose.Schema({
        _id: mongoose.Schema.Types.ObjectId,
        year: String,
        category: String,
        laureates: [laureadoSchema]
});

module.exports = mongoose.model("premios", premioSchema, "premios")
