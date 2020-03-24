# Aula TP - 01/Abr/2019

# 1. Vulnerabilidade de codificação

## Pergunta 1.1

Considerando que, em média, qualquer pacote de *software* tem entre 5 a 50 *bugs* por cada 1000 linhas de código fonte, excluindo comentários (**SLOC**) deve ser
aplicada a seguinte fórmula para aproximar o número de *bugs* num dado projeto:

**#bugs = (SLOC/1000) * #bugs_por_1000_linhas_de_código**

Esta fórmula permite estabelecer um limite inferior e superior para o número de *bugs* num dado projeto em função da dimensão (número de linhas de código) do mesmo.

### Número de linhas de código:

- **Facebook -** 62000000
- **Software de automóveis -** 100000000
- **Linux 3.1 -** 15000000
- **Serviços Internet da Google -** 2000000000

### 1. Estimativa do número de Bugs

- Limite inferior (5 bugs por cada 1000 SLOC)

    - **Facebook -** 310000
    - **Software de automóveis -** 500000
    - **Linux 3.1 -** 75000
    - **Serviços Internet da Google -** 10000000

- Limite superior (50 bugs por cada 1000 SLOC)

    - **Facebook -** 3100000
    - **Software de automóveis -** 5000000
    - **Linux 3.1 -** 750000
    - **Serviços Internet da Google -** 100000000


### 2. Número de Vulnerabilidades

De uma forma geral um *bug* pode ser visto como uma falha num programa que resulte em comportamento inesperado no funcionamento do mesmo. Como tal é possível estabelecer
uma relação direta entre o o número de *bugs* e o número de linhas de código de um pacote de software. Por outro lado, a relação entre o número de  *bugs* e o número
de vulnerabilidades é menos clara, sendo difícil determinar, com precisão, quantos *bugs* num dado sistema resultam em vulnerabilidades, bem como quais dessas vulnerabilidades 
são passíveis de serem exploradas. 

Como tal é complexo estimar o número de vulnerabilidades no código fonte de cada projeto, visto ser algo que depende de diversos fatores, como a linguagem de programação 
escolhida, a experiência e conhecimento do programador ou até o tipo de aplicação desenvolvida, entre outros. Segundo a *National Vulnerability Database*, até ao momento 
foram identificadas (e muitas das quais já corrigidas) 84 vulnerabilidades relacionadas com o Facebook, 11 vulnerabilidades relacionadas com o Linux 3.1, e 4721 
vulnerabilidades relacionadas com serviços Google.

## Pergunta 1.2

Uma vulnerabilidade corresponde a uma falha num sistema ou mecanismod e proteção que o torna vulnerável a possíveis ataques por parte de agentes maliciosos. Exemplos de 
vulnerabilidades são falhas no projeto, na implementação ou na configuração de programas, serviços ou equipamentos de rede. 

As vulnerabilidades podem ser classificadas em 3 categorias, **Projeto**, **Codificação** e **Operacional**.

- **Vulnerabilidades de projeto** são introduzidas durante a fase de projeto do *software* (obtenção de requisitos e desenho) e catalogados como 
**CVE (Common Vulnerabilities and Exposures)**. 

Mais concretamente estas vulnerabilidades podem consistir em:

1. Falhas no levantamento de requisitos, por exemplo, não incluir no plano do projeto uma fase de verificação de acesso;

2. Durante a fase de planeamento do projeto em que pode ser tomada a decisão de implementar um sistema que recorra a algoritmos com vulnerabilidades conhecidas que,
consequentemente, resultem num sistema vulnerável a ataques

3. Vulnerabilidades introduzidas deliberadamente, como o uso de credenciais "fracas" com o intuito de facilitar a sua memorização ainda que estas ponham em causa, de
forma clara, a segurança do sistema

4. Limitação do acesso aos dados do utilizador associado sem implementação de um mecanismo que garanta a confidencialidade dos mesmos. 


De seguida são apresentadas duas vulnerabilidades de projeto específicas:
    
- [CVE-2016-1960](https://nvd.nist.gov/vuln/detail/CVE-2016-1960)
        
Descoberta na versão **44.0.2** do *browser Firefox* que consistia num fluxo contínuo de números inteiros na **classe nsHtml5TreeBuilder** no analisador de sequências HTML5. 
que permitia que atacantes remotos executassem código arbitrariamente ou causassem uma negação de serviço **use-after-free**, promovendo a manipulação incorreta das 
*tags* finais.

A vulnerabilidade foi depois corrigida na versão 45 do Mozilla Firefox.

        
- [CVE-2015-4495](https://nvd.nist.gov/vuln/detail/CVE-2015-4495)

Descoberta na versão **39.0.3** e quando explorada permitia ao atacante ler e copiar informação do computador da vítima, assim que esta visitasse o website criado 
para exploração.

O leitor de PDF do Mozilla Firefox até à versão **39.0.3**, permitia que atacantes remotos ultrapassassem a política **Same Origin Policy** e lessem ficheiros arbitrários 
ou ganhassem privilégios, através de vetores que envolvem código JavaScript escrito pelo atacante e um setter nativo.

Para corrigir esta vulnerabilidade o utilizador só tinha de atualizar o browser para uma versão superior à 39.0.3.


- **Vulnerabilidades de codificação** são introduzidas durante a programação do *software*, como por exemplo, um *bug* com implicações de segurança. Assim como as 
anteriores, estas vulnerabilidades são também catalogadas como **CVE (Common Vulnerabilities and Exposures)**.

Com mais detalhe, pode-se considerar o caso do *buffer overflow*, caso em que o programador não teve os devidos cuidados na forma como a memória do programa é gerida; 
ou o caso do *heartbleed*, uma vulnerabilidade ao nível da implementação do código na biblioteca OpenSSL que levou ao *leak* de vários dados privados (como chaves privadas) 
de vários serviços que utilizam essa biblioteca. Esta vulnerabilidade é particularmente grave uma vez que se localiza ao nível da implementação de uma biblioteca que é 
muito usada para vários serviços, em que a segurança de dados e correspondente privacidade são essenciais.

Seguem-se duas vulnerabilidades de codificação específicas:


- [CVE-2016-5537](https://nvd.nist.gov/vuln/detail/CVE-2016-5537)

A vulnerabilidade no componente **NetBeans no Oracle Fusion Middleware 8.1** permitia aos utilizadores locais afetar a confidencialidade, integridade e disponibilidade 
através de vetores desconhecidos.

É uma vulnerabilidade de passagem de diretório que permitia que utilizadores locais com determinadas permissões escrevessem em arquivos arbitrários e, consequentemente, 
ganhassem privilégios numa entrada de arquivos num ficheiro ZIP importado como um projeto.

- [CVE-2017-9798](https://nvd.nist.gov/vuln/detail/CVE-2017-9798)

Permitia que os atacantes remotos lessem dados secretos da memória do processo se a diretiva limite pudesse ser definida no arquivo **.htaccess** de um utilizador, ou 
se o **httpd.conf** tivesse certas configurações erradas, (Optionsbleed). Isso afeta o Servidor HTTP Apache nas versões **2.2.34** e **2.4.x** até **2.4.27**. O atacante 
poderia enviar uma solicitação **HTTP de OPÇÕES** não autenticadas ao tentar ler dados secretos. 
            
Era um problema de **uso após o uso** e, portanto, os dados secretos nem sempre eram enviados e os dados específicos dependiam de muitos fatores, incluindo a configuração. 
A exploração com **.htaccess** podia ser bloqueada com um patch para a função **ap_limit_section** no **servidor/core.c**.


- **Vulnerabilidades operacionais** são causadas pelo ambiente no qual o *software* é executado ou pela sua configuração. Estas são catalogadas como 
**CCE (Common Configuration Enumeration)**.

Com mais detalhe, um exemplo de vulnerabilidade operacional será o de, num dado ambiente, poder haver entidades estranhas ao sistema 
com acesso a informações confidenciais, seja por fugas de informação, ou por outras falhas humanos como documentos confidenciais abertos num computador com o ecrã 
ligado e desbloqueado. Poderá também haver possíveis vulnerabilidades que resultem da configuração de funcionalidades 
do sistema por parte de entidades sem conhecimentos para tal, ou ainda da configuração de determinado *software* que não tem em conta configurações de segurança exigidas.

Seguem-se duas vulnerabilidades operacionais específicas:

- [CCE-10814-2](http://www.scaprepo.com/view.jsp?id=CCE-10814-2)
    
Por padrão, quando a rede do Windows está ativa num servidor, o Windows criará partilhas administrativas ocultas, o que é indesejável em servidores altamente seguros.

- [CCE-10061-0](http://www.scaprepo.com/view.jsp?id=CCE-10061-0)

Permite desativar a capacidade do computador cliente de imprimir em HTTP, o que permite que imprima em impressoras na intranet e na Internet.

A titulo de curiosidade, segue-se as correções associadas às três categorias de vulnerabilidades apresentadas:

A **correção das vulnerabilidades de projeto** pode implicar uma restruturação de todo o sistema, o que poderia implicaria gastos de dinheiro e de tempo excessivos 
para uma organização, mas também pode implicar apenas modificar componentes específicas do sistema, o que já é exequível.

Na **correção de vulnerabilidades de codificação** a dificuldade pode estar associada à deteção da vulnerabilidade, que por vezes pode ser difícil. A correção de um 
*bug* de *software* que esteja a introduzir uma vulnerabilidade deste tipo poderá normalmente passar por um ou mais *patches*. No entanto, pode ser necessário introduzir 
mais vulnerabilidades ou pode simplesmente não ser exequível a aplicação de um *patch* em certos sistemas.

A **correção de vulnerabilidades operacionais** passa por haver uma política rigorosa de práticas a ter quando se lida com dados confidenciais, de forma a que entidades 
terceiras não lhes possam nunca aceder.


## Pergunta 1.3


As principais diferenças entre vulnerabilidades dia-zero e qualquer outro tipo de vulnerabilidades de codificação concentra-se nas entidades que possuem conhecimento 
sobre a existência da mesma. Ao contrário da norma, que origina a sua divulgação pública de forma a que o fornecedor possa corrigir essas falhas, estas são conhecidas 
apenas por um grupo restrito de pessoas, não sendo divulgadas para a comunidade que lida com segurança informática.


Deste modo, vulnerabilidades dia-zero são falhas na segurança de um *software* e identificam-se por serem vulnerabilidades que são encontradas e podem ser exploradas 
antes que os *developers* tenham tempo para as resolver. A origem do seu nome vem do facto que estas vulnerabilidades terem de ser resolvidas em menos de um dia, desde 
a sua descoberta, ou seja, no dia zero, pois possíveis atacantes podem aproveitar-se.


Estas vulnerabilidades podem ser utilizadas por grupos de piratas informáticos para efetuar ataques, de forma sigilosa, ou vender na *dark web*, bem como no meio militar 
de um país (ciber-armas).

Em suma, vulnerabilidades de dia-zero são vulnerabilidades pré-existentes no código que os _developers_ do _software_ não conhecem, e que são descobertas e atacadas antes 
que sejam desenvolvidos _patches_ para as mesmas.
