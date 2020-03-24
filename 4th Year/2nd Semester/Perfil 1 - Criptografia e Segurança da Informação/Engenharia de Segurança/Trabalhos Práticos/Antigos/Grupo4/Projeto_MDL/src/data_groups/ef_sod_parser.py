from src.data_groups.pyasn1.type.univ import Integer, Sequence, OctetString, SequenceOf
from src.data_groups.pyasn1.type.namedtype import NamedType, NamedTypes
from src.data_groups.pyasn1.type.char import UniversalString
from src.data_groups.pyasn1.codec.der.encoder import encode
from src.data_groups.pyasn1.codec.der.decoder import decode
from src.data_groups.pyasn1.codec.native.decoder import decode as json_decode
from src.data_groups.pyasn1.codec.native.encoder import encode as json_encode

TAG = '77'

class Data(Sequence):
    componentType = NamedTypes(
        NamedType('dataGroupNumber', Integer()),
        NamedType('dataGroupHashValue', OctetString())
    )

class DataGroupHash(SequenceOf):
    componentType = Data()

class SignedData(Sequence):
    componentType = NamedTypes(
        NamedType('digestAlgorithm', UniversalString()),
        NamedType('signatureAlgorithm', UniversalString()),
        NamedType('certificate', OctetString()),
        NamedType('signature', OctetString()),
        NamedType('dataGroupHash', DataGroupHash())
    )

def create_signed_data(data):
    return json_decode(data, asn1Spec=SignedData())

def sod_encode(signed_data):
    global TAG
    return TAG + encode(signed_data).hex()

def sod_decode(hex_signed_data):
    global TAG
    assert hex_signed_data.startswith(TAG), 'ERROR: Unknown or invalid tag.'
    signed_data, rest = decode(bytes.fromhex(hex_signed_data[2:]), asn1Spec=SignedData())
    assert rest == b'', 'ERROR: "rest" not null.'

    return signed_data

def dump_json(signed_data):
    return json_encode(signed_data)
