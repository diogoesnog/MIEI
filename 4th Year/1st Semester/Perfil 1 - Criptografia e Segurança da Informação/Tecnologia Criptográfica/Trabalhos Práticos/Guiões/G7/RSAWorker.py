from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives.serialization import load_pem_private_key, load_pem_public_key, Encoding, PrivateFormat, NoEncryption, PublicFormat
from cryptography.hazmat.primitives import hashes
from cryptography.exceptions import InvalidSignature

# Gerar as Chaves de ambos os extremos do canal, salvando-as.
def generateAndSaveKey (flag):

    # 1. Gerar a Chave Privada e Pública.
    rsaPrivateKey = rsa.generate_private_key(
        public_exponent=65537,    
        key_size=2048,    
        backend=default_backend()
    )
    rsaPublicKey = rsaPrivateKey.public_key()

    # 2. Salvar a Chave Privada e Pública, consoante a flag.

    # Criação dos bytes serializados da Chave RSA Privada.
    privateBytes = rsaPrivateKey.private_bytes(
        encoding=Encoding.PEM,
        format=PrivateFormat.TraditionalOpenSSL,
        encryption_algorithm=NoEncryption()
    )

    # Criação dos bytes serializados da Chave RSA Pública.
    publicBytes = rsaPublicKey.public_bytes(encoding=Encoding.PEM,
        format=PublicFormat.SubjectPublicKeyInfo)

    # Guardar no ficheiro a Chave Privada.
    if(flag==0): nomeFicheiro = "serverRSA.private"
    else: nomeFicheiro = "clientRSA.private"
    with open(nomeFicheiro, "wb") as privateKeyFile:
        privateKeyFile.write(privateBytes)

    # Guardar no ficheiro a Chave Pública.
    if(flag==0): nomeFicheiro = "serverRSA.public"
    else: nomeFicheiro = "clientRSA.public"
    with open(nomeFicheiro, "wb") as publicKeyFile:
        publicKeyFile.write(publicBytes)

# Assinar a mensagem com a Chave Privada RSA.
def signingMessage(rsaPrivateKey, message):

    signature = rsaPrivateKey.sign(
        message,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
    )
    return signature

# Função standalone para verificar uma assinatura fornecendo também a Chave pública RSA.
def verification(rsaPublicKey, signature, message):
    try:
        rsaPublicKey.verify(
        signature,
        message,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
        )
        return True
    except InvalidSignature:
        return False

# Função standalone para efetuar o loading da Chave Privada RSA.
def loadPrivateKey(flag):

    if(flag==0): nomeFicheiro = "serverRSA.private"
    else: nomeFicheiro = "clientRSA.private"

    with open(nomeFicheiro, "rb") as privateKeyFile:

        privateKey = load_pem_private_key(
            privateKeyFile.read(),
            password=None,
            backend=default_backend()
        )
    return privateKey

# Função standalone para efetuar o loading da Chave Pública RSA.
def loadPublicKey(flag):
    
    if(flag==0): nomeFicheiro = "serverRSA.public"
    else: nomeFicheiro = "clientRSA.public"

    with open(nomeFicheiro, "rb") as publicKeyFile:
        
        publicRSAKey = load_pem_public_key(
            publicKeyFile.read(),
            backend=default_backend()
        )

    return publicRSAKey