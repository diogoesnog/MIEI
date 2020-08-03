
// ReadLine necessário para se fazer o parse do Input.
const readline = require("readline");

const interfaceReadLine = readline.createInterface({
    input: process.stdin,
    output: process.stdout
}); 

// Exec necessário para executar o comando em si.
const exec = require("child_process").exec

// Variável que permite verificar qual o número do Input.
// Necessário ser global.
let numeroInput = 1;

// Strings necessárias para executar o comando em si.
let database, collection, file;

// Função que executa o comando em si.
function executarComando() {

    let comando = "mongoimport -d " + database + " -c " + collection + " --jsonArray " + file;

    exec(comando, function (erro, stdout, stderr) {
        
        if(erro) console.log(erro);
        else console.log(stderr);
    });
}

// Função que faz o parse de todo o Input necessário.
function parseInput() {

    switch(numeroInput){

        case 1:
            interfaceReadLine.question("Inroduza o nome a dar à sua Database: ", function (answer){
                database = answer;
                numeroInput++;
                parseInput();
            })
            break;

        case 2:
            interfaceReadLine.question("Introduza o nome a dar à sua Collection: ", function (answer){
                collection = answer;
                numeroInput++;
                parseInput();
            })
            break;
        
        case 3:
            interfaceReadLine.question("Introduza o nome do ficheiro JSON a importar: ", function (answer){
                file = answer;
                numeroInput++;
                parseInput();
            })
            break;
        
        default:
            executarComando();
            interfaceReadLine.close();
    }

}

parseInput()
