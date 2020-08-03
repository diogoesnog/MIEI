from cryptography.exceptions import *
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization, hashes, hmac
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC

# Curva Eliptica a usar
default_curve = ec.SECP384R1()

# Algoritmo SHA-2 a usar
algoritmoSHA = hashes.SHA256()


# Criação duma hash com um algortimo SHA-2
def hashs(s):
    digest = hashes.Hash(algoritmoSHA, backend=default_backend())
    digest.update(s)
    return digest.finalize()


def myMAC(key):
    return hmac.HMAC(key, algoritmoSHA, default_backend())


def kdf(salt):
    return PBKDF2HMAC(
        algorithm=algoritmoSHA,
        length=32,
        salt=salt,
        iterations=100000,
        backend=default_backend()
    )


def ecdh_ecdsa(connection):
    # Geração da chave privada e pública de ECDH
    privatekeyECDH = ec.generate_private_key(default_curve, default_backend())
    publickeyECDH = privatekeyECDH.public_key().public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo)

    # Geração da Private e Public Key (ECDSA) para a assinatura
    privatekeyECDSA = ec.generate_private_key(default_curve, default_backend())
    publickeyECDSA = privatekeyECDSA.public_key().public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo)

    # Envia a chave pública ECDSA
    connection.send(publickeyECDSA)

    # Cálculo da assinatura ECDSA da chave pública ECDH
    assinatura = privatekeyECDSA.sign(publickeyECDH, ec.ECDSA(algoritmoSHA))

    # Receber a chave pública ECDSA do parceiro
    publickeyECDSApeer = serialization.load_pem_public_key(
        connection.recv(),
        backend=default_backend())

    # Enviar ao parceiro a chave pública ECDH e a assinatura ECDSA
    connection.send(publickeyECDH)
    connection.send(assinatura)

    # Verificar se as condições se verificam
    try:
        pubkeyECDH_Peer_PEM = connection.recv()
        assinaturaPeer = connection.recv()
        publickeyECDSApeer.verify(assinaturaPeer, pubkeyECDH_Peer_PEM, ec.ECDSA(hashes.SHA256()))
        print("Está verificada a assinatura do parceiro.")
    except InvalidSignature:
        print("A assinatura não pode ser verificada.")

    # Criação da Shared Key com o parceiro
    publickeyECDH_Peer = serialization.load_pem_public_key(
        pubkeyECDH_Peer_PEM,
        backend=default_backend())
    sharedKey = privatekeyECDH.exchange(ec.ECDH(), publickeyECDH_Peer)

    # Confirmação pela Hash
    myTag = hashs(bytes(sharedKey))
    connection.send(myTag)
    tag_Peer = connection.recv()
    if myTag == tag_Peer:
        print('Valid ECDH (MAC)')
        return myTag
    else:
        print('Invalid DH (MAC)')

    # Eliminar dados nas instâncias
    privatekeyECDH = None
    publickeyECDH = None
    pubkeyECDH_Peer_PEM = None
    publickeyECDH_Peer = None
    sharedKey = None
    myTag = None
    tag_Peer = None