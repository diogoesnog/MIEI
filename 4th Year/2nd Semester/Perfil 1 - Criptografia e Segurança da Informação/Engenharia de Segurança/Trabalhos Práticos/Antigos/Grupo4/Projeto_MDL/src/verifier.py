import os
import ast

from cryptography.hazmat.primitives.serialization import load_der_private_key, load_pem_private_key

from src import mDL
from src.data_groups import dg1,dg6,dg10,ef_sod
from src import verify_cert
from cryptography.x509 import load_pem_x509_certificate
from cryptography.hazmat.backends import default_backend
from OpenSSL import crypto
from cryptography import hazmat
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives.serialization import load_der_private_key

#verifica se uma data é maior que outra
def data_bigger(data1, data2):
    if data1 > data2:
        return True
    else:
        return False

#verifica se a parte 1 está bem contruida com os capos obrigatorios do asn1
def verify_part1(part_1):
    # podemos ter de retirar a função
    try:
        digest1 = dg1.DG1(part_1)
    except:
        print("Não tem todos os parâmetros no dg1")
    try:
        digest1.encode()
    except:
        print("Não apresenta o asn1")

#verifica se a parte 6 está bem contruida com os capos obrigatorios do asn1
def verify_part6(part_6):
    # podemos ter de retirar a função
    print(part_6)
    try:
        digest6 = dg1.DG6(part_6)
    except:
        print("Não tem todos os parâmetros no dg6")
    try:
        digest6.encode()
    except:
        print("Não apresenta o asn1")

#verifica se a parte 10 está bem contruida com os capos obrigatorios do asn1
def verify_part10(part_10):
    # podemos ter de retirar a função
    if len(part_10)>5:
        return False
    try:
        digest10 = dg10.DG10(part_10)
    except:
        print("Não tem todos os parâmetros no dg10")
    try:
        digest10.encode()
    except:
        print("Não apresenta o asn10")
    return True


def open_data():
    f = open("exemplo.txt", "r")
    retorno = f.read()
    f.close()
    return retorno

def set_signature(password, assinatura ,digest):
    f = open("certificates/key.der","rb").read()
    try:
        key = load_der_private_key(f, b"passphrase", backend=default_backend())
    except ValueError:
        print("ERROR: Bad decrypt. Incorrect password?")

    if assinatura == 'id-pk-RSA-PKCS1-v1_5-SHA256':
        signature = key.sign(
            digest,
            padding.PKCS1v15(),
            hashes.SHA256()
        )
    elif assinatura == 'id-pk-RSA-PSS-SHA256':
        signature = key.sign(
            digest,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
    elif assinatura == 'id-pk-RSA-PKCS1-v1_5-SHA1':
        signature = key.sign(
            digest,
            padding.PKCS1v15(),
            hashes.SHA1()
        )
    elif assinatura == 'id-pk-RSA-PSS-SHA1':
        signature = key.sign(
            digest,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA1()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA1()
        )
    else:
        print('ERROR: Signature algorithm not implemented.')
        sys.exit(1)
    return signature

def main():
    r = open_data()
    dictionary = ast.literal_eval(r)

    #verica se os campos estão bem construidos
    verify_part1(dictionary.get(1))
    #verify_part6(dictionary.get(6))
    verify_part10(dictionary.get(10))

    #verifica se o certificado ainda está na data e se as datas da carta estão corretas
    ver = verify_cert.cert_verifier("certificates/certificate.der")
    #ver.verificar(dictionary.get(1).get('date_of_issue'),dictionary.get(1).get('date_of_issue'))
    if (ver.verificar_data_certificado_expirada()):
        print("Data do certificado expirada")
    if (ver.verificar_datas(dictionary.get(1).get("date_of_issue"),dictionary.get(1).get("date_of_expiry"))):
        print("Datas não estão dentro do limite do certificado")

    digest1 = dg1.DG1(dictionary.get(1))
    digest10 = dg10.DG10(dictionary.get(10))

    sod = dictionary.get("ef_sod")

    # Compara os digests com a respetiva hash e verifica a assinatura
    hash1 = digest1.hash(sod.get("digestAlgorithm"))

    if (hash1 != dictionary.get(2).get(1)):
        print("Hash do digest 1 é diferente")

    #Compara os digests com a respetiva hash e verifica a assinatura
    hash10 = digest10.hash(sod.get("digestAlgorithm"))

    if (hash10 != dictionary.get(2).get(10)):
        print("Hash do digest 10 é diferente")

    sod = ef_sod.EF_SOD(sod)

    resultado = ver.verify_signature(hash10, dictionary.get("assinatura10"), dictionary.get("ef_sod").get("signatureAlgorithm"))
    if (resultado== False):
        print("Assinatura com a chave publica do certificado errada!!")

    resultado = ver.verify_signature(hash1, dictionary.get("assinatura1"),dictionary.get("ef_sod").get("signatureAlgorithm"))
    if (resultado == False):
        print("Assinatura com a chave publica 1 do certificado errada!!")


main()