var http = require("http")
var fs = require("fs")

var url = require("url")
var pug = require("pug")
var jsonfile = require("jsonfile")
var {parse} = require("querystring")

var baseDados = "listaTarefas.json"
var portaServidor = 3000

http.createServer((req, res)=> {
    
    var pedidoUrl = url.parse(req.url, true)
    var query = pedidoUrl.query
    
    console.log(req.method + " " + pedidoUrl.pathname)

    switch(req.method){
        
        // CASO SEJA UM GET
        
        case "GET": 
            
        // Página Inicial
        if(pedidoUrl.pathname == "/"){
            
            res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
            res.write(pug.renderFile("views/indice.pug"))
            res.end()
        }
        
        // Componentes Base da página WEB
        else if(pedidoUrl.pathname == "/bootstrap.css"){
            res.writeHead(200, {"Content-Type": "text/css"})
            fs.readFile("stylesheet/bootstrap.css", (erro, dados)=>{
                if(!erro){
                    res.write(dados)
                }
                else
                    res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: erro}))
                    res.end()
            })
        }
        
        else if(pedidoUrl.pathname == "/favicon.ico"){
            res.writeHead(200, {"Content-Type": "image/x-icon"})
            fs.readFile("imagens/favicon.ico", (erro, dados) => {
                if(!erro)
                    res.write(dados)
                else 
                    res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: erro}))
                    res.end()
                })
        }
        
        // Páginas de listagem e submissão de Tarefas
        else if(pedidoUrl.pathname == "/listaTarefas"){
            
            jsonfile.readFile(baseDados, (erro, tarefas) => {
                res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
                if(!erro){
                    res.write(pug.renderFile("views/listaTarefas.pug", {listaTarefas: tarefas}))
                    res.end()
                }
                else{
                    res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: "Erro ao ler a lista das tarefas."}))
                }
                res.end()
            })
        }
        
        else if(pedidoUrl.pathname == "/submeterTarefa"){
            res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
            res.write(pug.renderFile("views/submeterTarefa.pug"))
            res.end()
        }
        
        // GET desconhecido.
        else{
           res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
           res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: "Erro ao requerir a página solicitada. Verifique o seu URL."}))
           res.end()
        }
        
        break

        // CASO SEJA UM POST
        
        case "POST": 
        
        // Componentes Base da página WEB
        if(pedidoUrl.pathname == "/submeterTarefa"){
            recuperaInfo(req, resultado => {
                jsonfile.readFile(baseDados, (erro, tarefas)=>{
                    if (!erro) {
                        tarefas.push(resultado)
                        jsonfile.writeFile(baseDados, tarefas, erro => {
                            if (!erro) {
                                console.log("Tarefa submetida com sucesso.")
                                res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
                                res.write(pug.renderFile("views/submeterTarefa.pug", {mensagemSucesso: "A sua tarefa foi submetida com sucesso."}))
                                res.end()
                            } else {
                                console.log("Erro ao submeter a Tarefa.")
                                res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
                                res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: "Erro ao submeter a Tarefa."}))
                            }
                        })
                    }
                    else {
                        console.log("Erro ao ler ficheiro json.")
                        res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
                        res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: "Erro ao submeter a Tarefa."}))       
                    }
                })
            })
        }
        
        // POST desconhecido.
        else{
            res.writeHead(200, {"Content-Type": "text/html; charset=utf-8"})
            res.write(pug.renderFile("views/paginaErro.pug", {mensagemErro: "Erro ao enviar a página solicitada. Tente mais tarde."}))
            res.end()
        }
        
    }   
}).listen(portaServidor, () => {
    console.log("Servidor começou agora a correr na porta " + portaServidor + ".")
})

    function recuperaInfo(request, callback) {
        if (request.headers["content-type"] == "application/x-www-form-urlencoded") {
            let body = ""
            request.on("data", bloco => {
                body += bloco.toString()
            })
            request.on("end", () => {
                callback(parse(body))
            })
        }
    }