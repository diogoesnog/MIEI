# Guião 6 -  Protocolo *Diffie-Hellman*

O protocolo *Diffie-Hellman* é um método de troca segura para *keys* através de um canal público, pela introduzação de uma chave pública que pode ser partilhada em comunicações subsequentes.

A ideia deste Guião é prosseguir com o uso da Cifra por Blocos ```AES``` mas no modo ```CFB```, reforçando com este novo método para troca de chaves entre o Cliente e o Servidor. Dessa forma, é possível que as duas partes não tenham conhecimento uma sobre a outra mas que estabeleçam em conjunto uma *key* secreta pública que é depois compartilhada através de um canal que não necessita de ser seguro (como estudado/percebido nos Guiões anteriores).

---

## Resolução do Guião

De modo a simplicar a criação da *Private Key* de cada uma das Classes, usaram-se dois valores fixos, que são necessários para gerar os parâmetros a usar na criação dessa mesma chave. Com uma *Private Key*, cria-se então uma *Public Key* que será a chave a ser enviada através do canal público Cliente-Servidor.

**Este processo é similar tanto para os Clientes como para o Servidor.**

```python
# Número primo e valor de gerador dado pelo guião
P = 9949409665013933710618693397761 (...)
G = 4415740483796032876887268067768 (...)

# A criação do DH com os números fornecidos no guião
parameters = dh.DHParameterNumbers(P, G, None).parameters(backend=default_backend())

# Chave privada
serverPrivateKey = parameters.generate_private_key()

# Chave pública
serverPublicKey = serverPrivateKey.public_key()
```

Com este passo feito, a ideia é que ambas as extremidades do canal enviem a sua *Public Key*, permitindo que seja depois criada a *Shared Key* a usar para o processo de encriptação e desencriptação.

---

## Observações Finais

Uso da Cifra ```AES``` no modo ```CFB```, dado que este modo não necessita de ***padding***.