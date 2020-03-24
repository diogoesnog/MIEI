# Trabalho Prático 8 - 29/Abr/2019

## 1. Buffer Overflow

### Pergunta P1.1 - Buffer overflow em várias linguagens

O programa `LOverflow2`, escrito em Java, Python e C++, começa por solicitar a introdução de quantos números se pretende indicar. De seguida, são lidos e armazenados num *array* estático, com 10 posições, tantos números quantos os especificados.

O problema deste programa centra-se na ausência de verificação do primeiro valor inserido, isto é, se a quantidade de números que se pretende indicar é inferior ou igual a 10. Para além disso, nem sequer é validado se o *input* introduzido corresponde a um inteiro.

Assim, consideraram-se várias situações que pudessem representar as vulnerabilidades do programa, nas várias linguagens:

1. Inserção de uma quantidade de números muito superior a 10;
2. Inserção de uma quantidade de números negativa;
3. Inserção de um número, cujo valor é muito grande, podendo causar *overflow* de inteiros;
4. Inserção de letras, em vez de números;
5. Tentativa de invocação de funções (no caso da linguagem Python).

Relativamente ao programa escrito em **Java**, verificou-se que nos casos de inserção de valores muito elevados ou com *inputs* não inteiros (o que inclui invocação de funções), é lançada uma exceção. Para além disso, quando é inserida uma quantidade de números negativa, não é solicitado nenhum valor. O *output* gerado pelo programa Java para estas situações é apresentado na imagem que se segue.

![P1_1_Java](./images/P1_1_Java.PNG)

Quanto ao programa escrito em **Python**, continuou a verificar-se o lançamento de exceções no caso da introdução de inteiros demasiado elevados (*overflow*). Na introdução de uma quantidade de números negativa, ainda se constatou que simplesmente não era solicitado nenhum valor.

Um aspeto preocupante que se verifica com o recurso à função `input` do Python, é que a expressão lida do *stdin* é executada, como se de um script se tratasse. Assim, a introdução de `1+1` é equivalente à introdução do *input* `2`.

Todas estas experiências são apresentadas na imagem que se segue.

![P1_1_Python](./images/P1_1_Python.PNG)

De forma a explorar a vulnerabilidade associada à utilização da função `input`, optou-se por acrescentar uma função `segredo` ao *script*, que simplesmente imprime uma mensagem secreta:

```python
def segredo():
    print 'SEGREDO'

tests=[None]*10
count = input("Quantos numeros? ")
for i in range (0,count-1):
    test = input ("Insira numero: ")
    tests[i]=test
```

Sem efetuar qualquer alteração ao restante programa, conseguiu-se imprimir no terminal a mensagem secreta, conforme apresentado na imagem que se segue.

![P1_1_Python_result](./images/P1_1_Python_change_result.PNG)

Por fim, para o programa escrito em **C++**, verificou-se que a inserção de uma quantidade de números ligeiramente superior ao suportado (10), faz com que de seguida sejam solicitados mais valores do que o indicado. Caso se introduza uma quantidade de números bastante superior, o programa começa a solicitar a inserção de números repetidamente, sem parar, conforme se pode verificar na figura apresentada de seguida.

![P1_1_CPP_01](./images/P1_1_cpp_01.PNG)

A introdução de uma quantidade de números negativa continua a ter o mesmo resultado que para as restantes linguagens, isto é, não é solicitada a inserção de nenhum valor.

![P1_1_CPP_02](./images/P1_1_cpp_02.PNG)

Após indicação de uma quantidade de números válida, caso se introduza um valor que cause *overflow*, as restantes solicitações de valores são impressas e o programa termina, sem introdução de mais qualquer *input* por parte do utilizador.

![P1_1_CPP_03](./images/P1_1_cpp_03.PNG)

Quando se introduzem *inputs* não inteiros, obtêm-se os resultados apresentados na imagem abaixo. Caso se indique uma quantidade de números válida, seguida da introdução de uma letra, por exemplo, ocorre uma situação semelhante à introdução de um número que cause *overflow* nesta fase. Caso se insira essa letra na quantidade de números, simplesmente não é solicitada a introdução de nenhum valor.

![P1_1_CPP_04](./images/P1_1_cpp_04.PNG)


### Pergunta P1.2 - Buffer overflow em várias linguagens

O programa `LOverflow3` tem o seguinte algoritmo:

1. Inicializa um *array*/lista `vals` de inteiros com um tamanho de 10.
2. Lê um número `count` que determina a quantidade de valores que será guardado no *array*.
3. Preenche `vals` com o `count` elementos.
4. Lê um número `which` e imprime o valor `vals[which]`.

No caso do programa em Java, a proteção interna contra ataques de *buffer overflow* faz com que quaisquer tentativas de acesso à memória exterior a `vals` resulte no levantamento de uma exceção:

![LOverflow3.java](./images/P1_2_Java.PNG)


No caso do programa em Python, não é possível obter dados exteriores aos limites da lista. Ainda assim, é possível extrair valores de defeito em casos nos quais a lista não é preenchida por completo, bem como instruir o programa a preencher a lista por ordem inversa:

![LOverflow3.py](./images/P1_2_Python_01.PNG)


![LOverflow3.py](./images/P1_2_Python_02.PNG)


No caso do programa em C++, devido à falta de mecanismos de proteção contra este tipo de ataque, é possível explorar o algoritmo de modo a extrair dados exteriores ao *array*: 

![LOverflow3.cpp](./images/P1_2_cpp.PNG)


### Pergunta P1.3 - Buffer overflow

O programa `RootExploit.c` tem o seguinte algoritmo:

1. Lê uma *password* através da função `gets`.
2. Compara o valor lido com a string `"csi1"`.
3. Se for igual então a variável `pass` ficam com o valor 1.
4. Se `pass` for 1, então tem-se permissões de *root*/*admin*.

O problema reside na utilização da função `gets`, uma vez que esta não verifica o tamanho do input e o compara com o tamanho alocado para a variável que vai armazenar esse *input*. Desta forma, dado que `buff` é um array de 4 posições e a última está ocupado pelo `\0`, apenas se pode introduzir 3 caracteres. No entanto, se o utilizador continuar a escrever o programa continua a escrever para lá dos limites do `buff`.

Assim sendo, se se tiver em conta a organização das variáveis em memória, é possível subverter o comportamento do algoritmo. As variáveis são armazenadas em memória da seguinte forma:

```
    STACK
+----------+ <- Endereço de memória maiores
|   ....   |
+----------+
|   pass   |
+----------+
| buff[4]  |
+----------+
|   ....   |
+----------+ <- Endereço de memória menores
```

Desta forma, se se continuar a escrever no `buff` para além dos seus limites, começa-se a escrever na variável `pass` e a alterar o seu valor. A seguinte figura mostra isso mesmo:

![RootExploit](./images/P1_3_RootExploit.PNG)

Na prática, a porção do input `123` preencheu as 3 primeiras posições do `buff`. O valor `4` escreveu por cima do `\0` e por fim o último `1` escreveu na variável `pass`. Assim, apesar da `password` estar errada, a variável `pass` ficou a `1` e obteve-se privilégios de *root*/*admin*.

---

O programa `0-simple.c` tem o seguinte algoritmo:

1. A variável `control` é inicializada a `0`.
2. É lida uma *password* através da função `gets`.
3. Se a variável `control` for diferente de `0`, ganha-se.

Da mesma forma, este programa utiliza a função `gets` que não é segura como já foi referido anteriormente. Assim é possível através da variável `buffer` corromper a memória e escrever na variável `control`. As variáveis são armazenadas em memória da seguinte forma:

```
    STACK
+------------+ <- Endereço de memória maiores
|    ....    |
+------------+
|  control   |
+------------+
| endereço?  |
+------------+
| buffer[64] |
+------------+
|    ....    |
+------------+ <- Endereço de memória menores
```

Assim sendo, foi possível explorar a vulnerabilidade oferecida pela função `gets`, da seguinte forma:

![0-simple](./images/P1_3_0_simple.PNG)

A resposta envolve inserir um `input` com um tamanho 77. Os primeiros 64 caracteres servem para encher o array `buffer` inclusive a última posição que é do `\0`. Os próximos 12 caracteres (TODO: acabar). Por fim, o último caractere vai preencher a variável control e torná-la diferente de 0.


> DÚVIDA: 64 bytes (buffer) + 12 bytes => control

bc &control
   endereço?
70 &buffer

### Pergunta P1.4 - Read overflow

O programa `ReadOverflow.c` tem o seguinte algoritmo:

1. Lê uma quantidade de caracteres através da função `fgets`.
2. Converte o valor lido para inteiro (`n`) através da função `atoi`.
3. Lê uma frase através da função `fgets`.
4. Imprime os primeiros `n` caracteres presentes no *buffer* (o próprio, se for imprimível, e um '.', caso contrário).
5. Regressa a 1.

A utilização da função `fgets` já efetua uma validação do tamanho do *input* introduzido, sendo lido apenas tantos caracteres quantos puderem ser armazenados no *buffer* associado.

Contudo, o valor introduzido no passo `1` deve ser um inteiro, o que não é validado neste programa. A utilização da função `atoi` faz com que só seja lido os inteiros no início do *input*, antes de qualquer caracter não numérico. Assim, se for introduzida uma letra, por exemplo, o inteiro ficará com o valor 0.

A introdução de um inteiro negativo para o número de caracteres fará com que sejam impressos 0 caracteres da frase.

Tendo estes fatores em consideração, consegue-se perceber os *outputs* gerados pelo programa para alguns *inputs* básicos, apresentados na imagem que se segue.

![RootExploit](./images/P1_4_ReadOverflow_simple.PNG)

Nenhum destes comportamentos é considerado de risco, tendo em conta que não é possibilitada a introdução de conteúdo fora do espaço alocado nem o acesso indevido a dados.

No entanto, como o *buffer* não é limpo e o número de caracteres indicado não é comparado com o tamanho da *string* inserida, há a possibilidade de ocorrência de um *read overflow*. Isto é, consegue-se ler conteúdo de zonas do *buffer* que não foram escritas pela frase inserida, mas sim por outras anteriores. Este caso é demonstrado na figura que se segue.

![RootExploit](./images/P1_4_ReadOverflow.PNG)


### Pergunta P1.5

O programa `1-match.c` tem o seguinte algoritmo:

1. Lê uma *string* como argumento da linha de comandos durante o arranque do programa.
2. Inicializa a variável *integer* `control` a 0.
3. Copia o argumento da linha de comandos para o *array* `buffer` através da função `strcpy`.
4. Compara o valor da variável `control` com o valor hexadecimal `0x61626364`.
5. Se for igual então o programa mostra uma mensagem `congratulations`.
6. Senão, mostra uma mensagem `try again` e demonstra o valor de `control`.

O problema reside na utilização do método utilizado com o programa `0-simple.c` em conjunto com um conjunto de carateres cujo valor inteiro corresponda a `0x61626364`. Deste modo, é introduzido o argumento na linha de comandos de modo a que este preencha o `buffer` e sobreponha o valor do `control` quando é chamada a função `strcpy`. 

Para tal, verificou-se os valores hexadecimais dos carateres ASCII, determinando-se que os valores `0x61`, `0x62`, `0x63` e `0x64` correspondem aos carateres `a`, `b`, `c` e `d`, respetivamente. Sabendo isto, foi apenas necessário determinar o *endianness* da máquina virtual. Utilizando o próprio programa para tal, observou-se que este guarda os dados no modo *little-endian*, no qual os dados são armazenados por ordem inversa. Como tal, a resposta envolve inserir um argumento de tamanho 80, no qual os últimos 4 carateres são a sequência `dcba`

Assim sendo, foi possível explorar a vulnerabilidade oferecida pelo programa da seguinte forma:

![1-match](./images/P1_5_1match.PNG)

## 2. Vulnerabilidade de inteiros

### Pergunta P2.1

A vulnerabilidade presente na função `vulneravel` está relacionada com a realização de operações com `size_t` (inteiros positivos) sem verificar possíveis situações de *overflow*/*underflow*.

Assim sendo, uma possível execução que origina uma situação de *overflow* é a seguinte:

```c
void vulneravel (char *matriz, size_t x, size_t y, char valor) {
    int i, j;

    matriz = (char *) malloc(x*y);

    printf("HERE\n");

    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            matriz[i*y+j] = valor;
        }
    }
}

int main() {
    char *matriz;
    printf("Tamanho da matriz: %zu\n", SIZE_MAX*SIZE_MAX);
    vulneravel(matriz, SIZE_MAX, SIZE_MAX, '1');
    return 0;
}
```

O resultado obtido é o seguinte:

![Overflow](./images/P2_1_result.PNG)

Na prática apenas se aloca espaço para um `char` na variável `matriz` que fica preenchido pelo `\0` por ser uma string. Tendo em conta que o `SIZE_MAX` é o valor máximo que um `size_t` pode tomar, quando no `malloc` se faz `x*y` (`SIZE_MAX*SIZE_MAX`), origina-se um *overflow* e o resultado da operação é 1. No entanto, quando se vai a preencher a `matriz` nos ciclos `for` endereça-se posições para lá dos limites da variável `matriz`, pois as variáveis `x` e `y` são valores enormes.

Por fim, é de salientar que o programa termina em `Segmentation fault` devido ao facto de estar a preencher valores para lá dos limites da `matriz`.

### Pergunta P2.2

A vulnerabilidade presente na função `vulneravel` está, mais uma vez, relacionada com a realização de operações com `size_t` (inteiros positivos) sem verificar possíveis situações de *underflow* (a situação de *overflow* já é considerada).

Assim sendo, uma possível execução que origina uma situação de *underflow* é a seguinte:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_SIZE = 2048;


void vulneravel (char *origem, size_t tamanho) {
    size_t tamanho_real;
    char *destino;
    if (tamanho < MAX_SIZE) {
        tamanho_real = tamanho - 1; // Não copiar \0 de origem para destino
        printf("%zu\n", tamanho_real);
        destino = (char *) malloc(tamanho_real);
        printf("%p\n", destino);
        memcpy(destino, origem, tamanho_real);
        printf("%s\n", destino);
    }
}

int main() {
    char origem[10] = "MENSAGEM";
    vulneravel(origem, 0);
}
```

O resultado obtido é o seguinte:

![Underflow](./images/P2_2_result.PNG)

O que acontece é que, como a função `vulneravel` apenas valida se o argumento `tamanho` não é superior a um valor máximo antes de efetuar operações com o mesmo, quando se define o `tamanho` como sendo 0, a variável `tamanho_real` (`tamanho - 1`) fica com um valor enorme (*underflow*). Contudo, a função `malloc` retorna um apontador nulo, devido à incapacidade de reservar tanto espaço de memória.

Desta forma, quando a função `memcpy` tenta aceder ao apontador `destino` (nulo) para escrever os dados necessários, o programa termina com `Segmentation fault`.
