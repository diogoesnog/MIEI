# Trabalho Prático 8 - Resolução

## 1. Buffer Overflow

#### Pergunta P1.1

Executando o mesmo programa escrito em Java (LOverflow2.java), Python (LOverflow2.py) e C++ (LOverflow2.cpp), obtêm-se os seguintes resultados:

![Java](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_1/javaP1.png)

<p align="center">
  Java
</p>

![Python](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_1/pythonP1.png)

<p align="center">
  Python
</p>


![C++](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_1/cP1.png)

<p align="center">
  C++
</p>

Analisando o programa verifica-se que este começa por criar um *buffer* de tamanho 10 e recebe como input o número de números que queremos inserir nesse *buffer*. No entanto, ao executar o programa nas diferentes linguagens este comporta-se de forma distinta.

Note-se que quando executado em Java ou em Python, o comportamento do programa é análogo, pelo que a descrição do que acontece serve para ambas as linguagens. Tanto em Java como em Python, quando se insere um input que seja superior a 10, por exemplo 12, ao tentar escrever o 11º número no *buffer*, o programa dá erro uma vez que se está a tentar escrever numa posição da memória que não pertence ao *buffer*.

Por outro lado, quando executamos o programa em C++ o mesmo não se verifica. Verifica-se que ao se inserir o valor 12 como input, o programa permite que sejam inseridos 12 números, sendo que os primeiros 10 números são escritos no *buffer* e os restantes subrescrevem a memória adjacente ao *buffer*.

#### Pergunta P1.1

Executando o mesmo programa escrito em Java (LOverflow2.java), Python (LOverflow2.py) e C++ (LOverflow2.cpp), obtêm-se os seguintes resultados:

![Java](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_2/javaP1.png)

<p align="center">
  Java
</p>

![Python](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_2/PythonP1.png)

<p align="center">
  Python
</p>


![C++](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_2/cP1.png)

<p align="center">
  C++
</p>


Analisando o programa verifica-se que este começa por criar um *buffer* de tamanho 10 (em Java e em C++ o *buffer* é preenchido com 0's e, no caso, do Python o *buffer* é preenchido com *None*) e recebe como input o número valores que se quer guardar no array criado. No entanto, ao executar o programa nas diferentes linguagens este comporta-se de forma distinta.

Quando executamos o programa em Java e em Python este apresenta um comportamento semelhante. Como podemos analisar pelas imagens acima, conclui-se que ao tentar guardar no array mais do que 10 valores, o programa dá erro. No entanto, este comporta-se de forma normal se se quiser inserir valores iguais ou inferiores a 10. Note-se ainda que quando se guardam 10 valores no array e se tenta recuperar um valor na posição 11, por exemplo, o programa dá erro.

Relativamente ao programa C++, se inserir o valor 13 como input o programa fica em modo de espera, os restantes 3 casos são análogos aos respetivos casos nos programas Java e Python. Note-se ainda que, quando se pretendem guardar 10 valores no array e se tenta recuperar o 20º valor, o programa retorna um valor da memória adjacente.


#### Pergunta P1.3

![Root](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_3/Root.png)

<p align="center">
  RootExploit
</p>

No programa RootExploit.c a vulnerabilidade de *Buffer Overflow* está relacionada com o facto do *buffer* criado ter apenas 4 bytes e permitir *inputs* de tamanho maior. Deste modo, para explorar a vulnerabilidade existente basta inserir um *input* com, pelo menos, 5 caracteres.

![0-simple](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_3/0-simple.png)

<p align="center">
  0-simple
</p>

Relativamente ao programa 0-simple.c, a vulnerabilidade de *Buffer Overflow* está relacionada com o facto do *buffer* criado ter apenas 64 bytes e permitir *inputs* de tamanho maior. Deste modo, para explorar a vulnerabilidade existente, e obter a mensagem "YOU WIN", basta inserir um *input* com, pelo menos, 65 caracteres.


#### Pergunta P1.4

Testanto o programa escrito em C ReadOverflow.c, obtém-se os seguintes resultados:

![pergunta1_4](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_4.png)

<p align="center">
  Resultados Obtidos
</p>

Tendo em conta os resultados acima apresentados, pode concluir-se que o programa executado permite recuperar informação que estava guardada, anteriormente, no *buffer*.

A vulnerabilidade pode ser corrigida se o número de caracteres inseridos como input (*Insira numero de caracteres*) for sempre igual ao número de caracteres que são inseridos no input seguinte (*Insira frase*), para tal o programa apenas tem de verificar essa igualdade.


#### Pergunta P1.5

Após análise do programa 1-match.c, concluiu-se que para explorar a vulnerabilidade existente usamos o facto do sistema UNIX ser um sitema little-endian e, portanto, o byte menos significativo é colocado no endereço de memória mais baixo. Deste modo, para explorar a vulnerabilidade preenchemos a memória do *buffer* com 76 caracteres de 'lixo', acrescentando no final a sequência 'dcba', uma vez que esta sequência corresponde ao valor '64636261' em hexadecimal.

![solução](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P1_5.png)


## 2. Vulnerabilidade de inteiros

#### Pergunta 2.1
1. 
Podemos verificar que a função _malloc_ aloca espaço para um bloco de bytes consecutivos. No caso da função _vulneravel_, é possível ver que o tamanho da memória alocada é _x*y_. No entanto, x e y são variáveis do tipo _size_t_, cujo limite máximo é 18446744073709551615. Assim, caso sejam dados como input valores de x e y cujo produto é superior a este limite máximo, ocorre um **overflow de inteiros**.
É, então, possível manipular os valores de x e y de forma a que _x*y_ dê um valor baixo, fazendo com que, ao percorrer o ciclo sobre **i** e **j**, tente aceder a posições que estão fora da memória disponível para a matriz.

2.
![pergunta2_1 alteração do main()](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P2_1/main().png)

3. 
Ao executar a função _vulneravel_ com as alterações feitas no main(), obtemos o erro _Segmentation fault_.

![pergunta 2_1 segmentation fault](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P2_1/segmentation%20failed.png)

#### Pergunta 2.2
1.
No caso do programa **underflow**, a vulnerabilidade da função _variavel()_ reside no input que é dado à variável _tamanho_.
Este programa permite que seja atribuído à variável _tamanho_ o valor 0 e, tendo em conta que a variável _tamanho_real = tamanho - 1_, é assumido o valor -1 pela variável _tamanho_real_, ocorrendo assim **underflow de inteiros**, uma vez que _tamanho_real_ é do tipo _size_t_ e só devia assumir valores maiores que 0.

2.
![pergunta2_2 main()](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P2_1/main()2.png)

3.
Com base na vulnerabilidade acima descrita, o erro _Segmentation fault_ ocorre, pois estamos a tentar alocar a variável _destino_ em tamanho -1.

![pergunta2_2 segmentation fault](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP8/P2_1/Seg%20fault%202.png)
