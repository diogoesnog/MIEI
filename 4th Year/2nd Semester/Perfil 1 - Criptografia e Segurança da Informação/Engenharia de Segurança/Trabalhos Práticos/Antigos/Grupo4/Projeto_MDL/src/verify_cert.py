import os
import ast
import datetime
from cryptography.exceptions import InvalidSignature
from src import mDL
from src.data_groups import dg1,dg6,dg10
from cryptography.x509 import load_pem_x509_certificate
from cryptography.hazmat.backends import default_backend
from OpenSSL import crypto
from cryptography import hazmat
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.asymmetric import padding


def data_bigger(data1, data2):
    if data1 > data2:
        return True
    else:
        return False


class cert_verifier:
    def __init__(self, data):
        self.cert = crypto.load_certificate(crypto.FILETYPE_ASN1, open(data, 'rb').read())
        self.data_final = self.cert.get_notAfter().decode()
        self.data_inicial = self.cert.get_notBefore().decode()
        self.public_key = self.cert.get_pubkey().to_cryptography_key()

    #verifica se as datas do certificado abrangem as datas da carta de condução
    def verificar_datas(self,data_inicio,data_fim):
        data_final_certificado = datetime.date(int(self.data_final[:4]),int(self.data_final[5:6]),int(self.data_final[6:8]))
        data_inicial_certificado = datetime.date(int(self.data_inicial[:4]),int(self.data_inicial[5:6]),int(self.data_inicial[6:8]))
        data_inicio = datetime.date(int(data_inicio[:4]),int(data_inicio[5:6]),int(data_inicio[6:8]))
        data_fim = datetime.date(int(data_fim[:4]), int(data_fim[5:6]), int(data_fim[6:8]))
        if not (data_bigger(data_fim,data_final_certificado)):
            return False
        if (data_bigger(data_inicial_certificado,data_inicio)):
            return False
        return True

    #verifica se a data do certificado está expirada
    def verificar_data_certificado_expirada(self):
        data_atual = datetime.datetime.now().date()
        data_final = datetime.date(int(self.data_final[:4]),int(self.data_final[5:6]),int(self.data_final[6:8]))
        if data_bigger(data_atual,data_final):
            return True
        else:
            return False

    #verifica a assinatura
    def verify_signature(self,digest, signature, algorithm):
        try:
            if algorithm == 'id-pk-RSA-PKCS1-v1_5-SHA256':
                self.public_key.verify(
                    signature,
                    digest,
                    padding.PKCS1v15(),
                    hashes.SHA256()
                )
            elif algorithm == 'id-pk-RSA-PSS-SHA256':
                self.public_key.verify(
                    signature,
                    digest,
                    padding.PSS(
                        mgf=padding.MGF1(hashes.SHA256()),
                        salt_length=padding.PSS.MAX_LENGTH
                    ),
                    hashes.SHA256()
                )
            elif algorithm == 'id-pk-RSA-PKCS1-v1_5-SHA1':
                self.public_key.verify(
                    signature,
                    digest,
                    padding.PKCS1v15(),
                    hashes.SHA1()
                )
            elif algorithm == 'id-pk-RSA-PSS-SHA1':
                self.public_key.verify(
                    signature,
                    digest,
                    padding.PSS(
                        mgf=padding.MGF1(hashes.SHA1()),
                        salt_length=padding.PSS.MAX_LENGTH
                    ),
                    hashes.SHA1()
                )
            else:
                print('ERROR: Signature algorithm not implemented.')
            return True
        except InvalidSignature:
            return False