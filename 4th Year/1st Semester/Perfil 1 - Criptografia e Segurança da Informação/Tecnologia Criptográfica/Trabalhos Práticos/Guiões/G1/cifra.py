from cryptography.fernet import Fernet

### 1. Processo de crifrar o conteúdo do ficheiro. ###

key = Fernet.generate_key()

# Guardar a chave Fernet num ficheiro.
file = open('chave.key', 'wb')
file.write(key)
file.close()

# Abrir/Ler o conteúdo do texto a cifrar.
textofile = open('texto.txt', 'rb')
texto = textofile.read()
textofile.close()

# Crifrar o texto.
f = Fernet(key)
cifra = f.encrypt(texto)

# Criar/Escrever o conteúdo do texto cifrado num novo ficheiro.
fileencrypt = open('cifrado.txt', 'wb')
fileencrypt.write(cifra)
fileencrypt.close()

### 2. Processo de decifrar o conteúdo do ficheiro. ###

# Ler a chave Fernet.
file = open('chave.key', 'rb')
chave = file.read()
file.close()

# Ler o conteúdo do texto cifrado.
filecifrado = open('cifrado.txt', 'rb')
textocifrado = filecifrado.read()
filecifrado.close()

# Decifrar o texto por aplicação da chave Fernet.
f2 = Fernet(chave)
final = f2.decrypt(textocifrado)
print(final)