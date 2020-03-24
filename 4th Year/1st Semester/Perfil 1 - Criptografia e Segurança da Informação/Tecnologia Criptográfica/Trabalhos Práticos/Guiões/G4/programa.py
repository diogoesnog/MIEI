import random
import string

from cifraIdentidade import Cifra 
from adversario import Adversario

cifra = Cifra()
adversario = Adversario()

m = ["NULL", "NULL"]

key = cifra.keygen()
enc_oracle = lambda texto: cifra.enc(key, texto)

# Damos ao atacante dois textos que depois serão encriptados.
m[0], m[1] = adversario.choose(enc_oracle)

b =  random.randint(0, 1)
c = cifra.enc(key, m[b])

# Adivinhar qual será a mensagem original.
bLinha = adversario.guess(enc_oracle, c)

print(m[0])
print(m[1])

print(c)
print(b==bLinha)