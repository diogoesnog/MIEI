# Trabalho Prático 5 - Resolução

## 1. Blockchain

### Pergunta 1.1

Com o intuito de na criação do *Genesis Block*, o timestamp ser a data do dia de hoje e o dado incluído nesse Bloco ser "Bloco inicial da koreCoin", efetuaram-se algumas alterações no código disponibilizado. O código alterado encontra-se na [diretoria P1_1](https://github.com/uminho-miei-engseg-18-19/Grupo1/tree/master/TP5/P1_1).

### Pergunta 1.2

A adição de alguns blocos simulando várias transações em cada um deles encontra-se também da diretoria mencionada acima.

### Pergunta 1.2

## 2. Proof of Work Consensus Model

### Pergunta 2.1

![Dificuldade2](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP5/P2_1/P2_1_dificuldade2.png)


<p align="center">
  Dificuldade 2
</p>

![Dificuldade3](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP5/P2_1/P2_1_dificuldade3.png)

<p align="center">
  Dificuldade 3
</p>

![Dificuldade4](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP5/P2_1/P2_1_dificuldade4.png)

<p align="center">
  Dificuldade 4
</p>

![Dificuldade5](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP5/P2_1/P2_1_dificuldade5.png)

<p align="center">
  Dificuldade 5
</p>

O mecanismo de *Proof of Work* utilizado na experiência 2.1 consiste na difícil resolução de um puzzle Matemático. No caso do mecanismo utilizado na experiência anterior, a resolução do puzzle consiste em encontrar um valor de hash que comece com um determinado números de 0’s, sendo a quantidade de 0’s que são necessários encontrar que ditam a dificuldade de resolução do puzzle.

Assim, tendo em conta o mecanismo de *Proof of Work* adotado e analisando os resultados obtidos, conclui-se que à medida que se aumenta a dificuldade de minerar (ou seja, à medida que aumenta o número de 0’s da hash), o tempo de resolução do puzzle aumenta, o que era de esperar. 

Note-se que o trabalho colocado num determinado *puzzle* não influência a probabilidade de resolver os *puzzles* atuais ou futuros, uma vez que estes são independentes.

### Pergunta 2.2

1. Na experiência anterior, o algoritmo de *Proof of Work* utilizado consiste em: dado o valor que resolveu o último puzzle incrementá-lo de modo a obter-se, simultaneamente, um múltiplo de 9 e desse mesmo número.

2. O algoritmo implementado não parece ser o mais adequado, uma vez que não é possível definir o grau de dificuldade da resolução do puzzle (tal como se pode fazer no código analisado na pergunta anterior), pois o número de prova para a resolução do puzzle vai sendo cada vez maior e, como tal, vai sendo cada vez mais difícil encontrar um número múltiplo de 9 que seja também múltiplo do número de prova. Note-se ainda que, no caso deste algoritmo, a resolução de um determinado puzzle irá sempre depender do *puzzle* anterior, o que não acontecia no mecanismo de *Proof of Work* da pergunta anterior. O que significa que a resolução de um puzzle depende do puzzle anteriormente resolvido.
