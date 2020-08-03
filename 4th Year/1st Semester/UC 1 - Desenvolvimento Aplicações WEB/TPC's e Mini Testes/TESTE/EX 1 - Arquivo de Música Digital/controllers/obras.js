var mongoose = require("mongoose");
var Obra = require("../models/obras");

// Lista de todas as Obras consoante uma dada Query.
// Pode ser útil para futuras Queries.
module.exports.listaObrasQuery = query => {
    return Obra.find(query).exec();
}

// Lista de Obras que tenham uma ou mais Partituras para um dado Instrumento.
module.exports.listarObrasInstrumento = inst => {
    return Obra
        .aggregate([{
            $unwind: "$instrumentos"
        }, {
            $match: {
                'instrumentos.instrumento.designacao': inst
            }
        }])
        .exec();
}

// Lista de todas as Obras.
// Devolvemos apenas os campos id, titulo, tipo e compositor.
module.exports.listaObras = () => {
    return Obra.find(
        {},
        {
            _id: 1, 
            titulo: 1, 
            tipo: 1, 
            compositor: 1
        })
        .exec();
}

// Informação completa de uma Obra consoante o seu ID.
module.exports.infoObra = identificador => {
    return Obra
        .findOne({
            _id: identificador
        })
        .exec()
}

// Lista dos Tipos, sem repetições.
module.exports.listaTipos = () => {
    return Obra.distinct("tipo").exec();
}