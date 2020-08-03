# TPC 9 - Utilitário em NodeJS (Comando *mongoimport*)

O TPC 9 é um mini projeto extra que consiste em criar um programa em NodeJS que permita um funcionamento a nível da linha de comandos. Através do nome da *database*, *collection* e ficheiro JSON a importar, a ideia é o comando ser executado por si só, fazendo assim o povoamento da Base de Dados que se especificou.

---

## Resolução do TPC 9

Uso dos módulos **ReadLine** e **Child Process** para conseguir fazer o *parse* do *Input* e a execução do comando *mongoimport* em si, respetivamente.

**Para isso, criaram-se duas funções:** 

1. Função **parseInput()** - trata de extrair o nome da *database*, *collection* e ficheiro JSON, guardando-os numa variável própria, fazendo para isso uso de uma *Interface* criada através do módulo **ReadLine**. 
2. Função **executarComando()** - cria todo o comando, completando-o com as informações pedidas para o efeito e após isso executa-o.

**Além destes ficheiros, é feita a continuidade dos ficheiros PR.xml e PR.html.**

---

## Executar Aplicação WEB

Para testar/executar este projeto, é necessário ter o *Node Package Manager* (npm *command*) instalado. O comando vai criar o ficheiro **package.json**, que será necessário para se correr o ficheiro *JavaScript*.

```
npm install
```

Para executar o programa em si, basta executar o comando a seguir.

```
node mongoImport.js
```

---

## Dificuldades do TPC

Nada a apontar.