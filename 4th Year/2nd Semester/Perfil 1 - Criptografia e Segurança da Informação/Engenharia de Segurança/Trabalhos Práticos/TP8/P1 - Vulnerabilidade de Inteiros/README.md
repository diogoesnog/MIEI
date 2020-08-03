# Pergunta 1 - Vulnerabilidade de Inteiros

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Pergunta P1.1**](#pergunta-p11---overflow-numa-matriz-em-c) - ***Overflow* numa matriz em C**
   - Mudança do código C
   - Compreensão do resultado do programa

2. [**Pergunta P1.2**](#pergunta-p12---underflow-em-código-c) - ***Underflow* em código C**
   - Mudança do código C
   - Compreensão do resultado do programa
   - Utilização de técnicas de programação defensiva para mitigação das vulnerabilidades

---

## Resolução da Pergunta 1

### Pergunta P1.1 - *Overflow* numa matriz em C

<p>

#### 1. Deteção da vulnerabilidade da função *vulneravel()* e seus efeitos

O problema deste código vulnerável é a utilização do `typedef size_t` sem confirmação dos tamanhos do mesmo podendo causar *underflow/overflow* dos números.

<p>

#### 2. Explorar o *main()* de modo a demonstrar essa vulnerabilidade

Para tentar resolver o problema podemos mudar a função `main()` para:

```C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void vulneravel (char *matriz, size_t x, size_t y, char valor) {
    int i, j;
    matriz = (char *) malloc(x*y);

    printf("Teste para ver se chega aqui\n");
    
    for (i = 0; i < x; i++) {
            for (j = 0; j < y; j++) {
                    matriz[i*y+j] = valor;
            }
    }
}

int main() {
    
    char *mat;
    printf("Tamanho da matriz é: %zu\n", SIZE_MAX*SIZE_MAX);
    vulneravel(mat, SIZE_MAX, SIZE_MAX, '5');
    return 0;

}
```

Utilizando a *macro* definida no *header* `<stdint.h>` intitulada de `SIZE_MAX` podemos obter o valor máximo que um `size_t` pode tomar na máquina e compilador em questão, logo quando na função `vulneravel()` acontece o `malloc` fazendo $x*y \equiv SIZE\_MAX*SIZE\_MAX$, acontece um **overflow** e o resultado fica apenas 1. De seguida, vai-se preencher a matriz com endereçamentos e posições para lá dos limites, dado que as variáveis `x` e `y` são valores enormes e dessa forma o programa sofre um *Segmentation Fault*.

<p>

#### 3. Executar o programa depois da alteração e verificar possíveis erros

Conforme se verifica pelo *output* apresentado a seguir, acontece um erro de segmentação.

<p align = "center">
	<img src = "Images/Output Programa Overflow.png"/>
</p>
---

### Pergunta P1.2 - *Underflow* em código C

<p>

#### 1. Deteção da vulnerabilidade da função *vulneravel()* e seus efeitos

A vulnerabilidade detetada para o ficheiro `underflow.c` trata-se também (como acontecia no ficheiro `overflow.c`) da utilização do `typedef size_t` sem a confirmação dos tamanhos do mesmo podendo causar *underflow* dos números.

<p>

#### 2. Explorar o *main()* de modo a demonstrar essa vulnerabilidade

Para tentar resolver o problema podemos mudar a função `main()` para:

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_SIZE = 2048;


void vulneravel (char *origem, size_t tamanho) {
        size_t tamanho_real;
        char *destino;
        if (tamanho < MAX_SIZE) {
                tamanho_real = tamanho - 1; // Não copiar \0 de origem para destino
                destino = malloc(tamanho_real);
                memcpy(destino, origem, tamanho_real);
        }
}

int main() {
    char origem[5] = "Teste";
    vulneravel(origem, 0);
}
```

Esta mudança vai permitir então demonstrar a vulnerabilidade presente neste código, dado que força a que o valor da variável `tamanho_real` atinja um valor gigante, aplicando-se então o princípio do *underflow*. 

**Note-se que ao colocar o valor do parâmetro `tamanho` da função `vulneravel` como sendo 0, acontece o seguinte:**

- Valor da variável `tamanho` é dado como sendo 0;
- Valor da variável `tamanho_real` atingirá um valor muito grande, criando toda uma situação de *underflow*, dado que o seu cálculo consiste em subtrair ao valor de `tamanho` uma unidade;
- Função `malloc` retornará um apontador nulo, tendo em conta que não existe capacidade para reservar um espaço de memória tão grande quanto o declarado para o `tamanho_real`;
- Função `memcpy` tentará aceder a um apontador nulo, o que levará a uma situação de `Segmentation fault`.

<p>

#### 3. Executar o programa depois da alteração e verificar possíveis erros

O *output* torna a comprovar um erro de segmentação, dado que o programa tentou manipular dados numa variável nula.

<p align = "center">
	<img src = "Images/Output Programa Underflow.png" width = 50%/>
</p>


<p>

#### 4. Técnicas de programação defensiva para mitigar as vulnerabilidades

Depois de se ter entendido como todo o programa está a funcionar, fica clara a forma como a vulnerabilidade pode ser explorada e consequentemente mitigada. Pensando no erro em si, apenas foi necessário introduzir uma nova variável de nome `MIN_SIZE` que fizesse o controlo dos valores nulos que a variável pode assumir.

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MIN_SIZE = 0;
const int MAX_SIZE = 2048;

void vulneravel (char *origem, size_t tamanho) {
        size_t tamanho_real;
        char *destino;
        if (tamanho < MAX_SIZE && tamanho > MIN_SIZE) {
                tamanho_real = tamanho - 1; // Não copiar \0 de origem para destino
                destino = malloc(tamanho_real);
                memcpy(destino, origem, tamanho_real);
        }
}

int main() {
    char origem[5] = "Teste";
    vulneravel(origem, 0);
}
```

Desta forma, o programa é capaz de fazer uma filtragem dos valores que a variável `tamanho` pode efetivamente conter. Neste caso, verifica se esse `tamanho` está compreendido entre 0 e `MAX_SIZE` e só dessa forma é capaz de fazer todo o restante do processo. Caso não se cumpra esse requisito, o programa simplesmente não devolve nada.

---

## Notas/Observações Finais

- Imagem [**Output Programa Overflow**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP8/P1%20-%20Vulnerabilidade%20de%20Inteiros/Images/Output%20Programa%20Overflow.png) que demonstra o *output* do programa `overflow.c`.
- Imagem [**Output Programa Underflow**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP8/P1%20-%20Vulnerabilidade%20de%20Inteiros/Images/Output%20Programa%20Underflow.png) que demonstra o *output* do programa `underflow.c`.
