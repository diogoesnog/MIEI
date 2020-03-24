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

def printUsage():
    print("Usage: python verifySignature-app.py public-key.pem")

def parseArgs():
    if (len(sys.argv) != 6):
        printUsage()
    else:
        if(sys.argv[1] == "-cert"):
            eccPublicKeyPath = sys.argv[2]
            if(sys.argv[3] == "-msg"):
                data = raw_input("Original Data: ")
                if(sys.argv[4] == '-sDash'):
                    signature = raw_input("Signature: ")
                    if(sys.argv[5] == "-f"):
                        main(eccPublicKeyPath,data,signature)

def showResults(errorCode, validSignature):
    print("Output")
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

def main(eccPublicKeyPath,data,signature):
    pemPublicKey = utils.readFile(eccPublicKeyPath)
    f = open("requerente.txt", "r")
    pRComponents = f.read().split('\n')[0]
    f.close()
    f1 = open("requerente.txt", "r")
    blindComponents = f1.read().split('\n')[1]
    f1.close()
    errorCode, validSignature = eccblind.verifySignature(pemPublicKey, signature, blindComponents, pRComponents, data)
    showResults(errorCode, validSignature)


parseArgs()
