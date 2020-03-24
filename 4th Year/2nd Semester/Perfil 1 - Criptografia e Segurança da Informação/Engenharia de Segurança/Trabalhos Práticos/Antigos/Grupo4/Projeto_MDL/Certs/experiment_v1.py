import sys
import subprocess
import os
import datetime
import uuid
from cryptography import x509
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.x509.oid import NameOID


class CA(object):

    def __init__(self,private_key,name,key_identifier,serial_number):
        self.private_key = private_key
        self.name = name
        self.key_identifier = key_identifier
        self.serial_number = serial_number


def printUsage():
    print("Usage:")
    print("python experiment_v1.py -init OR")
    print("python experiment_v1.py -auth OR")
    print("python experiment_v1.py -qs")


def checkArguments():
    if (len(sys.argv) != 2):
        return -1
    elif(sys.argv[1] == "-init"):
        return 0
    elif(sys.argv[1] == "-auth"):
        return 1
    elif(sys.argv[1] == "-qs"):
        return 2
    else:
        return -1


def createRootCA():
    one_day = datetime.timedelta(1, 0, 0)
    ten_years = datetime.timedelta(3650, 0, 0)
    private_key = rsa.generate_private_key(
        public_exponent = 65537,
        key_size = 512,
        backend = default_backend()
    )
    public_key = private_key.public_key()
    name = x509.Name([
        x509.NameAttribute(NameOID.COUNTRY_NAME, 'PT'),
        x509.NameAttribute(NameOID.COMMON_NAME, 'IA1'),
        x509.NameAttribute(NameOID.ORGANIZATION_NAME, 'Issuing Authority')
    ])

    digest = hashes.Hash(hashes.SHA256(),default_backend())
    digest.update(public_key.public_bytes(
        encoding = serialization.Encoding.PEM,
        format = serialization.PublicFormat.SubjectPublicKeyInfo
    ))
    key_identifier = digest.finalize()

    builder = x509.CertificateBuilder()
    builder = builder.subject_name(name)
    builder = builder.issuer_name(name)
    builder = builder.not_valid_before(datetime.datetime.today() - one_day)
    builder = builder.not_valid_after(datetime.datetime.today() + ten_years)
    serial_number = int(uuid.uuid4())  
    builder = builder.serial_number(serial_number)
    builder = builder.public_key(public_key)
    builder = builder.add_extension(x509.BasicConstraints(ca=True, path_length=None),critical = True)
    builder = builder.add_extension(x509.SubjectKeyIdentifier(key_identifier),critical = False)

    certificate = builder.sign(
        private_key = private_key,
        algorithm = hashes.SHA512(),
        backend = default_backend()
    )

    os.mkdir('IA1')

    with open("IA1/IA1.key", "wb") as f:
        f.write(private_key.private_bytes(
            encoding = serialization.Encoding.PEM,
            format = serialization.PrivateFormat.TraditionalOpenSSL,
            encryption_algorithm = serialization.BestAvailableEncryption(b'ia1')
        ))

    with open("IA1/IA1.crt","wb") as f:
        f.write(certificate.public_bytes(
            encoding = serialization.Encoding.PEM
        ))

    ca = CA(private_key,name,key_identifier,serial_number)
    return ca
    
'''
def createAssignCA(root_ca):
    one_day = datetime.timedelta(1, 0, 0)
    eight_years = datetime.timedelta(2920, 0, 0)

    private_key = ec.generate_private_key(ec.SECP521R1(),default_backend())
    public_key = private_key.public_key()
    name = x509.Name([
        x509.NameAttribute(NameOID.COUNTRY_NAME, 'Certificado'),
        x509.NameAttribute(NameOID.COMMON_NAME, 'IA2'),
        x509.NameAttribute(NameOID.ORGANIZATION_NAME, 'Pt')
    ])

    digest = hashes.Hash(hashes.SHA256(),default_backend())
    digest.update(public_key.public_bytes(
        encoding = serialization.Encoding.PEM,
        format = serialization.PublicFormat.SubjectPublicKeyInfo
    ))
    key_identifier = digest.finalize()

    builder = x509.CertificateBuilder()
    builder = builder.subject_name(name)
    builder = builder.issuer_name(root_ca.name)
    builder = builder.not_valid_before(datetime.datetime.today() - one_day)
    builder = builder.not_valid_after(datetime.datetime.today() + eight_years)
    serial_number = int(uuid.uuid4())
    builder = builder.serial_number(serial_number)
    builder = builder.public_key(public_key)
    builder = builder.add_extension(x509.BasicConstraints(ca=True,path_length=None), critical = True)
    builder = builder.add_extension(x509.AuthorityKeyIdentifier(root_ca.key_identifier,None,None),critical = False)
    builder = builder.add_extension(x509.SubjectKeyIdentifier(key_identifier),critical = False)

    certificate = builder.sign(
        private_key = root_ca.private_key,
        algorithm = hashes.SHA512(),
        backend = default_backend()
    )

    os.mkdir('assign')

    with open('assign/assign.key','wb') as f:
        f.write(private_key.private_bytes(
            encoding = serialization.Encoding.PEM,
            format = serialization.PrivateFormat.TraditionalOpenSSL,
            encryption_algorithm = serialization.BestAvailableEncryption(b'v1_stateCA')
        ))
    
    with open('assign/assign.crt','wb') as f:
        f.write(certificate.public_bytes(
            encoding = serialization.Encoding.PEM
        ))
    
    ca = CA(private_key,name,key_identifier,serial_number)
    return ca
'''

def main():
    createRootCA()

if __name__ == "__main__":
    main()