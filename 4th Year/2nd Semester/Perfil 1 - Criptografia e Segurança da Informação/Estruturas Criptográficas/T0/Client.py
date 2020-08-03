import os
import sys
import asyncio
import socket
import getpass

from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

conn_port = 1234
max_msg_size = 9999

backend = default_backend()

# Método global para derivar a password utilizando o KDF.
def derivePassword():

    salt = b'R\xdb!K\xa3w\x98\xa3\xd3\xed\xf8\x9ew\x07\xa3\x17'


    # Criar instância da classe PBKDF2HMAC. 
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=100000,
        backend=backend
    )

    # Perguntar/Guardar a passphrase dada pelo User.
    try:
        password = getpass.getpass().encode()
    except Exception as error:
        print("Erro na password", error)

    return kdf.derive(password)


derivedKey = derivePassword()
nonce = b'\r\x8e\x19e:\xf5\x18\xfc\x1e\x8c\x97U'
class Client:

    def __init__(self, sckt=None):
        
        self.sckt = sckt
        self.msg_cnt = 0

    def process(self, msg=b""):

        # Número da mensagem.
        self.msg_cnt +=1

        try:
            textInput = input("Introduza o texto a cifrar.\n").encode()
        except KeyboardInterrupt:
            sys.exit()
        

        # Encriptar a mensagem a enviar.
        
        aesgcm = AESGCM(derivedKey) # 256 bit key
        encryptMessage = aesgcm.encrypt(nonce, textInput, None)
        
        return encryptMessage if len(encryptMessage)>0 else None


@asyncio.coroutine
def tcp_echo_client(loop=None):
    if loop is None:
        loop = asyncio.get_event_loop()

    reader, writer = yield from asyncio.open_connection('127.0.0.1',
                                                        conn_port, loop=loop)
    addr = writer.get_extra_info('peername')
    client = Client(addr)
    
    
    # Criação do MAC da chave e enviar
    # h = hmac.HMAC(keyMAC, hashes.SHA256(), backend)
    # h.update(chave)
    # macChave = h.finalize()
    # writer.write(derivedKey)
    
    msg = client.process()
    while msg:
        writer.write(msg)
        msg = yield from reader.read(max_msg_size)
        if msg :
            msg = client.process(msg)
        else:
            break
    writer.write(b'\n')
    print('Socket closed!')
    writer.close()

def run_client():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(tcp_echo_client())
run_client()