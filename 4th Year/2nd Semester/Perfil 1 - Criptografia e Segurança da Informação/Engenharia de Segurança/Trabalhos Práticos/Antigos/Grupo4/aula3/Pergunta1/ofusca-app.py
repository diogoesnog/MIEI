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


def printUsage():
    print("Usage: python generateBlindData-app.py")

def readfile():
    f= open("componentes.txt", "r")
    data = f.read().split('\n')[1]
    f.close()
    return data

def parseArgs():
    if (len(sys.argv) > 1):
       if(sys.argv[1] == "-msg"):
                msg = raw_input("Data: ")
                if(sys.argv[3] == "-RDash"):
                    pRDashComponents = readfile()
                ofusca(pRDashComponents,msg)
    else:
        printUsage()

def showResults(errorCode, result):
    print("Output")
    if (errorCode is None):
        blindComponents, pRComponents, blindM = result
        print("Blind message: %s" % blindM)
        f = open("requerente.txt","w")
        f.write(pRComponents + '\n')
        f.write(blindComponents + '\n')
        f.close()
    elif (errorCode == 1):
        print("Error: pRDash components are invalid")

def ofusca(pRDashComponents,msg):
    errorCode, result = eccblind.blindData(pRDashComponents, msg)
    showResults(errorCode, result)


parseArgs()
