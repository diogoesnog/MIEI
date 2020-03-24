from mDL import mDL
from getpass import getpass

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class mDL_transaction:
    def __init__(self, data=None):
        """
        Parâmetros
        ----------
        data : dict
            dicionário com os nomes das variáveis de instância como chaves
            e respetivo conteúdo como valor
        """
        password = getpass()
        self.mDL = mDL(password.encode(), data)

    def open(self):
        """ Realiza o processo de abertura do mDL."""
        done = False
        while not done:
            permission = input('Do you want to preselect the data to be shared? [Y/N] ')
            if permission in ('yes', 'y', 'Y'): # Modify permissions
                data_groups_available = self.mDL.get_available_data_groups()
                allowed = self.preselect(data_groups_available)
                allowed_str = [str(num_dg) for num_dg in allowed.keys()]
                if len(allowed_str):
                    print('Allowing data groups: ' + ', '.join(allowed_str) + '.')
                else:
                    print('No data group will be allowed.')
                self.mDL.set_permissions(allowed)
                print(bcolors.OKGREEN + "Permissions updated with success!" + bcolors.ENDC)
                done = True
            elif permission in ('no', 'n', 'N'): # Use default permissions
                print(bcolors.OKBLUE + "Current permissions retained." + bcolors.ENDC)
                done = True
            else:
                print(bcolors.FAIL + 'Invalid answer.' + bcolors.ENDC)

    def preselect(self, data_groups_available):
        """ Permite realizar uma pré-seleção dos DG's que se permite o acesso."""
        allowed = {}
        for tag in data_groups_available:
            num_dg = self.mDL.TAGS[tag]
            done = False
            while not done:
                allow = input(
                    'Do you allow access to data group ' +
                    str(num_dg) + ' (tag: ' + tag + ') ? [Y/N] '
                )
                if allow in ('yes', 'y', 'Y'): # Modify permissions
                    allowed[num_dg] = tag
                    done = True
                elif allow in ('no', 'n', 'N'): # Don't allow additional permissions
                    done = True
                else:
                    print(bcolors.FAIL + 'Invalid answer.' + bcolors.ENDC)
        return allowed

    def request_additional_data(self, data_group_tags):
        """ Permite requerir acesso a DG's adicionais."""
        request = {}
        for tag in data_group_tags:
            num_dg = self.mDL.TAGS[tag]
            request[num_dg] = tag
        request_list = []
        for num_dg, tag in request.items():
            request_list.append(str(num_dg) + ' (tag: ' + tag + ')')
        done = False
        while not done:
            permission = input(
                'Additionally, do you allow data groups\n\t' +
                '\n\t'.join(request_list) +
                '\nto be accessed? [Y/N] ')
            if permission in ('yes', 'y', 'Y'): # Update permissions
                print('Allowing data groups: ' + ', '.join(request_list) + '.')
                self.mDL.add_permissions(request)
                print(bcolors.OKGREEN + "Permissions updated with success!" + bcolors.ENDC)
                done = True
            elif permission in ('no', 'n', 'N'): # Use default permissions
                print(bcolors.OKBLUE + "Current permissions retained." + bcolors.ENDC)
                done = True
            else:
                print(bcolors.FAIL + 'Invalid answer.' + bcolors.ENDC)

    def transfer_data(self, data_group_tags):
        """ Retorna os dados do mDL requeridos."""
        return self.mDL.get_data(data_group_tags) #self.mDL.get_data_hex(data_group_tags)

    def transfer_sod(self):
        return self.mDL.get_sod_data()

    def print_permissions(self):
        print('DG1', self.mDL.ef_groupAccess.is_allowed(1))
        print('DG6', self.mDL.ef_groupAccess.is_allowed(6))
        print('DG10', self.mDL.ef_groupAccess.is_allowed(10))
