# Pergunta 2

## Pergunta 2.1

Como podemos ver pelos tempos apresentados de seguida, concluimos que à medida que aumentos o grau de dificuldade, o tempo de minerar a blockchain aumenta de forma significativa, havendo tendência que a diferença de tempo existente entre graus de dificuldade mais elevados seja cada vez maior.

* Dificuldade 2: 0,594s
* Dificuldade 3: 0,667s
* Dificuldade 4: 2,122s 
* Dificuldade 5: 26,295s
* Dificuldade 6: 7m 18s

Isto acontece uma vez que à medida que o nível de dificulade vai aumentando, torna mais elevado o grau de resolução do **puzzle** computacional, que serve de *proof of work*, de forma a os *mineiros* poderem publicar primeiro o próximo bloco da blockchain.

## Pergunta 2.2

### 1
O algoritmo de *proof of work* utilizado na expriência 2.2 começa por iniciar um contador tendo em conta o útlimo *proof of work* realizado. De seguida, se esse contador não for divisível por 9 e pelo último *proof of work* em simultâneo, o valor desse contador é atualizado sendo acresecentado uma unidade a cada iteração. Quando esta condição se verificar pode ser adicionado o respetivo bloco à blockchain.

### 2
O algoritmo descrito na pergunta acima não é mais indicado para *minerar* uma vez que é visível uma depêndencia entre provas de blocos que se encontram consecutivamente. Posto isto o *mineiro* que publicou o útlimo bloco pode levar uma certa vantagem em relação ao outros na publicação do próiximo bloco, uma vez que pode *pré-computar* os próximos valores do *proof of work*. 
