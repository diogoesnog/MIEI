from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
import asn1_parser as asn1
import sys

class DG10:
    """
    Classe utilizada para representar um grupo de dados 10.

    Atributos
    ---------

    Métodos
    -------
    """
    def __init__(self, data):
        """ Construtor da classe DG6.

        Parâmetros
        ----------
        data : list
            lista de dicionários que representam biometric templates
        """
        if isinstance(data, str):
            data = self.load(data)
        self.version = data['version']
        self.last_update = data['last_update']
        self.expiration_date = data['expiration_date']
        self.next_update = data['next_update']
        self.management_info = data['management_info']

    def save(self, filename):
        """Armazena os dados do DG10 num ficheiro, codificados com ASN1.

        Parâmetros:
        -----------
        filename : str
            nome do ficheiro onde se pretende armazenar os dados
        """
        with open(filename, 'w+') as fp:
            hex_data = asn1.encode(self, './data_groups/configs/dg10.json')
            fp.write(hex_data)


    def load(self, filename):
        """ Carrega os dados do DG6 de um ficheiro, codificado com ASN1.

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
            data = asn1.decode(fp.read(), './data_groups/configs/dg10.json')
        return data


    def __str__(self):
        """ Retorna uma string que apresenta os dados do DG10

        Retorna
        -------
        data : str
            string com os dados do DG10
        """
        return 'Version: ' + self.version + '\n' +\
            'Last update: ' + self.last_update + '\n' +\
            'Expiration date: ' + self.expiration_date + '\n' +\
            'Next update: ' + self.next_update + '\n' +\
            'Management information: ' + self.management_info


    def get_data(self):
        """ Devolve os dados associados.

        Retorna
        -------
        data : dict
            dicionário com os nomes das variáveis de instância como
            chaves e respetivo conteúdo como valor
        """
        return {
            'version': self.version,
            'last_update': self.last_update,
            'expiration_date': self.expiration_date,
            'next_update': self.next_update,
            'management_info': self.management_info
        }

    def encode(self):
        """Codificados os dados do DG10 com ASN1.

        Retorna:
        --------
        hex_data : str
            dados do DG10 codificados em hexadecimal
        """
        return asn1.encode(self, './data_groups/configs/dg10.json')

    def hash(self, oid):
        """ Calcula o valor de hash dos dados do DG10.

        Retorna
        -------
        digest : str
            valor de hash
        """
        data = "".join([
            self.version,
            self.last_update,
            self.expiration_date,
            self.next_update,
            self.management_info
        ])
        if oid == 'id-sha1':
            digest = hashes.Hash(hashes.SHA1(), backend=default_backend())
            digest.update(data.encode())
            return digest.finalize()
        elif oid == 'id-sha224':
            digest = hashes.Hash(hashes.SHA224(), backend=default_backend())
            digest.update(data.encode())
            return digest.finalize()
        elif oid == 'id-sha256':
            digest = hashes.Hash(hashes.SHA256(), backend=default_backend())
            digest.update(data.encode())
            return digest.finalize()
        elif oid == 'id-sha384':
            digest = hashes.Hash(hashes.SHA384(), backend=default_backend())
            digest.update(data.encode())
            return digest.finalize()
        elif oid == 'id-sha512':
            digest = hashes.Hash(hashes.SHA512(), backend=default_backend())
            digest.update(data.encode())
            return digest.finalize()
        else:
            print('ERROR: Hash algorithm not implemented.')
            sys.exit(1)
