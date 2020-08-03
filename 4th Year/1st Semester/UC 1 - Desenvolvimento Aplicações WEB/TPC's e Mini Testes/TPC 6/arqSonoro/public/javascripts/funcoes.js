// Funções necessárias para processar a informação.

function atualizaMusica (prov, local, tit, inst, filet, filetext, duracao){

	axios.put('/',{
        uprov:prov,
        ulocal:local,
		utit:tit,
		uinst:inst,
		ufilett:filet,
		ufiletext: filetext,
        uduracao: duracao
    })
	.then(function(response){
            window.location.assign('/')
    })
	.catch(error=>console.log(prov +"ola"))
}


function apagaMusica (ident){
	
	axios.delete('/'+ident)
		.then(response=> window.location.assign('/'))
		.catch(error=>console.log(error))
}