from __future__ import with_statement

import os
import sys
import errno
import random
import signal
import smtplib



from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from string import Template
from fuse import FUSE, FuseOSError, Operations

class Passthrough(Operations):
    
    def __init__(self, root):
        self.root = root

    # Helpers
    # =======

    def _full_path(self, partial):
        if partial.startswith("/"):
            partial = partial[1:]
        path = os.path.join(self.root, partial)
        return path

    # Filesystem methods
    # ==================

    def access(self, path, mode):
        full_path = self._full_path(path)
        if not os.access(full_path, mode):
            raise FuseOSError(errno.EACCES)

    def chmod(self, path, mode):
        full_path = self._full_path(path)
        return os.chmod(full_path, mode)

    def chown(self, path, uid, gid):
        full_path = self._full_path(path)
        return os.chown(full_path, uid, gid)

    def getattr(self, path, fh=None):
        full_path = self._full_path(path)
        st = os.lstat(full_path)
        return dict((key, getattr(st, key)) for key in ('st_atime', 'st_ctime',
                     'st_gid', 'st_mode', 'st_mtime', 'st_nlink', 'st_size', 'st_uid'))

    def readdir(self, path, fh):
        full_path = self._full_path(path)

        dirents = ['.', '..']
        if os.path.isdir(full_path):
            dirents.extend(os.listdir(full_path))
        for r in dirents:
            yield r

    def readlink(self, path):
        pathname = os.readlink(self._full_path(path))
        if pathname.startswith("/"):
            # Path name is absolute, sanitize it.
            return os.path.relpath(pathname, self.root)
        else:
            return pathname

    def mknod(self, path, mode, dev):
        return os.mknod(self._full_path(path), mode, dev)

    def rmdir(self, path):
        full_path = self._full_path(path)
        return os.rmdir(full_path)

    def mkdir(self, path, mode):
        return os.mkdir(self._full_path(path), mode)

    def statfs(self, path):
        full_path = self._full_path(path)
        stv = os.statvfs(full_path)
        return dict((key, getattr(stv, key)) for key in ('f_bavail', 'f_bfree',
            'f_blocks', 'f_bsize', 'f_favail', 'f_ffree', 'f_files', 'f_flag',
            'f_frsize', 'f_namemax'))

    def unlink(self, path):
        return os.unlink(self._full_path(path))

    def symlink(self, name, target):
        return os.symlink(target, self._full_path(name))

    def rename(self, old, new):
        return os.rename(self._full_path(old), self._full_path(new))

    def link(self, target, name):
        return os.link(self._full_path(name), self._full_path(target))

    def utimens(self, path, times=None):
        return os.utime(self._full_path(path), times)


    # File methods
    # ============
    
    def aviso(self,signum, frame):
        raise IOError("Couldn't open device!")


#função que procura o mail associado ao utilizador na lista de permissões 
    def getMail(self,filename, nome):
        
        with open(filename, 'r') as f:
            for line in f:
                x=line.split('*')
                if(x[0] == nome):
                   return x[1]

#função que transforma para ler em um arquivo de modelo
    def ler_template(self,filename):
        with open(filename, 'r', encoding='utf-8') as template_file:
            conteudo = template_file.read()
        return Template(conteudo)

    

    def open(self, path, flags):
        full_path = self._full_path(path)

    
        #Colocar o nome de utilizador(username)
        print("Insira aqui o seu nome de utilizador:")
        text = input()
        #Buscar o mail associado ao utilizador
        mail = self.getMail('permissoes.txt',text)
        print("Foi enviado um código de confirmação para o e-mail seguinte:" + mail)
       
        
        #geração do código de verificação aleatório
        code = str(random.randint(000000,999999))
        
        
        #criar a mensagem
        mensagem = self.ler_template('message.txt')
        msg = MIMEMultipart()
        message = mensagem.substitute(PERSON_NAME=text, CODE=code)
        msg['Subject'] = "Código de Verificação"
        msg['From'] = 'testeTrabalho3SSI@gmail.com'
        msg['To'] = mail
        msg.attach(MIMEText(message,'plain'))
        
        #criar o servidor e fazer o login
        server = smtplib.SMTP('smtp.gmail.com',587)
        server.ehlo()
        server.starttls()
        server.ehlo()
        server.login('testeTrabalho3SSI@gmail.com','2019.20TesteSSI')
        #print('fez login')
        server.send_message(msg)
        #server.sendmail('testeTrabalho3SSI@gmail.com',mail,msg.tostring())
        #print('mail enviado')
        server.quit()
       

        timeout = 30
        #Temporizador + verificação do código com o código inserido no terminal
        try:
            signal.signal(signal.SIGALRM,self.aviso)
            signal.alarm(timeout)
            print("Insira aqui o código de verificação enviado para o seu e-mail:")
            codigo= input()
            
            if (str(codigo)==code):
                print("Código inserido com sucesso, permissão aceite.")
                signal.alarm(0)
                return os.open(full_path, flags)
            else: 
                print("Código inserido incorretamente, permissão negada.")
                return 0
        except IOError:
           print("\nSessão expirada. O tempo de introdução do código excedeu o tempo limite.\n")
           return 0

    

    def create(self, path, mode, fi=None):
        full_path = self._full_path(path)
        return os.open(full_path, os.O_WRONLY | os.O_CREAT, mode)

    def read(self, path, length, offset, fh):
        os.lseek(fh, offset, os.SEEK_SET)
        return os.read(fh, length)

    def write(self, path, buf, offset, fh):
        os.lseek(fh, offset, os.SEEK_SET)
        return os.write(fh, buf)

    def truncate(self, path, length, fh=None):
        full_path = self._full_path(path)
        with open(full_path, 'r+') as f:
            f.truncate(length)

    def flush(self, path, fh):
        return os.fsync(fh)

    def release(self, path, fh):
        return os.close(fh)

    def fsync(self, path, fdatasync, fh):
        return self.flush(path, fh)


def main(mountpoint, root):
    FUSE(Passthrough(root), mountpoint, nothreads=True, foreground=True)

if __name__ == '__main__':
    main(sys.argv[2], sys.argv[1])
