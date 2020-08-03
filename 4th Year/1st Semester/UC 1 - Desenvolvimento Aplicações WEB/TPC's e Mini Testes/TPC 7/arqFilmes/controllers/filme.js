var mongoose = require("mongoose");
var FilmeAmericano = require("../models/filme");

// A lista inicial de Filmes é reduzida a 50 apenas.
module.exports.listaFilmes = () => {
    return FilmeAmericano
        .aggregate([{$sample: {size: 20}}])
        .sort({title: 1})
}

// Retorna um Filme consoante o seu ID.
module.exports.consultarID = id => {
    return FilmeAmericano.findOne({_id: id})
}

// Retorna um Filme consoante o seu Título.
module.exports.consultarTitulo = titulo => {
    return FilmeAmericano.findOne({title: titulo})
}

// Insere um novo Filme na Base de Dados.
module.exports.inserirFilme = (filme) => {
    var novoFilme = new FilmeAmericano({

        // Necessário para criar um novo ID.
        _id: new mongoose.Types.ObjectId,
        title: filme.title,
        year: filme.year,
        cast: filme.cast,
        genres: filme.genres
    })

    return novoFilme.save()
}

// Atualizar um Filme.
module.exports.atualizarFilme = (id, filme) => {
    return FilmeAmericano.updateOne({_id: id}, filme)
}

// Elimina um Filme.
module.exports.eliminarFilme = id => {
    return FilmeAmericano.deleteOne({_id: id})
}