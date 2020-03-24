# Guião 2 - Protecção de Segredos Criptográficos

Como visto no guião anterior, o ```Fernet``` garante a *confidencialidade* e *integridade* da informação. Com o objetivo de criar todo um processo de criptografia de um ficheiro, armazenávamos a chave ```Fernet``` num ficheiro à parte, aplicando depois a mesma ao texto já cifrado.
Com isto, ficou explícito o uso dual da chave, tanto para cifrar como para decifrar a informação.

O inconveniente de todo este processo é estarmos a guardar a chave num ficheiro totalmente desprotegido, pondo assim em causa a segurança dos segredos criptográficos.

**O objetivo desde guião passa por aplicar duas formas distintas de proteger os segredos criptográficos, criando assim novas estratégias na criptografia da informação:**

1. [pdkdf2.py](pdkdf2.py) refere-se à utilização do método *Password Based Key Derivation Functions (PBKDF)*.
2. [scrypt.py](scrypt.py) refere-se à utilização do método *Scrypt*.

--- 

## Resolução do Guião

- ### **Método *PBKDF***

No que toca à utilização do método *PBKDF*, a ideia passa por gerar uma espécie de segredo criptográfico através de uma *password* que é solicitada ao utilizador. Com isto, conseguimos garantir que a *password* não é diretamente utilizada como chave criptográfica, tal como acontecia com a chave ```Fernet``` do [Guião 1](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G1).

**Assim, para o algoritmo do método *PBKDF*, desenvolveram-se os seguintes passos:**

1. Criação de um *Salt* aleatório - valor seguro com 16 bits, que é guardado num ficheiro. O *Salt* é depois usado como entrada adicional na função *PBKDF2HMAC*.
2. Desenvolvimento de uma instância da classe PBKDF2HMAC, definindo todos os valores necessários para o processo matemático em si - como o *Salt*, número de iterações e algoritmo.
3. Solicitação da *passphrase* ao utilizador.
4. Aplicação da *passphrase* ao algoritmo definido na instância criada no passo 2. 

Nesta fase, o *PBKDF2HMAC* aplica o método *derive* à *password* do utilizador, produzindo uma chave derivada que irá ser usada como chave criptográfica no restante do processo.

Em termos de classe *Python*, o que acontece é que se aplica uma função pseudo aleatória à *passphrase* juntamente com o valor do *Salt* e repete-se o processo tantas vezes quanto o número de iterações, até se obter a chave derivada.

5. Tendo a chave criptográfica, o processo é similar ao do [Guião 1](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G1). A única diferença é que não estamos a usar/armazenar a chave original, mas sim uma chave criptográfica.

O processo de decifrar a informação é análogo, só que neste caso não se gera um novo *Salt* - usa-se o que anteriormente ficou gravado num ficheiro.

- ### **Método *Scrypt***

Este método encontra-se ainda em fase de desenvolvimento. Dada a complexidade de interpretação do problema proposto, o grupo apresenta algumas dificuldades em desenvolver um algoritmo que atenda aos requisitos enunciados.
Ainda assim, acreditamos conseguir resolver o problema mais tarde com a ajuda por parte do docente da Unidade Curricular.

---

## Observações Finais

O método *PBKDF*, apesar de complexo, tornou-se simples de entender, dado que parte do processo era equivalente ao [Guião 1](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G1). 

A dificuldade maior deste Guião foi distinguir os doi métodos e compreender como funcionam as *Key Stores*, daí não termos até então conseguido desenvolver uma solução para o problema. Está ainda em aberto a possibilidade de existir uma solução futura.
