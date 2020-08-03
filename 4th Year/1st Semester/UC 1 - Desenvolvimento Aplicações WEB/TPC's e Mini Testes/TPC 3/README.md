# TPC 3 - XLST Stylesheets

O processamento de documentos XML por meio de um processador XSLT permite que se transformem os dados e a estrutura do documento em si num novo documento em formato HTML (e não só), através de um conjunto de instruções especificadas num *Stylesheet*. 

---

## Resolução do TPC 3

A ideia deste TPC 3 é precisamente construir uma *Stylesheet* XSLT que possibilite a transformação do XML do Registo de Projetos do TPC 2 para uma página HTML funcional e preparada para os futuros TPCs.
Conjuntamente, espera-se desenvolver outra *Stylesheet* XSLT para o *dataset* dos Arqueossítios, criando-se um *website* constituído por várias páginas identificadas numa espécie de índice.

Assim, numa **primeira parte** espera-se desenvolver:

1. [**Ficheiro PR.xml**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%203/PR.xml) - Registo de Projetos em XML.
2. [**Ficheiro PR.xsl**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%203/PR.xsl) - *Stylesheet* preparado para transformar o RP.xml para uma página HTML.
3. [**Ficheiro PR.html**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%203/PR.html) - Página HTML criada através da combinação dos dois ficheiros anteriores.

Numa **segunda parte**:

1. [**Ficheiro ARQ.xsl**](https://github.com/diogoesnog/DWeb2019/blob/master/TPC%203/Arqueoss%C3%ADtios/arq.xsl) - *Stylesheet* preparado para transformar o XML dos Arqueossítios para uma página HTML.

2. [**Pasta *website***](https://github.com/diogoesnog/DWeb2019/tree/master/TPC%203/Arqueoss%C3%ADtios/website) - Pasta que contém todos os ficheiros HTML dos Arqueossítios.

---

## Dificuldades do TPC

As transformações com XSLT implicam o conhecimento da matéria dada até aqui, tendo em conta que é necessário filtrar a informação do XML através das *queries* XPath praticadas no TPC anterior.

Isto tudo surge numa nova linguagem, que necessita ser treinada/praticada até se ter um domínio suficiente sobre a mesma. É esse o grande obstáculo deste TPC - utilizar a nova linguagem XSLT desde o processo de processamento da informação até ao HTML "bonito" à vista do utilizador.