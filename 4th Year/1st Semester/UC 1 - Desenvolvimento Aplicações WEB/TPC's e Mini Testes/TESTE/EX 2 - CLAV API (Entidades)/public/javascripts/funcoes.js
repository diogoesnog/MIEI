// Mostra um Prémio consoante o seu ID.
function mostraEntidade(sigla, sioe) {

    if(sigla=="" && sioe== ""){
        window.location.assign("/");
    }
    else if(sigla=="" && sioe != ""){
        axios.get("/entidades?sioe=" + sioe)
        .then(() => window.location.assign("/entidades?sioe=" + sioe))
        .catch(error => console.log(error))  
    }
    else if (sigla!="" && sioe == ""){
        axios.get("/entidades/ent_" + sigla)
        .then(() => window.location.assign("/entidades/ent_" + sigla))
        .catch(error => console.log(error))        
    }

}
