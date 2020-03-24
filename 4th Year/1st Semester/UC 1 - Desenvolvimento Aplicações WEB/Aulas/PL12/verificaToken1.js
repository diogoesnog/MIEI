var jwt = require('jsonwebtoken')

var segredo = '2019-12-10'

var token = jwt.sign(
    {
        sub: 'Token Gerado na aula de DAW2019'
    }, 
    segredo, 
    {
        expiresIn: 300, 
        issuer: 'verificaToken1.js',
        audience: 'Alunos DAW'
    }
)

console.log(token)

console.log("Devolve o payload associado ao token. Aborta caso o segrego esteja errado.")
// Segredo Inválido. Conseguimos comprovar que a Assinatura é Inválida pelo output do terminal.
// Se colocarmos o segredo como sendo 2019-12-10, já nos vai devolver o payload.
jwt.verify(token, 'Aula Secreta', function(erro, decoded){
    if(erro) console.log(erro)
    else console.dir(decoded)
})