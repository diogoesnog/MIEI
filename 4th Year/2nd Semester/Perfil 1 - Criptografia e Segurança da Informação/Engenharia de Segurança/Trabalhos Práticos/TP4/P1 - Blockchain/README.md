# Pergunta 1 - Construindo uma *blockchain*

1. [Pergunta 1.1](#pergunta-11)
    - Alteração do método que cria o **Genesis Block**.
  
2. [Pergunta 1.2](#pergunta-12)
    - Adicionar blocos com transações novas.

## Pergunta 1.1

O código do *blockchain* está presente no ficheiro `main.experiencia1.1.js` e ele foi alterado para que o primeiro bloco desta implementação em *JavaScript* (que cria o **Genesis Block**) tivesse um *timestamp* com a data de hoje, ou seja, podemos utilizar um método da linguagem *JavaScript* que nos facilita automaticamente o processo:

```js
createGenesisBlock(){
        var timestamp = new Date();
        return new Block(0, timestamp.toDateString(), "Bloco inicial da koreCoin", "0");
    }
```

Assim podemos verificar o resultado através da impressão em JSON para a consola da *chain* toda e verificamos que o *timestamp* agora está na data corrente.

```json
"chain": [
        {
            "index": 0,
            "timestamp": "Thu Mar 19 2020",
            "data": "Bloco inicial da koreCoin",
            "previousHash": "0",
            "hash": "9cd159ef5ec62a1a3ba18639882ef9577347becdf100a5ded6cc4fa28299ba52"
        }
```
## Pergunta 1.2

Para adicionar mais transações na *blockchain* podemos adicionar o seguinte código à experiência, seguindo a mesma prática do artigo, colocando na parte da **data** vários `amount` diferentes.

```js
koreCoin.addBlock(new Block (1, "19/03/2020", {amount: 100}));
koreCoin.addBlock(new Block (2, "19/03/2020", {amount: 30}));
koreCoin.addBlock(new Block (3, "19/03/2020", {amount: 70, Block1: 10, Block3: 30}));
koreCoin.addBlock(new Block (4, "19/03/2020", {amount: 250, Block2: 10, Block3: 10}));
```