
var http = require('http')
var pug = require('pug')
var fs = require('fs')
var jsonfile = require('jsonfile')
var {parse} = require('querystring')

var myBD = "alunos.json"

var servidor = http.createServer((req, res)=>{

    console.log(req.method + ' ' + req.url)

    if(req.method == 'GET'){

        if( (req.url == '/') || (req.url  == '/alunos') ){
            jsonfile.readFile(myBD, (erro, alunos)=>{
                if(!erro){
                    res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
                    res.write(pug.renderFile('index.pug', {lista: alunos}))
                    res.end()
                }
                else{
                    res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
                    res.write(pug.renderFile('erro.pug', {e: 'Erro na leitura da BD.'}))
                    res.end()
                }
            })
        }
        else if(req.url == '/w3.css'){
            res.writeHead(200, {'Content-Type': 'text/css'})
            fs.readFile('stylesheets/w3.css', (erro, dados)=>{
                if(!erro) res.write(dados)
                else res.write(pug.renderFile('erro.pug', {e: erro}))
                res.end()
            })
        }
        else if(req.url == '/apagar.js'){
            res.writeHead(200, {'Content-Type': 'text/javascript'})
            fs.readFile('apagar.js', (erro, dados)=>{
                if(!erro) res.write(dados)
                else res.write(pug.renderFile('erro.pug', {e: erro}))
                
                res.end()
            })
        }
    }
    else if (req.method == 'POST'){
        if(req.url == '/'){
            recuperaInfo(req, resultado=>{
                jsonfile.readFile(myBD, (erro, alunos)=>{
                    if(!erro){
                        alunos.push(resultado)
                        jsonfile.writeFile(myBD, alunos, erro=>{
                            if(erro) console.log(erro)
                            else console.log('Registo gravado com sucesso.')
                            res.end(pug.renderFile('index.pug', {lista: alunos}))
                        })
                    }
                    else res.end(pug.renderFile('index.pug', {lista: alunos}))
                })
            })
        }
        else{
            res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
            console.log("ERRO: " + req.url + " não implementado.")
            res.write(pug.renderFile('erro.pug',{e: "ERRO: " + req.url + " não implementado."}))
            res.end()
        }
    }
    else if(req.method == 'DELETE'){
        if(req.url.startsWith('/')){
            var id = req.url.split('/')[1]
            jsonfile.readFile(myBD, (erro, alunos)=>{
                if(!erro){
                    // O findIndex é parametrizado com uma função boleana. 
                    // Quando encontrar no array quando for verdade, devolve de imediato a posição do elemento do array.
                    // Caso não encontre, devolve -1. 
                    // Neste caso o "id" é o que retiramos em si do URL (por ex. gestorAlunos/A7)
                    var index = alunos.findIndex(aluno => aluno.identificador == id)
                    if(index > -1){
                        // O splice, a partir da posição do array que dou, ele remove o índice, fazendo depois o shift direitinho.
                        // Devolve assim o array perfeitamente.
                        alunos.splice(index, 1)
                        // Depois de retirado, gravamos esta alteração.
                        jsonfile.writeFile(myBD, alunos, erro => {
                            if(erro) console.log(erro)
                            else console.log('BD atualizada com sucesso.')
                        })
                        // Devolve 0 se correr tudo bem. (Fomos nós que escolhemos lol.)
                        // Devolvemos isto para quem fez o pedido (browser).
                        res.end('0')
                    }
                    else{
                        console.log('Erro: não consegui encontrar o elemento a remover...')
                        // Devolvemos então 1 se tudo correr bem.
                        res.end('1')
                    }
                }
                else{
                    console.log('Erro na leitura da BD...')
                    res.end('1')
                }
            })
        }
    }
    else{
        res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
        console.log("ERRO: " + req.url + " não suportado.")
        res.write(pug.renderFile('erro.pug',{e: "ERRO: " + req.url + " não suportado."}))
        res.end()
    }
})

// Function não precisa ter argumentos.
servidor.listen(5005, ()=>{
    console.log("Servidor já está à escuta.")
})

function recuperaInfo(request, callback) {
    if (request.headers['content-type'] == 'application/x-www-form-urlencoded') {
        let body = ''
        request.on('data', bloco => {
            body += bloco.toString()
        })
        request.on('end', () => {
            callback(parse(body))
        })
    }
    else callback(null)
}