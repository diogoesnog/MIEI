# Guião 10 -  *DiCert* (Aplicação Cliente-Servidor Final)

Este último Guião surge com o objetivo de se agrupar tudo o que foi dado até então, criando uma aplicação robusta e completamente funcional, indo de encontro com as implementações pedidas pelos vários Guiões anteriores para esta aplicação entre Cliente e Servidor.

O grande melhoramento desta versão final é a geração dos vários Certificados, que precisarão depois ser usados no decorrer da sua execução.

---

## Resolução do Guião

No que toca ao código em si, poucas foram as alterações feitas em relação ao Guião anterior. Continua a existir a classe principal de métodos [OpenSSLWorker.py](https://github.com/uminho-miei-crypto/1920-G9/blob/master/Gui%C3%B5es/G10/OpenSSLWorker.py) e as classes correspondentes ao Cliente e Servidor.

A única diferença é a adição de um novo método na classe [OpenSSLWorker.py](https://github.com/uminho-miei-crypto/1920-G9/blob/master/Gui%C3%B5es/G10/OpenSSLWorker.py), de nome ```verifySubject``` e cuja responsabilidade passa por verificar se o Certificado é proveninente do *subject* correto/esperado cada uma das entidades, após se ter comprovado que o mesmo possui a *chain of trust* correta.

```python
def verifySubject(flag):
    
    if(flag == 0):
        cert = serverCert()
    else:
        cert = clientCert()

    subjectParameters = cert.get_subject()

    components = subjectParameters.get_components()

    tuploCN = components[-1]

    if(flag == 0):
        return tuploCN[-1] == b'Server'
    else:
        return tuploCN[-1] == b'Cliente'
```

Assim, e da forma como o código está pensado, conseguimos verificar a compatibilidade entre os certificados, dando luz verde para que seja depois verificada a assinatura em si e que as mensagens possam então começar a ser trocadas através do canal.

---

## Preparar a Aplicação

Antes mesmo de se começar a "correr" a aplicação, seguiram-se um conjunto de comandos ``openssl`` que permitiram gerar os Certificados a ser utilizados pela mesma. 

Tendo em conta que todo o código da nossa aplicação Cliente-Servidor já estava planeado e estruturado para os Certificados dados no Guião anterior, a ideia foi manter essa parte, na medida em que se manteve o tipo de ficheiros com que se estava a trabalhar.

**Estes comandos são fruto de todas essas decisões e os vários ficheiros que foram produzidos no entretanto encontram-se na pasta [Ficheiros Intermédios]().**

### 1. Criação de CA Root e Certificados personalizados usando OpenSSL

```bash
# CA Root
openssl genrsa -out chaveCA.key -aes256 -passout pass:DiCert
openssl req -new -x509 -key chaveCA.key -out CA.pem

# Servidor
openssl genrsa -aes256 -passout pass:Server -out chaveServer.key
openssl req -new -key chaveServer.key -out Server.csr 
openssl x509 -req -in Server.csr -CA CA.pem -CAkey chaveCA.key -out Server.pem -CAcreateserial

# Cliente
openssl genrsa -aes256 -passout pass:Server -out chaveCliente.key
openssl req -new -key chaveCliente.key -out Cliente.csr
openssl x509 -req -in Cliente.csr -CA DiCert.pem -CAkey chaveCA.key -out Cliente.pem -CAcreateserial
```

### 2. Criação da PKCS12 do Cliente e Servidor com a sua Chave Privada e Certificado
```bash
openssl pkcs12 -export -out Cliente.p12 -inkey chaveCliente.key -in Cliente.pem
openssl pkcs12 -export -out Server.p12 -inkey chaveServer.key -in Server.pem
```