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
import getopt
from eVotUM.Cripto import eccblind


def printUsage():
    print("Usage: python desofusca-app.py -s <Blind Signature> --RDash <pRDashComponents>")

def parseArgs():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hs:d:", ["help", "sgn=", "RDash="])
    except getopt.GetoptError as err:
        print(err)
        printUsage()
        sys.exit(2)
    blindSignature = None
    pRDashComponents = False
    for o, a in opts:
        if o in ("-h", "--help"):
            printUsage()
            sys.exit()
        elif o in ("-s", "--sgn"):
            blindSignature = a
        elif o in ('-d', '--RDash'):
            pRDashComponents = a
        else:
            print("Error: Unknown option.")
            printUsage()
            sys.exit(2)

    if not blindSignature or not pRDashComponents:
        print("Error: Message and RDash required.")
        printUsage()
        sys.exit(2)

    main(blindSignature, pRDashComponents)

def showResults(errorCode, signature):
    if (errorCode is None):
        print("Signature: %s" % signature)
    elif (errorCode == 1):
        print("Error: pRDash components are invalid")
    elif (errorCode == 2):
        print("Error: blind components are invalid")
    elif (errorCode == 3):
        print("Error: invalid blind signature format")

def main(blindSignature, pRDashComponents):
    with open('componentsRequerente.dat','r') as fp:
        blindComponents = fp.readline()
    errorCode, signature = eccblind.unblindSignature(blindSignature, pRDashComponents, blindComponents)
    showResults(errorCode, signature)

if __name__ == "__main__":
    parseArgs()
