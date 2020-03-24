# Trabalho Prático 6 - 1/Abr/2019

## 1. Vulnerabilidade de codificação

### Pergunta 1.1 - 1

Considerando que o SO Linux 3.1, o Facebook e a Google tratam-se de *sofware* dito normal, em contraste com o *car software*, que recorre a métodos de desenvolvimento rigorosos. Assim, para o primeiro caso, considerar-se-ão 50 *bugs* por cada 1 000 SLOC, enquanto que para o segundo se considerarão 5.

Através do *website* [Information is beautiful](https://informationisbeautiful.net/visualizations/million-lines-of-code/), cada um dos *softwares* tem os seguintes valores de SLOC:

+ Linux 3.1 - 15 milhões SLOC
+ Facebook - 62 milhões SLOC
+ Car software - 100 milhões SLOC
+ Google - 2 mil milhões SLOC

Aplicando os valores definidos para o número de *bugs* por 1 000 SLOC, obtêm-se as seguintes estimativas:

+ Linux 3.1 - 750 mil *bugs*
+ Facebook - 3 100 mil *bugs*
+ Car software - 500 mil *bugs*
+ Google - 100 milhões *bugs*

### Pergunta 1.1 - 2

Não é possível estimar quantos dos *bugs* previamente calculados corresponderão a vulnerabilidades.

### Pergunta 1.2

Vulnerabilidades do projeto:

1. Limitação do acesso aos dados do utilizador associado e, no entanto, não implementar um mecanismo de cifra dos dados. A correção deste problema envolve a implementação de um mecanismo de cifra, ação que apresenta um nível de dificuldade reduzido.
2. Armazenamento de uma *password* em texto limpo para posterior autenticação do utilizador. Para resolver este problema, é recomendado o armazenamento de um valor de *hash* da *password* cuja derivação, recorrendo a bibliotecas criptográficas, é uma tarefa trivial.

Vulnerabilidades de codificação:

1. Transmissão de dados em texto limpo. A correção deste problema passa pela implementação de um mecanismo de cifra, ação que apresenta um nível de dificuldade reduzido.
2. Possibilidade de ocorrência de *overflow* na introdução de *input*. Para solucionar este problema, basta validar o tamanho do *input* introduzido antes de o ler/armazenar, o que é muito simples de se implementar.

Vulnerabilidades operacionais:

1. Configuração deficiente de um servidor *web*, onde não é restrito o acesso do utilizador a diretorias externas ao serviço. A correção deste problema passa por configurar o servidor de forma a validar o acesso, tendo em conta os mecanismos de autenticação e permissão implementados, o que deverá ser uma tarefa simples.
2. Coexistência do *software* com serviços/programas com vulnerabilidades. Para tentar resolver este problema, deve-se efetuar um levantamento das vulnerabilidades existentes no sistema, bem como corrigir a máxima quantidade possível das mesmas, dando prioridade às de maior risco. O grau de dificuldade desta solução varia com a quantidade e tipo de vulnerabilidades encontrado, sendo que, no limite, pode nem ser exequível resolver todas as vulnerabilidades.


### Pergunta 1.3

A diferença entre uma vulnerabilidade de dia zero e uma que não seja de dia zero centra-se nas entidades que possuem conhecimento sobre a existência da mesma. Enquanto que no primeiro caso a vulnerabilidade só é conhecida num meio restrito, no segundo é conhecida na comunidade de segurança informática, isto é, por todas as partes interessadas em corrigi-la.

Assim, uma vulnerabilidade de dia zero é uma falha na segurança de um *software*, que ainda não é conhecida pelos desenvolvedores do mesmo, os fabricantes de antivírus ou o público em geral.

As vulnerabilidades de dia zero podem ser utilizadas por grupos de piratas informáticos para efetuar ataques de forma sigilosa ou vender na *dark web*, bem como no meio militar de um país (ciber-armas).
