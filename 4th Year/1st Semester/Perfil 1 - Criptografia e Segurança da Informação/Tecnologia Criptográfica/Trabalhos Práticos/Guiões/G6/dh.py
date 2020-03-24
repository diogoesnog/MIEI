from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.primitives.kdf.hkdf import HKDF

# Número primo e valor de gerador dado pelo guião
P = 99494096650139337106186933977618513974146274831566768179581759037259788798151499814653951492724365471316253651463342255785311748602922458795201382445323499931625451272600173180136123245441204133515800495917242011863558721723303661523372572477211620144038809673692512025566673746993593384600667047373692203583
G = 44157404837960328768872680677686802650999163226766694797650810379076416463147265401084491113667624054557335394761604876882446924929840681990106974314935015501571333024773172440352475358750668213444607353872754650805031912866692119819377041901642732455911509867728218394542745330014071040326856846990119719675

# A criação do DH com os números fornecidos no guião
parameters = dh.DHParameterNumbers(P, G, None).parameters(backend=default_backend())

# Geração da chave privada do servidor
serverPrivateKey = parameters.generate_private_key()

# Geração da chave privada do cliente
clientPrivateKey = parameters.generate_private_key()

# verificação que é a mesma (handshake)
clientPublicKey = clientPrivateKey.public_key()
sharedKey1 = serverPrivateKey.exchange(clientPublicKey)

# Derivação da shared key com 32 bytes ou seja 256 bits (mais seguro)
derivedKey1 = HKDF(
algorithm=hashes.SHA256(),
length=32,
salt=None,
info=b'handshake data',
backend=default_backend()
).derive(sharedKey1)


# a mesma chave shared, agora ao contrário
serverPublicKey = serverPrivateKey.public_key()
sharedKey2 = clientPrivateKey.exchange(serverPublicKey)

# derivar essa também
derivedKey2 = HKDF(
algorithm=hashes.SHA256(),
length=32,
salt=None,
info=b'handshake data',
backend=default_backend()
).derive(sharedKey2)

# ver que são iguais
print(derivedKey1 == derivedKey2)