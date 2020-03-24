const mongoose = require('mongoose')

var eventoSchema = new mongoose.Schema({
    titulo: { type: String, required: true },
    data: { type: String, required: true },
    local: String,
    desc: String,
    participantes: [String]
  });

module.exports = mongoose.model('evento', eventoSchema)
