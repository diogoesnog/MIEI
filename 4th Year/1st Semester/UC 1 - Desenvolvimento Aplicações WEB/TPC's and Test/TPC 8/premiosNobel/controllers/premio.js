var PremioNobel = require("../models/premio")

// Lista de Prémios consoante uma Query.
module.exports.listaPremios = (query) => {
    return PremioNobel.find(query).exec();
}

// Lista de todas as categorias existentes na Base de Dados.
module.exports.listaCategorias = () => {
    return PremioNobel.distinct("category").exec();
}

// Lista de Laureados.
module.exports.listaLaureados = () => {
    return PremioNobel.aggregate()
        .unwind("$laureates")
        .group({
            _id: "$laureates.id",
            firstname: {$first: "$laureates.firstname"},
            surname: {$first: "$laureates.surname"},
            prizes: {
                $push: {
                    year: "$year",
                    category: "$category"
                }
            }
        })
        .sort({
            firstname: true,
            surname: true
        })
        .project({
            _id: 0,
        })
        .exec()
}

// Retorna um Prémio consoante o seu ID.
module.exports.consultarID = (idPremio) => {
    return PremioNobel.findOne({_id: idPremio}).exec();
}

// Elimina um Prémio consoante o seu ID.
module.exports.eliminarID = (idPremio) => {
    return PremioNobel.deleteOne({_id: idPremio}).exec();
}
