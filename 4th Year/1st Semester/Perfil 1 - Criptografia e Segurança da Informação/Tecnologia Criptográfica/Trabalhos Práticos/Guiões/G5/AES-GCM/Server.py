# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams

import asyncio
import os

from cryptography.hazmat.primitives.ciphers.aead import AESGCM

conn_cnt = 0
conn_port = 8888
max_msg_size = 9999

# Random Key with 128 bits.
key = AESGCM.generate_key(bit_length=128)

# Nonce - Not need to be kept secret.
nonce = os.urandom(12)

class ServerWorker(object):

    def __init__(self, cnt, addr=None):

        self.idClient = cnt
        self.addr = addr
        self.messageCounter = 0

    def process(self, msg):

        # Number of Message from Client.
        self.messageCounter += 1

        # Decrypt Message received from Client.
        aesgcm = AESGCM(key)
        decryptMessage = aesgcm.decrypt(nonce, msg, None)

        print('%d' % self.idClient + ": " + decryptMessage.decode())

        return decryptMessage if len(decryptMessage)>0 else None

@asyncio.coroutine
def handle_echo(reader, writer):
    global conn_cnt
    conn_cnt +=1
    addr = writer.get_extra_info('peername')
    srvwrk = ServerWorker(conn_cnt, addr)
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
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(handle_echo, '127.0.0.1', conn_port, loop=loop)
    server = loop.run_until_complete(coro)
    # Serve requests until Ctrl+C is pressed
    print('Serving on {}'.format(server.sockets[0].getsockname()))
    print('  (type ^C to finish)\n')
    
    keyAndNonce = key + nonce

    # Saved to a file Key and Nonce - Client use the same key.
    file = open('keyAndNonce.key', 'wb')
    file.write(keyAndNonce)
    file.close()
    
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