# TPC 4 - Servidor de Ficheiros

Ao iniciar o desenvolvimento de trabalhos com ```NodeJS```, depressa se nota que com simples código acabamos por viabilizar um conjunto de funcionalidades importantes.

Com o ```NodeJS```, a entrada e saída de dados não bloqueiam os processos de execução das aplicações, tornando a concorrência entre vários clientes simultâneos o mais eficiente e intuitiva possível.

---

## Resolução do TPC 4

Continuando o TPC anterior, pretende-se desenvolver uma *Stylesheet* que gere um XML para cada registo do arquivo dos Arqueossítios. Com estes ficheiros prontos, a ideia é criar um servidor em ```NodeJS``` (na porta **7777**) que os sirva, de acordo com o pedido do Cliente (*browser*).

**Assim, se o pedido em URL for ```localhost:7777/1```, é colocado no *browser* o conteúdo do ficheiro arq1.xml em formato HTML.**



**Para atender a estes requisitos, foram desenvolvidos os ficheiros:**

1. [**Ficheiro xml-split.xsl**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%204/arqueoss%C3%ADtios-nodeJS/xml-split.xsl) - *Stylesheet* que permite criar os vários XML para todos os registos dos Arqueossítios.

2. [**Ficheiro arq2html.xsl**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%204/arqueoss%C3%ADtios-nodeJS/arq2html.xsl) - *Stylesheet* que aplique a formatação em HTML para cada ficheiro XML dos registos criados anteriormente.

3. [**Ficheiro servidor.js**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%204/arqueoss%C3%ADtios-nodeJS/servidor.js) - Servidor em ```NodeJS``` que permita estabelecer a ligação entre o Cliente e Servidor, respondendo aos pedidos no URL do *browser*.

4. **Ficheiros Extra** - Ficheiros que adicionam algum interesse/funcionalidade ao trabalho de casa.
   
      4.1. [**Ficheiro paginaErro.html**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%204/arqueoss%C3%ADtios-nodeJS/paginaErro.html) - Página simples em HTML que é acionada quando o pedido ao servidor for incorreto.
      
      

**Além destes ficheiros, é feita a continuidade dos ficheiros PR.xml e PR.html.**

---

## Dificuldades do TPC

Este trabalho de casa foi o mais difícil de resolver durante todo este processo contínuo de aprendizagem, dado que não pude comparecer na aula prática e foi necessário pesquisar sobre como os servidores em ```NodeJS``` funcionam - mais especificamente entender o módulo de rede HTTP que serve para criar *web applications* no ```NodeJS```.

Apesar de ser uma tecnologia nova e desconhecida para mim, a quantidade de informação *online* facilitou a instrução sobre o assunto e foi suficente para resolver o problema proposto.
