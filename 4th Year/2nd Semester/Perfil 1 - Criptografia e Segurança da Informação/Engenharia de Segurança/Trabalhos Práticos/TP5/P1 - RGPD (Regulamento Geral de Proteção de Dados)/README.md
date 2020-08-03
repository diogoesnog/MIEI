# Pergunta 1 - RGPD (Regulamento Geral de Proteção de Dados)

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Experiência 1.1**](#experiência-11---regulamento-ue-2016679-rgpd) - **Regulamento (UE) 2016/679 (RGPD)**
    - Análise do Artigo 32.º - Segurança do tratamento
    - Escrita de pequeno texto que reflete a forma como este artigo pode influir no desenvolvimento de *software*

2. [**Pergunta P1.1**](#pergunta-11---recommendations-on-shaping-technology-according-to-gdpr-provisions---exploring-the-notion-of-data-protection-by-default) - ***Recommendations on shaping technology according to GDPR provisions - Exploring the notion of data protection by default***
	- Análise da Secção 3 - *Data protection by default in practice*
	- Pequeno resumo da mesma

3. [**Experiência 1.3**](#experiência-13---guidelines-on-data-protection-impact-assessment-dpia-and-determining-whether-processing-is-likely-to-result-in-a-high-risk-for-the-purposes-of-regulation-2016679) - ***Guidelines on Data Protection Impact Assessment (DPIA) and determining whether processing is “likely to result in a high risk” for the purposes of Regulation 2016/679***
	- Nove critérios a ser considerados na avaliação do risco do processamento de dados pessoais
	- Projeto hipotético que envolva a utilização de dados pessoais
	  - Explicação do projeto
	  - Processamento dos dados pessoais
	  - Critérios que satisfaz
	  - Template DPIA

4. [**Experiência 1.4**](#experiência-14---ferramenta-usada-para-o-data-protection-impact-assessment-dpia) - **Ferramenta usada para o *Data Protection Impact Assessment* (DPIA)**
	- Utilização da ferramenta no projeto hipotético pensado anteriormente

5. [**Pergunta P1.2**](#pergunta-p12---handbook-on-security-of-personal-data-processing) - ***Handbook on Security of Personal Data Processing***
    - Análise do caso de uso *Marketing/advertising*
    - Passos metodológicos seguidos até à avaliação do risco
    - Medidas propostas para diminuir/mitigar determinados riscos

---

## Resolução da Pergunta 1

### Experiência 1.1 - Regulamento (UE) 2016/679 (RGPD)

O artigo escolhido para esta pequena análise foi o Artigo 32.º, cujo tema assenta sobre a **Segurança do tratamento**. De modo a compreender melhor toda esta secção e aproveitando já para contextualizar com o tema primordial em si, veja-se no significado do RGPD.

> *The **General Data Protection Regulation** (EU) [2016/679](https://eur-lex.europa.eu/eli/reg/2016/679/oj) (**GDPR**) is a [regulation](https://en.wikipedia.org/wiki/Regulation_(European_Union)) in [EU law](https://en.wikipedia.org/wiki/EU_law) on [data protection](https://en.wikipedia.org/wiki/Data_protection) and privacy in the [European Union](https://en.wikipedia.org/wiki/European_Union) (EU) and the [European Economic Area](https://en.wikipedia.org/wiki/European_Economic_Area) (EEA). It also addresses the transfer of [personal data](https://en.wikipedia.org/wiki/Personal_data) outside the EU and EEA areas. The GDPR aims primarily to give control to individuals over their personal data and to simplify the regulatory environment for [international business](https://en.wikipedia.org/wiki/International_business) by unifying the regulation within the EU.*

Assim se entende que este regulamento visa proteger os dados pessoais dentro da comunidade europeia, surgindo assim como objetivo de garantir uma segurança mais eficaz aos cidadãos em si.

<br/>

**Atente-se nas seguintes considerações iniciais que são importantes ter em conta para a reflexão que vai ser feita para este artigo:**

- **Consideração N.º 74** 

  > Deverá ser consagrada a responsabilidade do responsável por qualquer tratamento de dados pessoais realizado por este ou por sua conta. Em especial, o responsável deverá ficar obrigado a executar as medidas que forem adequadas e eficazes (...)

  Isto significa que o responsável pelos dados está responsável por executar as medidas de segurança que forem necessárias.

- **Consideração N.º 75**

  >O risco para os direitos e liberdades das pessoas singulares, cuja probabilidade e gravidade podem ser variáveis, poderá resultar de operações de tratamento de dados pessoais suscetíveis de causar danos físicos, materiais ou imateriais (...)

  Fala-se do risco que surge no uso dos dados pessoais de indivíduos, que variam consoante determinados fatores.

<br/>

Estas considerações inicias trazem noções necessárias para este Artigo N.º 32. O mesmo começa por deixar claro que devido à globalização e consequente evolução tecnológica por parte das diversas técnicas acaba por ser preciso estabelecer um controlo mais pesado em relação à natureza dos dados pessoais, o seu armazenamento, tratamento e respetivo acesso.

**Assim, define as medidas técnicas e organizativas adequadas para assegurar um nível de segurança apropriado ao risco:**

- Pseudonimização e cifragem dos dados pessoais;
- Capacidade de assegurar a confidencialidade, integridade, disponibilidade e resiliência dos sistemas e serviços de tratamento;
- Capacidade de restabelecer a disponibilidade e o acesso aos dados pessoais atempadamente, caso existam incidentes físicos ou até mesmo técnicos;
- Existência de um processo para testar, apreciar e consequentemente avaliar regularmente a eficácia das medidas técnicas e organizativas de modo a garantir a segurança do tratamento.

<br/>Se pensarmos nestas medidas em termos práticos e tentarmos "encaixa-las" no processo de desenvolvimento dum *software* entendemos ainda mais a sua importância e de que forma podem atuar/influenciar de forma positiva nestes tipos de desenvolvimentos, e vice-versa. A tabela abaixo permite obter uma noção basilar acerca destas duas relações.



| RGPD -> Software                                                                                                                                                                                                                                                                                                                                                                         | Software -> RGPD                                                                                                                                                                                                                                                                                                                                                                                                                            |
| ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A ideia é que se tenha uma atenção reforçada ao nível dos dados pessoais ao longo de todo o processo de desenvolvimento de *software*. <br />Isso deve ser feito usando-se técnicas que garantam a segurança dos dados, ao mesmo tempo que se avaliam essas mesmas técnicas, deixando assim clara a certeza de que o sistema está integrado num plano de técnicas perfeitamente seguras. | O *software* pode ajudar a estabelecer um encontro entre o RGPD, ao mesmo tempo que traz benefícios para o negócio. Através do *software* podemos realizar um conjunto de processos obrigatórios ao regulamento, evitando intervenções manuais com custos superiores.<br />Dessa forma, simplifica na execução de determinadas medidas que são impostas, como o acesso aos dados, o seu rastreamento e ainda as suas respetivas limitações. |

---

### Pergunta P1.1 - *Recommendations on shaping technology according to GDPR provisions - Exploring the notion of data protection by default*

Perante os critérios de escolha definidos para os vários grupos, cabe-nos analisar a Secção 3 do documentos em causa, de seu título *Data protection by default in practice*.

Esta secção apresenta como objetivo a apresentação de apresentar práticas recomendadas para definir estes dos padrões existentes para a proteção de dados. Deixa-se claro que estes exemplos visam apenas demonstrar como a proteção de dados por padrão pode ser aplicada em termos práticos e quais os desafios inerentes a esta implementação.

<br/>

- **Critério N.º 1: *Minimum amount of personal data***, Quantidade mínima de dados pessoais.

| Prática                                                                                                          | Descrição da Prática                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| ---------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| "***The less data, the better***", Quanto menos data, melhor.                                                    | Recolher apenas os dados que sejam considerados estritamente necessários. <br />**Exemplo:** Formulários online. Neste caso pode-se minimizar a quantidade de dados pessoais que são recolhidos do utilizador.                                                                                                                                                                                                                                                               |
| "***Granular collection of data on the basis of necessity***", Coleta granular dos dados baseada na necessidade. | Garantir que a recolha de dados seja feita de forma granular. A ideia é ir recolhendo os dados consoante a necessidade gradual dos serviços prestados.<br />**Exemplo:** Pagamentos online antecipados. Neste caso não há a necessidade de pedir ao utilizador uma quantidade de dados tão grande à partida.                                                                                                                                                                 |
| "***Use of privacy enhancing technologies***", Uso de tecnologias que melhorem a privacidade.                    | Fala-se do uso de técnicas criptográficas, de pseudonimização ou anonimização perante cada caso, no sentido de melhorar a segurança e a privacidade dos dados.<br />**Exemplo:** Gerir maiores de idade para compras de bebidas alcoólicas. Em vez de se retirar o ano de nascimento, implementar um mecanismo/técnica que verifica se a condição de "maior de idade" é cumprida. Assim, em vez de retirarmos a data de nascimento, retiramos o resultado dessa verificação. |
| "***Different minimum per purpose***", Diferentes mínimos para cada propósito.                                   | Definir o minímo de dados perante cada situação.<br />**Exemplo:** O acesso ao microfone não deve ser obrigatório em todo o tipo de aplicações.                                                                                                                                                                                                                                                                                                                              |

<br/>

- **Critério N.º 2: *Minimum extent of the processing of the personal data***, Mínima extensão do processamento dos dados pessoais.

| Prática                                                                      | Descrição da Prática                                                                                                                                                                                                             |
| ---------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| "***The less processing, the better***", Quanto menos processamento, melhor. | Diminuir a quantidade de dados que são processados, o que não significa reduzir a quantidade de operações de processamento. <br />**Exemplo:** Deixar de armazenar dados pessoais em casos que seja possível trabalhar sem eles. |
| "***User empowering tools***", Ferramentas de empoderamento do usuário.      | Deixar que o titular dos dados pessoais em causa saiba o rumo de todos esses dados, ou seja, o que será feito com os mesmos.                                                                                                     |

Ter em mente que *less processing* inclui também *less data*, *less storage* e *less acessibility*. Dessa forma, este critério deve ser combinado com outros conjuntos de práticas que englobem estes conceitos.

<br/>

- **Critério N.º 3: *Minimum period of the storage of the personal data***, Mínimo período do armazenamento dos dados pessoais.

| Prática                                                                           | Descrição da Prática                                                                                                      |
| --------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------- |
| "***Storage - the shorter, the better***", Quanto menos tempo armazenado, melhor. | Diminuir o período de armazenamento para os dados pessoais., dado que nem sempre o armazenamento permanente é necessário. |

Para este critério, deixa-se evidente que esta minimização do armazenamento pode-se conseguir através do uso de tecnologias que melhorem segurança e privacidade dos dados. 

<br/>

- **Critério N.º 4: *Minimum accessibility of the personal data***, Mínima acessibilidade aos dados pessoais

| Prática                                                                                                  | Descrição da Prática                                                                                                                                                                                                                                                                                                                                                   |
| -------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| "***Restricting access on the basis of necessity***", Restringir o acesso consoante a necessidade.       | Uso de políticas e controles de acesso, projetados consoante o princípio da necessidade de conhecimento.                                                                                                                                                                                                                                                               |
| "***Limiting ways of sharing***", Limitar as formas de compartilhar dados                                | Tendo em conta que existe uma facilidade em copiar e partilhar informação parra outros destinatários, devem existir técnicas que definam permissões para esse tipo de ações, de modo a limitar esta partilha excessiva e desautorizada.                                                                                                                                |
| "***No public by default without active intervention***", Impedir que o dado se torne público por padrão | Os dados precisam ser privados/restritos por padrão. A ideia é que exista uma intervenção ativa por parte do titular para que os mesmos possam ser divulgados para os demais.<br />**Exemplo**: Redes Sociais. Este é o melhor exemplo que se pode dar. Fala-se quando queremos limitar certas informações nossas para que sejam visíveis apenas pela lista de amigos. |

---

### Experiência 1.3 - *Guidelines on Data Protection Impact Assessment (DPIA) and determining whether processing is “likely to result in a high risk” for the purposes of Regulation 2016/679*

Este artigo surge como uma mais valia no processamento de dados, dado que fornece informações essenciais acerca deste processo e ajuda a avaliar os riscos associados ao mesmo. Aborda ainda a noção de DPIA como medida a ter em conta sempre que este processamento de dados satisfaça um conjunto de critérios que o artigo induz a considerar.

<br/>

#### Alínea I. Noves critérios a considerar na avaliação do risco do processamento de dados pessoais

1. *Evaluation or scoring*
2. *Automated-decision making with legal or similar significant effect*
3. *Systematic monitoring*
4. *Sensitive data or data of a highly personal nature*
5. *Data processed on a large scale*
6. *Matching or combining datasets*
7. *Data concerning vulnerable data subjects*
8. *Innovative use or applying new technological or organisational solutions*
9. *Prevents data subjects from exercising a right or using a service or a contract*

<br/>

#### Alínea II. Conceção de um projeto que envolve a utilização de dados pessoais

Nesta alínea importa idealizar um projeto que envolva a utilização de dados pessoais cujo seu processamento resulte num risco elevado.

<br/>

Dadas as circunstâncias atuais, o projeto consistiria numa *web app* para informar os seus utilizadores registados acerca do estado do COVID-19 e seu devido acompanhamento. **A ideia desta *web app* seria focar-se na região geográfica do utilizador, no sentido de o colocar a par de toda a informação  e prestar a assistência necessária:**

- Informações acerca do número de infetados em tempo real;
- Informações acerca do número de recuperados e mortos em tempo real;
- Divulgação de gráficos acerca do estado atual do COVID-19 no mundo e, principalmente, na região em específica;
- Assistência *online* relativamente à compra de medicamentos, comida e outros bens essenciais;
  - Esta assistência seria conjugada com o posterior envio à casa do utilizador com todas as medidas de higiene.

<br/>

**Estas seriam as ideias gerais para o projeto, mas para tal acontecer teria de existir a facultação de dados por parte do utilizador:**

- Nome de Utilizador/Email;
- Morada (tanto para as informações do COVID-19 como para a assistência necessária);
- Dados Bancários (para processar os devidos pagamentos);

**Dessa forma, iriam-se satisfazer os seguintes critérios:**

- *Sensitive data or data of a highly personal nature*
- *Data processed on a large scale*

<br/>

#### Alínea III. Preenchimento do *template* DPIA

O *template* DPIA foi devidamente preenchido, encontrando-se em modo [PDF](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP5/P1%20-%20RGPD%20(Regulamento%20Geral%20de%20Prote%C3%A7%C3%A3o%20de%20Dados)/DPIA.pdf) em anexo neste repositório.

---

### Experiência 1.4 - Ferramenta usada para o *Data Protection Impact Assessment* (DPIA)

O PIA está em modo [PDF](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP5/P1%20-%20RGPD%20(Regulamento%20Geral%20de%20Prote%C3%A7%C3%A3o%20de%20Dados)/pia-COVID%20app.pdf) e [ZIP](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP5/P1%20-%20RGPD%20(Regulamento%20Geral%20de%20Prote%C3%A7%C3%A3o%20de%20Dados)/pia-COVID%20app.zip) na pasta deste repositório.

---

### Pergunta P1.2 - *Handbook on Security of Personal Data Processing*

O documento a analisar apresenta uma metodologia para avaliar o risco de segurança no processamento de dados pessoais e alguns casos de uso para calcular o nível de risco associado. O caso de uso a avaliar pelo nosso grupo é a secção de *Marketing/Advertising* duma empresa.

Este caso de uso pega numa pequena e média empresa que processa os dados pessoais de potenciais clientes para promover os seus produtos. Para esta operação, utiliza uma ferramenta *web* oferecida por terceiros que se especializam nestas atividades de publicidade e *marketing*. Assim cria-se uma *mailing list* e cada semana uma campanha de *marketing* acontece e a ferramenta *web* dá um relatório com estatísticas sobre os *emails* que foram lidos, ignorados ou apagados, mas sem informações detalhadas sobre as pessoas envolvidas em cada parte.

<br/>

| Descrição de operação          | Marketing e publicidade                                   |
| ------------------------------ | --------------------------------------------------------- |
| Dados pessoais processados     | Informação de contacto (nome, endereço, telefone e email) |
| Propósito                      | Publicidade de artigos e ofertas novas                    |
| Sujeito dos dados              | Clientes e potenciais clientes                            |
| Meios de processamento         | Serviço web de terceiros                                  |
| Destinatários dos dados        | Departamento de marketing, CRM, e o serviço Web           |
| Processador de dados escolhido | Empresa que criou o *web service* de marketing            |

O impacto na perda de confidencialidade e/ou integridade e/ou disponibilidade dos dados é considerado **BAIXO**, dado que a inconveniência máxima que pode acontecer é a divulgação dos dados que pode surgir *spam* ou a eliminação dos mesmos, que os pode excluir duma campanha de *marketing* ideal.
Fugindo ao exemplo seguido no documento, o impacto pode ser maior caso o processamento de dados pessoias inclua hábitos, preferências, origens étnicas, opiniões políticas ou informações de saúde. Dessa forma acontece um *profiling* mais sério, levando ao impacto ser **MÉDIO** caso terceiros tenham acesso a esses dados de forma anónima, ou **ALTO** caso o *profiling* seja baseado em informação sensível.

<br/>

| Área de análise                                  | Probabilidade (Nível/Score) |
| :----------------------------------------------- | :-------------------------: |
| Recursos técnicos e em rede                      |          Médio / 2          |
| Processos relacionados ao processamento de dados |           Low / 1           |
| Pessoas involvidas no processamento de dados     |          Médio / 2          |
| Setor de negócio (e-shop)                        |          Médio / 2          |
| Ocorrência de ameaças                            |          **MÉDIA** / 7          |

<br/>

Desta forma, podemos considerar que o risco no geral é baixo e algumas medidas a tomar para tal seriam:

- Política de controlo de acesso (interno)
- Autenticação desse controlo
- *Logging* para o processamento de dados
- Segurança no servidor/base de dados
- Política de segurança e proteção dos dados ao transferir para terceiros

---

## Notas/Observações Finais

- PDF [**DPIA**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP5/P1%20-%20RGPD%20(Regulamento%20Geral%20de%20Prote%C3%A7%C3%A3o%20de%20Dados)/DPIA.pdf) que corresponde ao *template* DPIA proposto.
- PDF [**PIA**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP5/P1%20-%20RGPD%20(Regulamento%20Geral%20de%20Prote%C3%A7%C3%A3o%20de%20Dados)/DPIA.pdf) que corresponde ao output do PIA *software*.
- ZIP [**PIA**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP5/P1%20-%20RGPD%20(Regulamento%20Geral%20de%20Prote%C3%A7%C3%A3o%20de%20Dados)/pia-COVID%20app.zip) que corresponde ao output do PIA *software*.