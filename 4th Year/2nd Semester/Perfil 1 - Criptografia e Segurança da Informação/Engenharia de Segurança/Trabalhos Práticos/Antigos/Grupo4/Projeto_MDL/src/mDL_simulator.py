#! /bin/python
import ast
import sys
import json
from mDL_transaction import mDL_transaction
from data_groups import dg1
from data_groups import dg6
from data_groups import dg10
from data_groups import ef_sod
from data_groups import ef_sod_parser
from OpenSSL import crypto
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography import x509
from cryptography.hazmat.backends import default_backend
from cryptography.exceptions import InvalidSignature

DATA = None

if len(sys.argv) > 1:
    if sys.argv[1] in ['--help', '-h']:
        print('Usage: mDL_simulator [FILE]')
        sys.exit()
    with open(sys.argv[1], "r") as fd:
        DATA = json.load(fd)
        for bt in DATA['dg6']['biometric_templates']:
            FILENAME = bt['bdb']
            with open(FILENAME, "rb") as fd:
                IMAGE = fd.read()
                bt['bdb'] = IMAGE
        FILENAME = DATA['ef_sod']['certificate']
        with open(FILENAME, "rb") as fd:
            CERT = fd.read()
            DATA['ef_sod']['certificate'] = CERT
        FILENAME = DATA['ef_sod']['signature']
        with open(FILENAME, "rb") as fd:
            KEY = fd.read()
            DATA['ef_sod']['signature'] = KEY

def calculate_digests(groups, digestAlgorithm):
    digests = {}
    for id, group in groups.items():
        digests[id] = group.hash(digestAlgorithm)
    return digests

def verify_signature(digest, der_cert, signature, algorithm):
    cert = x509.load_der_x509_certificate(der_cert, default_backend())

    public_key = cert.public_key()

    try:
        if algorithm == 'id-pk-RSA-PKCS1-v1_5-SHA256':
            public_key.verify(
                signature,
                digest.encode(),
                padding.PKCS1v15(),
                hashes.SHA256()
            )
        elif algorithm == 'id-pk-RSA-PSS-SHA256':
            public_key.verify(
                signature,
                digest.encode(),
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )
        elif algorithm == 'id-pk-RSA-PKCS1-v1_5-SHA1':
            public_key.verify(
                signature,
                digest.encode(),
                padding.PKCS1v15(),
                hashes.SHA1()
            )
        elif algorithm == 'id-pk-RSA-PSS-SHA1':
            public_key.verify(
                signature,
                digest.encode(),
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA1()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA1()
            )
        else:
            print('ERROR: Signature algorithm not implemented.')
            sys.exit(1)
        return True
    except InvalidSignature:
        return False

def open_data():
    f = open("data.json", "r")
    retorno = f.read()
    f.close()
    return retorno


r = open_data()
dictionary = ast.literal_eval(r)
print(dictionary["ef_sod"])
sod = ef_sod.EF_SOD(dictionary["ef_sod"])
#sod.save("./data_groups/asn1_hex_data/ef_sod.txt")

MDLT = mDL_transaction(DATA)
MDLT.open()
print()

MDLT.request_additional_data(['61', '62'])
print()

transfer_data = MDLT.transfer_data(['61', '62'])
print('DATA:', transfer_data)
print()

transfer_sod_data = MDLT.transfer_sod()
print('SOD:', transfer_sod_data)
print()

dg1 = dg1.DG1(transfer_data[1])
#dg6 = dg6.DG6(transfer_data[6])
dg10 = dg10.DG10(transfer_data[10])
dgs = {
  1: dg1,
  #6: dg6,
  10: dg10
}

print("0ola" + sod.get_signature())

transfer_digests = calculate_digests(dgs, transfer_sod_data['digestAlgorithm'])
dig1 = transfer_sod_data['dataGroupHash'][0]['dataGroupHashValue']
dig6 = transfer_sod_data['dataGroupHash'][1]['dataGroupHashValue']
dig10 = transfer_sod_data['dataGroupHash'][2]['dataGroupHashValue']

sod_digests = ''
for dig in transfer_sod_data['dataGroupHash']:
    sod_digests += str(dig['dataGroupHashValue'])

print('DIGESTS VALIDATION:',
        transfer_digests[1] == dig1 and\
        #transfer_digests[6] == dig6 and\
        transfer_digests[10] == dig10)

print('SIGNATURE VALIDATION:', verify_signature(
    sod_digests,
    bytes(transfer_sod_data['certificate']),
    bytes(transfer_sod_data['signature']),
    transfer_sod_data['signatureAlgorithm'])
)
