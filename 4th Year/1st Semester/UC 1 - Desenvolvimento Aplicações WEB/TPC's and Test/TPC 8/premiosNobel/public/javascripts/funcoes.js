// Função que elimina um registo de Prémio da Base de Dados.
function eliminarPremio(idPremio) {
    
    axios.delete("/premios/" + idPremio)
        .then(response => window.location.assign("/"))
        .catch(err => console.log(err))
}

// Mostra um Prémio consoante o seu ID.
function mostraPremio(categoriaPremio, dataPremio) {

    if(categoriaPremio=="" && dataPremio== ""){
        window.location.assign("/");
    }
    else if(categoriaPremio=="" && dataPremio != ""){
        window.location.assign("/");
    }
    else if(categoriaPremio!="" && dataPremio == ""){
        axios.get("/premios?categoria=" + categoriaPremio)
        .then(() => window.location.assign("/premios?categoria=" + categoriaPremio))
        .catch(error => console.log(error))        
    }
    else{
        axios.get("/premios?categoria=" + categoriaPremio + "&data=" + dataPremio)
        .then(() => window.location.assign("/premios?categoria=" + categoriaPremio + "&data=" + dataPremio))
        .catch(error => console.log(error))        
    }

}