const http = require('http');
const fs = require('fs');

var portaServidor = 7777;

http.createServer( function(req, res) {
    
    /* Ao colocarmos (por exemplo) 'localhost:7777/1', o split tratará o URL como um array.
     * Assim, o nosso array terá duas posições - posição 0 e 1 - 'localhost:7777' e '1'. */
    var array = req.url.split('/');
    
    /* O tamanho do Array será então de 2. */
    var tamanhoArray = array.length;
    
    /* Apenas queremos a parte do número da página do Arqueossítio em causa. */
    var pagina = array[tamanhoArray-1];
    
    switch (pagina) {
        
        case 'arq2html.xsl':
        
            fs.readFile('arq2html.xsl', function (erroXSL, dataXSL){
                
                if(erroXSL) throw err;
                
                res.writeHead(200, {'Content-Type': 'text/xsl'});
                res.write(dataXSL);
                res.end();         
            });
            
        break;
        
        default:
        
            fs.readFile('dataset/arq' + pagina + '.xml', function (erroXML, dataXML){
                
                // Neste caso, se o XML em do Arqueossítio pedido não existir, devolvemos uma página de erro.
                // Esta página de erro foi desenvolvida à parte e encontra-se (como esperado) no formato HTML.
                if(erroXML){
                
                    fs.readFile('paginaErro.html', function (erroHTML, dataHTML){
                        
                        if(erroHTML) throw erroHTML;
                        
                        // Nesta caso, o Content-Type é HTML. 
                        res.writeHead(200, {'Content-Type': 'text/html'});
                        res.write(dataHTML);
                        res.end();         
                    });
                    
                    return;
                }
                    
                res.writeHead(200, {'Content-Type': 'text/xml'});
                res.write(dataXML);
                res.end();         
            });
            
        break;
    }
    
}).listen(portaServidor);

console.log('O servidor está ativo na porta ' + portaServidor + '. Faça o seu pedido.');


