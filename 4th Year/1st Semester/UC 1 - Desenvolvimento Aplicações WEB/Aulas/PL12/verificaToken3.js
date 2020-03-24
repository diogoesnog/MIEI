var jwt = require('jsonwebtoken')

var segredo = '2019-12-10'

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019'
    }, 
    segredo, 
    {
        expiresIn: 300, 
        issuer: 'verificaToken3.js',
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
readLine.question('Introduza o Issuer -> ', issuer => {
    jwt.verify(token, '2019-12-10', {issuer: issuer}, function(erro, decoded){
        if(erro) console.log(erro)
        else console.dir(decoded)
    })
    readLine.close()
})