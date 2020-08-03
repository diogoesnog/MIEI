# coding: latin-1
###############################################################################
# eVotUM - Electronic Voting System
#
# generateBlindData-app.py
#
# Cripto-7.1.1 - Commmad line app to exemplify the usage of blindData
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
Command line app that receives Data and pRDashComponents from STDIN and writes
blindMessage and blindComponents and pRComponents to STDOUT.
"""

import sys
from eVotUM.Cripto import eccblind

# Possibilidade de input.
def printUsage():
    print("Usage:\n")
    print("1. Fornecendo apenas a Mensagem a Assinar: python ofusca-app.py -msg <Mensagem a Assinar>")
    print("2. Fornecendo a Mensagem a Assinar e pRDashComponents: python ofusca-app.py -msg <Mensagem a Assinar> -RDash <pRDashComponents>")

# Parse dos Argumentos.
# 1. Se tem 3 argumentos - primeira opção input.
# 2. Se tem 5 argumentos - segunda opção input.
def parseArgs():
    if (len(sys.argv) < 3):
        printUsage()
    elif (len(sys.argv) == 3):
        if (sys.argv[1] != '-msg'):
            printUsage()
        else:
            main(1)
    elif (len(sys.argv) == 5):
        if (sys.argv[1] != '-msg'):
            printUsage()
        elif (sys.argv[3] != '-RDash'):
            printUsage()
        else:
            main(2)

# Mostra e Salva os Resultados.
def showAndSaveResults(errorCode, result):
    print("Output\n")

    if (errorCode is None):
        blindComponents, pRComponents, blindM = result
        
        print("Blind Message: %s" % blindM)

        print("Guardando BlindComponents e pRComponents em 'ficheiroRequerente.txt'.")
        f=open('ficheiroRequerente.txt','w+')
        f.write("BlindComponents: %s\n" % blindComponents)
        f.write("pRComponents: %s\n" % pRComponents)
        f.write("BlindMessage: %s" % blindM)
        f.close()

    elif (errorCode == 1):
        print("Error: pRDash components are invalid")

def main(tipoInput):
    
    if (tipoInput == 1):
        mensagemAssinar = sys.argv[2]
        
        # Abrir Ficheiro Assinante e retirar pRDashComponents.
        f = open('ficheiroAssinante.txt','r')
        pRDashComponents = f.readlines()[1].split(': ')[1]
        f.close()

        errorCode, result = eccblind.blindData(pRDashComponents, mensagemAssinar)
        showAndSaveResults(errorCode, result)
    
    else:
        mensagemAssinar = sys.argv[2]
        pRDashComponents = sys.argv[4]

        errorCode, result = eccblind.blindData(pRDashComponents, mensagemAssinar)
        showAndSaveResults(errorCode, result)

if __name__ == "__main__":
    parseArgs()
