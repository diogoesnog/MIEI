# Pergunta 1 - Números Aleatórios/Pseudoaleatórios

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Experiência 1.1**](#experiência-11---comando-openssl) - **Execução comando OpenSSL `openssl rand -base64 1024` para gerar 1024 *bytes* pseudoaleatórios**
    - Pequeno enquadramento teórico.

2. [**Pergunta P1.1**](#pergunta-p11---outros-comandos-openssl-e-diferenças) - **Execução outros comandos OpenSSL para gerar conjuntos de *bytes***
    - Tabela que permite estabelecer uma diferença entre os vários comandos.
    - Conclusões.

3. [**Pergunta P1.2**](#pergunta-p12---daemon-haveged) - **Execucão comandos OpenSSL com o *package* haveged instalado**
    - Pequena explicação do *daemon* de entropia haveged.
    - Tabela que permite estabelecer uma nova diferença entre os vários comandos.
    - Conclusões.

4. [**Experiência 1.2**](#experiência-12---ficheiro-randombytesjava) - **Uso do Ficheiro *RandomBytes.java* para gerar conjuntos de *bytes***
    - Análise do *output* do ficheiro.

5. [**Experiência 1.3**](#experiência-13---ficheiro-generatesecret-apppy) - **Uso do Ficheiro *generateSecret-app.py* para gerar conjunto de *bytes***
    - Análise do *output* do ficheiro.
    - Tentativa de não limitar este *output* a letras e dígitos.
    
---

## Resolução da Pergunta 1

### Experiência 1.1 - Comando OpenSSL

O comando `openssl rand -base64 1024` pedido para teste na Experiência 1.1 é claro de se compreender.

Segundo a documentação oficial do **OpenSSL**,

> The **rand** command outputs *num* pseudo-random bytes after seeding the random number generator once.

O que faz sentido, dado que o *output* produzido por este comando consiste precisamente num conjunto de 1024 *bytes* pseudoaleatórios. 

<br/>

<p align="center">
    <img width="519" height="349" src="Images/Comando OpenSSL.png">
</p>

<br/>

**Como vamos constar ao executar/analisar os comandos abaixo, existem diferenças determinantes entre as duas fontes de aleatoriedade do UNIX cujo propósito passa por gerar números pseudoaleatórios, através de um gerador que se baseia numa estimativa em termos de *bits* do ruído da *pool* de entropia.**

- `/dev/random`- devolve *bytes* aleatórios estimados pela *pool* de entropia existente, bloqueando a operação de leitura quando a entropia disponível é inferior à solicitada/necessária para a geração em causa;
- `/dev/unrandom`- contrariamente ao anterior, caso não exista entropia suficiente/necessária, reusa o *pool* de forma a produzir os bits pseudoaleatórios em causa. 

Dado que a fonte de aleatoriedade vinda do `/dev/unrandom` nunca interrompe a operação de leitura, é possível que os valores dados no *output* estejam vulneráveis a ataques criptográficos.

---

### Pergunta P1.1 - Outros Comandos OpenSSL e Diferenças

|               Comando/Tipologia               | Tempo de Execução |                    Resultados/Observações                    |
| :-------------------------------------------: | :---------------: | :----------------------------------------------------------: |
|   **Comando 1** - 32 *bytes*, `/dev/random`   |     ≡ 0.004s      |  Devolução do resultado imediata. Número de *bytes* baixo.   |
|   **Comando 2** - 64 *bytes*, `/dev/random`   |     ≡ 0.012s      | Devolução do resultado imediata. Tempo de Execução superior ao **Comando 1**. |
|  **Comando 3** - 1024 *bytes*, `/dev/random`  |    ≡ 5m30.232s    | Número de *bytes* mais elevado logo maior Tempo de Execução. |
| **Comando 4** - 1024 *bytes*, `/dev/unrandom` |     ≡ 0.004s      | Apesar do número de *bytes* ser igual ao **Comando 3**, resultado imediato. |

*Note-se que o tempo de execução destes comandos é uma estimativa dada pelo próprio Linux, fazendo-se uso do comando `time`, podendo variar consoante certos fatores.*

<br/>

**Conclusões:**

- O Tempo de Execução aumenta à medida que aumentamos também o número de *bytes* a serem gerados, dado que é preciso mais entropia para o processo em si.
  - Isto fica percetível pelo **Comando 1** e pelo **Comando 2**. Ambos usam o `random`, mas diferem no tempo que demoram a ser executados.
- O uso da fonte de aleatoriedade `/dev/random` ou `/dev/unrandom` é determinante no Tempo de Execução.
  - O **Comando 3** e o **Comando 4** solicitam a mesma quantidade de *bytes*, mas a diferença de tempo é consideravelmente grande. Isso acontece porque o **Comando 4** faz uso do `unrandom`, o que leva a que quando a entropia não é suficiente, exista uma espécie de implementação de PRNG próprio através de uma *seed* (que é o que OpenSSL acaba por fazer), acelerando todo o processo em si.

---

### Pergunta P1.2 - *Daemon* haveged

Conforme anunciado, o haveged é um *daemon* de entropia totalmente adaptado através do algoritmo HAVEGE, criado com o objetivo de corrigir/colmatar problemas em que existe uma baixa entropia no *special file* em si. A sua ideia base passa por fornecer um RNG simples de usar que possibilite essa medida através da criação da entropia necessária para se excutar o comando/operações em causa.

Este *daemon* obtém assim sequências imprevisíveis de números aleatórios, com base na entropia de eventos externos que se baseiam no algoritmos HAVEGE.

<br/>

| Comando/Tipologia                             | Tempo de Execução | Resultados/Observações                                     |
| :-------------------------------------------- | :---------------: | :--------------------------------------------------------- |
| **Comando 3** - 1024 *bytes*, `/dev/random`   |     ≡ 0.004s      | Tempo de Execução muito inferior ao da **Pergunta P1.1**.  |
| **Comando 4** - 1024 *bytes*, `/dev/unrandom` |     ≡ 0.004s      | Tempo de Execução mantém-se igual ao da **Pergunta P1.1**. |

<br/>

**Conclusões:**

- Ambos os comandos executam em tempos aproximadamente iguais. 
- Relativamente à **Pergunta P1.1**, nota-se uma diferença significativa em relação ao **Comando 3**. 
  - Isto deve-se ao facto de que quando o `/dev/random` é executado, passa a existir desta vez a entropia essencial/necessária para que se produzam os 1024 *bytes* pedidos. 
  - Essa entropia é então calculada pelo haveged. 

---

### Experiência 1.2 - Ficheiro *RandomBytes.java*

Fazendo uma pequena análise do ficheiro em causa, tanto em termos de código em si como em termos de resultado, chegamos à conclusão que se trata de um algoritmo similar ao que vimos anteriormente.

Dessa forma, podemos gerar *bytes* aleatórios correndo apenas o ficheiro de Classe que se cria quando se executa o ficheiro *Java* em si.

<br/>

<p align="center">
    <img width="650" height="217" src="Images/Random Bytes Java.png">
</p>

<br/>

---

### Experiência 1.3 - Ficheiro *generateSecret-app.py*

O ficheiro em causa tem o mesmo princípio base em relação aquilo que temos vindo a falar nesta **Pergunta 1** - gerar um segredo que consiste num conjunto pseudoaleatório de dígitos e letras.

<br/>

<p align="center">
    <img width="647" height="361" src="Images/Generate Secret Python.png">
</p>

<br/>

1. O ficheiro é muito pequeno, dado que usa o módulo **eVotUM.Cripto** e que este acaba por fazer o trabalho principal na geração de *bytes*.
O link fornecido permite estudar como funciona este módulo e com isso chegar a uma conclusão acerca do *output* quando se executa o programa Python.

  Como o próprio main indica, para processar os *bytes*, recorre-se ao módulo *shamirscret.py*, mais propriamente ao método **generateSecret**.

  ```python
  def main(length):
    sys.stdout.write("%s\n" % shamirsecret.generateSecret(length))
  ```
  É precisamente esse método que importa compreender, tendo em conta que é ele que trata de gerar todo o "segredo".

  ```python
  def generateSecretTime(secretLength, timeToLive, chars="ABCDEFGHJKLMNPQRSTUVWXYZ23456789"):

    (...)

    while (l < secretLength):
        s = utils.generateRandomData(secretLength - l)
        for c in s:
            if (c in chars and l < secretLength): 
            # printable character
                l += 1
                secret += c
    return secret, time.time() + timeToLive
  ```
  O código indica que para gerar a sequência de *bytes* existe um ciclo que "sobrevive" enquanto não for atingido o número de *bytes* pedido.

  O módulo *utils* usado para a variável **s** permite que esta seja construída através do comando *unrandom*.
  Após esta variável ser construída existe uma verificação *if*, que trata de verificar cada caractér da mesma e com isso limitar apenas aqueles que são letras (```string.ascii_letters```) ou dígitos (```string.digits```).

<br/>

2. Para não se limitar o *output* a letras e dígitos a alteração necessária em termos de código seria muito simples.

Ao invés de declararmos o **chars** no *if* intrínseco ao ciclo *for*, poderia-se escrever:

  ```python
  def generateSecretTime(secretLength, timeToLive):

    (...)
    
    while (l < secretLength):
        s = utils.generateRandomData(secretLength - l)
        for c in s:
            if (c in (string.ascii_letters + string.digits + string.punctuation) and l < secretLength): 
            # printable character
                l += 1
                secret += c
    return secret, time.time() + timeToLive
  ```

---

## Notas/Observações Finais

- Imagem [**Comando OpenSSL**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP1/P1%20-%20N%C3%BAmeros%20Aleat%C3%B3rios%20e%20Pseudoaleat%C3%B3rios/Images/Comando%20OpenSSL.png) permite observar o tipo de resposta por parte do comando e os tais *bytes* pseudoaleatórios que devolve.
- Imagem [**Random Bytes Java**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/TP1/P1%20-%20N%C3%BAmeros%20Aleat%C3%B3rios%20e%20Pseudoaleat%C3%B3rios/Images/Random%20Bytes%20Java.png) permite observar que é necessário fornecer o número de *bytes* a gerar e o resultado caso esse número seja fornecido.
- Imagem [**Generate Secret Python**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP1/P1%20-%20N%C3%BAmeros%20Aleat%C3%B3rios%20e%20Pseudoaleat%C3%B3rios/Images/Generate%20Secret%20Python.png) iguala-se à imagem anterior mas o algoritmo é processado na linguagem Python.
