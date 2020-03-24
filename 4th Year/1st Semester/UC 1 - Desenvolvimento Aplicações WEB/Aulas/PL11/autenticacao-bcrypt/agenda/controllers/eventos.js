var Evento = require('../models/eventos')

module.exports.listar = () => {
    return Evento
        .find()
        .exec()
}

module.exports.consultar = id => {
    return Evento
        .findOne({_id: id})
        .exec()
}

module.exports.filtrarParticipante = pid => {
    return Evento
        .find({participantes: pid})
        .exec()
}