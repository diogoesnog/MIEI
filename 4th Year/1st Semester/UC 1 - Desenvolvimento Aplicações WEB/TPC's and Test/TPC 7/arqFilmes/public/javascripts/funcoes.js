// Mostra um Filme consoante o seu ID.
function mostraFilmeID(idFilme) {

    axios.get("/filmes/id/" + idFilme)
    .then(() => window.location.assign("/filmes/id/" + idFilme))
    .catch(error => console.log(error))
}

// Mostra um Filme consoante o seu Título.
function mostraFilmeTitulo(tituloFilme){

    axios.get("/filmes/titulo/" + tituloFilme)
    .then(() => window.location.assign("/filmes/titulo/" + tituloFilme))
    .catch(error => console.log(error))
}

// Elimina um Filme.
function eliminarFilme(idFilme) {
    
    axios.delete("/filmes/" + idFilme)
         .then(() => window.location.assign("/filmes"))
         .catch(error => console.log(error))
}

// Atualiza um Filme.
function atualizarFilme(idFilme, tituloFilme, anoFilme, atoresFilme, generosFilme) {
        
    // Ter em conta que os Atores são um Array.
    var atores = [];
    var indiceAtor = 0;

    if (atoresFilme.length != 0) {

        while(indiceAtor<atoresFilme.split(",").length){
            atores.push(document.getElementById("ator" + indiceAtor).value);
            indiceAtor++;
        }

    }

    // Os Géneros também são um Array.
    var generos = [];
    var indiceGenero = 0;

    if (generosFilme.length != 0) {

        while(indiceGenero<generosFilme.split(",").length){
            generos.push(document.getElementById("genero" + indiceGenero).value);
            indiceGenero++;
        }
    }

    // Cirar a variável do registo atualizado.
    var novoFilme = {
        _id: idFilme,
        title: tituloFilme,
        year: anoFilme,
        cast: atores,
        genres: generos
    }

    axios.put("/filmes/" + idFilme, novoFilme)
        .then(() => window.location.assign("/filmes/id/" + idFilme))
        .catch(error => console.log(error))
}

