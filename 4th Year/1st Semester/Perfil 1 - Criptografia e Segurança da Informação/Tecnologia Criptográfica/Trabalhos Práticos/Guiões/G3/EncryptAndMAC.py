import os
import getpass
import base64

from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, hmac

# Obter randoms para o Salt e Nonce.
salt = os.urandom(16)
nonce = os.urandom(16)

# Criar instância da classe PBKDF2HMAC.
kdf = PBKDF2HMAC(
    algorithm=hashes.SHA256(),
    length=64,
    salt=salt,
    iterations=100000,
    backend = default_backend()
)

# Perguntar/Guardar a passphrase dada pelo User.
try:
    password = getpass.getpass().encode()
except Exception as error:
    print("Erro na password", error)

# Derivação da passphrase.
key = kdf.derive(password)

# Divisão dos 64 bits de chave derivada para a chave de encriptação e para a chave para o MAC.
chaveC = key[:32]
chaveMAC = key[32:]

# FASE 1 - Encriptar

# Abrir o ficheiro a cifrar.
textofile = open('texto.txt', 'rb')
textoCifrar = textofile.read()
textofile.close()

# Algoritmo Chacha20 para a cifragem.
algorithm = algorithms.ChaCha20(chaveC, nonce)
cipher = Cipher(algorithm, mode=None, backend = default_backend())
encryptor = cipher.encryptor()
mensagemEncriptada = encryptor.update(textoCifrar)

# Parte HMAC.
mac = hmac.HMAC(chaveMAC, hashes.SHA256(), backend = default_backend())
mac.update(textoCifrar)
tagMAC = mac.finalize()

mensagemFinal = tagMAC + mensagemEncriptada

# Guardar a tag MAC e o criptograma.
fileCrypt = open('textoCrypt.txt', 'wb')
fileCrypt.write(mensagemFinal)
fileCrypt.close()

# FASE 2 - Desencriptar

decryptor = cipher.decryptor()

desencriptado = decryptor.update(mensagemFinal[32:])
print(desencriptado)
