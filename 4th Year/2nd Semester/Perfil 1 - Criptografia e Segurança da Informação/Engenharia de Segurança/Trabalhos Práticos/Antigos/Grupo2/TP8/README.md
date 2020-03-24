# Aula TP - 06/Mai/2019


## P1.1 - *SQL Injection*

A inserção da *string* `Smith'; select * from user_data;  --` no campo de entrada permite obter todos os dados de todos os utilizadores:

![String SQLi](Pictures/String_SQLi.png)

Por outro lado, o uso da *string* `Smith' OR 1=1 --` também permite obter os dados de todos os utilizadores visto que a condição `1=1` 
se trata de uma tautologia **i.e.** é verdade para qualquer utilizador:

![String SQLi Tautology](Pictures/String_SQLi_T.png)


## P1.2 - *Numerical SQL Injection*

A escolha dos valores disponíveis permite observar que a *query* é construída com um código identificador do local que se pretende
consultar:

![No Numerical SQLi](Pictures/NoNumericalSQLi.png)

Uma inspeção do código HTML da página permite identificar que estes valores estão presentes no atributo *value* de cada *tag* do tipo
*option*:

![No Numerical SQLi](Pictures/NoNumericalSQLi_HTML.png)

Como tal, para conseguir injectar SQL basta modificar este atributo de forma a que constitua uma *string* como a seguinte: `101 OR 1=1`

![Numerical SQLi](Pictures/NumericalSQLi_HTML.png)

que resulta na *query* SQL:

![Numerical SQLi](Pictures/NumericalSQLi_Query.png)

permitindo visualizar todas as temperaturas presentes na base de dados:

![Numerical SQLi](Pictures/NumericalSQLi.png)



## P1.3 - *Database Backdoors*

Construindo a *query* `101; UPDATE employee SET salary = 550000000 WHERE userid = 101;` é possível atualizar o salário de um utilizador
cujo `userid` seja igual a 101:


![No DB Backdoor](Pictures/NoDBBackdoor.png)


![DB Backdoor](Pictures/DBBackdoor.png)


## P2.1 - *Reflected XSS*

A realização de testes em todos os campos permite identificar que o último campo é vulnerável a *Reflect XSS*. Esta suspeita é confirmada
com a inserção de uma *string* como: `<script>alert('hello')</script>`: 

![Reflected XSS Payload](Pictures/ReflectedXSS_Payload.png)

que, ao ser interpretado pelo *browser* como código Javascript, apresenta um alerta no browser do utilizador com a mensagem "hello":

![Reflected XSS](Pictures/ReflectedXSS_Dialog.png)

## P3.1 - *Broken Authentication*

O uso de mecanismos para recuperação de password que recorram a perguntas com um número reduzido de respostas e sem limite de tentativas
erradas permite que sejam realizados ataques de força bruta com base nas respostas possíveis. Por outro lado, o teor das respostas pode 
facilitar a tarefa de determinar a resposta certa, no caso do utilizador *webgoat* a resposta está provavelmente certa *red* tendo em conta
os dados que se possuem deste utilizador:

![Broken Authentication - WebGoat](Pictures/BrokenAuthentication_Webgoat.png)

Por outro lado, para o utilizador *admin*, comum em diversos sistemas por permitir, como o nome indicar, gerir o sistema em causa, as respostas
apesar de menos óbvias podem ser testadas uma a uma com recurso a um ataque de força bruta que pode ser realizado em tempo útil, permitindo
encontrar a respostas *green* para recuperar a *password* deste utilizador:

![Broken Authentication - admin](Pictures/BrokenAuthentication_admin.png)
