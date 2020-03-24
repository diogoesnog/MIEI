var jwt = require('jsonwebtoken')

var segredo = 'DAW21019'

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
    }
)

console.log(token)