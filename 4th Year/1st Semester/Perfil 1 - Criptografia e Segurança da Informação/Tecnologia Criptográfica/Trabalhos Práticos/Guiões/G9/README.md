# Guião 9 -  Finalização do protocolo *Station-to-Station* usando Certificados

O protocolo *Station-to-Station* consiste numa espécie de "contrato" em termos de chave criptográfica. Baseia-se no protocolo *Diffie-Hellman*, adicionando segurança em termos de ataques intermediários.

Através do uso de **certificados X509**, espera-se assim alterar a metodologia das assinaturas no protocolo do [Guião 7](https://github.com/uminho-miei-crypto/1920-G9/tree/master/Gui%C3%B5es/G7) anterior, permitindo que as mensagens enviadas pelo canal público sejam agora encriptadas e também assinadas com os certificados do Cliente e Servidor respetivamente, além da sua verificação sobre o *Certificate Authority* (CA).

---

## Resolução do Guião


De modo a simplificar o funcionamento do programa, foi desenvolvida um ficheiro adicional em Python [**OpenSSLWorker.py**](https://github.com/uminho-miei-crypto/1920-G9/blob/master/Gui%C3%B5es/G9/OpenSSLWorker.py), contendo todos os métodos que tratam de todo o requisito adicional pretendido para este Guião. 

Nesse ficheiro adicional temos o *import* da biblioteca Python usada adicionalmente, chamada de [PyOpenSSL](https://www.pyopenssl.org/en/stable/) que nos forneceu alguns métodos fundamentais para a manipulação e leitura dos ficheiros dos certificados fornecidos pelo professor.

Antes de começar a programar a melhor maneira para implementar o enunciado, utilizou-se a ferramenta *OpenSSL* na linha de comandos para converter o CA fornecido em `DER` (formato binário para guardar certificados e/ou chaves) para o formato usado mais recentemente `PEM`.

```bash
> openssl x509 -inform DER -outform PEM -in CA.cer -out CertCA.cer
```

- ### Transformação dos ficheiros para objetos *PyOpenSSL*

No ficheiro [**OpenSSLWorker.py**](https://github.com/uminho-miei-crypto/1920-G9/blob/master/Gui%C3%B5es/G9/OpenSSLWorker.py) temos a inicialização da leitura dos ficheiros fornecidos, ou seja a CA.pem (agora em formato `PEM`) e os certificados `Cliente1.p12` e `Servidor.p12` utilizando da biblioteca [PyOpenSSL](https://www.pyopenssl.org/en/stable/) os métodos `crypto.load_certificate()` e `load_pkcs12()`.

```python
# Abertura dos vários ficheiros e transformação para instâncias do PyOpenSSL
with open('Certificados/CertCA.pem', 'r') as ca_file:
    ca_pem = ca_file.read()
ca = crypto.load_certificate(crypto.FILETYPE_PEM, ca_pem)

# Abertura do PKCS12 com o certificado e chave privada do cliente.
with open('Certificados/Cliente1.p12', 'rb') as client_file:
    clientPKCS12 = client_file.read()
p12Client = crypto.load_pkcs12(clientPKCS12, bytes('1234', 'utf-8'))
```
Com os objetos agora em Python podemos obter os seus certificados e chaves privadas inseridas nas *keystores* PKCS12.

No caso do *Certificate Authority* (CA) foi colocado num objeto `X509Store` para futura verificação com os certificados do Cliente e Servidor e os seus *chain of trust* respetivamente.

```python
# A criação duma X509 Store para guardar o nosso Certificate Authority (CA)
store = crypto.X509Store()
store.add_cert(ca)
```

- ###  Verificação do *chain of trust*

Para este método foi utilizado uma *flag*, que caso fosse 0 (Servidor) ou 1 (Cliente) verificasse através do método `verify_certificate()` se o certificado da parte envolvida foi realmente assinado pelo *issuer* mencionado, ou seja o nosso `CertCA.pem`.

```python
def certVerify(flag):
    if (flag == 0):
        cert = serverCert()
    else:
        cert = clientCert()

    # Criação dum X509StoreContext entre a nossa store o certificado a verificar.
    store_ctx = crypto.X509StoreContext(store, cert)

    # Verificação do chain of trust.
    try:
        store_ctx.verify_certificate()
        return True
    except Exception:
        return False
```

- ### Assinar e verificar com os certificados

Através das chaves privadas fornecidas nas *keystores* PKCS12 pudemos utilizar o método `crypto.sign()` para assinar a mensagem do Servidor ou Cliente e também o método `crypto.verify()` para verificar se um determinado certificado assinou a mensagem pedida.

- ### Exemplo destes métodos no ficheiro `Servidor.py`

```python
# Verificação do chain of trust do certificado do cliente antes da verificação da assinatura.
    if certVerify(1):
        print("O certificado tem a sua chain of trust correta")
        
        # Chamada da função para verificar se a mensagem recebida do Cliente foi assinada pelo mesmo, usando Chave Pública do Certificado.
        if verifySignature(1, signature, publicKeyBytes):
            print("A assinatura do cliente foi corretamente verificada com o seu certificado")
            
            publicKeyServer = load_pem_public_key(publicKeyBytes, backend=default_backend())
            sharedKey = serverPrivateKey.exchange(publicKeyServer)
        
        else: sys.exit("Ataque Intermediário - O cliente/certificado não assinou esta mensagem.")
    
    else: sys.exit("O certificado do cliente não conseguiu ser verificado no seu chain of trust (CA)")
```
---
