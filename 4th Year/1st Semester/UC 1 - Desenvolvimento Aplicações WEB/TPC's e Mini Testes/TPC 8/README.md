# TPC 8 - Servidor de Ficheiros (Pug + Express + MongoDB + API Dados)

O TPC 8 procura combinar todo o conteúdo programático da Unidade Curricular, introduzindo-se a noção de API de Dados para se criar uma "ponte" entre as aplicações. Dessa forma, consegue-se processar os pedidos do Cliente através da *Interface*, recorrendo à API para tratar a informação em modo bruto.

---

## Resolução do TPC 8

Com um ficheiro JSON relativo a um conjunto de Prémios Nobel, deve-se criar uma Base de Dados limpa, exportanto-se todos os dados existentes para a mesma. Tendo-se a Base de Dados pronta e devidamente povoada, pretende-se que seja possível manipular a sua informação de modo bruto através de uma API, que é depois mostrada ao Cliente através de uma *Interface* preparada para esse mesmo efeito.



**Com isto em mente e com a estrutura de pastas totalmente definida foram desenvolvidos os seguintes ficheiros:**

1. **Ficheiro** [premio.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%208/premiosNobel/controllers/premio.js) existente na pasta ***/controllers*** - Ficheiro que define os Controlados do conjunto de Prémios, definindo as *queries* que tratam das operações essenciais para manipular o conteúdo.

De modo a se facilitar certas *queries*, foi criada uma *query* que age consoante aquilo que recebe no seu parâmetro, permitindo devolver uma lista de Prémios personalizada.

```javascript
// Lista de Prémios consoante uma Query.
module.exports.listaPremios = (query) => {
    return PremioNobel.find(query).exec();
}
```

2. **Ficheiro** [premio.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%208/premiosNobel/models/premio.js) existente na pasta ***/models*** - Ficheiro que define o Modelo de um Prémio Nobel, pela definição de um *Schema* que é universal a todos os registos. Dado que cada Prémio Nobel tem um conjunto de Laureados, foi necessário definir também o seu Modelo.
3. **Ficheiro** [funcoes.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%208/premiosNobel/public/javascripts/funcoes.js) existente na pasta ***/public/javascripts*** - Ficheiro que processa os pedidos do Cliente, encaminado-o para a devida rota. Neste ficheiro é declarada uma função que serve para eliminar um registo de Prémio Nobel e ainda uma função que devolve um registo consoante a sua categoria e data.
4. **Ficheiro** [index.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%208/premiosNobel/routes/index.js) e **ficheiro** [api.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%208/premiosNobel/routes/api.js) existente na pasta ***/routes*** - Ficheiros que definem conjuntamente todas as rotas que são necessárias para atender às necessidades impostas pelo Cliente. Uma vez que se está a trabalhar agora com a ideia de API de Dados, existe um ficheiro que trata de toda a parte da informação em si e outro que perante este tratamento, manda os dados para as devidas *views*.

Todos os outros ficheiros desenvolvidos são triviais, correspondendo essencialmente aos vários *Template Engines* localizados na pasta ***/views*** necessários para transformar o conteúdo processado em uma página WEB intuitiva. É ainda usado o CSS do *Bootstrap*, que se encontra na pasta ***public/sytlesheets***.



**Além destes ficheiros, é feita a continuidade dos ficheiros PR.xml e PR.html.**

---

## Executar Aplicação WEB

Para testar/executar este projeto, é necessário ter o *Node Package Manager* (npm *command*) instalado. O comando serve assim para instalar todos os módulos listados como dependências no **package.json**, criando todo o processo numa pasta de nome **node_modules**.

```
npm install --save
```

Para executar o servidor em si, corre-se o seguinte comando. O servidor ficará a correr na porta 3000.

```
npm start
```
---

## Dificuldades do TPC

Nada a apontar.