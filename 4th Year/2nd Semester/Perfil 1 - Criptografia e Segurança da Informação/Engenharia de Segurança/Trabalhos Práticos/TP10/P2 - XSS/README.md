# Pergunta 2 - XSS

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Pergunta  2.1**](#) - ***XSS***

   - Entendimento básico de como o *XSS* é/pode ser usado e para quê
   - Entendimento do que é *Reflected XSS*
     - *Reflected XSS Injection*
     - *DOM-based XSS Injection*

---

## Resolução da Pergunta 2

### Pergunta 2.1 -*XSS*

Através da *lesson* dada pelo WebGoat, conseguimos executar e consequentemente entender como funciona toda a ideia de uma *Cross Site Scripting*.

**Com todo os passos resolvíveis feitos (começando-se no dois, conforma a *lesson* o indica) e compreendidos, detalham-se os mesmos:**

#### Passo 2

Tal como é explicado no próprio WebGoat, pode-se fazer uso das *developer tools* para tentar perceber se os *cookies* das duas *tabs* efetivamente correspondem. Fazendo-se isso, valida-se esta igualdade através da consola *javascript*.

#### Passo 7

Para este passo, a ideia é observar/estudar qual o campo que está suscetível ao *XSS*. Esta operação torna-se simples de efetuar. Basta tentar introduzir um mini pedação de código nos *fields* em causa e observar o seu comportamento.

<br/>

**Note-se o que acontece ao alterar o valor do *field* `﻿Enter your credit card number:`**

Está-se a introduzir a string `<script>alert("Hello")</script>`. Dado que é mostrado uma espécie de *pop-up* com o texto pedido no mini código, deduz-se então que este campo está suscetível ao *XSS*.

<p align="center">
    <img src="Images/XSS Field 1.png" width=40%>
</p>

<br/>

**Note-se o que acontece ao alterar o valor do *field* `﻿Enter your three digit access code:`**

Está-se a introduzir também a string `<script>alert("Hello")</script>`. Conforme a própria mensagem de *output* o indica, está-se a tentar comprometer toda a data da loja com um *Reflected XSS attack*. Assim, deduz-se que este campo já não está suscetível ao *XSS*.

<p align="center">
    <img src="Images/XSS Field 2.png" width=60%>
</p>

#### Passo 10

Fazendo-se uso do *Inspect Element* do Mozilla, consegue-se visualizar toda a estrutura e código JS da página em causa. Navega-se até ao ficheiro **GoatRouter.js** e no seu conteúdo pode-se encontrar a linha `'test/:param': 'testRoute'`, consoante a imagem abaixo o demonstra.

<p align="center">
    <img src="Images/XSS GoatRouter.png" width=70%>
</p>


Com a observação/interpretação necessária, conclui-se que a *route* para o *test code* seria então`start.mvc#test/`.

#### Passo 11

- Descoberta a rota para o *test code* parte do URL http://localhost:8080/WebGoat/start.mvc#test/

- Adicione-se o *script* `<script>webgoat.customjs.phoneHome()</script>` como parâmetro
- Fazendo-se o *encode* de todo este URL pensado, obtém-se o URL final http://localhost:8080/WebGoat/start.mvc#test/%3Cscript%3Ewebgoat.customjs.phoneHome()%3C%2Fscript%3E

Ao fazer-se a inserção deste URL na *Address Bar*, obtém-se uma mensagem na parte da consola do *Inspect Element* do *browser*.

A mensagem `phone home said {"lessonCompleted":true,"feedback":"Congratulations. You have successfully completed the assignment.","output":"phoneHome Response is 550178464","assignment":"DOMCrossSiteScripting","attemptWasMade":true}` indica então que a resposta para o *script* criado e incorporado pelo URL é **550178464**.

#### Passo 12

| Pergunta                                                 | Resposta                                                     |
| -------------------------------------------------------- | ------------------------------------------------------------ |
| ***Are trusted websites immune to XSS attacks?***        | *No because the browser trusts the website if it is acknowledged trusted, then the browser does not know that the script is malicious.* |
| ***When do XSS attacks occur?***                         | *The data is included in dynamic content that is sent to a web user without being validated for malicious content.* |
| ***What are Stored XSS attacks?***                       | *The script is permanently stored on the server and the victim gets the  malicious script when requesting information from the server.* |
| ***What are Reflected XSS attacks?***                    | *They reflect the injected script off the web server. That occurs when input sent to the web server is part of the request.* |
| ***Is JavaScript the only way to perform XSS attacks?*** | *No there are many other ways. Like HTML, Flash or any other type of code that the browser executes.* |

---

## Notas/Observações Finais

- Imagem [**XSS Field 1**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP10/P2%20-%20XSS/Images/XSS%20Field%201.png) que demonstra o resultado obtido pela alteração do parâmetro ﻿`Enter your credit card number`.
- Imagem [**XSS Field 2**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP10/P2%20-%20XSS/Images/XSS%20Field%202.png) que demonstra o resultado obtido pela alteração do parâmetro ﻿`Enter your three digit access code:`.
- Imagem [**XSS GoatRouter**](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP10/P2%20-%20XSS/Images/XSS%20GoatRouter.png) que mostra o conteúdo do ficheiro `GoatRouter.js`.