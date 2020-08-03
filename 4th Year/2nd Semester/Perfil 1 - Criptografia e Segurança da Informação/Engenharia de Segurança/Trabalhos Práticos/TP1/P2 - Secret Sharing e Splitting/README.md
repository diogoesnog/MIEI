# Pergunta 2 - Secret Sharing/Splitting

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Experiência 2.1 e 2.2**](#experiência-21-e-22---ficheiro-gensharedsecretphp-e-reconstroisecretphp) - **Uso do Ficheiro *genSharedSecret.php* e *reconstroiSecret.php* gerar e reconstruir segredos**
    - Análise dos ficheiros que tratam de criar e reconstruir um segredo de forma simples.

2. [**Pergunta 2.1**](#pergunta-21---criação-e-reconstrução-de-segredos-com-uso-de-uma-private-key) - **Criação e Reconstrução de Segredos com o uso de uma *Private Key***
    - Introdução de *Private Key* (com *passphrase*) para a criação de um segredo.
    - Uso de Certificado associado à *Private Key* para reconstruir um segredo.
    - Diferenças entre dois programas de reconstrução de segredos.
    - Conclusões.
---

## Resolução da Pergunta 2

### Experiência 2.1 e 2.2 - Ficheiro *genSharedSecret.php* e *reconstroiSecret.php*

<br/>

<p align="center">
    <img width="490" height="232" src="Images/Generate Shared Secret.png">
</p>

<br/>

  - Se executarmos este exemplo a limpo verificamos que é necessário fornecer o **segredo** em si e o **número de entidades** a partilhar;
  - Quando são fornecidos esses dois parâmetros, é dado um código binário para cada entidade em causa.
  - Ao tentar reconstruir o segredo com o código binário dado para essa entidade verificamos a necessidade de explicitar os códigos gerados anteriormente.
  - Caso os códigos tenham sido dados corretamente, o segredo é reconstruído com sucesso.
  - No caso de aplicarmos a duas entidades (por ex.), para reconstruir o segredo não basta o código de uma delas mas sim de ambas. O que acontece é que quando é dado apenas "parte" do código, o segredo não é apresentado na sua forma natural mas sim através de caractéres estranhos aos comuns dígitos e letras.

---

### Pergunta 2.1 - Criação e Reconstrução de Segredos com uso de uma *Private Key*

A. O programa Python anunciado baseia-se na divisão de um determinado segredo por um determinado grupo de entidades, sendo entregue a cada uma destas uma parte de um código que é depois essencial para reconstruir o segredo em si. Este processo torna-se semelhante ao que ficou visto na **Experiência 2.1** e **2.2**, estando neste caso a lidar com um algoritmo mais complexo e moldável ao pedido via terminal, através de um conjunto de parâmetros essenciais para o *output* deste programa.

Conforme indicado no enunciado, estamos agora a lidar com uma chave privada , dado que cada parte do segredo é devolvida num objeto JWT assinado sob forma de base 64.

<br/>

**Para gerarmos a chave privada podemos recorrer ao seguinte comando:**

`openssl genrsa -aes128 -out privateKey.pem 1024`

**Com a *Private Key* pronta, podemos agora executar o programa, dividindo em oito partes, um *quorom* de 5 (tal como pedido), o *uid* de 0 e a chave em causa:**

`python createSharedSecret-app.py 8 5 0 privateKey.pem`

*Note-se que para existir a construção da Private Key incial é pedido uma passphrase ao utilizador. Esta passphrase é depois usada ao executar o ficheiro Python, juntamente com o segredo que se pretende dividir.*

<br/>

<p align="center">
    <img width="500" height="411" src="Images/Create Shared Secret.png">
</p>

<br/>

Em termos de algoritmo existe a recorrência à função **createSharedSecretComponents** presente no módulo *shamirscret.py* do *package* **eVotUM** usado para a [Pergunta 1](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/TP1/P1%20-%20N%C3%BAmeros%20Aleat%C3%B3rios%20e%20Pseudoaleat%C3%B3rios).

Esta função divide o segredo nas n partes pedidas em modo *array*, gerando um *hash* através da função de *hash* criptográfica SHA256 para cada uma destas mesmas partes. Com isto feito, cria-se um ficheiro jwt com *array* para a totalidade das partes, devidamente assinado pela *Private Key* usada para todo o processo.

<br/>

B. Estando o segredo criado e os códigos devidamente distribuídos para todas as partes, surgem dois ficheiros que facilitam na recuperação/reconstrução do nosso segredo inicial. Estes diferem entre si em certos detalhes e é exatamente sobre ambos que se pretende estabelecer um termo de comparação.

<br/>

**Antes demais, comece-se por criar um certificado à *Private Key* criada na alínea anterior.**

`openssl req -key privateKey.pem -new -x509 -days 365 -out keyCert.cert`

Este certificado servirá para auxiliar na reconstrução do segredo em si.

<br/>

| Ficheiro                                    | Diferenças                                                   | Situações a Utilizar                                         |
| ------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ***recoverSecretFromComponents-app.py***    | Não necessita de todos os componentes.<br /> **Número de componentes deve ainda ser igual ou superior ao *quorum***. | Quando não é extritamente necessário que todas as entidades envolvidas confirmem uma determinada ação.<br /> **Número de entidades envolvidas deve ainda ser igual ou superior ao *quorum***. |
| ***recoverSecretFromAllComponents-app.py*** | Necessário introduzir todos os componentes anteriormente gerados (incluindo o Certificado). | Quando é necessário que todas as entidades envolvidas confirmem uma determinada ação. |

<br/>

**Conclusões:**

Pensando um cenário hipotético de um **Depósito Bancário**. Se assumirmos que existem 10 superiores que precisam de autorizar cada **Depósito** cujo valor ultrapasse um determinado limite, então, dependendo do valor a depositar, o banco optaria por um dos programas Python.

- Utilização do programa ***recoverSecretFromAllComponents-app.py*** deve constar quando procuramos uma confidencialidade/fidelidade praticamente total/absoluta.
  - No caso do nosso exemplo, o Banco recorreria a este programa quando o valor de depósito estivesse acima desse limite, dado que nesse caro seria necessária a aprovação dos 10 superiores.
- Em contrapartida, a utilização do programa ***recoverSecretFromComponents-app.py*** deve constar quando não é necessário uma total confirmação por todas as partes envolvidas.
  - Neste caso, o Banco recorreria a este programa, sendo assim necessária a aprovação de 5 superiores (assumindo que o *quorum* possui esse valor).

---

## Notas/Observações Finais

- Imagem [**Generate Shared Secret**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP1/P2%20-%20Secret%20Sharing%20e%20Splitting/Images/Generate%20Shared%20Secret.png) permite observar o processo simples de Geração e Reconstrução de um Segredo.
- Imagem [**Create Shared Secret**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP1/P2%20-%20Secret%20Sharing%20e%20Splitting/Images/Create%20Shared%20Secret.png) permite observar o processo de Criação da Chave Privada e do Segredo através da mesma.
