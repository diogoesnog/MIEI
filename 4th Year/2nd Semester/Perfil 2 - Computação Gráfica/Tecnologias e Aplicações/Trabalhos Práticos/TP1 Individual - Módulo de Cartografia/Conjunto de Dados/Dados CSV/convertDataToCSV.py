#coding: utf-8

import requests
import stat
import time
import csv
import re
import os

class DataToCSV():

    def getDataJSON(self):
        
        os.system('chmod 755 dataCommands.sh')
        os.system('./dataCommands.sh')
    
    def  JSONtoCSV(self, name):

        fileJSON = 0
        fileCSV = 0
        
        if(name == "reservasUE"):
            fileJSON = open("dadosReservasAereasUE.json", "r")
            fileCSV = open("dadosReservasAereasUE.csv", "w")

        elif(name == "reservasPT"):
            fileJSON = open("dadosReservasAereasPT.json", "r")
            fileCSV = open("dadosReservasAereasPT.csv", "w")
        
        elif(name == "turismoRegiaoPT"):
            fileJSON = open("dadosApoioTurismoRegiaoPT.json", "r")
            fileCSV = open("dadosApoioTurismoRegiaoPT.csv", "w")

        elif(name == "turismoTipologiaPT"):
            fileJSON = open("dadosApoioTurismoTipologiaPT.json", "r")
            fileCSV = open("dadosApoioTurismoTipologiaPT.csv", "w")

        else:
            print("Name Errado\n")

        with fileCSV:
            reader = csv.writer(fileCSV)
            
            if(name == "reservasUE" or name == "reservasPT"):
                reader.writerow(["Data", "Reservas"])
            
            elif(name == "turismoRegiaoPT"):
                reader.writerow(["Região", "Valor Pago"])

            else:
                reader.writerow(["Tipologia", "Valor Pago"])

            for line in fileJSON:
                linesTable = re.findall('C":\[(.*?)\]', line)

            for element in linesTable:
                cleanElement =  element.replace('"', '')
                line = cleanElement.split(',')
                
                if(name == "reservasUE" or name == "reservasPT"):
                     coluna1 = time.strftime('%d-%m-%Y', time.localtime(int(str(line[0])[:-3])))
                
                else:
                    coluna1 = line[0].capitalize()

                coluna2 = line[1]

                reader.writerow([coluna1, coluna2])

        fileJSON.close()
        fileCSV.close()
    
# Run
myDataToCSV = DataToCSV()

myDataToCSV.getDataJSON()

myDataToCSV.JSONtoCSV("reservasUE")
os.remove("dadosReservasAereasUE.json")

myDataToCSV.JSONtoCSV("reservasPT")
os.remove("dadosReservasAereasPT.json")

myDataToCSV.JSONtoCSV("turismoRegiaoPT")
os.remove("dadosApoioTurismoRegiaoPT.json")

myDataToCSV.JSONtoCSV("turismoTipologiaPT")
os.remove("dadosApoioTurismoTipologiaPT.json")
