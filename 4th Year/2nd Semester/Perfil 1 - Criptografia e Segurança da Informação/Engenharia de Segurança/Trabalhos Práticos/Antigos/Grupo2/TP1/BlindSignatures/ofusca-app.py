import sys, getopt
from eVotUM.Cripto import eccblind


def printUsage():
    print("Usage: python ofusca-app.py --msg <msg> --RDash <pRDashComponents>")

def showResults(errorCode, result):
    print("Output")
    if (errorCode is None):
        req_file = open("requerente", "w")
        blindComponents, pRComponents, blindM = result
        print("Blind message: %s" % blindM)
        req_file.write("Blind components: %s\n" % blindComponents)
        req_file.write("pRComponents: %s\n" % pRComponents)
        req_file.close()
        print("Components saved in file: requerente")
    elif (errorCode == 1):
        print("Error: pRDash components are invalid")

def main():
    args, _ = getopt.getopt(sys.argv[1:], "", ["msg=", "RDash="])
    args = dict(args)
    if "--msg" in args:
        data = args["--msg"]
        if "--RDash" in args:
            pRDashComponents = args["--RDash"]
            errorCode, result = eccblind.blindData(pRDashComponents, data)
            showResults(errorCode, result)
        else:
            printUsage()
    else:
        printUsage()
    
if __name__ == "__main__":
    main()
