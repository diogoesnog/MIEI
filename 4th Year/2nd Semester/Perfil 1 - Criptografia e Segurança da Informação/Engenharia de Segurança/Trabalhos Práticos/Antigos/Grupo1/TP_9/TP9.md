# Trabalho Prático 9 - Resolução

## 1. Injection

#### Pergunta 1.1 String SQL Injection

1.
No sítio pedido no WebGoat, colocámos últimos nomes, como _Smith_, _Green_, _Snow_, etc, verificando se existiam ou não na base de dados. Exisitindo, obtivemos informações sobre _user_id_, _cc_type, cc_number_, etc.

2.
Utilizando a tautologia 1=1, exacutámos o ataque de _SQL injection_, obtendo, como pedido, informação sobre todos os cartões de crédito.
![pergunta 1.1](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP_9/pergunta1.1.png)

#### Pergunta 1.2 Numeric SQL Injection

Através da ferramenta **Inspector** no Firefox, procurámos as linhas onde estavam as diferentes _stations_, alterando o valor relativo a Columbia para "101 or 1=1".

![pergunta 1.2](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP_9/pergunta1.2.png)


#### Pergunta 1.3 Database Backdoors

![pergunta 1.3](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP_9/pergunta1.3(1).png)

Introduzindo o seguinte comando **ID:101; update employee set salary=-50**, alterámos o valor do salário para algo irrealista no contexto, isto é, para o valor negativo -50.
![pergunta 1.3 resolvida](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP_9/pergunta1.3.png)

## 2. XSS

#### Pergunta 2.1 Reflected XSS

Ao introduzir a script `<script> alert("SSA!!!")</script>` nos espaços relativos às quantidades, podemos verificar que o programa altera os caracteres especias (por exemplo: < > /) para '.', porém, ao colocar a mesma script no espaço _Enter your three digit access code_, já é executada a script.
![pergunta 2.1](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP_9/pergunta2.1%20(2).png)

## 3. Quebra na Autenticação

#### Pergunta 3.1 Forget Password

Constatamos, depois de algumas tentativas, que existe uma conta chamada _admin_. Além disso, tentámos uma ou outra cor até chegarmos à conclusão que a cor favorita do _admin_ é _green_. Depois disto, obtivemos a _password_ desta conta.
![pergunta 3.1](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP_9/pergunta3.1.png)
