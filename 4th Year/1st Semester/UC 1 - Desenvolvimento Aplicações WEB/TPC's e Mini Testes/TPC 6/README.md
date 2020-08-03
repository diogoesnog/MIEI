# TPC 6 - Servidor de Ficheiros (Pug + Express)

Vimos no TPC 5 que o uso de um *Template Engine* no desenvolvimento de aplicações WEB permite manipular e organizar todo o conteúdo HTML de uma forma mais dinâmica e limpa à vista do utilizador. 

Através da combinação deste *Template Engine* com a WEB *framework* Express, conseguimos construir uma *app* WEB ainda mais simples e flexível, através de um conjunto robusto de recursos que acaba por ser essencial na construção de aplicações WEB e também *Mobile*.

---

## Resolução do TPC 6

Este TPC acaba por ser um aprofundar do TPC anterior, dado que é necessário desenvolver novamente um servidor baseado na tecnologia NodeJS juntamente com os *templates* Pug devidamente modelados e adaptados aos requisitos pedidos.

Com um ficheiro XML relativo ao registo do Arquivo Sonoro EVO, deve-se transformá-lo para um ficheiro JSON adaptado às necessidades futuras, servindo asism como a Base de Dados para este projeto. Através desta Base de Dados, o servidor deve ser capaz de atender às principais operações dos arquivos musicais - *add*, *update* e *delete* - criando assim um **Gestor do Arquivo Sonoro** funcional e intuitivo.



**Com isto em mente e com a estrutura de pastas totalmente definida foram desenvolvidos os seguintes ficheiros:**

1. **Ficheiro** [funcoes.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%206/arqSonoro-nodeJS%2BExpress/public/javascripts/funcoes.js) existente na pasta ***/public/javascripts*** - Ficheiro que processa os pedidos do Cliente, encaminado-o para a devida rota.
2. **Ficheiro** [index.js](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%206/arqSonoro-nodeJS%2BExpress/routes/index.js) existente na pasta ***/routes*** - Ficheiro que define todas as rotas do Gestor do Arquivo Sonoro, que são necessárias para atender às necessidades impostas pelo Cliente.

Os restantes ficheiros correspondem aos *Template Engines* localizados na pasta ***/views***, que definem o processamento do conteúdo das várias páginas WEB criadas para este projeto. É ainda usado o CSS do *Bootstrap*, que se encontra na pasta ***public/sytlesheets***.



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

Dado que o TPC acaba por ser uma continuação do que foi lecionado no TPC anterior, a ideia geral da sua resolução tornou-se simples, sendo apenas necessário compreender a simplicidade que a *framework* Express traz na construção de servidores em NodeJS.

Com a estrutura da pasta principal da aplicação WEB (que é feita pelo próprio Express) esboçada, apenas foi preciso adaptar ao problema em causa, adicionando os *templates* necessários para processar a informação/páginas declaradas no próprio servidor e os *javascripts* que permitem que ações importantes (como o *update* e *delete*) realmente aconteçam.