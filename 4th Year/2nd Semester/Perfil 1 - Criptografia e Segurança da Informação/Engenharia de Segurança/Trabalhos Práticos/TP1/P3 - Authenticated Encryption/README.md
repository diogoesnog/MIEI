# Pergunta 3 - Authenticated Encryption

1. [**Experiência 3.1**](#experiência-31---cifragemdecifragem-de-segredos-usando-authenticated-encryption) - **Cifragem/Decifragem de Segredos usando Authenticated Encryption**
    - Justificação da abordagem usada - *encrypt then MAC*.
    - Desenvolvimento/Explicação do algoritmo de Cifragem e Decifragem do Segredo.
---

## Resolução da Pergunta 3

### Experiência 3.1 - Cifragem/Decifragem de Segredos usando Authenticated Encryption

Perante o cenário descrito e as especificações do serviço que a empresa pretende/ambiciona colocar no mercado, o primeiro passo a adotar é escolher a forma como vai ser feita a implementação da *Authenticated Encryption*.
As abordagens estudadas na Unidade Curricular de **Tecnologia Criptográfica** permitem concluir que o método *encrypt then MAC* se revela uma melhor opção, dado que não associa o *plaintext* ao MAC em si.

<br/>

<p align="center">
    <img src="Images/encrypt then MAC.png">
</p>


<br/>

Assim, a ideia passa por combinar a Cifra com um MAC e aplicar a mesma tanto sobre a **etiqueta** como sobre o **criptograma**, de modo a se tentar obter uma confidencialidade, integridade e autenticidade dos mesmos.

<br/>

**Veja-se um possível exemplo do algoritmo correspondente ao processo de Cifragem e as decisões tomadas:**

```python
def cifrar(segredo, etiqueta, uID):
  
  if verificaAnuidade(uID) == False:
    print("Não foi feito o pagamento da Anuidade.")
    return -1

  # Data e Criação Chave
  data = dataAtual()
  key = criarChave(data)
  
  # Valores Cifrados
  cripto = cifra(segredo)
  label - cifra(etiqueta)
  
  # Valores MAC
  MACCripto = hmac(key, cripto)
  MACLabel = hmac(key, label)
  
  # Criptograma Final
  criptogramaFinal = [data, cripto, label, MACCripto, MACLabel]
  
  return criptogramaFinal
```

- Verificar se o Utilizador com um determinado identificador uID fornecido pagou a anuidade.
- Retirar a data atual no formato "ano.mes.dia" através da função **dataAtual**.
- Aplica-se a operação/algoritmo de cifragem tanto ao segredo como à etiqueta, através da função **cifra** já existente na API.
- Uso da função **hmac** para criar um MAC para ambos.
  - A chave necessária para este processo é calculada através da função **criarChave** que usa por si só a data atual.
- Com tudo isto, cria-se um *array* contendo todos os valores e devolve-se o mesmo.

<br/>

**Veja-se um possível exemplo do algoritmo correspondente ao processo de Decifragem e as decisões tomadas:**

```python
def decifrar(criptograma, uID):
  
  if verificaAnuidade(uID) == False:
    print("Não foi feito o pagamento da Anuidade.")
    return -1

  # Valores do Array
  dataArray = criptograma[0]
  
  criptoArray = criptograma[1]
  labelArray = criptograma[2]
  
  MACCriptoArray = criptograma[3]
  MACLabelArray = criptograma[4]
  
  # Novo cálculo MAC
  key = obtemChave(data)
  MACCripto = hmac(key, criptoArray)
  MACLabel = hmac(key, labelArray)
  
  # Verificação do Segredo e Etiqueta
  if( (MACCripto == MACCriptoArray) and (MACLabel == MACLabelArray) ):
    segredo = decifra(criptoArray, key)
    etiqueta = decifra(labelArray, key)
    
    return (segredo, etiqueta)
  
  return -1
```

- Verificar se o Utilizador com um determinado identificador uID fornecido pagou a anuidade.
- Retiram-se os valores todos do *array* que serão necessários para o processo de decifragem em si.
- Obtém-se a chave através da função **obtemChave**, fazendo o uso da data que estava implícita no criptograma final.
- Recalcula-se o MAC do segredo e da etiqueta.
- Verificam-se os valores recalculados com os obtidos no processo de cifragem.
