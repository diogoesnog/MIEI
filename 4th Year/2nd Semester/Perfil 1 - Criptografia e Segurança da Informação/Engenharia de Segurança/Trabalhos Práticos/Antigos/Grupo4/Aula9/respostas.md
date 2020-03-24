# Pergunta 1.1

## 1

* **Linux 3.1** - uma vez que o linux 3.1 possui cerca de 15 milhões de linhas de código e tendo em conta bases estatisticas que existem cerca de 5 a 50 bugs por cada 1000 linhas de código. Pode-se concluir que este sistema tenha entre 75 mil a 750 mil bugs no seu código.

* **Software de automóveis** - em média um software de automóveis tem 100 milhões de linhas de código, logo tendo por base o mesmo pensamento este software pode conter entre 500 mil a  5 milhões de bugs no respetivo código.

* **Facebook** - o facebook tem cerca de 62 milhões de linhas de código, pelo o seu código pode ter entre 310 mil a 3 milhões de bugs.

* **Google** - todos os serviços da internet pertencentes ao google tem cerca de 2 mil milhões, pelo que tem entre 10 milhões a 100 milhões de bugs.

## 2

Uma vez que não se pode calcular uma estimativa de vulnerabilidades por número de bugs encontrado, não é possível fazer uma estimativa do número de vulnerabilidades em cada um dos sistemas em cima mencionados.

# Pergunta 1.2

### Vulnerabilidades de projeto:

1. O software realiza uma verificação de autorização quando um ator tenta aceder a um recurso ou realizar uma autorização, mas a verificação não é executada corretamente. O que permite aos atacantes contornar as restrições de acesso. A correção desta vulnerabilidade é relativamente simples, uma vez que passa por dividir o software em grupos, como por exemplo, pessoas sendo utilizadores normais, utilizadores com acesso administrativos e utilizadores com acessos priveligiados. Pode-se ainda dar uso a frameworks que não permitem este tipo de vulnerabilidades ou fornece construções que dificultam que esta vulnerabilidade seja explorada, como por exemplo de Frameworks: *JAAS Authorization Framework* e *OWASP ESAPI Access Control feature*.

2. Um cliente/servidor realiza autenticação no código do cliente mas não no código do servidor, o que permite assim que a autenticação do lado do servidor seja ignorada através de um cliente modificado que omite a verificação da autenticação. A correção desta vulnerabilidade é bastante fácil, uma vez que apenas é necessário executar sempre autenticação do lado do cliente.

### Vulnerabilidades de codificação:
	
1. A informação enviada através da internet pode ser comprometida enquanto está a ser transmitida, um atacante pode ler ou modificar o conteúdo caso esteja tenha uma fraca encriptação. A correção desta vulnerabilidade implica configurar o software de modo a garantir que o SSL ou outro mecanismo de criptografia equivalente seja usado para todas as páginas controladas por acesso. Pelo que o grau de dificuldade também não é elevado.

2. Executar comandos ou carregar livrarias de uma fonte desconhecida num ambiente não confiável pode levar a que uma aplicação execute comandos maliciosos ou por outro lado ataques. Para este exemplo a correção da vulnerabilidade passa por as livrarias a serem carregadas devem ser percebidas e serem de fontes confiáveis.

### Vulnerabilidades operacionais:

1. O softaware pode gerar mensagens de erros que incluem informação sensíveis sobre o ambiente, utilizadores ou dados associados a esse mesmo software. Isto permite a qualquer atacante que receba este tipo de mensagens, possuir de informação de modo a atacar o software. Uma forma de corrigir esta vulnerabilidade consiste em configurar o ambiente de maneira a mostar mensagens de erros menos detalhadas, ou mensagens de erros que não revelem informação crítica.
 
2. Os recursos do software não são extensos os sufecientes para lidar com um "pico" de pedidos, o que pode permitir a um atacante evitar que as pessoas tenham acessos a esses recursos usando um número elevado de pedidos a esse recurso. Uma forma de combater esta vulnerabilidade passa por ser feito uma balanceamento dos recursos/cargas para lidar com este tipo de ataques.


# Pergunta 1.3

Uma vulnerabilidade dia-zero é uma vulnerabilidade de codificação que ainda não foi tornada pública a toda a comuninadade informática, mas apenas um grupo restrito tem conhecimento da mesma, ao contrário das vulnerabilidades de codifcação "normais" que é do conhecimento geral de toda a comunidade informática.