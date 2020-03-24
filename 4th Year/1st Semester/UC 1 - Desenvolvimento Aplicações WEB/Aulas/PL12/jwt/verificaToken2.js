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
console.log('------------Verificação------------------')
console.log('---Devolve o payload associado ao token, aborta se o segredo estiver errado---')

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
  })
  
readline.question('Introduza o segredo: ', (s) => {
    jwt.verify(token, s, function(err, decoded) {
        if(err){
            console.log('Erro: ' + err)
        }
        else{
            console.dir(decoded)
        }
    })
    readline.close()
  })
