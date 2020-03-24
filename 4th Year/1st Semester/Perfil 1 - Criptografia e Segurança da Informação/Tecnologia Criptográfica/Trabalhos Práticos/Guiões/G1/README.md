# Guião 1 - Ambiente de Desenvolvimento

O Fernet é um método de criptografia simétrica que certifica que uma mensagem codificada não possa ser manipulada ou lida sem a devida chave.

O objetivo deste guião prático é essencialmente compreender como funciona este mecanismo de cifra autenticada e como assegura a *confidencialidade* e *integridade* dos dados armazenados num ficheiro.

--- 

## Resolução do Guião

**Para começar a resolução do trabalho proposto, o grupo desenvolveu um ficheiro de texto com a mensagem a cifrar, seguindo o seguinte pensamento:**

1. Criação de uma chave codificada ```Fernet```, que é depois guardada num ficheiro.

A chave ```Fernet``` deve ser mantida em segredo, dado que é através dela que o texto é cifrado e posteriormente decifrado. 

2. Abertura/*Parse* do texto a ser cifrado. A este texto é aplicada a criptografia em si, que resulta num *token* ```Fernet```. Esta informação cifrada é escrita num outro ficheiro.

O *token* ```Fernet``` possui garantias de *privacidade* e *autenticidade*.

3. Estanto o texto cifrado, abre-se e lê-se o seu ficheiro, assim como o ficheiro da chave. Com estas duas informações, decifra-se o conteúdo do *token* por aplicação da chave ```Fernet```, obtendo-se assim o texto original. 

---

## Observações Finais
 
Este método ```Fernet``` tornou-se simples de utilizar, dado que já faz todo o trabalho difícil no processo de criptografia de um ficheiro. Apenas foi preciso conhecer o propósito de cada método usado, os seus parâmetros e ainda os seus valores de retorno. 

Neste guião apenas foi necessário fazer o *import* da classe Fernet.
