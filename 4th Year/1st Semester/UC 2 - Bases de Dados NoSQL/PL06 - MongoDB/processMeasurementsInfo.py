import urllib.request, json, time
from pymongo import MongoClient

try:
    clientMongo = MongoClient("mongodb://localhost:27017/")
    print("Conexão à database estabelecida com sucesso.")

except clientMongo.errors.ServerSelectionTimeoutError as err:
    print("Não foi possível conectar à database.")

# Assim também se está a criar a database/collection caso ainda não exista.
database = clientMongo["medicoes"]
collection = database["medicoes"]

# Enquanto a conexão à database existir.
while True:
  
  # Contador para usar no número de ficheiros.
  numeroFicheiro = 1

  while(numeroFicheiro <= 5):
        
    # 1. CARDIAC INFO

    cardiac = "http://nosql.hpeixoto.me/api/sensor/300{}".format(numeroFicheiro)
    
    # Abrir o ficheiro URL em si.
    infoCardiac = urllib.request.urlopen(cardiac)
    # Formatar a informação em JSON para um objeto Python.
    dataCardiac = json.loads(infoCardiac.read())

    print("Inserting Cadiac Data")
    database.medicoes.insert_one(dataCardiac)
    print(dataCardiac)

    # 2. BLOOD INFO

    blood = "http://nosql.hpeixoto.me/api/sensor/400{}".format(numeroFicheiro)
    infoBlood = urllib.request.urlopen(blood)
    dataBlood = json.loads(infoBlood.read())

    print("Inserting Blood Data")
    database.medicoes.insert_one(dataBlood)
    print(dataBlood)
    
    ++numeroFicheiro

  # Fazer um sleep entre cada leitura de todos os ficheiros.
  time.sleep(5)

clientMongo.close()