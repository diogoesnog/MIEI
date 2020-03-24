from data_groups import dg1 as DG1
from data_groups import dg6 as DG6
from data_groups import dg10 as DG10
from data_groups import ef_com as EF_COM
from data_groups import ef_groupAccess as EF_GroupAccess
from cryptography import x509
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives.serialization import load_der_private_key
from data_groups import ef_sod_parser as parser
import re
import sys

class EF_SOD:
    def __init__(self, data):
        """
        Parâmetros
        ----------
        data : dict
            dicionário com os nomes das variáveis de instância como chaves
            e respetivo conteúdo como valor
        """
        if isinstance(data, str):
            self.signed_data = self.load(data)
        else:
            self.signed_data = parser.create_signed_data(data)

    def save(self, filename):
        """Armazena os dados do EF_SOD num ficheiro.

        Parâmetros:
        -----------
        filename : str
            nome do ficheiro onde se pretende armazenar os dados
        """
        with open(filename, 'w+') as fp:
            print(self.signed_data)
            hex_data = parser.sod_encode(self.signed_data)
            fp.write(hex_data)


    def load(self, filename):
        """ Carrega os dados do EF_SOD de um ficheiro.
        
        Parâmetros
        ----------
        filename : str
            nome do ficheiro a partir do qual se pretende obter os dados
        
        Retorna
        -------
        data : dict
            dicionário com os nomes das variáveis de instância como chaves
            e respetivo conteúdo como valor
        """
        with open(filename, 'r') as fp:
            data = parser.sod_decode(fp.read())
        return data

    def set_digests(self, groups):
        dgh = parser.DataGroupHash()
        for n, (id, group) in enumerate(groups.items()):
            data = parser.Data()
            data['dataGroupNumber'] = id
            data['dataGroupHashValue'] = group.hash(self.signed_data['digestAlgorithm'])
            dgh.setComponentByPosition(n, data)
        self.signed_data['dataGroupHash'] = dgh

    def get_digests(self):
        res = {}
        for group in self.signed_data['dataGroupHash']:
            res[int(group['dataGroupNumber'])] = str(group['dataGroupHashValue'])
        return res

    def set_signature(self, password):
        try:
            key = load_der_private_key(bytes(self.signed_data['signature']), password=password, backend=default_backend())
        except ValueError:
            print("ERROR: Bad decrypt. Incorrect password?")
            sys.exit(1)

        digest = ''.join([str(x['dataGroupHashValue']) for x in self.signed_data['dataGroupHash']])

        signature = None

        if self.signed_data['signatureAlgorithm'] == 'id-pk-RSA-PKCS1-v1_5-SHA256':
            signature = key.sign(
                digest.encode(),
                padding.PKCS1v15(),
                hashes.SHA256()
            )
        elif self.signed_data['signatureAlgorithm'] == 'id-pk-RSA-PSS-SHA256':
            signature = key.sign(
                digest.encode(),
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )
        elif self.signed_data['signatureAlgorithm'] == 'id-pk-RSA-PKCS1-v1_5-SHA1':
            signature = key.sign(
                digest.encode(),
                padding.PKCS1v15(),
                hashes.SHA1()
            )
        elif self.signed_data['signatureAlgorithm'] == 'id-pk-RSA-PSS-SHA1':
            signature = key.sign(
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
        self.signed_data['signature'] = signature

    def get_signature(self):
        return self.signed_data['signature']

    def encode(self):
        return parser.sod_encode(self.signed_data)
