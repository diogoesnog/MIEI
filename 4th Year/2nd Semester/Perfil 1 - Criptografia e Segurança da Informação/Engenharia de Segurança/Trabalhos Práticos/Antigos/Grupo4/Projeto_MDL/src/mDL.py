from data_groups import dg1
from data_groups import dg6
from data_groups import dg10
from data_groups import ef_com
from data_groups import ef_groupAccess
from data_groups import ef_sod

class mDL:
    # Mapeamento entre a tag e o número do DG
    TAGS = {
        '61': 1,
        '75': 6,
        '62': 10
    }

    def __init__(self, password, data=None):
        """
        Parâmetros
        ----------
        data : dict
            dicionário com os nomes das variáveis de instância como chaves
            e respetivo conteúdo como valor
        """
        if not data:
            self.load()
        else:
            self.dg1 = dg1.DG1(data['dg1'])
            self.dg6 = dg6.DG6(data['dg6'])
            self.dg10 = dg10.DG10(data['dg10'])
            self.ef_com = ef_com.EF_COM(data['ef_com'])
            self.ef_groupAccess = ef_groupAccess.EF_GroupAccess(data['ef_groupAccess'])
            self.ef_sod = ef_sod.EF_SOD(data['ef_sod'])
            self.ef_sod.set_digests({
                1: self.dg1,
                6: self.dg6,
                10:self.dg10
            })
            self.ef_sod.set_signature(password)

    def load(self):
        """ Carrega os dados do mDL dos ficheiros respetivos, codificados com ASN1."""
        self.dg1 = dg1.DG1('./data_groups/asn1_hex_data/dg1.txt')
        self.dg6 = dg6.DG6('./data_groups/asn1_hex_data/dg6.txt')
        self.dg10 = dg10.DG10('./data_groups/asn1_hex_data/dg10.txt')
        self.ef_com = ef_com.EF_COM('./data_groups/asn1_hex_data/ef_com.txt')
        self.ef_groupAccess = ef_groupAccess.EF_GroupAccess(
            './data_groups/asn1_hex_data/ef_groupAccess.txt'
        )
        self.ef_sod = ef_sod.EF_SOD('./data_groups/asn1_hex_data/ef_sod.txt')

    def save(self):
        """ Guarda os dados do mDL nos ficheiros respetivos, codificados com ASN1."""
        self.dg1.save('./data_groups/asn1_hex_data/dg1.txt')
        self.dg6.save('./data_groups/asn1_hex_data/dg6.txt')
        self.dg10.save('./data_groups/asn1_hex_data/dg10.txt')
        self.ef_com.save('./data_groups/asn1_hex_data/ef_com.txt')
        self.ef_groupAccess.save('./data_groups/asn1_hex_data/ef_groupAccess.txt')
        self.ef_sod.save('./data_groups/asn1_hex_data/ef_sod.txt')

    def set_permissions(self, allow):
        """ Define quais os DG's que têm permissão para serem acedidos.

        Parâmetros
        ----------
        allow : dict
            dicionário com o número do DG, que se pretende permitir o acesso,
            como chave e respetiva tag como valor
        """
        self.ef_groupAccess.set_permissions(allow)

    def add_permissions(self, allow):
        """ Adiciona novos DG's aos que têm permissão para serem acedidos.

        Parâmetros
        ----------
        allow : dict
            dicionário com o número do DG, que se pretende permitir o acesso,
            como chave e respetiva tag como valor
        """
        self.ef_groupAccess.add_permissions(allow)

    def get_dg(self, num_dg):
        """
        Devolve o DG do mDL que corresponde ao número passado por argumento.

        Parâmetros
        ----------
        num_dg : int
            número de um DG

        Retorna
        -------
        dg : class
            classe do DG presente no mDL
        """
        dg = None
        if num_dg == 1:
            dg = self.dg1
        elif num_dg == 6:
            dg = self.dg6
        elif num_dg == 10:
            dg = self.dg10
        return dg

    def get_data(self, data_group_tags):
        """ Devolve um dicionário com os dados do mDL,
        que se pretendem aceder e que podem ser acedidos.

        Parâmetros
        ----------
        data_groups : list
            lista com o número do DG que se pretende aceder

        Retorna
        -------
        data : dict
            dicionário com os números dos DG's como chaves
            e respetivo conteúdo num dicionário como valor
        """
        data = {}
        for tag in data_group_tags:
            num_dg = self.TAGS[tag]
            if self.ef_groupAccess.is_allowed(num_dg):
                data[num_dg] = self.get_dg(num_dg).get_data()
        return data

    def get_sod_data(self):
        return self.ef_sod.signed_data

    def get_sod_data_hex(self):
        return self.ef_sod.encode()

    def get_data_hex(self, data_group_tags):
        """Devolve os dados do mDL que se pretende aceder
        e que podem ser acedidos, codificados em ASN1.

        Parâmetros
        ----------
        data_groups : list
            lista com o número do DG que se pretende aceder

        Retorna:
        --------
        hex_data : str
            dados do mDL codificados em hexadecimal
        """
        hex_data = ''
        for tag in data_group_tags:
            num_dg = self.TAGS[tag]
            if self.ef_groupAccess.is_allowed(num_dg):
                hex_data += self.get_dg(num_dg).encode()
        return hex_data

    def get_signature(self):
        """ Devolve a assinatura dos dados do mDL.

        Retorna:
        --------
        signature : str
            assinatura dos dados do mDL
        """
        return self.ef_sod.get_signature()

    def get_digests(self):
        """ Devolve os digests dos DG's do mDL.

        Retorna:
        --------
        digests : dict
            dicionário em que a chave é o número do DG e
            o valor é o respetivo digest
        """
        return self.ef_sod.get_digests()

    def get_available_data_groups(self):
        """ Devolve as tags dos DG's presentes no mDL.

        Retorna:
        --------
        tag_list : list
            lista de tags
        """
        return self.ef_com.get_data()['tag_list']
