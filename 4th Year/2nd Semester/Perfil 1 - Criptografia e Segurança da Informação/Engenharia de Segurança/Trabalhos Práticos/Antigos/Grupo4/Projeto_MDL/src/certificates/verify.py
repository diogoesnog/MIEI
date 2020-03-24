import os
import sys
from OpenSSL import crypto
from cryptography.hazmat.backends import default_backend
from cryptography import x509

def verify_cert(cert_der, cn):
    cert = crypto.load_certificate(crypto.FILETYPE_ASN1, cert_der)
    if cert.get_subject().CN != cn:
        raise crypto.Error()
    with open("CA/certificate.der", "rb") as f:
        ca_cert = crypto.load_certificate(crypto.FILETYPE_ASN1, f.read())
    old_cert_cn = None
    new_cert_cn = cert.get_subject().CN
    verify = False
    # Trusted certificates
    store = crypto.X509Store()
    store.add_cert(ca_cert)
    # Checking
    issuer_cn = cert.get_issuer().CN
    issuer_cert = ca_cert
    if not ca_cert:
        raise crypto.Error
    if ca_cert.get_subject().CN != issuer_cn:
        raise crypto.Error()
    try:
        store_ctx = crypto.X509StoreContext(store, cert)
        store_ctx.verify_certificate()
        verify = True
    except crypto.Error:
        pass

    if not verify:
        raise crypto.Error


with open("./certificate.der", "rb") as f:
    cert_der = f.read()

verify_cert(cert_der, u"mysite1.com")
