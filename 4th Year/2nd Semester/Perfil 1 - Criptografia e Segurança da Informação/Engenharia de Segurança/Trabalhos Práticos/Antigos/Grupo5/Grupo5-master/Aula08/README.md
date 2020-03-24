# Trabalho Prático 5 - 25/Mar/2019

## 1. Blockchain

### Pergunta 1.1

O código alterado resultante é:

```javascript
createGenesisBlock(){
    return new Block(0, "25/03/2019", "Bloco inicial da koreCoin", "0");
}
```

### Pergunta 1.2

O código alterado resultante é:

```javascript
koreCoin.addBlock(new Block (1, "26/03/2019", {t1: 20, t2: 90, t3: 50}));
koreCoin.addBlock(new Block (2, "26/03/2019", {t1: 40, t2: 1000}));
koreCoin.addBlock(new Block (3, "27/03/2019", {t1: 40, t2: 900, t3: 60}));
```

## 2. Proof of Work Consensus Model

### Pergunta 2.1

O excerto do código que será alterado é:

```javascript
constructor(){
    this.chain = [this.createGenesisBlock()];
    this.difficulty = 6;                        // <------
}
```

Para a dificuldade 2, obtiveram-se os seguintes tempos:
```bash
$ time node main.experiencia2.1.js
Mining block 1...
Block mined: 007abd29e589b6a35f6107095cbc8a3628b7a8ff9ac5f7a203f79b262fff077e
Mining block 2...
Block mined: 009d3e5e004957e04604a4032cc58a97f33adb6711f93bc7514de8fe4a531a37
Mining block 3...
Block mined: 004bb82a658a99fd8c9f0d40ec9e69d3a441dacb6383242659b1ff8f7b42195b

real	0m0.258s
user	0m0.212s
sys	    0m0.012s
```

Para a dificuldade 3, obtiveram-se os seguintes tempos:
```bash
$ time node main.experiencia2.1.js
Mining block 1...
Block mined: 0007c25169f5256ebb80fcbb423b582a8e699a759e41abb28906295973f9de4c
Mining block 2...
Block mined: 0004af57b70136e9f4b5309f92d518b3f297168d4cf47d4f9354808daadce457
Mining block 3...
Block mined: 00075796ab77bb5289bb9a952b91047482b3348d54d915ff5e5bce28256d01fe

real	0m0.887s
user	0m0.812s
sys	    0m0.020s
```

Para a dificuldade 4, obtiveram-se os seguintes tempos:
```bash
$ time node main.experiencia2.1.js
Mining block 1...
Block mined: 0000023168f87d968813b22c4dc92f60c127ff5084af8487d913d497ea7a7900
Mining block 2...
Block mined: 00008e0c291aaf728e015855328b14e651231cce209e6413503fd299e0df6c5e
Mining block 3...
Block mined: 0000fb4a126ef4c1c3c93bf2ed25e8db4c7da2ec89a46aad4f7bf092afd8b6b4

real	0m3.477s
user	0m3.364s
sys	0m0.044s
```

Para a dificuldade 5, obtiveram-se os seguintes tempos:
```bash
$ time node main.experiencia2.1.js
Mining block 1...
Block mined: 0000023168f87d968813b22c4dc92f60c127ff5084af8487d913d497ea7a7900
Mining block 2...
Block mined: 000000b950a180294edddf4340a2d5834119a41bf89e4b2027f341f0fc02365e
Mining block 3...
Block mined: 0000088dc9c3115ee6ab7e95d2e8836f932d75d303ab451a825241acde589a58

real	0m42.159s
user	0m41.756s
sys	    0m0.168s
```

Após a análise dos resultados obtidos, detetou-se que existe um aumento no tempo de execução conforme a dificuldade incrementa. Este facto deve-se à complexidade algorítmica dos desafios que compõem o modelo de consenso. Efetivamente, a dificuldade corresponde ao número de 0s que se tem de obter como prefixo do valor de *hash* gerado, para o mesmo ser aceite. Desta forma, quanto maior a dificuldade, maior a quantidade de tentativas necessárias para obter um valor de *hash* válido.

### Pergunta 2.2 - 1

A função `proof_of_work` começa por inicializar um contador, que será utilizado para encontrar o próximo *proof of work*. De seguida, este é incrementado até que seja divisível por 9 e pela prova do último bloco da cadeia. Assim, quando este valor for encontrado, o bloco pode ser adicionado à *blockchain*.

```python
def proof_of_work(last_proof):
    incrementor = last_proof + 1
    while not (incrementor % 9 == 0 and incrementor % last_proof == 0):
        incrementor += 1
    return incrementor
```

### Pergunta 2.2 - 2

Considera-se que este algoritmo não é o indicado para minerar, uma vez que não existe independência entre provas de blocos consecutivos. Assim, os próximos valores de *proof of work* podem ser pré-computados pelo *miner* que publicou o último bloco e, como tal, este tem vantagem em relação à publicação dos blocos seguintes.
