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


def printUsage():
    print("Usage: python unblindSignature-app.py")

def readfile():
    f= open("componentes.txt", "r")
    data = f.read().split('\n')[1]
    f.close()
    return data

def parseArgs():
    if (len(sys.argv) > 1):
        if(sys.argv[1] == "-s"):
            blindSignature = raw_input("Blind Signature: ")
            if(sys.argv[2] == "-RDash"):
                pRDashComponents = readfile()
        main(blindSignature,pRDashComponents)
    else:
        printUsage()

def showResults(errorCode, signature):
    print("Output")
    if (errorCode is None):
        print("Signature: %s" % signature)
    elif (errorCode == 1):
        print("Error: pRDash components are invalid")
    elif (errorCode == 2):
        print("Error: blind components are invalid")
    elif (errorCode == 3):
        print("Error: invalid blind signature format")

def main(blindSignature,pRDashComponents):
    f = open("requerente.txt")
    blindComponents = f.read().split('\n')[1]
    f.close()
    errorCode, signature = eccblind.unblindSignature(blindSignature, pRDashComponents, blindComponents)
    showResults(errorCode, signature)


parseArgs()
