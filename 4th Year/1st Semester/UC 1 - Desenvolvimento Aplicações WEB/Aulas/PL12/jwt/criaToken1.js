var jwt = require('jsonwebtoken')
var segredo = "Aula secreta"
var token = jwt.sign({ sub: 'token gerado na aula de PRI2019' }, segredo, {expiresIn: 300})

console.log('Token: ' + token)