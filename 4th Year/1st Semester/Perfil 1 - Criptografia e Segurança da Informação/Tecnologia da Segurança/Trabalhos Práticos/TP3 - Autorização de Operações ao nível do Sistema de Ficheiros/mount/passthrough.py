import os
import sys
import stat
import errno
import random
import signal

import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

from fuse import FUSE, FuseOSError, Operations

def handler(signum, frame):
    raise IOError("Couldn't open device!")

def sendEmail(email, code):
   
    msg = MIMEMultipart()

    msg['From'] = "trabalhoTS2020@gmail.com"
    msg['To'] = email
    msg['Subject'] = "TS - FUSE code"

    body = "O código para acesso às funcionalidades pedidas: " + code

    msg.attach(MIMEText(body, 'html'))

    try:
        server = smtplib.SMTP("smtp.gmail.com", 587)

        server.starttls()

        server.login(msg['From'], "&/=4{6(_>33'7(!-")
        
        server.sendmail(msg['From'], email, msg.as_string())
        
        server.close()
        print("Email Sent Successfully")
        return True
    except:
        print ("failed to send mail")
        return False

def verifyToken(token):
    # Verificar Codigo de Validacao.
    print("Introduza o Codigo de Validacao.")
    validationCode = input()
    if (str(token) == validationCode):
        print("Codigo Validado.")
        return True
    else:
        print("Codigo Incorreto.")
        return False

class Passthrough(Operations):

    def __init__(self, root):
        self.root = root
    
    def open(self, path, flags):
        full_path = self._full_path(path)
        
        # Introdução do Identificador do Utilizador a querer aceder.
        print("Introduza o seu Identificador.")
        username = input()

        # Abertura do Ficheiro de Users com permissão para executar o open.
        os.chmod("users.txt", 400)
        with open('users.txt', 'r') as ficheiroUsers:

            for line in ficheiroUsers:
                user = line.split('/')

                if(user[0] == username): 

                    # Tratar de Enviar o SMS.
                    # Strip trata de remover espacos e outros caracteres desnecessarios.
                    tokenToSend = str(random.randint(100000, 999999))
                    e = sendEmail(user[1].strip(), tokenToSend)
                    if e:
                        
                        # Parte de verificacao e possivel timeout.
                        timeout = 30
                        try:
                            signal.signal(signal.SIGALRM, handler)
                            signal.alarm(timeout)
                            v = verifyToken(tokenToSend)
                            signal.alarm(0)
                            if v:
                                os.chmod("users.txt", 000)
                                return os.open(full_path, flags)
                            else: 
                                os.chmod("users.txt", 000)
                                return 0
                        except IOError:
                            os.chmod("users.txt", 000)
                            print("\nExcedeu o tempo limite.\n")
                    else: 
                        os.chmod("users.txt", 000)
                        return 0

    # Helpers
    # =======

    def _full_path(self, partial):
        if partial.startswith("/"):
            partial = partial[1:]
        path = os.path.join(self.root, partial)
        return path

    # Filesystem Methods
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

    # File Methods
    # ============

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
    # colocar o ficheiro das permissões sem se poder ler.
    os.chmod("users.txt", 000)
    FUSE(Passthrough(root), mountpoint, nothreads=True, foreground=True)

if __name__ == '__main__':
    main(sys.argv[2], sys.argv[1])
