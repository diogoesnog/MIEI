var jwt = require('jsonwebtoken')

var segredo = '2019-12-10'

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019'
    }, 
    segredo, 
    {
        expiresIn: 300, 
        issuer: 'verificaToken2.js',
        audience: 'Alunos DAW'
    }
)

console.log(token)

console.log("Devolve o payload associado ao token. Aborta caso o segrego esteja errado.")

const readLine = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
})

readLine.question('Introduza o Segredo -> ', segredo => {
    jwt.verify(token, segredo, function(erro, decoded){
        if(erro) console.log(erro)
        else console.dir(decoded)
    })
    readLine.close()
})