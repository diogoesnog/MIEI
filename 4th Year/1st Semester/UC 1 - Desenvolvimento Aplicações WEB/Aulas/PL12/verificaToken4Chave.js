var jwt = require('jsonwebtoken')
var fs = require('fs')

var segredo = '2019-12-10'
// ssh-keygen -t rsa -b 4096 -m PEM -f jwR256.key
// openssl rsa -in jwR256.key -pubout -outform PEM -out jwR256.key.pub
var chavePrivada = fs.readFileSync('jwR256.key');

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019'
    }, 
    chavePrivada, 
    {
        algorithm: 'R256',
        expiresIn: 300, 
        issuer: 'verificaToken4Chave.js',
        audience: 'Alunos DAW'
    }
)

console.log(token)

console.log("Devolve o payload associado ao token. Aborta caso o segrego esteja errado.")

const readLine = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
})

// Neste caso estamos a "brincar" e ver que podemos fazer o mesmo para o Issuer e não só para o segredo.
readLine.question('Instroduza o Nome do Ficheiro da Chave Pública -> ', segredo => {

    var chavePublica = fs.readFileSync(segredo);

    jwt.verify(token, chavePublica, function(erro, decoded){
        if(erro) console.log(erro)
        else console.dir(decoded)
    })
    readLine.close()
})