import sys, getopt
from eVotUM.Cripto import eccblind


def printUsage():
    print("Usage: python desofusca-app.py -s <Blind Signature> --RDash <pRDashComponents>")

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

def main():
    args, _ = getopt.getopt(sys.argv[1:], "s:", ["RDash="])
    args = dict(args)
    if "-s" in args:
        blindSignature = args["-s"]
        if "--RDash" in args:
            pRDashComponents = args["--RDash"]
            print("Input")
            blindComponents = raw_input("Blind components: ")
            errorCode, signature = eccblind.unblindSignature(blindSignature, pRDashComponents, blindComponents)
            showResults(errorCode, signature)
        else:
            printUsage()
    else:
        printUsage()
    
if __name__ == "__main__":
    main()
