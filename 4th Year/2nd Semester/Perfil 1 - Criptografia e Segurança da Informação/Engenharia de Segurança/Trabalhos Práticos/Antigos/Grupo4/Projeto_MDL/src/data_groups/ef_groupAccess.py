import asn1_parser as asn1

class EF_GroupAccess:
    def __init__(self, data):
        """
        Parâmetros
        ----------
        data : dict
            dicionário com os nomes das variáveis de instância como chaves
            e respetivo conteúdo como valor
        """
        if isinstance(data, str):
            self.allowed_data_groups = self.load(data)['allowed_data_groups']
        else:
            self.allowed_data_groups = {}
            for dg, tag in data.items():
                self.allowed_data_groups[int(dg)] = tag

    def save(self, filename):
        """Armazena os dados do GroupAccess num ficheiro, codificados com ASN1.
        
        Parâmetros:
        -----------
        filename : str
            nome do ficheiro onde se pretende armazenar os dados
        """
        with open(filename, 'w+') as fp:
            hex_data = asn1.encode(self, './data_groups/configs/ef_groupAccess.json')
            fp.write(hex_data)


    def load(self, filename):
        """ Carrega os dados do GroupAccess de um ficheiro, codificado com ASN1.
        
        Parâmetros
        ----------
        filename : str
            nome do ficheiro a partir do qual se pretende obter os dados
        
        Retorna
        -------
        data : dict
            dicionário com os nomes dos data groups como chaves e uma lista do
            respetivo conteúdo cujo acesso é permitido como valor
        """
        with open(filename, 'r') as fp:
            data = asn1.decode(fp.read(), './data_groups/configs/ef_groupAccess.json')
        return data
    

    def __str__(self):
        """ Retorna uma string que apresenta os dados do GroupAccess

        Retorna
        -------
        data : str
            string com os dados do GroupAccess
        """
        return ' | '.join([ 'DG' + str(dg) + ' (' + tag + ')'
                            for dg, tag in self.allowed_data_groups.items()])

    def set_permissions(self, allowed):
        """ Estabelece os campos que têm autorização para serem lidos.

        Parâmetros
        ----------
        allowed : dict
            dicionário com os números dos data groups como chaves e uma lista das
            tags cujo acesso ao conteúdo é permitido como valor
        """
        self.allowed_data_groups = {}
        for dg, tag in allowed.items():
            self.allowed_data_groups[dg] = tag

    def add_permissions(self, allowed):
        """ Adiciona novos campos que têm autorização para serem lidos.

        Parâmetros
        ----------
        allowed : dict
            dicionário com os números dos data groups como chaves e uma lista das
            tags cujo acesso ao conteúdo é permitido como valor
        """
        for dg, tag in allowed.items():
            self.allowed_data_groups[dg] = tag

    def is_allowed(self, dg):
        """ Obtém indicação se acesso a determinado data group é permitido.

        Parâmetros
        ----------
        dg : int
            identificador do data group

        Retorna
        -------
        result : boolean
            True, se existe permissão para aceder ao data group. False,
            caso contrário.
        """
        return dg in self.allowed_data_groups
