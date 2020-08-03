# Pergunta 2 - Proof of Work Consensus Model

1. [Pergunta 2.1](#pergunta-21)
    - Análise temporal das diferentes dificuldades do algoritmo **Proof of Work**.

2. [Pergunta 2.2](#pergunta-22)
    - Análise sobre complexidade e segurança do algoritmo **Proof of Work**.

## Pergunta 2.1

Para efetuar esta pergunta o objetivo foi alterar a porção do código do construtor da *Blockchain*, mais concretamente a variável de instância da dificuldade.

```js
class Blockchain{
    constructor(){
        this.chain = [this.createGenesisBlock()];
        this.difficulty = COLOCAR AQUI A DIFICULDADE;
    }
(...)
```
- Dificuldade 2:

```bash
Mining block 1...
Block mined: 007abd29e589b6a35f6107095cbc8a3628b7a8ff9ac5f7a203f79b262fff077e
Mining block 2...
Block mined: 009d3e5e004957e04604a4032cc58a97f33adb6711f93bc7514de8fe4a531a37
Mining block 3...
Block mined: 004bb82a658a99fd8c9f0d40ec9e69d3a441dacb6383242659b1ff8f7b42195b

real    0m0.072s
user    0m0.056s
sys     0m0.024s
```

- Dificuldade 3
```bash
Mining block 1...
Block mined: 0007c25169f5256ebb80fcbb423b582a8e699a759e41abb28906295973f9de4c
Mining block 2...
Block mined: 0004af57b70136e9f4b5309f92d518b3f297168d4cf47d4f9354808daadce457
Mining block 3...
Block mined: 00075796ab77bb5289bb9a952b91047482b3348d54d915ff5e5bce28256d01fe

real    0m0.265s
user    0m0.180s
sys     0m0.108s
```

- Dificuldade 4
```bash
Mining block 1...
Block mined: 0000023168f87d968813b22c4dc92f60c127ff5084af8487d913d497ea7a7900
Mining block 2...
Block mined: 00008e0c291aaf728e015855328b14e651231cce209e6413503fd299e0df6c5e
Mining block 3...
Block mined: 0000fb4a126ef4c1c3c93bf2ed25e8db4c7da2ec89a46aad4f7bf092afd8b6b4

real    0m1.158s
user    0m0.976s
sys     0m0.220s
```
- Dificuldade 5
```bash
Mining block 1...
Block mined: 0000023168f87d968813b22c4dc92f60c127ff5084af8487d913d497ea7a7900
Mining block 2...
Block mined: 000000b950a180294edddf4340a2d5834119a41bf89e4b2027f341f0fc02365e
Mining block 3...
Block mined: 0000088dc9c3115ee6ab7e95d2e8836f932d75d303ab451a825241acde589a58

real    0m15.929s
user    0m13.524s
sys     0m2.660s
```

## Pergunta 2.2

### 1.
O algoritmo **Proof of Work** que foi utilizado foi relativamente simples de entender. Cada *miner* tem que incrementar (1) ao número obtido no **Proof of Work** anterior e assim quando esse número for divisível por 9 (nº de caracteres da palavra *SnakeCoin*) e também divisível pelo número da prova do bloco anterior, será criado um novo bloco e o _mining_ recompensado.

### 2.
Um algoritmo de mineração tem de oferecer ao *miner* um problema intensivo para existir a recompensa e a criação dum novo bloco. Este problema tem de ser difícil de resolver, mas verificável com uma facilidade grande. 

Após fazer algumas tentativas dá para perceber que o padrão deste **Proof of Work** é que todos os números gerados vão ser múltiplos de 9 e assim conseguem divisíveis pela "prova" anterior e consequentemente por 9. A "prova" do próximo bloco será o "próximo" múltiplo de 9, associando assim o resultado de forma determinística com o índice do bloco na *chain*. 

| Índice | **Proof of Work** | Mat  |
| -----  | ------------- | -------  |
|   0    |            9  | 2^0 * 9  |
|   1    |           18  | 2^1 * 9  |
|   2    |           36  | 2^2 * 9  |
|   3    |           72  | 2^3 * 9  |
|   4    |          144  | 2^4 * 9  |
|   5    |          288  | 2^5 * 9  |

Claro que a fatorização é algo complexo computacional, mas só quando o número de blocos seja bem grande (índice) de forma a ser díficil fatorizar esse número. Daí o algoritmo **não é válido** porque é previsível tanto os números anteriores como os futuros através do índice. (Isto assumindo-se que o algoritmo é conhecido).