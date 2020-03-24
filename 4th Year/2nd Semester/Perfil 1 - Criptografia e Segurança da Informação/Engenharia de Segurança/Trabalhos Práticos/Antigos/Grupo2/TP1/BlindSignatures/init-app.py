import sys, getopt
from eVotUM.Cripto import eccblind

def printUsage():
    print("Usage: python init-app.py --init")

def main():
    args, _ = getopt.getopt(sys.argv[1:], "", ["init"])
    args = dict(args)
    if "--init" in args:
        initComponents, pRDashComponents = eccblind.initSigner()
        sig_file = open("assinante", "w")
        sig_file.write("Init components: %s\n" % initComponents)
        sig_file.write("pRDashComponents: %s\n" % pRDashComponents)
        sig_file.close()
        print("Components saved in file: assinante")
    else:
        try:
            initComponents, pRDashComponents = tuple(open("assinante", "r").readlines())
            pRDashComponents = pRDashComponents.split(' ')[1]
            print("pRDashComponents: %s" % pRDashComponents)
        except:
            printUsage()

if __name__ == "__main__":
    main()
