import os

class Cifra:

    def keygen(self):
        return os.urandom(16)

    def enc(self, key, text):
        return text