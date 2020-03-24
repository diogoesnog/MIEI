# coding: latin-1
###############################################################################
# eVotUM - Electronic Voting System
#
# verifySignature-app.py
#
# Cripto-7.4.1 - Commmad line app to exemplify the usage of verifySignature
#       function (see eccblind.py)
#
# Copyright (c) 2016 Universidade do Minho
# Developed by André Baptista - Devise Futures, Lda. (andre.baptista@devisefutures.com)
# Reviewed by Ricardo Barroso - Devise Futures, Lda. (ricardo.barroso@devisefutures.com)
#
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
###############################################################################
"""
Command line app that receives signer's public key from file and Data, Signature, Blind Components and
prComponents from STDIN and writes a message to STDOUT indicating if the signature is valid..
"""

import sys
from eVotUM.Cripto import eccblind
from eVotUM.Cripto import utils
import getopt

def printUsage():
    print("Usage: python verify-app.py --cert <certificado do assinante> --msg <mensagem original a assinar> --sDash <Signature> -f <ficheiro do requerente>")

def parseArgs():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hc:m:d:f:", ["help", "cert=", "msg=", "sDash=", "file="])
    except getopt.GetoptError as err:
        print(err)
        printUsage()
        sys.exit(2)

    msg = None
    eccPublicKeyPath = None
    sDash = None
    filename = None
    
    for o,a in opts:
        if o in ("-h", "--help"):
            printUsage()
            sys.exit()
        elif o in ("-c", "--cert"):
            eccPublicKeyPath = a
        elif o in ("-m", "--msg"):
            msg = a
        elif o in ("-d", "--sDash"):
            sDash = a
        elif o in ("-f", "--File"):
            filename = a
        else:
            print("Error: Unknown option.")
            printUsage()
            sys.exit(2)
        
    if not msg or not eccPublicKeyPath or not sDash or not filename:
        print("Error: Certificate, message, sDash and filename required.")
        printUsage()
        sys.exit(2)

    main(eccPublicKeyPath, msg, sDash, filename)

def showResults(errorCode, validSignature):
    if (errorCode is None):
        if (validSignature):
            print("Valid signature")
        else:
            print("Invalid signature")
    elif (errorCode == 1):
        print("Error: it was not possible to retrieve the public key")
    elif (errorCode == 2):
        print("Error: pR components are invalid")
    elif (errorCode == 3):
        print("Error: blind components are invalid")
    elif (errorCode == 4):
        print("Error: invalid signature format")

def main(eccPublicKeyPath, data, signature, componentsPath):
    pemPublicKey = utils.readFile(eccPublicKeyPath)
    components = utils.readFile(componentsPath)
    blindComponents, pRComponents = components.split('\n')[:2]
    errorCode, validSignature = eccblind.verifySignature(pemPublicKey, signature, blindComponents, pRComponents, data)
    showResults(errorCode, validSignature)

if __name__ == "__main__":
    parseArgs()
