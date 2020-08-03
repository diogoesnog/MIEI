# coding: latin-1
###############################################################################
# eVotUM - Electronic Voting System
#
# initSigner-app.py
#
# Cripto-7.0.2 - Commmad line app to exemplify the usage of initSigner
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
Command line app that writes initComponents and pRDashComponents to STDOUT.
"""

import sys
from eVotUM.Cripto import eccblind

# Possibilidade de input.
def printUsage():
    print("Usage:\n")
    print("1. Devolver R' (pRDashComponents): python init-app.py")
    print("2. Inicializar Componentes (InitComponents e pRDashComponents): python init-app.py -init")

# Parse dos Argumentos.
# 1. Se não tem argumentos - primeira opção input.
# 2. Se tem 2 argumento - segunda opção input.
def parseArgs():
    if (len(sys.argv) > 2):
        printUsage()
    elif (len(sys.argv) == 1):
        main(1)
    elif (len(sys.argv) == 2):
        if(sys.argv[1] != '-init'):
            printUsage()
        else:
            main(2)

def main(tipoInput):
    initComponents, pRDashComponents = eccblind.initSigner()

    if (tipoInput == 1):

        print("Output\n")
        print("pRDashComponents: %s" % pRDashComponents)

    else:

        print("Guardando InitComponents e pRDashComponents em 'ficheiroAssinante.txt'.")
        
        f = open('ficheiroAssinante.txt','w+')
        f.write("InitComponents: %s\n" % initComponents)
        f.write("pRDashComponents: %s" % pRDashComponents)
        f.close()

if __name__ == "__main__":
    parseArgs()