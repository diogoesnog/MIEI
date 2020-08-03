# coding: latin-1
###############################################################################
# eVotUM - Electronic Voting System
#
# generateBlindSignature-app.py
#
# Cripto-7.2.1 - Commmad line app to exemplify the usage of generateBlindSignature
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
Command line app that receives signer's private key from file and Passphrase, Blind message and
initComponents from STDIN and writes Blind signature to STDOUT.
"""

from eVotUM.Cripto import utils
import sys
from eVotUM.Cripto import eccblind

# Possibilidade de input.
def printUsage():
    print("Usage:\n")
    print("1. Fornecendo apenas a Private Key: python  python blindSignature-app.py -key <Private Key>")
    print("2. Fornecendo a Private Key e Blind Message: python blindSignature-app.py -key <Private Key> -bmsg <Blind Message>")

# Parse dos Argumentos.
# 1. Se tem 3 argumentos - primeira opção input.
# 2. Se tem 5 argumentos - segunda opção input.
def parseArgs():
    eccPrivateKeyPath = sys.argv[2]

    if (len(sys.argv) < 3):
        printUsage()
    elif (len(sys.argv) == 3):
        if (sys.argv[1] != '-key'):
            printUsage()
        else:
            main(1, eccPrivateKeyPath)
    elif (len(sys.argv) == 5):
        if (sys.argv[1] != '-key'):
            printUsage()
        elif (sys.argv[3] != '-bmsg'):
            printUsage()        
        else:
            main(2, eccPrivateKeyPath)

# Mostra e Salva os Resultados.
def showAndSaveResults(errorCode, blindSignature):
    print("\nOutput\n")

    if (errorCode is None):
        print("Blind Signature: %s" % blindSignature)

        print("Guardando BlindSignature em 'ficheiroAssinante.txt'.")
        f=open('ficheiroAssinante.txt','a+')
        f.write("\nBlindSignature: %s" % blindSignature)
        f.close()

    elif (errorCode == 1):
        print("Error: it was not possible to retrieve the private key")
    elif (errorCode == 2):
        print("Error: init components are invalid")
    elif (errorCode == 3):
        print("Error: invalid blind message format")

def main(tipoInput, eccPrivateKeyPath):
    pemKey = utils.readFile(eccPrivateKeyPath)

    if (tipoInput == 1):
        print("Input\n")

        passphrase = raw_input("Passphrase: ")
        
        # Abrir Ficheiro Requerente e retirar BlindMessage.
        f = open('ficheiroRequerente.txt','r')
        blindMessage = f.readlines()[2].split(': ')[1]
        f.close()

        # Abrir Ficheiro Assinante e retirar InitComponents.
        f = open('ficheiroAssinante.txt','r')
        initComponents = f.readlines()[0].split(': ')[1]
        f.close()

        errorCode, blindSignature = eccblind.generateBlindSignature(pemKey, passphrase, blindMessage, initComponents)
    
        showAndSaveResults(errorCode, blindSignature)
    
    else: 
        print("Input\n")

        passphrase = raw_input("Passphrase: ")
        blindMessage = sys.argv[4]

        # Abrir Ficheiro Assinante e retirar InitComponents.
        f = open('ficheiroAssinante.txt','r')
        initComponents = f.readlines()[0].split(': ')[1]
        f.close()

        errorCode, blindSignature = eccblind.generateBlindSignature(pemKey, passphrase, blindMessage, initComponents)

        showAndSaveResults(errorCode, blindSignature)

if __name__ == "__main__":
    parseArgs()
