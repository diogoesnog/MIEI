import re # Expressoes Regulares
import string # Strings
import sys

def valida_num(numero):

    #Soma de controlo para NIC e NIF

    listanum = [int(x) for x in str(numero)]

    # computar soma de controlo
    sum = 0
    
    for pos, dig in enumerate(listanum[:-1]):
        sum += (dig * (9 - pos))

    # verificar soma de controlo
    return (sum % 11 and (11 - sum % 11) % 10) == listanum[-1]

def valida_cc(cc):

    # converter número para lista de inteiros e inverter lista
    listanum = [int(x) for x in str(cc)]
    listanum.reverse()

    # verificar tamanho do número
    if 7 > len(cc) or len(cc) > 19:
        return False

    # computar soma de controlo
    sum = 0
    alt = False

    for i in listanum:
        if alt:
            i *= 2
            if i > 9:
                i -= 9
        sum += i
        alt = not alt

    # verificar soma de controlo
    return not (sum % 10)

# -------

# Valor introduzido pelo utilizador

valor = input("Insira o valor que pretende pagar: \n")

if re.match("[0-9]{1,5}(.[0-9][0-9])?", valor):
    print("Valor introduzido corretamente.\n")
else:
    print("Inseriu um valor que não segue as normas de x(..)x.xx\n")
    sys.exit()

data = input("Insira a data de nascimento (AAAA-MM-DD): \n")

if re.match("[1,2][0-9]{3}-[0,1][0-9]-[0-9]{2}", data):
    print("Valor introduzido corretamente.\n")
else:
    print("Inseriu uma data que não segue as normas de (AAAA-MM-DD)\n")
    sys.exit()

nome = input("Insira o seu nome: \n")

if re.match("[a-zA-Z]{2,8}", nome):
    print("Nome introduzido corretamente.\n")
else:
    print("Inseriu um nome errado. Tem de ter pelo menos nome e apelido e no máximo 7 apelidos.\n")
    sys.exit()

nif = input("Insira o seu NIF: \n")

if valida_num(nif):
    print("NIF introduzido corretamente.\n")
else:
    print("Inseriu um NIF errado. Tem de ter 9 algarismos e ser verdadeiro.\n")
    sys.exit()

nic = input("Insira o seu NIC: \n")

if valida_num(nic):
    print("NIC introduzido corretamente.\n")
else:
    print("Inseriu um NIC errado. Tem de ter 8 algarismos + o algarismo de controlo e ser verdadeiro.\n")
    sys.exit()

numCC = input("Insira o seu cartão de crédito: \n")
validade = input("Insira a validade do mesmo (MM/AA): \n")
cvv = input("Introduza o seu CVV/CVC: \n")

verify_validade = re.match("[0,1][0-9]/[1,2][0-9]", validade)
verify_cvv = re.match("[0-9]{3}", cvv)



if verify_validade and verify_cvv and valida_cc(numCC):
    print("Cartão inserido corretamente. \n")
else:
    print("Inseriu um cartão errado. \n")
    sys.exit()