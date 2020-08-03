from cryptography.exceptions import *
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization, hashes, hmac
from cryptography.hazmat.primitives.asymmetric import dh, dsa


def myMAC(key):
    return hmac.HMAC(key, hashes.SHA256(), default_backend())


# Criação duma hash com um algortimo SHA-2
def hashs(s):
    digest = hashes.Hash(hashes.SHA256(), backend=default_backend())
    digest.update(s)
    return digest.finalize()


# Geração duns parâmetros Diffie-Hellman
parametrosDH = dh.generate_parameters(generator=2, key_size=1024,
                                      backend=default_backend())

# Geração dos parâmetros DSA
parametrosDSA = dsa.generate_parameters(key_size=1024, backend=default_backend())


def dh_dsa(connection):
    # Geração da Private e Public Key (DH)
    privatekeyDH = parametrosDH.generate_private_key()
    publickeyDH = privatekeyDH.public_key().public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo)

    # Geração da Private e Public Key (DSA) para a assinatura
    privatekeyDSA = parametrosDSA.generate_private_key()
    publickeyDSA = privatekeyDSA.public_key().public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo)

    # Envia a chave pública DSA
    connection.send(publickeyDSA)

    # Cálculo da assinatura DSA da chave pública DH
    assinatura = privatekeyDSA.sign(publickeyDH, hashes.SHA256())

    # Receber a chave pública DSA do parceiro
    publickeyDSApeer = serialization.load_pem_public_key(
        connection.recv(),
        backend=default_backend())

    # Enviar ao parceiro a chave pública DH e a assinatura DSA
    connection.send(publickeyDH)
    connection.send(assinatura)

    # Verificar se as condições se verificam
    try:

        pubkeyDH_Peer_PEM = connection.recv()
        signaturePeer = connection.recv()
        publickeyDSApeer.verify(signaturePeer, pubkeyDH_Peer_PEM, hashes.SHA256())
        print("Está verificada a assinatura do parceiro.")

    except InvalidSignature:
        print("A assinatura não pode ser verificada.")

    # Criação da Shared Key com o parceiro
    pubkeyDH_Peer = serialization.load_pem_public_key(
        pubkeyDH_Peer_PEM,
        backend=default_backend())
    sharedKey = privatekeyDH.exchange(pubkeyDH_Peer)

    # Confirmação pela Hash
    myTag = hashs(bytes(sharedKey))
    connection.send(myTag)
    tag_Peer = connection.recv()

    if myTag == tag_Peer:
        print('Valid DH (MAC)')
        return myTag
    else:
        print('Invalid DH (MAC)')

    # Eliminar dados nas instâncias
    privatekeyDH = None
    publickeyDH = None
    pubkeyDH_Peer_PEM = None
    pubkeyDH_Peer = None
    sharedKey = None
    myTag = None
    tag_Peer = None
