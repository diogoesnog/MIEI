import sys, getopt
from eVotUM.Cripto import eccblind
from eVotUM.Cripto import utils

def printUsage():
    print("Usage: python verify-app.py --cert <certificate.crt> --msg <msg> --sDash <signature> -f <requerente>")

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

def main():
    args, _ = getopt.getopt(sys.argv[1:], "f:", ["cert=", "msg=", "sDash="])
    args = dict(args)
    if "--cert" in args:
        pemPublicKey = utils.readFile(args["--cert"])
        if "--msg" in args:
            data = args["--msg"]
            if "--sDash" in args:
                signature = args["--sDash"]
                if "-f" in args:
                    blindComponents, pRComponents = tuple(open(args["-f"], "r").readlines())
                    blindComponents = blindComponents.split(' ')[2]
                    pRComponents = pRComponents.split(' ')[1]
                    errorCode, validSignature = eccblind.verifySignature(pemPublicKey, signature, blindComponents, pRComponents, data)
                    showResults(errorCode, validSignature)
                else:
                    printUsage()

            else:
                printUsage()
        else:
            printUsage()
    else:
        printUsage()



if __name__ == "__main__":
    main()
