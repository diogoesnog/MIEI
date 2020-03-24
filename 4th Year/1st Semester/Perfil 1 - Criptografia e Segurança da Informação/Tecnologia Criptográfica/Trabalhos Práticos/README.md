# Tecnologia Criptográfica
Repositório criado para a Unidade Curricular Tecnologia Criptográfica, do perfil **Criptografia e Segurança da Informação**, que irá conter as resoluções de todos os trabalhos práticos propostos assim como uma breve descrição das decisões tomadas e possíveis dificuldades encontradas no decorrer de cada um dos guiões.

---

## **Composição do Grupo**
* Diogo Araújo, A78485 - [dichico](https://github.com/dichico)
* Diogo Nogueira, A78957 - [diogoesnog](https://github.com/diogoesnog)

---

## Lista dos [**Guiões**](https://github.com/uminho-miei-crypto/1920-TC/blob/master/doc/guioes.md)

- **Guião 1** [Ambiente de Desenvolvimento](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G1) 

	- Preparação do repositório da Unidade Curricular no ```Github```.
	- Instalação da biblioteca de suporte ```cryptography``` para se usar ao longo dos guiões.
	- Proposta de exercício para se criar uma **cifra autenticada de um ficheiro** através do método de criptografia ```Fernet```.

- **Guião 2** [Protecção de Segredos Criptográficos](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G2)

  - Discussão da necessidade de evitar armazenar segredos criptográficos em ficheiros sem qualquer tipo de proteção.
  - **Estudo de duas estratégias para evitar utilização de ficheiros desprotegidos:**
		- Evitar o armazenamento da chave - *Password Based Key Derivation Functions (PBKDF)*;
		- Armazenar o ficheiro de forma protegida - *KeyStore*.

- **Guião 3** [Implementação de Cifra Autenticada](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G3)

	- Tentativa de entender como é que as propriedades oferecidas pelo método ```Fernet```(*confidencialidade* dos dados e *integridade* da informação) podem ser criadas através de técnicas criptográficas disponíveis.
	- **Desenvolvimento de três versões de cifras pela diferente combinação entre uma *cifra simétrica* e de um *MAC*:**
		- encrypt and MAC;
		- encrypt then MAC;
		- MAC then encrypt.

- **Guião 4** [Animação de Modelos de Segurança](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G4)

	- Animação de modelos de segurança que permitam obter uma ideia de como o(s) ataque(s) à  confidencialidades das cifras pode(m) ocorrer.
	- Desenvolver o "jogo" ```IND-CPA``` através do mecanismo de classes do *Pyhton* - Adversário + Cifra ```Identidade```.

- **Guião 5** [Comunicação Cliente-Servidor](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G5)

    - Estabelecer comunicão entre Cliente e Servidor.
    - **Authenticated Encryption** - Uso da Cifra por Blocos ```AES``` no modo ```CGM```, garantindo-se assim a *confidencialidade* e *integridade* na comunicação entre Cliente e Servidor.

    *(Aplicação de outras Cifras apenas para prática e entendimento do conceito desta comunicação entre Cliente e Servidor.)*

- **Guião 6** [Protocolo *Diffie-Hellman*](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G6)

	- **Symetric Encryption** - Uso da Cifra ```AES``` no modo ```CFB``` (evitando o *padding*), aplicando-se ainda o protocolo *Diffie-Hellman* para se efetuar a troca das chaves criptográficas (através de uma chave pública) entre o Cliente e Servidor.

- **Guião 7** [Protocolo *Station-to-Station* Simplificado](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G7)
  
	- Continuar o [*Guião 6*](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G6), adicionando-se a funcionalidade análoga à do protocolo *Station-to-Station* - Troca de assinaturas digitais (RSA).
  
- **Guião 8** [Manipulação de Certificados X509](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Guiões/G8)

	- Estudo da validação de Certificados em *Python* para que possam depois ser integrados na aplicação Cliente e Servidor ([Guião 9](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Guiões/G9)).
	- **Uso de três sub-comandos do OpenSSL para o estudo de como deve ser feita a extração de informação destes Certificados:**
		- x509;
		- pkcs12;
		- verify.

- **Guião 9** [Finalização do protocolo *Station-to-Station* usando Certificados](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Guiões/G9)

	- Conclusão da implementação do protocolo *Station-to-Station* fazendo uso de Certificados X509.
	- Validação dos Certificados para garantir que cada um dos intervenientes usam a chave pública correta na verificação da assinatura em si.

- **Cliente/Servidor Final** [*DiCert* (Aplicação Cliente-Servidor Final)](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/CliServ)

	- Melhoramento da aplicação Cliente e Servidor.
	- Geração dos Certificados através do OpenSSL.
---

## **Datas *Updates* Finais/Notas**

- **Guião 1 e 2**
  - Resolução dos Guiões totalmente completa a 08 de Outubro.
  - README dos Guiões totalmente completos a 10 de Outubro. 

Devido a um problema de atualização nos ficheiros README, apenas conseguimos introduzir na data mencionada.

- **Guião 3**
  - Resolução e README do Guião totalmente completos a 14 de Outubro.

Conseguimos colocar o requisito de guardar a *tag* MAC juntamente com o criptograma no mesmo ficheiro para o método **encrypt and MAC** e **encrypt then MAC**. Assim, ao fazer a desencriptação, retiram-se apenas os bits a partir do 32 (MAC).

```python
# FASE 2 - Desencriptar

decryptor = cipher.decryptor()

desencriptado = decryptor.update(mensagemFinal[32:])
print(desencriptado)
```
- **Guião 4**
  - Resolução e README do Guião parcialmente completos a 30 de Outubro.

Não conseguimos compreender a ideia do Guião. Dessa forma, fizemos apenas aquilo que conseguimos, tentado entender melhor a teoria por detrás do modelo de ataque em si.

- **Guião 5**
  - Resolução e README do Guião totalmente completos a 04 de Novembro.

Alterado de ```ChaCha20``` para ```ChaCha20Poly1305```. Adição da Cifra ```AES-CCM```, dado que assim estamos efetivamente a usar uma Cifra por Blocos, onde se garante a *confidencialidade* e a *integridade*.

- **Guião 6**
  - Resolução e README do Guião totalmente completos a 13 de Novembro.

- **Guião 7**
  - Resolução e README do Guião totalmente completos a 19 de Novembro.

- **Guião 8**
  - Resolução e README do Guião totalmente completos a 01 de Dezembro.


Tendo em conta que este Guião apenas consistia em compreender/estudar o OpenSSL e os seus sub-comandos, o grupo fez este estudo ao mesmo tempo que iniciava o Guião 9. Por essa razão, as datas dos *updates* mais recentes coincidem.

- **Guião 9**
  - Resolução e README do Guião totalmente completos a 01 de Dezembro.

- **Cliente/Servidor Final**
  - Resolução e README do Guião totalmente completos a 08 de Dezembro.
