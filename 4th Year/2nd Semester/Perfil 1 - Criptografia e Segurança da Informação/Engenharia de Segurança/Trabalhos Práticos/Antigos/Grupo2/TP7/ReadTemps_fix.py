temps = [None]*10
numTemps = 0
infile = open("/tmp/temps.txt","r")           
for line in infile.readlines():         
    for i in line.split():            
        if numTemps < 10:
            temps[numTemps] = float(i)   
            numTemps += 1
        else:
            break
print('Foram lidas ' + str(numTemps) + ' temperaturas.')
