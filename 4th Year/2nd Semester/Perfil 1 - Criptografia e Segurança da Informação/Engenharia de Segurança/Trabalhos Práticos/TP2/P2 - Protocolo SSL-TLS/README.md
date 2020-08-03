# Pergunta 2 - Protocolo SSL/TLS

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Experiência 2.1**](#experiência-21---ssl-server-test-para-o-site-do-governo-português) - ***SSL Server Test* para o site do Governo Português**
    - Uso do *website SSL Labs* para obter informações acerca da segurança do *website* correspondente ao Governo Português.  

2. [**Pergunta 2.1**](#pergunta-21---protocolo-ssltls) - **Protocolo SSL/TLS**
    - Uso do *website SSL Labs* para obter informações acerca da segurança de dois *websites* de Governo de dois países europeus diferentes.  
    - Análise do resultado do *website* com pior *rating*.
    - Análise do **BEAST *attack*** e do seu impacto no protocolo TLS. 

---

## Resolução da Pergunta 2

### Experiência 2.1 - SSL *Server Test* para o site do Governo Português

A observação do resultado do *Server Test* desta experiência permite de imediato perceber quais os resultados que este teste fornece e de que forma importam em termos de segurança num servidor público.

**Dessa forma, retiram-se as seguintes conclusões iniciais:**

- Disponibilizaçã de um *rating*, que parece basear-se em 4 métricas base (como o Certificado e a força da Cifra usada);
- Listagem de todos os Certificados usados bem como as suas características internas.
- Outras pequenas informações extra.

---

### Pergunta 2.1 - Protocolo SSL/TLS

Dado o número do Grupo, fez-se uma escolha de dois sites correspondentes ao Ministério de Governos Europeus, mas não portugueses. Para facilitar na seleção, o grupo decidiu focar-se nos Ministérios da Educação, usando para o efeito o site [Ministerios de Educación - Europa](http://www.sc.ehu.es/sfwseec/miniseuropa.htm) que faz uma listagem dos mesmos.

<br/>

**Assim, escolheu-se a Espanha e Holanda para casos de estudo:**

- **Ministeries**, que abrange todos os Ministérios da Holanda.
    - [Ministerie van Onderwijs, Cultuur en Wetenschap](https://www.rijksoverheid.nl/ministeries/ministerie-van-onderwijs-cultuur-en-wetenschap)
- **Ministerio de Educación, Cultura e Deporte (MECD)**, que abrange tanto o Ministério de Educação e Formação Profissional como o Ministério da Cultura e Desporto.
    - [Ministerio de Educacíon y Formacíon Profesional](https://www.educacionyfp.gob.es/)

<br/>

#### Alínea I - Análise dos Resultados do *SSL Test Server*

Para a análise destes resultados foram retiradas todas as informações disponibilizadas pelo site [*SSL Labs*](www.ssllabs.com) e guardadas em modo PDF. Adicionalmente, retirou-se a informação sumária em modo imagem, para que fosse mais simples de colocar no README e compreender o restante do exercício.

<br/>

- **Ministério da Educação - Holanda** ([Ministerie van Onderwijs, Cultuur en Wetenschap](https://www.rijksoverheid.nl/ministeries/ministerie-van-onderwijs-cultuur-en-wetenschap))

    - [Informação dada pelo site *SSL Labs*](https://www.ssllabs.com/ssltest/analyze.html?d=www.rijksoverheid.nl&s=2a00%3ad00%3a3%3a2%3a0%3a0%3a0%3a119&latest)
    - [PDF com toda essa informação]()
    - [Imagem do Sumário do *SSL Server Test*]()
    <p align="center">
        <img src="Images/SSL Server Test - Holanda.png">
    </p>

<br/>

- **Ministério da Educação - Espanha** ([Ministerio de Educacíon y Formacíon Profesional](https://www.educacionyfp.gob.es/))

    - [Informação dada pelo site *SSL Labs*](https://www.ssllabs.com/ssltest/analyze.html?d=www.educacionyfp.gob.es)
    - [PDF com toda essa informação]()
    - [Imagem do Sumário do *SSL Server Test*]()
    <p align="center">
        <img src="Images/SSL Server Test - Espanha.png">
    </p>

<br/>

#### Alínea II - Análise do Resultado do site com pior *rating*

O site com pior *rating* corresponde ao do Ministério da Educação de Espanha, avaliado num *rating* de B. Conforme ficou percetível numa primeira análise experimental, esse *rating* baseia-se na análise/cálculo de um conjunto de métricas, que conjuntamente formam uma nota geral relativa à segurança do *website* em causa.

<br/>

**As observações que se podem realizar pela simples análise do sumário são as seguintes:**

- O Servidor suporta parâmetros fracos no que toca à troca de chaves pelo protocolo *Diffie-Hellman* (DH), o que diminui o *rating* para B.
    - Isto deve-se ao facto do protocolo de troca de chaves *Diffie-Hellman* estar a ser usado com parâmetros de 1024 *bits*. A ideia seria usar esse protocolo mas com um conjunto de *bits* maior (2048 para cima).
- O servidor suporta TLS 1.0 e TLS 1.1, o que diminui também o *rating* para B.
    - Apesar de suportar o protocolo TLS 1.0 e 1.1, existe o suporte para o TLS 1.2, o que acaba por não influenciar de forma tão negativa em termos de *rating*. Em outros casos, comprovados por análises esporádicas, o facto de não usar TLS 1.2 poderia ser decisivo para diminuir o *rating* para C.

Num balanço geral, este *rating* não é 100% significativo no que toca á segurança em si, no entanto, há considerações e atualizações que devem ser tomadas em conta para que se consiga garantir uma maior segurança.

<br/>

**A tabela abaixo vai permitir compreender de forma mais simples os problemas em causa, aquilo que podem causar e a sua possível solução**

| Problema                                                  | Consequência(s)                                              | Possíveis Soluções/Novas Versões                             |
| --------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Suporte a fracos parâmetros no protocolo *Diffie-Hellman* | Possíveis ataques *Logjam*, comprometendo toda a segurança do serviço. | Aumentar o conjunto de *bits* dos parâmetros para **pelo menos** 2048 *bits*. |
| Suporte ao TLS 1.0                                        | Possíveis ataques *man-in-the-middle* (p.e. **POODLE**, **BEAST**), comprometendo a integridade e autenticação ao nível dos dados enviados entre um *website* e um *browser* (dados estes que normalmente seriam criptografados). | TLS 1.1 livra-se praticamente de todos problemas do TLS 1.0, no entanto, continua a basear-se numa combinação de MD5 e SHA-1. |
| Suporte ao TLS 1.1                                        | Apesar de não oferecer um risco/falha de segurança real e imediato, o protocolo TLS 1.1 baseia-se numa combinação de MD5 e SHA-1, algoritmos estes que já foram quebrados. | TLS 1.2 faz uso do SHA-256. Além disso, usa *Authenticated Encryption* (como **GCM**). |

O *website* [**acunetix**](https://www.acunetix.com/blog/articles/tls-vulnerabilities-attacks-final-part/) possui uma lista de exemplos de vulnerabilidades e ataques TLS, o que nos permite perceber que existem ataques que podem ser executados e que torna-se importante eliminar estes suportes a versões antigas.

<br/>

 **Com isso e com a tabela acima, concluímos o seguinte**:

- Apesar do TLS 1.1 resolver quase todos os problemas encontrados no TLS 1.0, o seu uso torna-se igualmente um péssimo comprometimento, dado que também não fornece suporte para os métodos mais atuais da criptografia.
- TLS 1.2 não é de todo uma má alternativa, dado que já usa *Authenticated Encryption* e dessa forma torna o processo de combinação de Modos de Operação de Cifras por Blocos mais simples e seguro, algo que é extremamente importante hoje em dia. 
  - Isto permite assim uma confidencialidade e autenticação ao nível dos dados, evitando ataques desnecessários.
- TLS 1.2 possui *patches* contra diversas vulnerabilidades conhecidas.
- TLS 1.3 pode e deve ser implementado, já que traz consigo todo um desempenho HTTPS mais rápido e seguro.
  - Ainda é recente, existindo muitos *websites* que usam o TLS 1.2 e até mesmo o TLS 1.1.

<br/>

#### Alínea III - Termo *BEAST attack* em *Protocol Details*

O ataque **BEAST** (*Browser Exploit Agains SSL/TLS*) permite que um *man-in-the-middle* descubra informações acerca de uma sessão TLS 1.0 naturalmente criptografada, através de uma vulnerabilidade na implementação do Modo de Operação de Cifra por Blocos denominado CBC (*Cipher-block chaining*) no TLS 1.0.

<br/>

##### Modo de Funcionamento Ataque

Conforme dito de forma resumida acima, o ataque **BEAST** explora uma vulnerabilidade na forma como o protocolo TLS 1.0 gera os vetores de inicialização para as Cifras de Bloco no modo CBC. Essa fraqueza pode ser inteligentemente estudada e com isso descobrir-se pequenas quantidades de informação (como pequenos pedaços de dados, *cookies* de sessões de HTTP, credenciais de autenticação, *tokens*, etc.) sem mesmo executar qualquer tipo de *decryption* e sem depender da força da cifra ou até mesmo do bloco em si.

<br/>

**Toda essa ideia fica mais clara se entendermos como funciona a Cifras por Blocos no modo CBC. Analise-se a imagem abaixo anexada.**

Dado que este modo consiste na ideia de usar o ***block cipher*** anterior para fazer XOR com cada bloco do *plaintext*, percebe-se logo que é necessário corrigir a fase de inicialização de todo o processo, dado que o primeiro bloco não terá com quem fazer esta combinação XOR.

Por isso surge o Vetor de Inicialização (IV), que permite eliminar esta "falha" e com isso iniciar o processo combinado com o primeiro bloco de *plaintext*.

<p align="center">
	<img src="Images/CBC Encryption.png">
</p>

**Dessa forma, a segurança da Cifra por Blocos no modo CBC depende inteiramente da aleatoriedade dos Vetores de Inicialização, sendo neles que surge o problema.**

No TLS 1.0, estes Vetores de Inicialização não são gerados de forma aleatória. Assim, ao invés de gerar um novo Vetor para cada mensagem distinta, o protocolo TLS usa o último bloco de *ciphertext* da mensagem anterior como sendo o seu IV para iniciar o processo.

Como os blocos em si são "agrupados" usando a operação XOR, que por si só é uma operação reversível, o facto de se conhecer os Vetores de Inicialização pode possibilitar que o atacante descubra informações pertencentes às mensagens encriptadas.

<br/>

##### Conclusões

No resultado obtido pelo *SSL Server Test*, o campo **BEAST attack** apresenta o valor de *Not mitigated server-side*, o que significa que este critério deixou de penalizar o *rating* geral em si desde 2013 (0xc013).

<p align="center">
	<img src="Images/Protocol Details - Espanha.png">
</p>

<br/>

**Isto significa que foram encontradas/exploradas várias maneiras de mitigar esta vulnerabilidade sem necessidade de se atualizar a versão do protocolo TLS:**

- Alterar para uma Cifra de Fluxo, tendo em conta que isto afeitou apenas as Cifras por Bloco no modo CBC.
  - Cifra RC4 provou-se igualmente insegura, acabando por se proibir este modo errado de mitigar a vulnerabilidade.
- Alterar o modo de operação da Cifra de Bloco
  - Implementação impossível porque apenas o modo CBC é suportado pelo TLS 1.0.
- Usar a técnica **1/n-1 split**, que permitia dividir a mensagem a enviar em duas, impedindo o ataque.
  - Primeira mensagem continha apenas 1 *byte*
  - Segunda mensagem continha os restantes (n-1) *bytes*
  - Primeiro pacote/mensagem é preenchido com dados aleatórios antes de fazer XOR com o IV, restaurando todo o processo de aleatoriedade em falha.

---

## Notas/Observações Finais

- PDF [**SSL Server Test - Espanha**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P2%20-%20Protocolo%20SSL-TLS/SSL%20Server%20Test%20-%20Espanha.pdf) que contém todo o resultado dado pelo *website SSL Labs* relativamente ao *website* do Ministério de Educação de Espanha.
- Imagem [**SSL Server Test - Espanha**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P2%20-%20Protocolo%20SSL-TLS/Images/SSL%20Server%20Test%20-%20Espanha.png) que contém o sumário do resultado descrito no ponto anterior.
- PDF [**SSL Server Test - Holanda**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P2%20-%20Protocolo%20SSL-TLS/SSL%20Server%20Test%20-%20Holanda.pdf) que contém todo o resultado dado pelo *website SSL Labs* relativamente ao *website* do Ministério de Educação de Holanda..
- Imagem [**SSL Server Test - Holanda**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P2%20-%20Protocolo%20SSL-TLS/Images/SSL%20Server%20Test%20-%20Holanda.png) que contém o sumário do resultado descrito no ponto anterior.
- Imagem [**CBC Encryption**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P2%20-%20Protocolo%20SSL-TLS/Images/CBC%20Encryption.png) que contém o esquema relativo ao modo de operação CBC de uma Cifra por Blocos.
- Imagem [**Protocol Details**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P2%20-%20Protocolo%20SSL-TLS/Images/Protocol%20Details%20-%20Espanha.png) que comprova a mitigação do **BEAST *attack***.