# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import os

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.serialization import load_pem_public_key, PublicFormat, Encoding

# Número primo e valor de gerador dado pelo Guião.
P = 99494096650139337106186933977618513974146274831566768179581759037259788798151499814653951492724365471316253651463342255785311748602922458795201382445323499931625451272600173180136123245441204133515800495917242011863558721723303661523372572477211620144038809673692512025566673746993593384600667047373692203583
G = 44157404837960328768872680677686802650999163226766694797650810379076416463147265401084491113667624054557335394761604876882446924929840681990106974314935015501571333024773172440352475358750668213444607353872754650805031912866692119819377041901642732455911509867728218394542745330014071040326856846990119719675

# A criação do DH com os números fornecidos no Guião.
parameters = dh.DHParameterNumbers(P, G, None).parameters(backend=default_backend())

# Chave Privada do Servidor.
serverPrivateKey = parameters.generate_private_key()

# Chave Pública do Servidor.
serverPublicKey = serverPrivateKey.public_key()

# IV
iv = b'\x8f\x84\x82\xb0\xfc\x19\xe4!\xd6\xf3"\xce\x87o\xe4}'

conn_cnt = 0
conn_port = 8888
max_msg_size = 9999
class ServerWorker(object):

    def __init__(self, cnt, addr=None):

        self.idClient = cnt
        self.addr = addr
        self.messageCounter = 0

    def process(self, msg, sharedKey):

        # Número da mensagem.
        self.messageCounter += 1

        # Derivação da shared key para 32 bytes ou seja 256 bits (mais seguro).
        derivedKey = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=b'\x8f\x84\x82\xb0\xfc\x19\xe4!\xd6\xf3"\xce\x87o\xe4}',
        info=b'handshake data',
        backend=default_backend()
        ).derive(sharedKey)

        # Desencriptar a mensagem vinda do Cliente.
        cipher = Cipher(algorithms.AES(derivedKey), modes.CFB(iv), backend=default_backend())
        decryptor = cipher.decryptor()
        decryptMessage = decryptor.update(msg) + decryptor.finalize()
        
        print('%d' % self.idClient + ": " + decryptMessage.decode())

        return decryptMessage if len(decryptMessage)>0 else None

@asyncio.coroutine
def handle_echo(reader, writer):
    global conn_cnt
    conn_cnt +=1
    addr = writer.get_extra_info('peername')
    srvwrk = ServerWorker(conn_cnt, addr)
    
    # Enviar a Chave Pública para o Cliente que entrou.
    publicKeyEnviar = serverPublicKey.public_bytes(Encoding.PEM, PublicFormat.SubjectPublicKeyInfo)
    writer.write(publicKeyEnviar)

    # Receber a Chave Pública do Cliente para a criação da Shared Key.
    publicKeyBytes = yield from reader.read(max_msg_size)
    publicKeyServer = load_pem_public_key(publicKeyBytes, backend=default_backend())
    sharedKey = serverPrivateKey.exchange(publicKeyServer)

    data = yield from reader.read(max_msg_size)
    while True:
        if not data: continue
        if data[:1]==b'\n': break
        data = srvwrk.process(data, sharedKey)
        if not data: break
        writer.write(data)
        yield from writer.drain()
        data = yield from reader.read(max_msg_size)
    print("[%d]" % srvwrk.idClient + "left.")
    writer.close()


def run_server():
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(handle_echo, '127.0.0.1', conn_port, loop=loop)
    server = loop.run_until_complete(coro)
    # Serve requests until Ctrl+C is pressed
    print('Serving on {}'.format(server.sockets[0].getsockname()))
    print('  (type ^C to finish)\n')
    
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        pass
    # Close the server
    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()
    print('\n Server stopped!')

run_server()