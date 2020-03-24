var jwt = require('jsonwebtoken')

var segredo = '2019-12-10'

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019',
        teste: 'Porcaria de Aulas'
    }, 
    segredo, 
    {
        expiresIn: 100, 
        issuer: 'criaToken2.js',
        audience: 'Alunos DAW',
        noTimestamp: true
    }
)

console.log(token)