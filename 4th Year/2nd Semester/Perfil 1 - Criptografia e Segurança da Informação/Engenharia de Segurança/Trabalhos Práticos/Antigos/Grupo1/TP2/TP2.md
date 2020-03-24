# TP2 - Resolução

## 1\. Assinaturas cegas (_Blind signatures_) baseadas no Elliptic Curve Discrete Logarithm Problem (ECDLP)

### Pergunta P1.1

Para a realização desta pergunta foi necessário criar, previamente, um par de chaves e o respetivo certificado, utilizando o openssl.

De modo a simplificar o input e output do código fornecido para a experiência 1.2 foi necessário efetuar algumas alterações no respetivo código. Assim, os ficheiros com as respetivas alterações encontram-se guardados na pasta *[Pergunta1](https://github.com/uminho-miei-engseg-18-19/Grupo1/tree/master/TP2/Pergunta1)*.

## 2\. Protocolo SSL/TLS

### Pergunta P2.1

O objectivo era efetuar o teste _SSL Server test_ para 3 sites de Universidades Portuguesas. Assim sendo, optámos por investigar a _Universidade do Porto, a Universidade de Aveiro e o ISCTE_.

  *1. [Anexe os resultados](https://github.com/uminho-miei-engseg-18-19/Grupo1/tree/master/TP2/Pergunta2) do _SSL Server test_ à sua resposta.*
  
  *2. Analise o resultado do _SSL Server test_ relativo ao site escolhido com pior rating. Que comentários pode fazer sobre a sua segurança. Porquê?*
  
  O pior ranking que nos surge nesta pesquisa é um **B**, relativo ao site da _Universidade de Aveiro_, como podemos verificar:
  ![Ranking UA](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta2/ua.pt.PNG)
  É de notar que os maiores problemas surgem devido ao *Cipher Strength*.
  Alguns problemas de segurança poderão surgir com o facto do site não suportar ainda o protocolo **TLS 1.3** que é o mais recente destes protocolos e, no entanto, ainda utilizar as versões **1.1** e **1.0**.
  
  Também apresenta algumas *Cipher Suites* fracas, como por exemplo:
  
- TLS_RSA_WITH_AES_256_CBC_SHA256 (0x3d)  
- TLS_RSA_WITH_AES_256_CBC_SHA (0x35) 
- TLS_RSA_WITH_AES_128_CBC_SHA256 (0x3c) 
- TLS_RSA_WITH_AES_128_CBC_SHA (0x2f) 
- TLS_RSA_WITH_3DES_EDE_CBC_SHA (0xa)
  
Mais ainda, permite que seja reusada o parâmetro da chave pública do algoritmo de **Elliptic Curve Dilfie Hellmann**, o que pode comprometer o sistema e, por isso, a avaliação da _cipher strenght_ é mais baixo do que o expectável.
  
*3. É natural que tenha sido confrontado com a seguinte informação: "_This site works only in browsers with SNI support._". O que significa, para efeitos práticos?*
  
  Uma vez que nos testes aos servidores que escolhemos, referentes às 3 universidades acima mencionadas, não nos deparámos com esta mensagem, vamos usar, a título exemplificativo, o site do _Governo Português_, onde esta mensagem aparece.
  ![Teste Gov Português](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta2/GovPort.PNG)
  Como referido, esta mensagem não é de erro, mas sim de aviso/informação. **SNI** (_Server Name Identication_) é uma extensão do protocolo TLS.
  Ao criar uma ligação TLS, o cliente requer um certificado ao servidor web com um IP. Ao receber, examina os nomes do certificado para verificar se algum deles coincide com aquele a que se queria conectar. Se houver _match_, a ligação continua normalmente.
  
  Por outro lado, em _name-based virtual hosting_, são armazenados vários domínios no mesmo _servidor web_ com o mesmo IP.
  
  Um servidor com **SNI** pode inibir a publicação de vários certificados SSL no mesmo IP.


## 3\. Protocolo SSH

### Pergunta P3.1

Com o intuito de simplificar a pesquisa de serviços disponíveis na Web com o *ssh* ativo, começou por fazer-se uma pesquisa no site https://www.shodan.io/ com o intuito de encontrar servidores ssh de Universidades Portuguesas. Tendo-se efetuado a seguinte pesquisa:

> [`port:22 org:"Universidade do Minho"`](https://www.shodan.io/search?query=port%3A22+org%3A%22Universidade+do+Minho%22)

> [`port:22 org:"Universidade de Aveiro"`](https://www.shodan.io/search?query=port%3A22+org%3A%22Universidade+de+Aveiro%22)

Após análise dos resultados obtidos, escolheram-se os seguintes servidores:

> 193.137.11.59, servidor relativo à Universidade do Minho;

> 193.137.172.96, servidor relativo à Universidade de Aveiro.

Assim, utilizando o ssh-audit para efetuar os respetivos testes, obtiveram-se os seguintes resultados:

**Universidade de Aveiro**

1. *[Resultados](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta3/mmlog.fis.ua.pt.md)*
2. *Software e versão utilizada:* OpenSSH 7.2p2

**Universidade do Minho**

1. *[Resultados](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta3/193.137.11.59.md)*
2. *Software e versão utilizada:* OpenSSH 6.7p1

De modo a responder aos pontos 3, 4, e 5, procedeu-se à pesquisa de vulnerabilidades, no site CVE details, para cada um dos softwares identificados anteriormente, tendo-se obtido os seguintes resultados:


**OpenSSH 7.2p2**

![UMinho](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta3/UMinho.png)

https://www.cvedetails.com/vulnerability-list/vendor_id-97/product_id-585/version_id-194112/Openbsd-Openssh-7.2.html


**OpenSSH 6.7p1**

![UA](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta3/UA.png)

https://www.cvedetails.com/vulnerability-list/vendor_id-97/product_id-585/version_id-188833/Openbsd-Openssh-6.7.html


#### Discussão dos resultados obtidos

3. *Qual das versões de software tem mais vulnerabilidades?* Tendo por base a pesquisa efetuada e avaliando as versões de software relativas aos sites utilizados, conclui-se que a versão *OpenSSH 7.2p2* é a que apresenta maior número de vulnerabilidades. Observando-se que esta versão apresenta 7 vulnerabilidades, enquanto a versão *OpenSSH 6.7p1* apresenta apenas 6.

4. *Qual tem a vulnerabilidade mais grave?* Analisando o CVSS score de ambos os softwares em análise, conclui-se que a versão *OpenSSH 7.2p2* é a que apresenta a vulnerabilidade mais grave, apresentando uma vulnerabilidade com *CVSS score* de 7.8, vulnerabilidade representada como: *CVE-2016-6515*.

5. *Para efeitos práticos, a vulnerabilidade indicada no ponto anterior é grave? Porquê?* Para melhor perceber e analisar a vulnerabilidade apresentada no ponto anterior, optou por se fazer uma pesquisa mais detalhada em relação à mesma. Tendo-se obtido os seguintes resultados:

![NVD](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta3/NVD.png)

https://nvd.nist.gov/vuln/detail/CVE-2016-6515


![CVE](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP2/Pergunta3/CVE.png)

https://www.cvedetails.com/cve/CVE-2016-6515/


Analisando os resultados obtidos conclui-se que a vulnerabilidade apresentada consiste no facto da função *auth_password*, contida em *auth_passwd.c*, não limitar o tamanho da *password* que será usada para se autenticar no sistema, o que pode levar à negação de serviço (crypt CPU consumption).

Observa-se que a vulnerabilidade em análise não tem qualquer impacto na confidencialidade nem na integridade do sistema; no entanto, em termos práticos, esta vulnerabilidade pode ser considerada grave, uma vez que a existência desta vulnerabilidade permite que atacantes remotos sem necessidade de estarem autenticados, causem, temporariamente, uma negação de serviço, levando ao desligamento do mesmo, podendo ficar completamente indisponível durante um período de tempo.

Ora, isto pode trazer graves problemas se estivermos a falar por exemplo de uma loja que venda os seus produtos online. Imagine-se que o atacante explora a vulnerabilidade deixando então o site indisponível, durante o tempo em que o site estiver indisponível a loja não vai conseguir vender os seus produtos, isto teria um impacto negativo a nível financeiro, dependendo do tempo que o site ficar indisponível.

No entanto, esta pode ser resolvida fazendo a atualização do OpenSSH.

https://www.secpod.com/blog/openssh-crypt-cpu-consumption/
