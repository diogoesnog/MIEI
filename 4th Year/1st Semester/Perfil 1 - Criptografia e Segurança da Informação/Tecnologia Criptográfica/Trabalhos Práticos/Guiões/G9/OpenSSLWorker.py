from OpenSSL import crypto

# Abertura dos vários ficheiros e transformação para instâncias do PyOpenSSL
with open('Certificados/CertCA.pem', 'r') as ca_file:
    ca_pem = ca_file.read()
ca = crypto.load_certificate(crypto.FILETYPE_PEM, ca_pem)

# Abertura do PKCS12 com o certificado e chave privada do cliente.
with open('Certificados/Cliente1.p12', 'rb') as client_file:
    clientPKCS12 = client_file.read()
p12Client = crypto.load_pkcs12(clientPKCS12, bytes('1234', 'utf-8'))

# Abertura do PKCS12 com o certificado e chave privada do servidor.
with open('Certificados/Servidor.p12', 'rb') as servidor_file:
    servidorPKCS12 = servidor_file.read()
p12Servidor = crypto.load_pkcs12(servidorPKCS12, bytes('1234', 'utf-8'))

# A criação duma X509 Store para guardar o nosso Certificate Authority (CA)
store = crypto.X509Store()
store.add_cert(ca)

def clientCert():
    return p12Client.get_certificate()

def serverCert():
    return p12Servidor.get_certificate()

def sPrivateKey():
    return p12Servidor.get_privatekey()

def cPrivateKey():
    return p12Client.get_privatekey()

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


def signingMessage(privateKey, message):
    return crypto.sign(privateKey, message, 'sha256')

def verifySignature(flag, signature, message):
    
    if (flag == 0):
        try:
            cert = serverCert()
            crypto.verify(cert, signature, message, 'sha256')
            return True
        except Exception:
            return False
    else:
        try:
            cert = clientCert()
            crypto.verify(cert, signature, message, 'sha256')
            return True
        except Exception:
            return False