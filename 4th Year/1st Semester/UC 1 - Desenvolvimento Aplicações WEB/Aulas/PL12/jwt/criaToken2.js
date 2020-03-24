var jwt = require('jsonwebtoken')

/*
audience - a que se destina
issuer - quem está a gerá-lo
jwtid - identificador para o token
subject - assunto associado
noTimestamp - evita que se gere o iat
*/
var segredo = "Aula secreta"
var token = jwt.sign({ sub: 'token gerado na aula de PRI2019' }, 
                        segredo, 
                        {
                            expiresIn: 300, 
                            issuer: "ex2.js"})

console.log('Token: ' + token)