# Guião 7 -  Protocolo *Station-to-Station* Simplificado

O protocolo *Station-to-Station* consiste numa espécie de "contrato" em termos de chave criptográfica. Baseia-se no protocolo *Diffie-Hellman*, adicionando segurança em termos de ataques intermediários, dado que pressupõe que ambas as extremidades possuem uma *key* de assinatura, que é usada para "assinar" a mensagem em si.

Através do uso do **algoritmo RSA**, espera-se assim integrar as assinaturas no protocolo do [Guião 6](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G6) anterior, permitindo que as mensagens enviadas pelo canal público sejam agora encriptadas e também assinadas.

---

## Resolução do Guião

De modo a simplificar o funcionamento do programa, foi desenvolvida uma classe [**RSAWorker.py**](https://github.com/uminho-miei-crypto/1920-G9/blob/master/Gui%C3%B5es/G7/RSAWorker.py), contendo todos os métodos que tratam de todo o requisito adicional pretendido para este Guião. 

Dado que a ideia passava pela existência de uma espécie de *script* que gerasse as chaves públicas/privadas de ambas as extremidades do canal de comunicação, criou-se um método na nova classe que consegue fazê-lo para o Cliente e Servidor, consoante uma *flag* indicativa da entidade em causa. 

**Essa execução inicial pode ser feita no terminal python da seguinte forma (assumindo que se está na diretoria correta):**

```python
> python3
Python 3.6.8 (default, Aug 20 2019, 17:12:48) 
[GCC 8.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.

>>> from RSAWorker import generateAndSaveKey
>>> generateAndSaveKey(0)
>>> generateAndSaveKey(1)
>>> exit()
```

Tendo-se todas as chaves necessárias,  a integração das assinaturas neste protocolo torna-se relativamente simples. Apenas é necessário criar uma assinatura, permitindo que antes da execução do programa em si, consiga ficar provado que a mensagem está a ser enviada pelo Cliente que a assinou.

**Veja-se como esse processo é feito na parte do Servidor:**

```python
# Receber a Chave Pública do Cliente para a criação da Shared Key.
publicKeyBytes = yield from reader.read(625)
signature = yield from reader.read(max_msg_size)
    
# Ler a Chave Pública RSA do Cliente para verificar.
rsaPublicKey = loadPublicKey(1)

# Chamada da função para verificar se a mensagem recebida do Cliente foi assinada pelo mesmo, usando Chave Pública.
if verification(rsaPublicKey,signature, publicKeyBytes):
	publicKeyServer = load_pem_public_key(
            publicKeyBytes, 
            backend=default_backend()
        )
	sharedKey = serverPrivateKey.exchange(publicKeyServer)
else: sys.exit("Ataque Intermediário!!!")
```

---

## Observações Finais

Inicialmente estava a ser feita uma classe RSAWorker tanto no Cliente como no Servidor, gerando e salvando as chaves de ambos assim que a classe era criada.

Dado que a ideia era que essa parte fosse feita separadamente, alterou-se o ficheiro [**RSAWorker.py**](https://github.com/uminho-miei-crypto/1920-G9/blob/master/Gui%C3%B5es/G7/RSAWorker.py), permitindo que esse processo fosse feito antes de todo o programa começar, passando o Cliente e Servidor a lerem as chaves dos ficheiros criados para cada uma delas.
