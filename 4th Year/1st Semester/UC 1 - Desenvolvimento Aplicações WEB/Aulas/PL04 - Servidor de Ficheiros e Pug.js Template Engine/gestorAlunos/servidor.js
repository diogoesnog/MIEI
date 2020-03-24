
// Módulos

var http = require('http')
// Usado para ir buscar a Query String.
var url = require('url')
// Sistema de template
var pug = require('pug')
var fs = require('fs')
var jsonfile = require('jsonfile')
// Para fazer o parse da Query String. Não se faz só com o módulo 'url'.
// Delcaramos diferente porque significa que só queremos exportar a parte do parse por parte da 'querystring'.
var {parse} = require('querystring')

var myBD = "alunos.json"

// Em vez de escrevermos funtion(){}, podemos escrever ()=>{}
var servidor = http.createServer((req, res)=>{

    var pedidoUrl = url.parse(req.url, true)
    var query = pedidoUrl.query

    console.log(req.method + ' ' + pedidoUrl.pathname)

    if(req.method == 'GET'){

        if( (pedidoUrl.pathname == '/') || (pedidoUrl.pathname == '/gestaoAlunos') ){
            // Cabeçalho.
            res.writeHead(200, {
                'Content-Type': 'text/html; charset=utf-8'
            })
            // Body - vamos renderizar já um template.
            res.write(pug.renderFile('index.pug'))
            // Fechar o pacote.
            res.end()
        }
        else if(pedidoUrl.pathname == '/w3.css'){
            res.writeHead(200, {'Content-Type': 'text/css'})
            fs.readFile('stylesheets/w3.css', (erro, dados)=>{
                if(!erro){
                    res.write(dados)
                }
                else
                    res.write("<p>Erro: " + erro + "</p>")
                    // Coloca-se aqui o end dado que se colocarmos fora, como a programação é assíncrona,
                    // podíamos estar ainda a ler o readFile e ele já estar a fazer o end.
                    res.end()
            })
        }
        else if(pedidoUrl.pathname == '/listar'){
            jsonfile.readFile(myBD, (erro, alunos)=>{
                res.writeHead(200, {
                    'Content-Type': 'text/html; charset=utf-8'
                })  
                if(!erro){
                    res.write(pug.renderFile('lista-alunos.pug', {lista: alunos}))
                    res.end()
                }
                else{
                    res.write(pug.renderFile('templateErro.pug', {e: "Erro na leitura da BD..."}))
                }
                res.end()
            })
        }
        else if(pedidoUrl.pathname == '/registar'){
            res.writeHead(200, {
                'Content-Type': 'text/html; charset=utf-8'
            })
            res.write(pug.renderFile('formAluno.pug'))
            res.end() 
        }
    }
    else if(req.method == 'POST'){
        if(pedidoUrl.pathname == '/aluno'){
            recuperaInfo(req, resultado=>{
                jsonfile.readFile(myBD, (erro, alunos)=>{
                    if(!erro){
                        alunos.push(resultado)
                        jsonfile.writeFile(myBD, alunos, erro=>{
                            if(erro) console.log(erro)
                            else console.log('Registo gravado com sucesso.')
                        })
                    }
                })
            })
        }
    }
    else{
        // Cabeçalho.
        res.writeHead(200, {
            'Content-Type': 'text/html; charset=utf-8'
        })
        // Colocar também na consola do Admin que tem o server a correr é sempre boa prática.
        console.log("ERRO: " + req.method + " não suportado...")
        // Body - vamos renderizar já um template.
        res.write(pug.renderFile('templateErro.pug', 
            {e: "ERRO: " + req.method + " não suportado..."}))
        // Fechar o pacote.
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
}