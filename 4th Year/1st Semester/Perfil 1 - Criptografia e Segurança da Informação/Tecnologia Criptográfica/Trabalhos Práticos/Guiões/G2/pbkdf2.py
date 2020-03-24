import os
import getpass
import base64

from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.backends import default_backend
from cryptography.fernet import Fernet

### 1. Processo de crifrar o conteúdo do ficheiro. ###

backend = default_backend()
salt = os.urandom(16)

# Guardar o Salt gerado.
file = open('salt.key', 'wb')
file.write(salt)
file.close()

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

# Deriva uma chave criptográfica através da passphrase do User.
key = kdf.derive(password)

# Abrir/Ler o conteúdo do texto a cifrar.
textofile = open('texto.txt', 'rb')
texto = textofile.read()
textofile.close()

# Criar o texto.
key = base64.urlsafe_b64encode(key)
f = Fernet(key)
cifra = f.encrypt(texto)

# Criar o ficheiro com texto cifrado.
fileencrypt = open('cifrado.txt', 'wb')
fileencrypt.write(cifra)
fileencrypt.close()

# FASE 2 -Desencriptar

# Buscar o Salt.
file = open('salt.key', 'rb')
salt2 = file.read()
file.close()

# Criar nova instância da classe PBKDF2HMAC.
kdf2 = PBKDF2HMAC(
    algorithm=hashes.SHA256(),
    length=32,
    salt=salt2,
    iterations=100000,
    backend=backend
)

# Perguntar novamente a password para se poder decifrar o texto.
try:
    password2 = getpass.getpass().encode()
except Exception as error:
    print("Erro na password", error)

key2 = kdf2.derive(password2)

# Ler texto cifrado.
filecifrado = open('cifrado.txt', 'rb')
textocifrado = filecifrado.read()
filecifrado.close()

# Decifrar o texto final.
key2 = base64.urlsafe_b64encode(key2)
f2 = Fernet(key2)
final = f2.decrypt(textocifrado)

print(final)