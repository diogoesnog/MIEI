import sys
import os
import asyncio
import getpass

from cryptography.hazmat.primitives.ciphers.aead import AESGCM
from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.backends import default_backend
from cryptography.exceptions import InvalidSignature, InvalidKey

conn_cnt = 0
conn_port = 1234
max_msg_size = 9999

backend = default_backend()

# Criação do nonce de 96 bits (12 bytes)
nonce = b'\r\x8e\x19e:\xf5\x18\xfc\x1e\x8c\x97U'

# Criação do salt de 16 bytes
salt = b'R\xdb!K\xa3w\x98\xa3\xd3\xed\xf8\x9ew\x07\xa3\x17'

def derivePassword():

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
        derivedKey = kdf.derive(password)
        return derivedKey
    except Exception:
        print("Erro na password")
    
derivedKeyServer = derivePassword()

def verifyMAC(mac):

    # Criar instância da classe PBKDF2HMAC. 
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=100000,
        backend=backend
    )

    try:
        kdf.verify(mac, derivedKeyServer)
    except Exception:
        print("Os MACs das chaves não correspondem.")
        sys.exit()


class ServerWorker(object):

    def __init__(self, cnt, addr=None):

        self.idClient = cnt
        self.addr = addr
        self.messageCounter = 0

    def process(self, msg):

        # Número da mensagem
        self.messageCounter += 1

        # Desencriptar a mensagem vinda do Cliente.
        aesgcm = AESGCM(derivedKeyServer)
        decryptMessage = aesgcm.decrypt(nonce, msg, None)

        print('%d' % self.idClient + ": " + decryptMessage.decode())

        return decryptMessage if len(decryptMessage)>0 else None

@asyncio.coroutine
def handle_echo(reader, writer):
    global conn_cnt
    conn_cnt +=1
    addr = writer.get_extra_info('peername')
    srvwrk = ServerWorker(conn_cnt, addr)

    

    # Receber o MAC da chave e criar um MAC igual para verificar (com a )
    # derivedKeyClient = yield from reader.read(32)
    # verifyMAC(derivedKeyClient)

    # try:
    #     h = hmac.HMAC(keyMAC, hashes.SHA256(), backend)
    #     h.update(chave)
    #     h.verify(macChave)
    # except InvalidSignature:
    #     print("Os MACs não correspondem.")
    #     sys.exit()

    data = yield from reader.read(max_msg_size)
    while True:
        if not data: continue
        if data[:1]==b'\n': break
        data = srvwrk.process(data)
        if not data: break
        writer.write(data)
        yield from writer.drain()
        data = yield from reader.read(max_msg_size)
    print("[%d]" % srvwrk.idClient + "left.")
    writer.close()


def run_server():
    
    # Parte para correr o servidor.
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(handle_echo, '127.0.0.1', conn_port, loop=loop)
    server = loop.run_until_complete(coro)
    # Terminar o servidor ao enviar Ctrl+C ou Cmd+C
    print('Serving on {}'.format(server.sockets[0].getsockname()))
    print('  (type ^C to finish)\n')
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        sys.exit()

    # Close the server
    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()
    print('\n Server stopped!')

run_server()