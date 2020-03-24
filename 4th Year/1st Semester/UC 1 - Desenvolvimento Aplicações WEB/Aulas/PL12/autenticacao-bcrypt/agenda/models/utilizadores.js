const mongoose = require('mongoose')

var utilizadorSchema = new mongoose.Schema({
    email: { type: String, required: true },
    nome: { type: String, required: true },
    password: { type: String, required: true },
    ultimoAcesso: String
  });

module.exports = mongoose.model('utilizadores', utilizadorSchema)