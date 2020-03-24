var jwt = require('jsonwebtoken')
var segredo = '2019-12-10'

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019'
    }, 
    segredo, 
    {
        expiresIn: 300, 
        issuer: 'criaToken1.js',
        audience: 'Alunos DAW'
    }
)

console.log(token)