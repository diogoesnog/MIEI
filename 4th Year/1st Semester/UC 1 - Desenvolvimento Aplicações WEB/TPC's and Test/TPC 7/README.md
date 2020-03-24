# TPC 7 - Servidor de Ficheiros (Pug + Express + MongoDB)

O TPC 7 é o culminar das aprendizagens obtidas até então, fazendo-se a substituição de um ficheiro JSON para uma *database* real em MongoDB. Assim, introduz-se uma nova forma de tratar os dados, permitindo uma facilidade superior em se efetuar os pedidos básicos por parte do Cliente.

---

## Resolução do TPC 7

Com um ficheiro JSON relativo ao Arquivo de Filmes, deve-se criar uma Base de Dados limpa, exportanto-se todos os dados existentes para a mesma. Com a Base de Dados pronta e devidamente povoada, pretende-se que seja possível atender às principais operações dos arquivos musicais - *add*, *update* e *delete* - criando assim um **Gestor do Arquivo Filmes** funcional e intuitivo.

Adicionalmente à aplicação NodeJS com a *Framework* Express, foram propostas um conjunto de [*queries*](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%207/Queries.md) no sentido de acostumar o uso do MongoDB e compreender como podem ser feitas as operações em si.



**Com isto em mente e com a estrutura de pastas totalmente definida foram desenvolvidos os seguintes ficheiros:**

1. **Ficheiro** [filme.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%207/arqFilmes-nodeJS%2BExpress%2BMongoDB/controllers/filme.js) existente na pasta ***/controllers*** - Ficheiro que define os Controlados do conjunto de Filmes, definindo as *queries* que tratam das operações essenciais para manipular o conteúdo.
2. **Ficheiro** [filme.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%207/arqFilmes-nodeJS%2BExpress%2BMongoDB/models/filme.js) existente na pasta ***/models*** - Ficheiro que define o Modelo de Filmes, pela definição de um *Schema* que é universal a todos os registos.
3. **Ficheiro** [funcoes.js]() existente na pasta ***/public/javascripts*** - Ficheiro que processa os pedidos do Cliente, encaminado-o para a devida rota.
4. **Ficheiro** [filme.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%207/arqFilmes-nodeJS%2BExpress%2BMongoDB/routes/filme.js) existente na pasta ***/routes*** - Ficheiro que define todas as rotas do Gestor do Arquivo Filmes, que são necessárias para atender às necessidades impostas pelo Cliente.

Todos os outros ficheiros desenvolvidos são triviais, correspondendo essencialmente aos vários *Template Engines* localizados na pasta ***/views*** necessários para transformar o conteúdo processado em uma página WEB intuitiva. É ainda usado o CSS do *Bootstrap*, que se encontra na pasta ***public/sytlesheets***.

Nota-se uma maior complexidade em relação ao trabalho anterior, no que toca à estrutura de pastas existente. Isto deve-se à necessidade de existerem Controladores e Modelos adaptados à Base de Dados em MongoDB.



**Além destes ficheiros, é feita a continuidade dos ficheiros PR.xml e PR.html.**

---

## Executar Aplicação WEB

Para testar/executar este projeto, é necessário ter o *Node Package Manager* (npm *command*) instalado. O comando serve assim para instalar todos os módulos listados como dependências no **package.json**, criando todo o processo numa pasta de nome **node_modules**.

```
npm install --save
```

Para executar o servidor em si, corre-se o seguinte comando. O servidor ficará a correr na porta **3000**.

```
npm start
```

---

## Dificuldades do TPC

TPC mais fácil até então, dado que apenas foi necessário associar uma *database* em MongoDB ao que já tinha sido feito. Esta implementação facilita a procura/alteração de dados, diminuindo a dificuldade do *source-code* e da própria interpetação.