var mongoose = require("mongoose")

// Schema do Array da Partitura em si.
var partituraSchema = new mongoose.Schema({
        _voz: String,
        _type: String,
        _path: String
});

// Schema do Array do Instrumento em si.
var instrumentoSchema = new mongoose.Schema({
        designacao: String,
        partitura: partituraSchema
});

// Schema de uma Obra.
var obraSchema = new mongoose.Schema({
        _id: String,
        titulo: String,
        subtitulo: String,
        arranjo: String,
        tipo: String, 
        compositor: String,
        instrumentos: [instrumentoSchema]
});

module.exports = mongoose.model("obras", obraSchema, "obras")
