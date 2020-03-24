# Aula TP - 1 de Abril - Resolução

## 1. Vulnerabilidades e codificação

### Pergunta P1.1

**1.**

Em relação ao número de bugs no código de um software, estima-se que este está entre 5 e 50 por cada 1000 linhas de código - _SLOC_ -, tendo em conta o tipo de software que é.

Ora, através do site citado no enunciado e fazendo os cálculos necessários, podemos concluir o que está na tabela abaixo:

| Software | Linhas de código | Estimativa do nº de bugs |
| :-----------: | :---------------: | :-----------------: |
| Facebook | 62.000.000 | 31.000 a 310.000 |
| Car Software | 100.000.000 | 50.000 e 500.000 |
| Linux 3.1 | 15.000.000 | 7.500 e 75.000 |
| Google Services | 2.000.000.000 | 1.000.000 e 10.000.000 |

**2.**

Não existe uma fórmula que calcule o número de vulnerabilidades a partir do número de bugs de um software, isto é, não é possível determinar quantos dos 5 a 50 bugs por cada 1000 linhas de código se vão manifestar como vulnerabilidades!

*************

### Pergunta P1.2

**Vulnerabilidades de Projecto**

- [Not using password aging](https://cwe.mitre.org/data/definitions/262.html). Apesar de maior parte das aplicações recomendar a atualização das passwords e a não utilização de passwords iguais em todos os sistemas, muitas vezes, não é incluído no desenho do software uma forma de prever que as passwords "passem o seu prazo de validade". Para melhorar esta característica de segurança podia ser incluído um sistema de notificação/aviso de password "velha" com a sugestão de que a substituíssem por uma forte, atualmente. Assim, seria algo corrigido com alguma facilidade.
- [Execution with unnecessary privileges](https://cwe.mitre.org/data/definitions/250.html). Esta vulnerabilidade remete-nos para um nível de permissões muito elevado em certas aplicações, permissões estas que podiam ser bem mais reduzidas. Assim sendo, é bastante plausível para um atacante ter acesso e explorar funcionalidades que não lhe deviam ser alcançáveis. Resolver isto passaria por criar utilizadores diferentes, com permissões limitadas para o propósito do utilizador ou para tarefas únicas. Elevar os privilégios quando necessário e reduzi-los assim que deixasse de ser aplicável também seria uma boa hipótese. Implementar isto pode não ser imediato, mas precaveria muitos ataques que são considerados fáceis. 

**Vulnerabilidades de Codificação**

- [Improper input validition](https://cwe.mitre.org/data/definitions/20.html). Se um input é mal lido, todo o fluxo de dados pode tornar-se confuso e ser mesmo afetado negativamente. Uma estratégia é implementar o código de forma a que aceite apenas determinados inputs, isto é, mais específicos ou incluir logo funções que convertam os inputs na forma que pretendemos.
- [Heap-based buffer overflow](https://cwe.mitre.org/data/definitions/122.html). A vulnerabilidade _heap overflow_ é como um _buffer overflow_, porém, o pedaço de memória onde o _buffer_ pode subscrever é no chamado _heap_ que funciona como uma alocação de memória dinâmica... que pode ocorrer em qualquer pedaço livre de memória. Ocorre o _buffer_ quando se usa um comando como _malloc()_. Explorar esta vulnerabilidade tem um nível elevado de possível sucesso, assim como não é imediato corrigir esta, uma vez que pode ser atacada na fase de projecto, assim como na fase de operações.

**Vulnerabilidades Operacionais**

- [J2EE Misconfiguration - Data transmission without encryption](https://cwe.mitre.org/data/definitions/5.html). Enviar informação não cifrada pela rede torna-a substancialmente mais frágil e acessível. Assim, se um atacante interceptar a comunicação ou tiver acesso à rede onde está a ser comunicada a informação, terá visibilidade sobre o _plaintext_. Fazer uso do SSL, ou de algum tipo de sistema criptográfico, resolveria este problema, uma vez que seria possível cifrar toda a informação e assim garantir alguma segurança na comunicação.

- [OWASP 2017 - Information exposure through an error message](https://cwe.mitre.org/data/definitions/209.html). Ao executar uma operação, o atacante pode receber mensagens de erro com informação mais detalhada e relevante ao ponto de fornecer informações sobre outras funcionalidades da aplicação ou do sistema. Isto é, ao receber uma mensagem de erro pode descobrir como explorar e atacar outras características do software. A solução passa por reduzir a informação que se destaca nas mensagens de erro que aparecem durante o _runtime_, com funções facilmente implementáveis na fase de configuração.

********

### Pergunta P1.3

Uma **vulnerabilidade de dia zero** é uma vulnerabilidade que não é conhecida na comunidade de segurança informática (desenvolvedores de software, fabricantes de antivírus ou público em geral), mas que é conhecida num meio restrito. 

Por outro lado, uma **vulnerabilidade de codificação** encontra-se listada em bases de dados cujo objetivo é disponibilizar as diferentes vulnerabilidades existentes. Deste modo, toda a comunidade fica a conhecer as diferentes vulnerabilidades que cada software apresenta.
