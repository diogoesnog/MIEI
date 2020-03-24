from eVotUM.Cripto import utils
import sys, getopt
from eVotUM.Cripto import eccblind

def printUsage():
    print("Usage: python blindSignature-app.py --key <pkey.pem> --bmsg <message>")

def showResults(errorCode, blindSignature):
    print("Output")
    if (errorCode is None):
        print("Blind signature: %s" % blindSignature)
    elif (errorCode == 1):
        print("Error: it was not possible to retrieve the private key")
    elif (errorCode == 2):
        print("Error: init components are invalid")
    elif (errorCode == 3):
        print("Error: invalid blind message format")

def main():
    args, _ = getopt.getopt(sys.argv[1:], "", ["key=", "bmsg="])
    args = dict(args)
    if "--key" in args:
        eccPrivateKeyPath = args["--key"]
        if "--bmsg" in args:
            blindM = args["--bmsg"]
            print(blindM)
            pemKey = utils.readFile(eccPrivateKeyPath)
            print("Input")
            passphrase = raw_input("Passphrase: ")
            initComponents = raw_input("Init components: ")
            errorCode, blindSignature = eccblind.generateBlindSignature(pemKey, passphrase, blindM, initComponents)
            showResults(errorCode, blindSignature)
        else:
            printUsage()
    else:
        printUsage()
    
if __name__ == "__main__":
    main()
