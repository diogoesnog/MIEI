import sys
import asn1_parser as asn1
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes

class EF_COM:
    def __init__(self, data):
        """
        Parâmetros
        ----------
        data : dict
            dicionário com os nomes das variáveis de instância como chaves
            e respetivo conteúdo como valor
        """
        if isinstance(data, str):
            data = self.load(data)
        self.version = data['version']
        self.tag_list = data['tag_list']

    def save(self, filename):
        """Armazena os dados do DG1 num ficheiro, codificados com ASN1.

        Parâmetros:
        -----------
        filename : str
            nome do ficheiro onde se pretende armazenar os dados
        """
        with open(filename, 'w+') as fp:
            hex_data = asn1.encode(self, './data_groups/configs/ef_com.json')
            fp.write(hex_data)


    def load(self, filename):
        """ Carrega os dados do DG1 de um ficheiro, codificado com ASN1.

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
            data = asn1.decode(fp.read(), './data_groups/configs/ef_com.json')
        return data


    def __str__(self):
        """ Retorna uma string que apresenta os dados do DG1

        Retorna
        -------
        data : str
            string com os dados do DG1
        """
        return 'Version: ' + self.version + '\n' +\
                'DG\'s available: ' + ', '.join(self.tag_list)

    def get_data(self):
        """ Devolve os dados do EF_COM.

        Retorna
        -------
        data : dict
            dicionário com os nomes das variáveis de instância como
            chaves e respetivo conteúdo como valor
        """
        data = {}
        data['version'] = self.version
        data['tag_list'] = self.tag_list
        return data
