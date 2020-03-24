# Pergunta 1.1

O programa **LOverflow2** escrito nas linguagens de programção C++, Python e Java tem o mesmo objetivo nas diferentes linguagens, que consiste em armazenar um certa quantidade de números num *array*. Posto isto em todas as suas implementações o programa começa por alocar memória estática para 10 inteiros. Posteriormente é pedido para indicar a quantidade de inteiros que cada *user* quer guardar.

O problema das implementações nas diversas linguagens foca-se exatamente no momento da inserção da quantidade que pretendemos guardar, onde o valor que é inserido pelo *user* não é verificado. 

Posto isto existem diversos casos que devemos considerar, o caso de o valor inserido não ser um inteiro, ou caso o valor colocado seja inteiro negativo o programa é abortado, em todos os casos. Existe ainda o caso de o inteiro introduzido ser superior 10, neste caso surgem mensagens de erros diferentes de acordo com a linguagem respetiva.

No caso da implementação em *C++* ao inserir mais 10 números, que é o valor limite do tamanho do *array*, o programa é abortado, dando o erro de **stack smashing detected**. Por sua vez a quando do teste na linguagem java, o programa é abortado com a produção da seguinte mensagem  **Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException: 10**. Por fim na linguagem Python, o programa é abortado com a seguinte mensagem  **IndexError: list assignment index out of range**. 

# Pergunta 1.2

Nesta questão o programa **LOverflow3** tal como na questão anterior em cima, permite guardar uma certa quantidade de inteiros. De seguida, este os valores são guardados por ordem decrescente tendo em conta o valor introduzido pelo *user*. Posteriormente, o *user* pode indicar qual a posição do *array* que quer aceder. No entanto surge o mesmo problema que na questão acima, quando o valor inserido é superior a 10, uma vez que não existe verificação do valor inserido e a memória é alocada estaticamente. Existe ainda também o caso de quando o *user* quer aceder a uma posição do array superior ao valor introduzido pelo mesmo, como por exemplo aceder à posição 3 de um *array* que apenas tem duas posições.

Quando estes casos em cima mencionados acontecem, são tratados de maneira diferentes nas diversas linguagens de programação. No caso das linguagem Java, caso o valor introduzido seja maior que 10, é lançada um exceção igual à mencionada na questão acima. Caso aconteca o segundo caso, o valor devolvido é sempre 0.

Quanto à linguagem de programação Python quando o valor inserido é superior 10, é lançada uma exceção que não permite aceder às variáveis não alcadas para o programa, lançado uma exceção como acontece na primeira questão. No entanto, caso o *user* queira aceder a uma posição que superior à definida neste caso o valor retornado é *None*.

No caso da linguagem de programação C++, esta não contem mecanismos de proteção contra este tipo de ataques, pelo que é possível extarair qual tipo de informação sobre os valores presentes na memória.

# Pergunta 1.3

## RootExploit

O programa **RootExploit.c** começa por ler a passowrd inserida pelo *user* através da função *gets*, de seguida compara o valor lido com a *string* **csi1**, caso sejam iguais a variável pass fica com o valor 1, caso contrário fica com o valor com qual foi incializada, neste caso 0. Caso a variável pass tome o valor 1, o *user* fica com permissões *root/admin*

O prolema deste programa econtra-se no uso da função *gets*, uma vez que esta função como é avisado aquando da compilação do programa, é uma função perigosa e que raramente deve ser usada, pois esta não verifica o tamanho do imput inserido e não compara com o tamanho que vai ser da variável a que corresponde esse input. Pelo que dado que o *array* buf é composto por 4 posições, apenas é possível inserir 3 caracteres. Mas tal como podemos comprovar, caso o *user* escreva para além de 3 caracteres, o programa continua a escrever para lá dos limites definidos pelo *array*. Posto isto, é escrito no espaço de endereçamento reservado para a variável pass, podendo assim conseguir as permissões de *root/admin* sem a password inserida estar correta, caso esta variável seja alterada para o valor 1.

## 0-simple

O programa **0-simple.c** começa por inicializar a variável control a 0 e de seguida é lido o input inserido pelo *user* através da função *gets*, tal como no programa anterior e tendo em conta que para ganhar é preciso alterar o valor da variável 0 e tendo em conta a maneira como são armazenadas as variáveis na stack, basta colocar como input uma tamanho máximo de caracteres superiores a 64 bytes. Sendo assim utltrapassa os limites do buffer pondendo ser aletrado a variável control e como consequência aparecer a mensagem "you win".

# Pergunta 1.4

Após a análise do código presnete no ficheiro **ReadOverflow.c** podemos conlcuir que a função começa por ler uma série de caracteres input, através da função *fgets*. De seguida o valor lido, é convertido para inteiro por meio da função *atoi*. Posteriormente lê a frase inserida no input, fazendo por fim *print* dos primeiros n (valor introduzido pelo *user*) caracteres presentes no *buffer*. 

No entanto após os testes realizados ao código, pode-se concluir que se consegue extair informação presente na memória, uma vez que o *buffer* nunca é limpo e o número de caracteres indicado pelo *user* nunca é comparado ao longo do código com o tamanho da frase inserida, pelo que pode haver a ocorrência de *read overflow*, isto consiste em ler o conteúdo do *buffer* que não foi inserido pela frase escrita no momento mas sim por anteriores.

# Pergunta 1.5
O programa **1-matc.c** começa por ler o argumento passado na linha de comandos, de seguida inica variável *control* a 0, e copia o argumento lido para um *buffer*. Por fim a variável *control* é comparado com o valor hexadecimal *0x61626364*, caso este seja igual o jogo é ganho, caso contrário é necessário tentar outra vez.

O problema é idêntico ao já identificado numa das perguntas acima, temos que introduzir como argumento uma quantidade de bytes sufecientes de modo a preencher o tamanho do *buffer* presente no programa, posteriormente temos de verificar a que valores correspondem os valores hexadecimais na tabela *ASCII*, e verifica que correspondem aos caracteres a,b,c,d. Por fim tivemos de verificar como o computador guarda os dados na memória, para isso reccoremos ao comando *lscpu* do terminal linux de forma a verificar, acabou-se por descobir que os guardados são guardados no formato *little-endian*, pelo que a ordem certa seria **dcba**.

Como conclusão o argumento a passar seria o número sufeciente de bytes para preencher o *buffer* juntamente com os caracteres dcba.

# Pergunta 2.1

O problema encontrado durante o programa **overflow.c** está a relacionada com o tamanho dos dados do tipo *size_t* que depois são usados para a realização da alocação de espaço para a matriz. No entanto esta gama de valores tem um valor limitado pelo que se a multiplicação para alocação de memória exceder essa gama de valores ocorre um overflow de inteiros. De modo a explorar essa vulnerabilidade completamos a *main* da seguinte maneira:

```c 
int main() {
        char* matriz;
        printf("Tamanho da matriz: %zu\n", SSIZE_MAX * SSIZE_MAX);
        vulneravel(matriz, SSIZE_MAX, SSIZE_MAX, 'c');
        return 0;
}
```
Após a multiplicação destes valores, irá haver o tal overflow de inteiros, o que fará com que o resultado do tamanho da matriz será 1.

Após a execução do programa, foi possível concluir que houve um erro designado *segmentation fault*.


# Pergunta 2.2
O problema aqui encontrado é o mesmo mencionado na questão 2.2, mas aqui vamos verificar situações de *underflow*, uma vez que as situações de *overflow* não podem acontecer devido ao facto de o *malloc* só acontecer enquanto a condição ```c tamanho < MAX_SIZE ``` se verifica. Uma vez que as variáveis *tamanho* e *tamanho_real* apresentam o mesmo tipo, também não se poderá explorar tirando partido desse ponto de vista. 
No entanto, não existe verificação para valores negativos, pelo que de modo a testar o programa preenchemos a main da seguinte maneira:

```c
int main() {
        
        char origem[3] = "ok";
        vulneravel(origem,0);
}
```

Após a execução do mesmo deparamo nos com o mesmo erro apresentado na pergunta 2.1.