# Trabalho Prático 3 - Resolução

## 1\. TOR (The Onion Router)

### Pergunta P1.1

#### 1.
Ao efetuar o comando ``sudo anonsurf start`` não conseguimos garantir que estamos nos EUA.

#### 2.
Ao estabelecer uma comunicação TOR, o OP salta de circuito para circuito em intervalos de 1 minuto. Para este circuito, o OP necessita de, por norma, 3 OR acordando uma chave simétrica com cada um deles. Note-se que o OP não tem poder de escolha em relação a estes OR, uma vez que estes são fornecidos, de forma aleatória, por um Directory Server. Assim sendo, sabemos quais as localizações que os circuitos abragem, mas não podemos escolher estar numa, isto porque o TOR garante anonimato ponto a ponto, ou seja, quando o OP estabelece os circuitos não tem controlo sobre os OR que formarão esse circuito, pelo que é impossível saber, após estabelecimento de um circuito, qual o OR ao qual o OP se vai ligar.

### Pergunta P1.2

#### 1. Acedendo a https://www.facebookcorewwwi.onion/ obteve-se o seguinte circuito:

![circuito](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP3/pergunta1_2.png)

#### 2.

Analisando a imagem acima, observa-se que existem 6 "saltos" até ao site Onion, sendo que os 3 últimos são do tipo "relay". Isto deve-se ao facto de se estabelecerem pontos *rendezvous*, pontos estes que servem de suporte à disponibilização de serviços anónimos. Note-se que na rede TOR, a disponibilização deste tipo de serviços permite a um OP disponibilizar serviços TCP, como por exemplo, *web services*, sem revelar o seu endereço IP. Deste modo, como o OP que acede ao serviço anónimo é também ele anonimizado, tanto o OP que acede como o OP que é acedido são anónimos.

Recordando o que foi visto nas aulas teóricas, normalmente, os circuitos com o estabelecimento de pontos *rendezvous* consistem em circuitos de 6 OR, sendo que 3 deles são escolhidos pelo utilizador e os restantes 3 pelo servidor. Nesse circuito, o utilizador escolhe os 3 primeiros OR, sendo o terceiro OR um RP (após a escolha do RP, o utilizador constrói um circuito TOR até ele), e o servidor escolhe os últimos 3; assim, após escolhido este RP o utilizador envia uma célula *relay begin* através do circuito que, chegando ao servidor, se conecta com o serviço web ao qual se pretende aceder.

O servidor escolhe pontos de introdução e anuncia-os no Directory Server, assinando o anúncio com a sua chave privada, sendo que estes pontos de introdução servirão para criar um circuito TOR. Assim, quando um utilizador quiser aceder a esse servidor, terá de o fazer no TOR através do Directory Server.

Ou seja, com o intuito de identificar o serviço que vai disponibilizar, o servidor começa por gerar um par de chaves de longo tempo e escolhe alguns pontos de introdução. Assim, o circuito formado pelo utilizador vai tentar conectar-se a um dos pontos de introdução escolhidos pelo servidor, esta conexão é feita através do RP. Após estabelecida esta conexão, o utilizador envia células relay que transportam informação necessária para que o servidor verifique se quer, de facto, permitir que o utilizador se conecte ao serviço que disponibiliza. Caso o servidor aceite "falar" com o utilizador estabelece um circuito TOR até ao RP. Note-se que o RP não consegue reconhecer o utilizador, o servidor nem os dados que estão a ser transmitidos.

Por fim, a existência das células *relay* devem-se ao facto da comunicação necessitar de transferir dados de uns OR para outros, dados estes necessários para que a conexão entre utilizador e servidor seja estabelecida. Note-se que estas células têm como principal função transportar dados de um lado para o outro, daí que o uso das mesmas, neste contexto, faça todo o sentido.
