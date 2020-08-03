# TPC 5 - Servidor de Ficheiros. Introdução ao *Template Engine* Pug.

O uso de um *Template Engine* no desenvolvimento de aplicações WEB permite manipular e organizar todo o conteúdo HTML de uma forma dinâmica e limpa à vista do utilizador. 

O *Template Engine* Pug é um mecanismo de modelagem bastante poderoso, que disponibiliza uma variedade de recursos que são depois úteis na construção do servidor em si. É precisamente sobre este mecanismo que se pretende trabalhar, apurando o trabalho feito na aula e construindo assim uma página WEB que permita gerir todo um conjunto de tarefas.

---

## Resolução do TPC 5

Neste TPC torna a ser necessário desenvolver um servidor baseado na tecnologia NodeJS, mas com novas funcionalidades *Core*, no sentido de se adaptar o seu uso com a criação dos ficheiros Pug relativos às páginas WEB essenciais a este projeto. 

Com os *templates* Pug modelados, o servidor deve ser capaz de os processar consoante o pedido do Cliente, criando um gestor de tarefas em tempo real com uma persistência de dados em *JSON* que agrega o conjunto de tarefas que são enviadas/requiridas pelo utilizador.



**Com essa finalidade em mente, foram desenvolvidos os seguintes ficheiros:**

1. [**Ficheiro layout.pug**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/layout.pug) - *Template* que define a estrutura base das várias páginas WEB.

2. [**Ficheiro indice.pug**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/indice.pug) - *Template* relativo à página inicial do Gestor de Tarefas.

3. [**Ficheiro listaTarefas.pug**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/listaTarefas.pug) - *Template* relativo à página que agrega o conjunto de tarefas presentes até então na Base de Dados.

4. [**Ficheiro submeterTarefa.pug**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/submeterTarefa.pug) - *Template* relativo à página dedicada para se submeter uma tarefa.

5. [**Ficheiro servidor.js**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/servidor.js) - Servidor em ```NodeJS``` que permite estabelecer a ligação entre o Cliente e Servidor, respondendo aos pedidos no URL do *browser* e processando a submissão/listagem das tarefas.

6. **Ficheiros Extra** - Ficheiros que adicionam algum interesse/funcionalidade ao trabalho de casa.
   
      6.1. [**Ficheiro paginaErro.pug**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/paginaErro.pug) - Página simples em HTML que é acionada quando o pedido ao servidor for incorreto, adaptando a resposta dada ao Cliente consoante o erro ocorrido.
      
      6.2. [**Ficheiro favicon.ico**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/imagens/favicon.ico) - *Favicon* das páginas no geral.
      
      

**Além destes ficheiros, é feita a continuidade dos ficheiros PR.xml e PR.html.**

---

## Executar Aplicação WEB

Para testar/executar este projeto, é necessário ter o *Node Package Manager* (npm *command*) instalado. O comando serve assim para instalar os módulos *pug* e *jsonfile*.

```
npm install pug jsonfile
```

Para executar o servidor em si, corre-se o seguinte comando. O servidor ficará a correr na porta **3000**.

```
node servidor.js
```

---

## Dificuldades do TPC

A única dificuldade do TPC foi trabalhar no *Template Engine* Pug, dado que em si o código é todo indentado e por vezes tornava-se difícil compreender os *Tabs* necessários.

Além disso, foi preciso compreender como é que a informação introduzida pelo Cliente no *Form* desenvolvido para submissão de tarefas, conseguia ser retirado e relacionado com os parâmetros do [*JSON file*](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%205/listaTarefas-nodeJS/listaTarefas.json) da Base de Dados.