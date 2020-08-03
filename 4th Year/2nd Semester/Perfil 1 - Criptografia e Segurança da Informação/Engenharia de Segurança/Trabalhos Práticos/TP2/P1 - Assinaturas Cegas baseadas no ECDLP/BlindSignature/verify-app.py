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

# Possibilidade de input.
def printUsage():
    print("Usage:\n")
    print("1. Fornecendo apenas o Certificado e a Mensagem Original a Assinar: python verify-app.py -cert <Certificado> -msg <Mensagem Original a Assinar>")
    print("2. Fornecendo o Certificado, Mensagem, Signature e Ficheiro Requerente: python verify-app.py -cert <Certificado> -msg <Mensagem Original a Assinar> -sDash <Signature> -f <Ficheiro Requerente>")

# Parse dos Argumentos
# 1. Se tem 5 argumentos - primeira opção input.
# 2. Se tem 9 argumentos - segunda opção input.
def parseArgs():
    eccPublicKeyPath = sys.argv[2]

    if (len(sys.argv) < 5):
        printUsage()
    elif (len(sys.argv) == 5):
        if sys.argv[1]!='-cert':
            printUsage()
        elif sys.argv[3]!='-msg':
            printUsage()
        else:
            main(1, eccPublicKeyPath)
    elif (len(sys.argv) == 9):
        if sys.argv[1]!='-cert':
            printUsage()
        elif sys.argv[3]!='-msg':
            printUsage()
        elif sys.argv[5]!='-sDash':
            printUsage()
        elif sys.argv[7]!='-f':
            printUsage()
        else:
            main(2, eccPublicKeyPath)

# Mostra Resultado Final da Validação.
def showResults(errorCode, validSignature):
    print("\nOutput\n")
    
    if (errorCode is None):
        if (validSignature):
            print("Valid Signature")
        else:
            print("Invalid Signature")
    elif (errorCode == 1):
        print("Error: it was not possible to retrieve the public key")
    elif (errorCode == 2):
        print("Error: pR components are invalid")
    elif (errorCode == 3):
        print("Error: blind components are invalid")
    elif (errorCode == 4):
        print("Error: invalid signature format")

def main(tipoInput, eccPublicKeyPath):
    pemPublicKey = utils.readFile(eccPublicKeyPath)
    
    if (tipoInput == 1):
        mensagemAssinar = sys.argv[4]

        # Abrir Ficheiro Requerente e retirar Signature, BlindComponents e pRComponents.
        f = open('ficheiroRequerente.txt','r')
        blindComponents = f.readlines()[0].split(': ')[1]
        f.close()

        f = open('ficheiroRequerente.txt','r')
        pRComponents = f.readlines()[1].split(': ')[1]
        f.close()

        f = open('ficheiroRequerente.txt','r')
        signature = f.readlines()[3].split(': ')[1]
        f.close()
            
        errorCode, validSignature = eccblind.verifySignature(pemPublicKey, signature, blindComponents, pRComponents, mensagemAssinar)
        showResults(errorCode, validSignature)

    else:
        mensagemAssinar = sys.argv[4]

        # Abrir Ficheiro Requerente Fornecido e retirar Signature.
        f = open(sys.argv[6],'r')
        signature = f.readlines()[3].split(': ')[1]
        f.close()

        # Abrir Ficheiro Requerente Fornecido e retirar BlindComponents e pRComponents.
        f = open(sys.argv[6],'r')
        blindComponents = f.readlines()[0].split(': ')[1]
        pRComponents = f.readlines()[1].split(': ')[1]
        f.close()
    
        errorCode, validSignature = eccblind.verifySignature(pemPublicKey, signature, blindComponents, pRComponents, mensagemAssinar)
        showResults(errorCode, validSignature)

if __name__ == "__main__":
    parseArgs()
