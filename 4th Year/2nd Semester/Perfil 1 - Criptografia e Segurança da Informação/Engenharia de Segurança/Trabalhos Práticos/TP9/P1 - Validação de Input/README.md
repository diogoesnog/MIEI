# Pergunta 1 - Validação de *Input*

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Pergunta 1.1**](#pergunta-11)
   - Análise do programa `filetype.c`
   - Análise/Exploração de vulnerabilidades presentes

2. [**Pergunta 1.2**](#pergunta-12)
   - Criação/desenvolvimento de um programa em Python
   - Validação do *input* consoante as regras de validação dadas na aula teórica

---

## Resolução da Pergunta 1

### Pergunta 1.1

Fazendo uma pequena análise do conteúdo/*source code* do programa `filetype.c` consegue-se deduzir que o mesmo trata de receber um nome de um ficheiro como argumento na linha de comandos, devolvendo como *output* o tipo de conteúdo que o ficheiro em causa possui.

<p align="center">
    <img src="Images/Output Programa filetype.png" width=60%/>
</p>


<p>

#### 1. Deteção e Exploração das Vulnerabilidades

Tendo em conta as vulnerabilidades estudadas na aula teórica de "Validação de Input", pode-se referir as seguintes vulnerabilidades para o programa `filetype.c`:

- Ausência da verificação dos tamanhos dados como *input*;

- O uso da função `system()` torna-se perigoso, dado que não existe qualquer parte de código que valide a extensão do ficheiro que está a ser mandado como argumento na altura de executar o programa;

**Note-se a seguinte sequência de execuções em modo terminal:**

  <p align = "center">
      <img src = "Images/Output Programa filetype V1.png" width = 60%/>
  </p>
<br/>
  
  A criação do ficheiro `teste.txt; ps -a` permite demonstrar que não é feita a tal verificação do nome/extensão do ficheiro, acabando assim por devolver não só o resultado da aplicação do programa ao ficheiro `teste.txt` mas também o resultado da execução do programa `ps -a`, dado que o operador `;` é usado para a execução de vários comandos.
  
  **Isto demonstra o perigo aqui implícito, dado que se se pode fazer algo simples como a execução de um comando que de nada tem a ver com o propósito do programa em si, então pode existir outras "maldades" podem eventualmente funcionar.**

  

- O uso da função `system()` possibilita ainda a realização de *path traversal*. Neste caso apenas seria necessário usar `/ ` para executar esse processo e obter a diretoria através do *autocomplete*.

  <p align = "center">
      <img src = "Images/Output Programa filetype V2.png" width = 90%/>
  </p>

  <br/>

<p>

#### 2. Programa com permissões *setuid root*


Pensando-se agora num cenário onde o programa estudado anteriormente tivesse permissões *setuid root*. Fornecer estas permissões torna-se realmente perigoso, dado que permite a um *user* com poucas permissões padrão a possibilidade de executar comandos indesejáveis, comprometendo assim todo o sistema em termos de **Confidencialidade**, **Integridade** e **Disponibilidade**.

A execução de programas maliciosos, leitura/manipulação de ficheiros, etc seriam possibilidades perfeitamente exequível tendo-se estas permissões.

---

### Pergunta 1.2

Como falado na aula teórica foram adotados alguns métodos que facilitaram todo o código para inserção de valores sensíveis e dessa forma existir um *parse* correto utilizando a linguagem de programação `Python` e a utilização de expressões regulares de forma a filtrar corretamente esses dados. Dessa forma temos:

- Valor a pagar: O valor a pagar filtrou-se para um máximo de 5 números à esquerda da vírgula e possivelmente ser decimal.
- Data de nascimento: A data de nascimento tinha de seguir à regra de AAAA-MM-DD.
- Nome: O nome tinha de ter no mínimo 2 nomes e no máximo 8.
- NIF: O NIF foi utilizado o algoritmo oficial do módulo de 11 do Governo Português.
- NIC: O NIC foi utilizado o algoritmo oficial do módulo de 11 do Governo Português.
- Nº de Cartão de Crédito: Foi utilizado o algoritmo oficial da VISA e MASTERCARD para verificar a introdução correta.
- Validade: A regra teria de ser MM/AA como está presente nos cartões verdadeiros.
- CVC/CVV: Uma regra para ser apenas três algarismos.

Dessa forma, o código-fonte para esta pergunta está na sua integralidade na pasta onde se encontra este documento Markdown.
[Código Fonte Python](/Trabalhos%20Pr%C3%A1ticos/TP9/P1%20-%20Valida%C3%A7%C3%A3o%20de%20Input/responsible.py)
<p>

---


## Notas/Observações Finais

- Imagem [**Output Programa filetype**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP9/P1%20-%20Valida%C3%A7%C3%A3o%20de%20Input/Images/Output%20Programa%20filetype.png) que demonstra o *output* do programa `filetype.c`.
- Imagem [**Output Programa filetype V1**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP9/P1%20-%20Valida%C3%A7%C3%A3o%20de%20Input/Images/Output%20Programa%20filetype%20V1.png) que demonstra o *output* do programa `filetype.c` com a exploração da primeira vulnerabilidade.
- Imagem [**Output Programa filetype V2**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP9/P1%20-%20Valida%C3%A7%C3%A3o%20de%20Input/Images/Output%20Programa%20filetype%20V2.png) que demonstra o *output* do programa `filetype.c` com a exploração da segunda vulnerabilidade.
