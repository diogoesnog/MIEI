# Aula TP - 18/Mar/2019

## Pergunta P1.1: Análise do artigo 25º do regulamento geral de proteção de dados (RGPD) 
### Proteção de dados desde a concepção e por defeito

O tratamento de dados pessoais abrange um grande conjunto de operações levadas a cabo sobre os mesmos, por meios manuais ou automatizados. Estas
operações podem incluem recolha, registo, organização, estruturação, conservação, alteração, recuperação, consulta, utilização, disponibilização, 
comparação, eliminação e destruição de dados. Inerente à proteção das pessoas singulares, este tratamento é um direito pertencente aos titulares 
dos dados.

A evolução crescente da tecnologia e a globalização geram novos desafios no que diz respeito à proteção de dados, exigindo um nível de proteção sólido e
coerente. Organizações públicas e privadas, independentemente da área de negócio ou dimensão, sofrem consideráveis impactos no desenvolvimento de
*software*.

O artigo do RGPD aqui analisado condiciona o processo de desenvolvimento de *software*, na medida em que o mesmo envolve dados relacionados com
pessoas singulares identificada e identificável. A aplicação de medidas de pseudonimização, destinadas garantir a proteção de dados e
necessárias no tratamento dos mesmos, pode conduzir à redução dos riscos associados aos titulares dos dados e ajudar os
responsáveis pelo tratamento e os subcontratantes a cumprir as suas obrigações, respeitando todos os requisitos do regulamento e protegendo os
direitos dos titulares.

Quanto à privacidade, desde a concepção, os *softwares* devem conter parâmetros, adequadamente implementados, tendo em conta os custos da aplicação, a
natureza, o âmbito, o contexto e as finalidades do tratamento dos dados, bem como os riscos decorrentes do tratamento para os direitos e liberdades
das pessoas singulares (segundo os pontos **76** e **77** do regulamentos).

Os *softwares* devem ainda ter em conta os critérios de privacidade de forma a que os gestores dos mesmos, ou os responsáveis pelo tratamento,
apliquem medidas técnicas e medidas de organização, para assegurar que, por defeito, só exista tratamento dos dados pessoais que são necessários para
cada finalidade específica do tratamento. Esta exigência aplica-se à quantidade de dados pessoais recolhidos, à extensão do seu tratamento, ao seu
prazo de conservação e à sua acessibilidade. Em especial, essas medidas permitem que, por defeito, dados pessoais não sejam disponibilizados sem
intervenção humana a um número indeterminado de pessoas singulares. Existe assim necessidade, de por exemplo, criar níveis de permissões que
restrinjam o acesso aos dados de acordo com as funções e necessidades de cada colaborador.

Consequentemente, o responsável pelo tratamento deverá proceder, antes do mesmo, a uma avaliação do impacto sobre a proteção de dados, a fim de
avaliar a probabilidade ou gravidade particular do elevado risco, tendo em conta a natureza, o âmbito, o contexto e as finalidades do tratamento e as
fontes do risco (segundo o ponto **90**).

Na aplicação de todas estas medidas, é também essencial garantir que o *software* que processa os dados pessoais esteja preparado para cumprir o
regulamento de forma a garantir propriedades de segurança, como a confidencialidade, integridade e disponibilidade.


## Pergunta P1.2: Resumo das *Pseudonymisation techniques*


A **ENISA** produziu o documento *Recommendations on shaping technology according to GDPR provisions - An overview on data pseudonymisation*, sobre o
qual apresenta-se, de seguida, um resumo da secção 3: *Pseudonymisation techniques*.

A pseudonimização pode contribuir para ocultar a identidade real de um indivíduo, bem como para apoiar a desvinculação em diferentes domínios de
processamento de dados.  Assim, ao examinar diferentes técnicas de pseudonimização, é importante avaliar se os propósitos acima mencionados podem ser
alcançados e em que medida. É de salientar que uma abordagem de pseudonimização pode gerar ganhos adicionais de proteção de dados em termos de
precisão.

Segue-se a apresentação de algumas técnicas que podem ser utilizadas para a pseudonimização:

- *Hashing without key*

*Hashing* é uma técnica que pode ser usada para suportar a precisão dos dados e derivar pseudónimos.

Uma função *hash* criptográfica *h* é uma função com propriedades específicas, que transforma qualquer mensagem de entrada, *m*, de comprimento
arbitrário, num *output* de tamanho fixo *h(m)*, designado por valor de *hash* ou *message digest*.

Tendo em consideração as propriedades de resistência de pré-imagem do *message digest*, note-se que, para qualquer *hash*, o mesmo *digest* é sempre
produzido para o mesmo *input* (mesmo bloco de dados).

É importante observar que funções *hash* como MD5 e SHA-1, com vulnerabilidades conhecidas - probabilidade de encontrar colisões - devem ser evitadas.
E funções *hash* criptograficamente resistentes devem ser preferíveis, por ex. SHA-2 e SHA-3.

As propriedades mencionadas acima permitem que funções de *hash* sejam usadas em várias aplicações, incluindo integridade de dados e autenticação de
entidades. No entanto, o *hash* de identificadores de dados para fornecer pseudónimos apresenta grandes desvantagens:

**i)** qualquer terceiro que aplique a mesma função *hash* ao mesmo identificador obtém o mesmo pseudónimo;

**ii)** qualquer terceiro, consegue verificar se um pseudónimo corresponde a um dado identificador.


- *Hashing with key or salt*

A principal diferença das funções anteriores é que, para o mesmo *input*, vários pseudónimos diferentes podem ser produzidos, de acordo com a escolha
da chave específica.

O controlador de dados deve manter a chave secreta armazenada separadamente de outros dados, pois esta fornece os meios para associar os indivíduos
aoss identificadores originais.	

As funções de *hash* com chave podem conduzir à anonimização de dados, pois apagar a chave secreta inibe quaisquer associações entre pseudónimos e os
identificadores iniciais. Mais concretamente, tal seria equivalente a gerar um pseudónimo aleatório, sem qualquer conexão aos identificadores
iniciais.

Note-se que, poderiam utilizar-se funções de *hash* sem chave, mas que recebessem um *salt*, valor aleatório. Pois se o *salt* é destruído de forma
segura pelo controlador, não é fácil restaurar a associação entre pseudónimos e identificadores.

Contudo, a utilização de *salt* para proteção de *hashes* tem alguns inconvenientes: o *salt* não possui as mesmas propriedades de imprevisibilidade
que as chaves secretas (menor tamanho) e as funções de *hash* com chave são consideradas, por norma, criptograficamente mais fortes.

- *Encryption as a pseudonymisation technique*

Criptografia simétrica dos identificadores dos participantes de dados é também um método eficiente para obter pseudónimos. Nesta o identificador
original de um sujeito de dados pode ser cifrado através de um algoritmo de criptografia simétrica (por exemplo, o AES), fornecendo assim um
criptografia que deve ser usado como um pseudónimo; a mesma chave secreta é necessária para a decifragem.

A principal diferença desta técnica em relação às funções *hash* com chave, em termos de pseudonimização, é que o controlador de dados pode sempre
obter os identificadores iniciais dos sujeitos de dados, recorrendo à decifragem.  No entanto, existem também propriedades idênticas às funções *hash*
com chave:

**i)** a mesma chave secreta deve ser usada para fornecer o mesmo pseudónimo para o mesmo identificador, 

**ii)** se a chave for destruída, não é fácil associar um pseudónimo ao identificador inicial, mesmo se este estiver a ser armazenado pelo controlador
de dados.

Deste modo, a criptografia simétrica pode ser aplicada em casos em que um controlador de dados precisa de rastrear os dados, mas também de conhecer os
seus identificadores iniciais.

Note-se que também os algoritmos de criptografia de chave pública podem ser usados em casos específicos para fins de pseudonimização. 


- *Other cryptography-based techniques*

A combinação apropriada de vários esquemas criptográficos também pode fornecer abordagens robustas de pseudonimização, por exemplo, através do uso de
técnicas como computação multipartidária segura e criptografia homomórfica. Estas abordagens, embora dispendiosas, parecem ser as melhores opções nos
casos em que o princípio da proteção de dados necessita de assegurar que o controlador não deve ter conhecimento prévio da identidade do sujeito de
dados, a menos que este opte por provar a sua identidade.

- *Tokenisation*

Tokenização refere-se ao processo em que os identificadores de indivíduos são substituídos por valores gerados aleatoriamente, conhecidos como
*tokens*, sem existir qualquer relação matemática com os identificadores originais. Assim, o conhecimento de um *token* é útil apenas para o
controlador ou o processador.

No entanto, apesar da eficiência da tokenização, a sua implementação pode, dependendo do contexto, ser muito desafiante e complexa. A sincronização de
tokens em vários sistemas pode ser necessária em várias aplicações. 

Assim, abordagens que empregam funções *hash* com chave ou algoritmos de criptografia podem ser preferíveis com relação à redução da complexidade e do
armazenamento.

- Outras abordagens

Existem muitas outras técnicas conhecidas no contexto de pseudonimização, como *masking*, *scrambling* e *blurring*, todas elas com foco em dados de
pseudonimização estão armazenados num arquivo ou banco de dados.

Resumidamente, *Masking* refere-se ao processo de ocultar parte do identificador de um indivíduo com caracteres aleatórios ou outros dados.
*Scrambling* é um processo que pode ser reversível ou não e refere-se a técnicas para misturar ou ofuscar características. *Blurring* é outra técnica,
que visa utilizar uma aproximação de valores de dados, de modo a reduzir a precisão dos mesmos, reduzindo a possibilidade de identificação dos
indivíduos.

Outras técnicas conhecidas, neste contexto, são as técnicas associadas aos códigos de barras, códigos QR ou similares, que visam principalmente
suportar a precisão dos dados, invés de fornecer uma solução de pseudonimização.

## Pergunta P1.3
O _ARTICLE 29 DATA PROTECTION WORKING PARTY_ publicou o [_Guidelines on Data Protection Impact Assessment (DPIA) and determining whether processing is
“likely to result in a high risk” for the purposes of Regulation 2016/679_](Aula7/EU.20171013_wp248_rev01_enpdf.pdf) em que indica os nove critérios
que devem ser considerados para avaliar se o processamento de dados pessoais irá resultar num risco elevado, devendo ser efetuado um DPIA sempre que o
processamento satisfizer dois desses critérios.

### Critérios de Avaliação
1. Avaliação ou pontuação;
2. Tomada de decisão automatizada com efeito legal ou similar significativo;
3. Monitorização Sistemático;
4. Dados sensíveis ou dados de natureza altamente pessoal;
5. Dados processados em grande escala;
6. Correspondência ou combinando conjuntos de dados;
7. Dados relativos a sujeitos vulneráveis;
8. Uso inovador ou aplicação de novas soluções tecnológicas ou organizacionais;
9. Quando o tratamento em si “impede que os titulares de dados exerçam um direito ou utilizem um serviço ou contrato”.

A título de exemplo consideremos um projeto que consiste numa aplicação de orientação académica para alunos que estejam numa determinada etapa de
transição, seja ensino básico-secundário, ensino secundário-universitário, entre outras.

Esta aplicação permite a disponibilização de informações, de modo a impulsionar reflexão nos alunos, e testes de carácter pedagógico e vocacionais,
supervisionados por especialistas qualificados. 

Adicionalmente, esta aplicação terá a intervenção de psicólogos e professores, que durante o processo de apoio na tomada de decisão do aluno, têm
acesso ao respetivo desenvolvimento do mesmo, com base nos resultados dos testes efetuados por este.

As credenciais de acesso dos alunos são disponibilizadas pelas escolas, que aderem à presente aplicação, e as credências de acesso dos especialistas
sãos disponibilizadas pelos mesmos, no momento em que se disponibilizam para serem orientadores neste projeto.

Cada aluno terá o seu perfil, acompanhado de informações básicas como: nome da escola, ano, turma, número de aluno, nome completo, nome de utilizador,
endereço de *email*, foto, *password*; e cada especialista será caracterizado por: nome completo, nome de utilizador, profissão, endereço de *email* e
*password*.

Após a autenticação dos alunos, estes serão abordados com algumas questões, de modo a efetuar-se uma primeira triagem de opções, tanto vocacionais
como de selecção do especialista que melhor o consegue acompanhar. Posteriormente, o aluno será convidado, pelo especialista que lhe foi atribuído, a
efectuar determinados testes. 

Todos esses testes serão armazenados de acordo com o nome da escola, ano e turma que o aluno frequenta, ano letivo e especialista responsável pelo seu
acompanhamento. Mais ainda, estes testes são analisados e acrescentados ao respetivo histórico. Este, por sua vez, apenas está acessível ao aluno e ao
seu especialista, tendo este último ainda acesso às estatísticas extraídas dos testes.

A escola possui a capacidade de eliminar a conta de um dado aluno, sendo, nesses casos,  removidos todos os dados associados a este, à excepção do
respetivo histórico anónimo, que é conservado para fins estatísticos.

Note-se que a aplicação apresentada suporta dois dos critérios enunciados acima: monitorização sistemática (resultante da execução de testes
periódicos) e dados relativos a sujeitos vulneráveis (alunos); devendo-se assim efetuar um DPIA.


### Segue-se o [template DPIA preenchido](ICO.pdf).



## Resposta à pergunta P1.4

O **CNIL** disponibilizou uma ferramenta open-source para ajudar no _Data Protection Impact Assessment_ (DPIA) em
https://www.cnil.fr/en/open-source-pia-software-helps-carry-out-data-protection-impact-assesment.

Após a instalação da ferramenta, que se encontra em https://www.cnil.fr/en/open-source-pia-software-helps-carry-out-data-protection-impact-assesment,
utilizou-se a mesma para o DPIA do projeto anterior, preenchendo sucintamente todas as componentes pedidas. 


### Como resposta a esta pergunta segue-se o documento em formato PDF: [PIA](PIA.pdf)
