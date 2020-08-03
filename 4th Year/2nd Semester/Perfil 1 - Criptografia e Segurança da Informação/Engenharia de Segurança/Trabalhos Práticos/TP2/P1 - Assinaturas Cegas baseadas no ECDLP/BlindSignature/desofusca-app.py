# coding: latin-1
###############################################################################
# eVotUM - Electronic Voting System
#
# unblindSignature-app.py
#
# Cripto-7.3.1 - Commmad line app to exemplify the usage of unblindSignature
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
Command line app that receives Blind signature, Blind components and prDashComponents
from STDIN and writes the unblinded signature to STDOUT.
"""

import sys
from eVotUM.Cripto import eccblind

# Possibilidade de input.
def printUsage():
    print("Usage:\n")
    print("1. Não fornecendo qualquer dado: python desofusca-app.py")
    print("2. Fornecendo BlindSignature e pRDashComponents: pyton desofusca-app.py -s <BlindSignature> -RDash <pRDashComponents>")

# Parse dos Argumentos
# 1. Se não tem argumentos - primeira opção input.
# 2. Se tem 5 argumentos - segunda opção input.
def parseArgs():
    if (len(sys.argv) == 1):
        main(1)
    elif (len(sys.argv) ==5):
        if sys.argv[1]!='-s':
            printUsage()
        elif sys.argv[3]!='-RDash':
            printUsage()
        else:
            main(2)

# Mostra e Salva os Resultados.
def showAndSaveResults(errorCode, signature):
    print("Output\n")
    
    if (errorCode is None):
        print("Signature: %s" % signature)

        print("Guardando Signature em 'ficheiroRequerente.txt'.")
        f=open('ficheiroRequerente.txt','a+')
        f.write("\nSignature: %s" % signature)
        f.close()

    elif (errorCode == 1):
        print("Error: pRDash components are invalid")
    elif (errorCode == 2):
        print("Error: blind components are invalid")
    elif (errorCode == 3):
        print("Error: invalid blind signature format")

def main(tipoInput):

    if (tipoInput == 1):

        # Abrir Ficheiro Assinante e retirar BlindSignature.
        f = open('ficheiroAssinante.txt','r')
        blindSignature = f.readlines()[2].split(': ')[1]
        f.close()

        # Abrir Ficheiro Requerente e retirar BlindComponents.
        f = open('ficheiroRequerente.txt','r')
        blindComponents = f.readlines()[0].split(': ')[1]
        f.close()

        # Abrir Ficheiro Assinante e retirar pRDashComponents.
        f = open('ficheiroAssinante.txt','r')
        pRDashComponents = f.readlines()[1].split(': ')[1]
        print(pRDashComponents)
        f.close()       

        errorCode, signature = eccblind.unblindSignature(blindSignature, pRDashComponents, blindComponents)
        showAndSaveResults(errorCode, signature)

    else:

        blindSignature = sys.argv[2]

        # Abrir Ficheiro Requerente e retirar BlindComponents.
        f = open('ficheiroRequerente.txt','r')
        blindComponents = f.readlines()[0].split(': ')[1]
        f.close()

        pRDashComponents = sys.argv[4]

        errorCode, signature = eccblind.unblindSignature(blindSignature, pRDashComponents, blindComponents)
        showAndSaveResults(errorCode, signature)

if __name__ == "__main__":
    parseArgs()
