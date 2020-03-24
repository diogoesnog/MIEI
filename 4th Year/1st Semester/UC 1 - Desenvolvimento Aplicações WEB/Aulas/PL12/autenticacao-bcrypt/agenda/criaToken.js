var jwt = require('jsonwebtoken')

var segredo = 'DAW2019'

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019',
        teste: 'Porcaria de Aulas'
    }, 
    segredo, 
    {
        expiresIn: 100, 
        issuer: 'criaToken.js',
        audience: 'Alunos DAW',
        noTimestamp: true
    }
)

console.log(token)