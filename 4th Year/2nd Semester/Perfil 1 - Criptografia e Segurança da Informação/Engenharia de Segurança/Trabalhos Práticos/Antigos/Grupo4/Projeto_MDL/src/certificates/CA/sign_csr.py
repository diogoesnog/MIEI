from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.serialization import load_der_private_key
import datetime
import sys

with open("./key_self_sign.der", "rb") as f:
    key_self_sign = load_der_private_key(f.read(), password=b"passphrase", backend=default_backend())

with open("./certificate.der", "rb") as f:
    ca_cert = x509.load_der_x509_certificate(f.read(), default_backend())

with open("../csr.der", "rb") as f:
    csr = x509.load_der_x509_csr(f.read(), default_backend())

subject = issuer = x509.Name([
    x509.NameAttribute(NameOID.COUNTRY_NAME, u"US"),
    x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, u"California"),
    x509.NameAttribute(NameOID.LOCALITY_NAME, u"San Francisco"),
    x509.NameAttribute(NameOID.ORGANIZATION_NAME, u"My Company"),
    x509.NameAttribute(NameOID.COMMON_NAME, u"mysite.com"),
])

cert = x509.CertificateBuilder().subject_name(
    csr.subject
).issuer_name(
    ca_cert.subject
).public_key(
    csr.public_key()
).serial_number(
    x509.random_serial_number()
).not_valid_before(
    datetime.datetime.utcnow()
).not_valid_after(
    # Our certificate will be valid for 10 days
    datetime.datetime.utcnow() + datetime.timedelta(days=10)
).add_extension(
    x509.SubjectAlternativeName([x509.DNSName(u"localhost")]),
    critical=False,
# Sign our certificate with our private key
).sign(key_self_sign, hashes.SHA256(), default_backend())

# Write our certificate out to disk.
with open("../certificate.der", "wb") as f:
    f.write(cert.public_bytes(serialization.Encoding.DER))
