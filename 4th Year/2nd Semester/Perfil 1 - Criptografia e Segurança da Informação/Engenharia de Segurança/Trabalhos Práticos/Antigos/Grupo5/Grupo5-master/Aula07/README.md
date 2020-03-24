# Trabalho Prático 4 - 18/Mar/2019

## 1. RGPD (Regulamento Geral de Proteção de Dados)

### Pergunta P1.1

> O grupo escolheu analisar a secção *Storage limitation principle* do livro *Handbook on European data protection law*.

Tanto o artigo 5 (1) (e) do Regulamento Geral de Proteção de Dados (RGPD) como o artigo 5 (4) (e) da *Modernised Convention 108* requerem que dados pessoais sejam mantidos em formulários, que permitam a identificação de indivíduos, apenas pelo tempo necessário tendo em conta os propósitos para os quais os dados são processados. Assim, os dados devem ser apagados ou anonimizados quando esses propósitos forem cumpridos (**princípio da limitação de armazenamento**). Com este objetivo, o controlador deve estabelecer limites de tempo para remover ou efetuar uma revisão periódica, de forma a assegurar que os dados não são mantidos por mais tempo que o necessário.

Por exemplo, no caso *S. and Marper*, o Tribunal Europeu dos Direitos Humanos (*European Court of Human Rights* - ECtHR) estabeleceu que a retenção de impressões digitais e amostras de ADN por tempo indefinido era desproporcional e desnecessária numa sociedade democrática, considerando que os processos criminais contra os dois requerentes tinham sido terminados por absolvição e desistência, respetivamente.

O armazenamento de dados com objetivos de interesse público, científicos, históricos ou estatísticos pode ser efetuado por períodos de tempo superiores, desde que esses dados apenas sejam utilizados com os propósitos referidos. Devem ser implementadas medidas técnicas e organizacionais adequadas para o armazenamento corrente e utilização de dados pessoais, de forma a salvaguardar os direitos e liberdade dos indivíduos em questão.

A *Modernised Convention 108* também permite exceções ao princípio de limitação de armazenamento, na condição destas verificarem o seguinte:

* estarem previstas na lei;
* respeitarem a essência dos direitos fundamentais e liberdades;
* serem necessários e proporcionais para cumprir um número limitado de objetivos legítimos (e.g., proteger a segurança nacional, investigar e processar infrações penais, aplicar sanções penais, proteger o individuo em causa e os direitos e liberdades fundamentais de outros).

Assim, há necessidade de se prever a possibilidade de remover ou anonimizar dados pessoais que não são utilizados à algum tempo, manualmente ou automaticamente (periodicamente), quando se desenvolve *software*.


### Pergunta P1.2

A pseudonimização permite a ofuscação da identidade de um indivíduo, bem como tornar a sua procura impossível através de diferentes domínios de processamento de dados. Deste modo, considera-se que as técnicas de pseudonimização tenham de cumprir dois objetivos:
+ Os pseudónimos de um dado indivíduo não podem ser fáceis de identificar por partes exteriores a um dado contexto de dados (D1).
+ Os pseudónimos não serão simples de reproduzir por terceiros, de modo a evitar que diferentes contextos de dados utilizem o mesmo pseudónimo para cada determinado indivíduo, certificando que nenhum utilizador pode ser ligado a qualquer pseudónimo (D2).

Para tal, foi desenvolvido um conjunto de técnicas pela ENISA que pretendem proteger a identidade de indivíduos como medida de segurança.

#### *Hashing without key*

Uma função de *hash* criptográfica `h` (e.g. SHA-2 e SHA-3) tem como objetivo transformar qualquer mensagem `m` de tamanho arbitrário num valor de *hash* `h(m)` de tamanho fixo. Apesar destas funções terem propriedades como *pre-image resistance*, *2nd pre-image resistance* e *collision resistance*, não cumprem alguns dos requisitos necessários na pseudonimização como:

- **D1**: é trivial verificar, por terceiros, se um pseudónimo corresponde a um dado identificador.
- **D2**: terceiros conseguem aplicar a mesma função de *hash* e a partir de um identificador obter o mesmo pseudónimo.

Desta forma, esta técnica é considerada pelo RGPD como sendo fraca, pois pode ser revertida sem informação adicional. Logo, não deve ser usada isoladamente para obter pseudonimização.

#### *Hashing with key or salt*

As funções de *hash* com chave podem ser utilizadas para anonimizar dados, uma vez que apagar a chave secreta elimina quaisquer associações entre pseudónimos e os identificadores iniciais. Isto seria equivalente, de forma geral, a gerar pseudónimos aleatórios, sem qualquer ligação aos identificadores iniciais.

Da mesma forma, poderiam-se utilizar funções de *hash* sem chave, mas que recebem um *salt* (dados aleatórios), pois se este é destruído de forma segura pelo controlador, não é trivial recuperar a associação entre pseudónimos e identificadores.

Contudo, o *salt* não possui as mesmas propriedades de imprevisibilidade que as chaves secretas (tamanho inferior) e as funções de *hash* com chave são consideradas, geralmente, criptograficamente mais fortes.

#### *Cifra como técnica de pseudonimização*

A utilização de cifras simétricas, tais como o AES, é também considerado um método eficiente de gerar pseudónimos. Nestes, o identificador de um indivíduo é cifrado com uma chave simétrica que deverá ser conhecida apenas pelo controlador e processador dos dados, que, quando necessário, é utilizada para decifrar o pseudónimo para recuperar o identificador original.

Tal como no caso das funções de *hash*, as chaves utilizadas têm um tamanho mínimo de 256 bits, tamanho considerado razoável para segurança mesmo em contexto quântico. No entanto, ao contrário das funções de *hash*, o controlador pode, a qualquer momento, recuperar o identificador do sujeito através de uma operação de decifragem. Assim, torna-se mais difícil o *tracking* de indivíduos devido ao facto de que estes não necessitam guardar os identificadores.

Por outro lado, as cifras assimétricas têm também um conjunto de caraterísticas que as tornam úteis na pseudonimização. A sua estrutura de chave pública ajusta-se bem para contextos nos quais o controlador de dados, responsável por efetuar a pseudonimização, não está autorizado para recuperar a respetiva identidade, utilizando a chave pública correspondente a um controlador que guarda a respetiva chave privada. Deste modo, permite-se a separação de tarefas de segurança. Ainda mais, recorrendo à utilização de valores aleatórios, assegura-se que os pseudónimos gerados não podem ser utilizados para seguir o percurso de um indivíduo através de vários contextos de dados.

É de notar, no entanto, que algoritmos de chaves assimétricas são bastante menos eficientes do que os de chaves simétricas, necessitando chaves de tamanho elevado, 3072 bits no caso do RSA. Mesmo recorrendo a curvas elíticas, que utilizam chaves bastante menores, incorrem tempos de processamento mais longos.

#### Outras técnicas baseadas em criptografia

Além das abordagens anteriormente mencionadas, é possível combinar esquemas criptográficos e obter um abordagem de pseudonimização segura. A título exemplificativo, tem-se a geração de diferentes pseudónimos para os vários domínios que compõe um sistema, através de *polymorphic encryption*. 

Mais ainda, existem as soluções descentralizadas. Nestas, cada participante gera e controla os seus próprios pseudónimos. De facto, esta é uma estratégia muitas vezes aplicada quando o controlador dos dados não pode ter conhecimento prévio da identidade dos utilizadores, ou seja, o acesso apenas é conseguido depois do utilizador assim o entender.

Por fim, referir que o desafio que todos os métodos enfrentam está relacionado com a gestão da chave. Este processo não é de todo trivial, uma vez que depende tanto da escala da aplicação, como da própria técnica escolhida.

#### *Tokenisation*

Tokenização refere-se ao processo em que os identificadores de indivíduos são substituídos por valores gerados aleatoriamente, conhecidos como *tokens*, sem existir qualquer relação matemática com os identificadores originais. Assim, o conhecimento de um *token* é inútil para qualquer um, exceto o controlador ou o processador.

<!--
Como existe uma entidade que armazena o mapeamento oculto (de dados originais para um *token* aleatório), a re-identificação de indivíduos pelo controlador de dados será possível em todos os casos, incluindo para efetuar rastreamento, desde que haja apenas um mapeamento para cada identificador.
-->

Apesar da eficiência da tokenização, a sua implementação pode, dependendo do contexto, ser relativamente complexa. De facto, em várias aplicações pode ser necessário, por exemplo, a sincronização de *tokens* através de vários sistemas.

#### Outras medidas

Existem também outras medidas bem conhecidas cujo objetivo são pseudonimisar a informação guardada num ficheiro, sendo estas relativamente limitadas na sua aplicação:

+ *Masking* refere-se ao processo de esconder o identificador de um indivíduo com carateres aleatórios ou outros dados. Tal prática nem sempre pode garantir as propriedades de pseudonimização. Ainda mais, se implementado pouco cuidadosamente, poderá atribuir o mesmo pseudónimo a indivíduos diferentes, gerando colisões.
+ *Scrambling* refere-se a um conjunto de técnicas de mistura e ofuscação de carateres de um identificador. Este processo é reversível de acordo com a técnica escolhida. O *Scrambling* pode ser considerado uma forma de cifra simétrica simplificada, tornando a fraca na manutenção da pseudonimização em casos específicos.
+ *Blurring* trata-se da utilização de valores aproximados com o intuito a precisão dos dados, reduzindo a identificabilidade dos indivíduos. Esta técnica pode também ser aplicada na ofuscação de imagens no processo de pseudonimização. É de notar, no entanto, que algoritmos de reconhecimento de imagens com redes neuronais poderão ser capazes de recuperar tais imagens.

### Pergunta P1.3 - 1

Os nove critérios que devem ser considerados para avaliar se o processamento de dados pessoais irá resultar num risco elevado são os seguintes:

1. **Avaliação e pontuação**, incluindo a criações de perfis e previsão, especialmente se envolver aspetos relacionados com dados do desempenho no trabalho, situação económica, saúde, preferências pessoais ou interesses, confiabilidade ou comportamento, localização ou movimentos.

2. **Realização automática de decisões relacionadas com aspetos legais ou de igual importância**. Por exemplo, o processamento pode levar a exclusão ou discriminação de indivíduos.

3. **Monitorização sistemática**: processamento usado para observar, monitorizar ou controlar indivíduos, incluindo dados armazenados através de redes ou uma monitorização sistemática de uma área de acesso público. Este é um critério uma vez que os indivíduos podem não ter conhecimento que estão a ser recolhidos dados a seu respeito. Mais ainda, pode ser impossível evitar tal processamento caso este seja feito em espaços públicos.

4. **Dados sensíveis ou de natureza altamente pessoal**: inclui dados pessoais como opinião política, registo criminal, registo médico, informações armazenadas por investigadores privados, documentos pessoais, emails, diários, notas, informação pessoal encontrada em aplicações que façam um registo da vida do indivíduo, entre outros. Estes dados pessoais são considerados sensíveis, porque estão ligados ao agregado familiar e atividades privadas, ou porque influenciam o exercício de um direito fundamental, ou porque a sua violação claramente acarreta sérios impactos na vida do dia à dia do indivíduo. Neste critério é importante ter em conta se os dados já foram tornados públicos pelo indivíduo ou se for através de terceiros. Se foi tornado público importa averiguar se era esperado que os dados fossem processados de determinada forma.

5. **Processamento de dados em grande escala**: apesar de o RGPD não definir o que é considerado grande escala, é importante ter em conta os seguintes fatores na sua definição:

	1. o número de indivíduos afetados;
	2. o volume de dados a ser processado;
	3. a duração ou permanência do processamento dos dados;
	4. a extensão geográfica abrangida pelo processamento dos dados.

6. **Combinação de datasets**: por exemplo, combinando dois ou mais *datasets*, que foram criados com diferentes propósitos, de forma a extrapolar os objetivos para os quais os dados foram cedidos.

7. **Dados relacionados com indivíduos vulneráveis**: a existência deste critério está relacionada com a discrepância de poder entre quem controla os dados e o seu titular, ou seja, os indivíduos podem não conseguir consentir, opor-se ao processamento dos seus dados ou exercer os seus direitos. De entre os indivíduos vulneráveis tem-se as crianças, empregados, funcionários, segmentos da população que necessitam de proteção especial (e.g. pessoas com doenças mentais, idosos, pacientes, etc) e todo e qualquer caso em que exista um desequilíbrio entre a posição do indivíduo dos dados e o controlador dos mesmos.

8. **Uso inovador ou aplicação de nova tecnologia ou soluções organizacionais**: por exemplo, a combinação do uso da impressão digital com reconhecimento facial para melhorar o controlo de acesso físico, entre outros. De realçar que as consequências pessoais e sociais do desenvolvimento de novas tecnologias são desconhecidas, e por isso deve ser feito um DPIA para avaliar tais fatores.

9. Quando o processamento em si **previne os indivíduos de exercer um direito ou usar um serviço ou contrato**. Isto inclui operações de processamento que têm como objetivo permitir, modificar ou recusar que os indivíduos tenham acesso a um serviço ou contrato. A título exemplificativo, quando um banco processa os dados dos seus clientes numa base de dados com referências de créditos de forma a perceber se pode fazer um empréstimo ou não.

Assim sendo, para avaliar se um dado processamento representa um risco elevado, os nove critérios apresentados devem ser tidos em conta. Sendo que, se dois deles forem aplicáveis, então deve ser efetuado um DPIA.

### Pergunta P1.3 - 2

O projeto que se pretende desenvolver consiste numa aplicação educativa para crianças, que permite a disponibilização de informações e testes relacionados com temas de carácter pedagógico, bem como estatísticas de acerto para o utilizador corrente. Para além disso, esta aplicação deverá permitir que professores consultem o desenvolvimento dos seus alunos.

As credenciais de acesso dos alunos e professores são disponibilizadas pela escola. Cada aluno terá associado ao seu perfil os seguintes dados: número de aluno, nome completo, nome de utilizador, *password*, escola, ano e turma. Cada professor será caracterizado por: nome completo, nome de utilizador, *password* e escola.

Após a autenticação, os professores podem disponibilizar informações e testes para os alunos de um ano e turma, num determinado ano letivo. Posteriormente, os alunos realizam os testes, que são automaticamente corrigidos e acrescentados ao respetivo histórico. Este, por sua vez, apenas é acessível pelo próprio aluno. Mais ainda, o professor tem acesso às estatísticas dos testes por si efetuados, para os vários alunos.

A escola tem a possibilidade de apagar a conta de um aluno ou professor. Nesse caso, são removidos todos os dados associados ao utilizador, exceto o respetivo histórico (anonimizado), que é mantido para fins estatísticos.

Desta forma, a aplicação proposta respeita os critérios 3 (monitorização sistemática) e 7 (dados sobre sujeitos vulneráveis) enunciados na pergunta anterior, pelo que é necessário efetuar o DPIA.


### Pergunta P1.3 - 3

O *template* DPIA encontra-se no ficheiro [PIA-1.3.3](./PIA-1.3.3.pdf).

### Pergunta P1.4

O *template* DPIA encontra-se no ficheiro [PIA-1.4.3](./PIA-1.4.3.pdf).
