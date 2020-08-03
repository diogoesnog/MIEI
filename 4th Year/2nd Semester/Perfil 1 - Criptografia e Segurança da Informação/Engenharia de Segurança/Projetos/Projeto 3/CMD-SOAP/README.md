# *Command Line Program* para teste das Operações do Serviço de Assinatura com Chave Móvel Digital

A aplicação Comando Linha (CLI) surge no sentido de permitir efetuar todos os testes das várias operações do serviço nacional SCMD (*Signature* CMD). Esta aplicação foi inicialmente desenvolvida na linguagem Pyhton, sendo este repositório reservado à sua implementação na linguagem Java, através de *Reverse Engineer* da aplicação original [CMD-SOAP](https://github.com/devisefutures/CMD-SOAP).

---

# Implementação/Estrutura do Programa

O programa encontra-se então implementado na linguagem Java, tendo-se feito uso do ***Software Project Management* Maven** que se baseia num  *Project Object Model* (POM) sob a forma de `xml`, onde se encontram listadas todas as dependências internas ao programa desenvolvido. 
Este ficheiro `xml` permite uma flexibilidade em termos de atualização das versões das várias bibliotecas e possíveis adições futuras, sendo apenas necessário fazer um *build* inicial para que as mesmas sejam automaticamente instaladas/integradas no projeto.

<br/>

**Assim, esta diretoria encontra-se organizada da seguinte forma:**

- :open_file_folder: **Diretoria [doc](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/doc)** que possui todos os Ficheiros e Diretorias necessárias ao uso do JavaDoc gerado para o projeto
- :open_file_folder: **Diretoria [src](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main)** que contém a diretoria **[java](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/java)** que possui toda a parte do código Java e ainda a diretoria **[resources](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/resources)** que possui todos os ficheiros extra ao programa
  - :open_file_folder: **Diretoria [java](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/java)**
    - :file_folder: **Diretoria [code](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code)**
      - :memo: Ficheiro [CmdConfig.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code/CmdConfig.java) que é usado para definir o *Application Id* fornecido pela AMA 
      - :memo: Ficheiro [CmdSoapMsg.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code/CmdSoapMsg.java) que contém todas as funções que preparam e executam os vários comandos SOAP da Assinatura com Chave Móvel Digital
      - :memo: Ficheiro [TestCmdWsdl.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code/TestCmdWsdl.java) que contém a *main* do programa que permite que os testes dos vários comandos sejam executados
    - :file_folder: **Diretoria [wsdlservice](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/wsdlservice)**
      - :memo: Ficheiros  [\*.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/wsdlservice)  que criam todo o *Web Service* necessário para executar o teste das várias operações da Assinatura com Chave Móvel Digital
  - :open_file_folder: **Diretoria [resources](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/resources)**
    - :page_facing_up: Ficheiro [ama.wsdl](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/resources/ama.wsdl) que define como descreve como todo o *Web Service* SOAP funciona 
    - :key: Ficheiro(s) [XXXXXXXXX.pem](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/resources/ama.wsdl) que correspondem a todos os ficheiros PEM dos vários utilizadores do programa, usando-se como nome do ficheiro o seu *User Id*
- :bookmark_tabs: Ficheiro [pom.xml](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/pom.xml) que consiste na *Bill of Materials* do *software* desenvolvido

<br/>

**Para demonstrar todo o processo da utilização da aplicação, desde a parte inicial de *build* até à parte do *compile* do ficheiro Java com a *main*, recorre-se ao *Code Editor* IntelliJ IDEA**.

---

# Inicialização/Utilização do Programa

Para começar a utilizar o programa Java pela primeira vez, e tendo em conta que o mesmo está já implementado com o **Maven**, o primeiro passo consiste em abrir o projeto no IntelliJ IDEA, selecionado para isso apenas o ficheiro `pom.xml` e selecionar `Open as Project`. 

<br/>

<p align = "center">
   <img src = "https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/GIFs/Run%20First%20Time%20Program.gif" alt = "Run First Time Program" width="70%"/>
</p>
<p align = "center"><b>Figura 1.</b> Demonstração de como fazer o <i>build</i> inicial do programa<br/></p>

<br/>

- Abrir o ficheiro `pom.xml` e clicar no ícone de ferramenta a verde na parte superior da janela.
  - Isto faz um *compile/build* inicial desse mesmo ficheiro `pom.xml`, que trata de criar toda a pasta **target** com as devidas Classes Java necessárias ao programa.
  - Todas as dependências definidas na *Bill of Materials* são corretamente instaladas e armazenadas na diretoria `.idea/libraries`.
- Navegar até à Diretoria [code](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code), selecionado o Ficheiro [TestCmdWsdl.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code/TestCmdWsdl.java).
- Com o ficheiro aberto, o próprio IntelliJ IDEA cria um ícone de play a verde que ao ser acionado permite fazer o *run* da Classse `main` nele descriminada.

<br/>

**Este conjunto de passos inicia o programa, espoletando a exibição do menu principal do mesmo:**

<br/>

<p align = "center">
   <img src = "https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/Images/Menu%20Command%20Line%20Program.png" alt = "Menu Command Line Program" width="70%"/>
</p>
<p align = "center"><b>Figura 2.</b>Menu Principal do <i>Command Line Program</i><br/></p>  

<br/>

## Exemplo da utilização da opção *Run All Commands*

Para demonstrar o uso de um dos comandos disponibilizados no Menu Principal do nosso *Command Line Program*, foque-se no compando principal que trata de executar todas as operações pensadas para o programa. 

<br/>

**Ao optar-se por esta *option* surge um novo menu totalmente adaptado a essa escolha. Note-se que para cada escolha existe um menu específico:**

<br/>

<p align = "center">
   <img src = "https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/Images/Menu%20Test%20All%20Commands.png" alt = "Menu Test All Commands" width="70%"/>
</p>
<p align = "center"><b>Figura 3.</b> Menu <i>Test All Commands</i><br/></p>

</br>

- Insere-se o *path* do documento ao qual se vai aplicar a Assinatura com Chave Móvel Digital.
- Insere-se o número de telemóvel do Utilizador seguido do seu Pin.
- **Caso não tenha sido configurado o *Application Id* no ficheiro [CmdConfig.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code/CmdConfig.java), insere-se também. Caso contrário, *enter* para ignorar**.

<br/>

**Com estes dados o programa será capaz de processar todo o resto, pedindo ao utilizador o OTP recebido no seu telemóvel. Com esse OTP validado, e se tudo correr bem como planeado, a assinatura é validada com sucesso, sendo o resultado esperado o seguinte:**

```
Test Command Line Program (for Preprod/Prod Signature CMD (SOAP) version 1.6 technical specification)
Initializing Test of All Commands
0% ...   Reading Arguments from the Command Line
         Document Name: teste.txt, User Id: +351 913392656
10% ...  Contacting CMD SOAP Server for GetCertificate Operation
20% ...  Certificate Emitted for "Diogo Emanuel da Silva Nogueira"
         by the Certification Entity "EC de Chave Móvel Digital de Assinatura Digital Qualificada do Cartão de Cidadão 00003"
         in the Hierarchy of "Cartão de Cidadão 006"
30% ...  Reading the Document "teste.txt"
40% ...  Hashing the Document "teste.txt"
50% ...  Generated Hash 
         [37, 94, -103, 42, 42, -117, -51, -128, 127, 80, -83, 102, ... ]
60% ...  Contacting CMD SOAP Server for CCMovelSign Operation
70% ...  Process Id returned by CCMovelSign Operation
         172ad597-4e77-499b-8f1e-6f00924b5cac
80% ...  Initializing OTP Validation

Enter the OTP received on your Device:
066181
90% ...  Contacting CMD SOAP Server for ValidateOtp Operation
OTP code is valid
100% ... Signature returned by ValidateOtp Operation
         [24, 0, -22, 35, -120, 36, -2, -91, -94, -5, 45, -55, -21, -63, ... ]
110% ... Validating Signature

Assinatura verificada com sucesso.

############################################ Test All Done ##############################################
```

---

# Notas

1. Não é necessário instalar qualquer biblioteca de forma manual.
2. A aplicação foi testada usando-se o SDK `openjdk-14.0.1`.
3. Antes de usar, verificar o *value* da variável ***Application Id***  no ficheiro [CmdConfig.java](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/src/main/java/code/CmdConfig.java).
4. Foi usado o *Documentation Generator* **JavaDoc**, uma vez que todo o código possui a documentação necessária e que dessa forma torna-se mais fácil visualizar as várias classes e métodos criados no projeto. Para fazer uso da mesma, basta aceder ao ficheiro [index.html](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Projetos/Projeto%203/CMD-SOAP/doc/index.html) presente na Diretoria [doc](https://github.com/uminho-miei-engseg-19-20/Grupo5/tree/master/Projetos/Projeto%203/CMD-SOAP/doc).
