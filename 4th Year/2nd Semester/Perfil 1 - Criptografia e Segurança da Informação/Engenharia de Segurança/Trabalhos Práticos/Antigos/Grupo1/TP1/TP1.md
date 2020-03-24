# Trabalho Prático 1 - Resolução

### 1\. Números aleatórios/pseudoaleatórios

Existem 2 "fontes" distintas para a geração de números aleatórios. Estes podem ser gerados através de:
>Fenómenos físicos;

>Algoritmos computacionais.

Nos fenómenos físicos expectáveis de serem aleatórios há a necessidade de, por vezes, serem compensados possíveis desvios no processo de medição. Note-se que a velocidade a que a entropia pode ser colhida a partir de fontes naturais é dependente dos fenómenos físicos subjacentes medidos. Fontes de ocorrência natural de “verdadeira” entropia dizem-se bloqueadas até que exista entropia suficiente para satisfazer o pedido de números aleatórios; como é o caso do dispositivo _/dev/random_ que bloqueia até ser recolhida entropia suficiente do ambiente.

Por outro lado, os algoritmos computacionais produzem longas sequências de resultados aparentemente aleatórios, mas estes são completamente determinados por um valor inicial denominado de semente ou chave. Assim, este tipo de “fonte” de números aleatórios é designada por geradores de números pseudoaleatórios, não podendo ser visto como um “verdadeiro” gerador de números aleatórios, no seu sentido mais puro. No entanto, geradores de números pseudoaleatórios cuidadosamente desenhados e implementados podem ser credenciados para fins criptográficos. Note-se ainda que estes tipos de geradores não dependem normalmente de fontes naturais de entropia; portanto, tratam-se de geradores que não são limitados por taxas de entropia de eventos externos, como é o caso do dispositivo _dev/urandom_, podendo, periodicamente, obter sementes de fontes naturais.

#### Pergunta P1.1

Para a resolução desta pergunta é necessário começar por definir a diferença entre `/dev/random` e `/dev/urandom`.

`/dev/random` e `/dev/urandom` são dispositivos de caracteres especiais presentes no Linux. Estes dispositivos fornecem uma interface para o gerador de números aleatórios do _kernel_, interface esta que reúne entropia através de fenómenos físicos ou de algoritmos computacionais, sendo a partir desta entropia que os números aleatórios são gerados.

Vejamos agora a diferança entre os dispositivos:
> **`/dev/random`** - este apenas retorna bytes aleatórios da entropia existente, sendo que, se não existir entropia suficiente a leitura deste dispositivo é bloqueada até que se reúna a entropia necessária para a geração de uma aleatoriedade de alta qualidade.

> **`/dev/urandom`** - este limita-se apenas a retornar os bytes aleatórios que foram pedidos, no entanto, se não existir entropia suficiente, este recorrerá a algoritmos computacionais que lhe permitem gerar os bytes aleatórios pretendidos a partir de uma determinada semente. Ou seja, neste caso, a operação nunca é interrompida, pelo que os valores são vulneráveis a ataques criptográficos teóricos.

Assim, executando os diferentes comandos no terminal observamos que quando executamos as 3 primeiras instruções o tempo de resposta aumenta consoante o número de _bytes_ que pretendemos gerar. Isto acontece, uma vez que a entropia necessária para gerar 1024 _bytes_ pseudoaleatórios é superior à entropia necessária para se gerarem 32 ou 64 _bytes_ pseudoaleatórios. É também de notar que enquanto não existir entropia suficiente para gerar o _output_, o mesmo fica a aguardar até que seja gerada entropia suficiente para concluir o mesmo.

Relativamente ao comando: `head -c 1024 /dev/urandom | openssl enc -base64`, este permite-nos obter de modo quase instantâneo 1024 _bytes_ pseudoaleatórios, isto deve-se ao facto de quando o `/dev/urandom` não tem entropia suficiente para gerar o _output_ de tamanho pretendido, gera uma _seed_ com a entropia disponível, e a partir da mesma usa um **PRNG** para gerar o restante output.

Na seguinte tabela são apresentados os tempos que cada comando demorou até ser concluído.

| Comando  | Tempo execução |
| ------------- | ------------- |
| head -c 32 /dev/random \| openssl enc -base64 | 0.005s
| head -c 64 /dev/random \| openssl enc -base64 | 0.006s
| head -c 1024 /dev/random \| openssl enc -base64 | 5min 54.626s
| head -c 1024 /dev/urandom \| openssl enc -base64 | 0.006s


#### Pergunta P1.2

A package _haveged_ é um gerador de números pseudoaleatórios, tendo sido criada com o objetivo de colmatar as condições de baixa entropia no dispositivo aleatório do _Linux_. Deste modo, após a instalação da package _haveged_ e executando os comandos propostos, observou-se que a geração de 1024 _bytes_ aleatórios recorrendo aos comandos:

- `head -c 1024 /dev/random | openssl enc -base64`
- `head -c 1024 /dev/urandom | openssl enc -base64`

ocorre em tempos muito semelhantes e, no caso, de `/dev/random` o tempo de execução é bastante mais baixo; isto deve-se ao facto de quando o dispositivo `/dev/random` é executado existir entropia suficiente para a geração dos 1024 bytes aleatórios, entropia essa gerada pela package _haveged_.

| Comando  | Tempo execução |
| ------------- | ------------- |
|head -c 1024 /dev/random \| openssl enc -base64 | 0.007s
|head -c 1024 /dev/urandom \| openssl enc -base64 | 0.006s


#### Pergunta P1.3

**1.**
Analisando o ficheiro *generateSecret-app.py* baseado no módulo _eVotUM.Cripto_ observa-se que este, para gerar os _bytes_ pseudoaleatórios, recorre ao módulo *shamirsecret.py*.

```python
def generateSecret(secretLength):
    """
    This function generates a random string with secretLength characters (ascii_letters and digits).
    Args:
        secretLength (int): number of characters of the string
    Returns:
        Random string with secretLength characters (ascii_letters and digits)
    """
    l = 0
    secret = ""
    while (l < secretLength):
        s = utils.generateRandomData(secretLength - l)
        for c in s:
            if (c in (string.ascii_letters + string.digits) and l < secretLength): # printable character
                l += 1
                secret += c
    return secret
```
Analisando o código relativo ao método _generateSecret()_, observa-se que para gerar a sequência de _bytes_ este inicia um ciclo que será executado enquanto o número de _bytes_ não for atingido. Neste ciclo é criada uma variável _s_ que é construída apartir do módulo _utils_, que faz uso do comando _urandom_. A variável _s_ contém caracteres imprimíveis e caracteres não imprimíveis. Assim, o _output_ do programa _generateSecret-app.py_ contém apenas letras e dígitos, uma vez que os únicos caracteres aceites para a contrução do _output_ têm de pertencer a `string.ascii_letters` ou `string.digits`.


Executando o programa obtém-se o seguinte _output_:

```python
python generateSecret-app.py 1024
JR2uivKXiFjQ4raZfCnRrugxL0CuJYcXAL3hRXWUK4OAebG3ySH1sRHjIpAKFpvHg9cgbNojw4FxOSfhcacFPup7QTMeys0UJR8pUNM3I1JIQghol7UhRg6o7HU0e1fsUcJ98E9FCbKaPGymvinyvIMCyGFwXhSvR0AfMOHCCrKzQ1UtSsP4o3vuw0jg8et1J0W5U7ofCDIw5owzeLFzcaJ7Q0EhP8DoKQyHlGd5P9Uj50W4w5BBZAQU7D31WPAH0EQbYjuRKsqX1KT1ajtvqAYpXob4EYZRfVz6A4d7S6yVk72OZChYS2QVmQjiyjOC27wfFi1YxhkEBe1k8lV5VA0pSBoasMsxwpxMXNgO5NdVvlImZNZyi4U2YncYGUTH4CB6VcF1GjQP5ab4GiAPsTlQBUzwWZzPIj1yAcWIyjCqT3dsN3YCXOBqx6KPSxYmfcQaGDgp5xBDbkyKtATkakT2MwwXStQGkf2sQktEHCJAqNDuy09C2xNBUZFQeElOpFXH0fDCFtIA7saZzCE6DDhThl4t5BNDq3Xmv6ERep7sxAwikabSlNJASepy90qA9b8GUQOnsbYBXdGSu96CRz9S8B876ZzD4fETH3csQc1h7bBxH8sO44iRAWoiAslwuh2OxJoEXgM724DI6OdJjSb19RBbP7D9LfCgLUUslSr2GDG4k9d405TJZtdNBEUqzYXmcYBsGH4PiG5hZrO1bZ6eDYPsWXJ9nG8PWX7qbkBWCyI3f19cRx0oqG85Is2V1olW3y65xQRRqIzhZMIgK2ROG6eo2NoWXLb3WA3ZH9QjfZjZwqfnJ3ZudpswX90SHiRewAJ8oNGqmUDPwNd5gtex2nX71NUDH4fSNirDNZOsDWjDXMYU9btCa6SL7EXju35TChV9EOe0B6m7GOtuv40g186jEWLCyYz8VhgLRBgJXxOVJUwPz8r5I0mUASWaeRbje3xNSXSOhLj33FOR5e8XhZxkUhhuu6X2ita08jwLeOw5FVs2N4OS96wFtrXJ
```

**2.**
Para não limitar o _output_ a letras e dígitos é necessário fazer uma alteração ao código. Por exemplo, basta adicionar `string.punctuation` de maneira a que _c_ possa também ter símbolos de pontuação. Neste caso, o código passa a ser o seguinte:

```python
def generateSecret(secretLength):
    """
    This function generates a random string with secretLength characters (ascii_letters and digits).
    Args:
        secretLength (int): number of characters of the string
    Returns:
        Random string with secretLength characters (ascii_letters and digits)
    """
    l = 0
    secret = ""
    while (l < secretLength):
        s = utils.generateRandomData(secretLength - l)
        for c in s:
            if (c in (string.ascii_letters + string.digits + string.punctuation) and l < secretLength): # printable character
                l += 1
                secret += c
    return secret
```

Executando o programa alterado obtém-se o seguinte _output_:

```python
python generateSecret-app.py 1024
:1`3/nb2;ITKrBIEi*A{4UEl,1u"@xiifR,%NSkEH{WDOVjIpJ![o36{dOe5rx&N[nmKwi=|R^l4=_IO*Fc[}1D1v6[0G)K*zOLb<~Vud-Y2g9x<KA2,rV;O2>#amkBK909rd:C)XXQ"Wljog[xGgll2JUk#`9KXeXC`N*)(QVX`qdAd[3P&RlyH!vmzl?yZf<%oq6",}WhXb%N4p8F/.Eejh2^]B/Oo,j70K'`QPl$Sp{;oU^!eE01JYchGE*tE<Y/>H<2JUy"Jj6^kzZ}"1Ob8qBJp\W-q[f<V?Gslq7*)MbPt7=GmhSD7^Yrr,M|~>H('anH6jUb5"0S<^~A?^EUioB\a5,1"ovG6Q),.tM-M'mnc)gWr!-hml/E%9HXdo<8R-t90)!ej>{fJ])0~q1UjtwUQ]e/n"lXLI5MB802]<1%b@m.G_T7#L\Hn~K+mpi0[NFcw@>;f_*kSI|zJx!ObW}cfqIo_.Y6i[4_|n~YZ^^m?a]/^dR+Q>oKH8G]2~D`U5AqN:W/JGQU(H9Zko?re]cY|$BlveX\+dJFB\=u}JD|=1A|r=W.Ol.F>&M<J^+OYkY<JaV!zt9@=}..PRMF)\p>JIS5LgRG_z]pOVcB6b?A[DVBNPdPF+}e[Kh&j+,&6B6:g)h>A/]oroRR5:I|8N3]Fl{X:')K,O-8PWNR7.4SI\^;BC(f6b]mzX~IA1k6u?/L@6S<4IX1)9{IJBkbNZ05KZpHf|De1j[[cnfEn0t}01%%+>ZKL_0\#6wC/$A8v)|\ii1Y7.<jsEsN)bvn+MCYbgk_83W{mrU,7M?Gg?CJ$Z2x-rEC8Exx&^Ze)MN,!)1_U(_*i".7PD2,&<0];lS8%[yV%^,*SHAF?<To)`&ls5]$kPx!:"QlEt{;!9f[vUtZVkt.[+=}HI"y=kq1mYu({1E(U#eC!=Ed-F-[,VT1cCo~Ht2qq393C3MU+:SS"gg6Ua3?J6.6<^B_^E@2E5FJzu#=?S[-<Q0zA4[)A|c1ILJt!uV/"tDe%#d]F

```

Deste modo podemos ver que o nosso _output_ já não se limita apenas a dígitos e letras.



### 2\. Partilha/Divisão de segredo (Secret Sharing/Splitting)

#### Pergunta P2.1

**A.**
Comecemos por analisar os ficheiros _createSharedSecret-app.py_, _recoverSecretFromComponents-app.py_ e _recoverSecretFromAllComponents-app.py_.

O ficheiro _createSharedSecret-app.py_ é utilizado para fazer a divisão de um determinado segredo por um grupo de entidades, a cada uma das quais é entregue uma parte de um “código” que, quando junto (na totalidade ou em parte), permitem reconstruir o segredo. Este programa aceita como input:

>o número de partes em que quer dividir o segredo;
>o número de partes necessárias para reconstruir o segredo;
>o identificador do segredo;
>a chave privada em base 64.

Percebido o modo como este programa funciona, efetue-se a divisão do segredo *"Agora temos um segredo extremamente confidencial"* em 8 partes, com quorom de 5. Para isso, começou-se por gerar a chave privada, usando o seguinte comando:

```
openssl genrsa -aes128 -out key.pem 1024
```
```
-----BEGIN RSA PRIVATE KEY-----
Proc-Type: 4,ENCRYPTED
DEK-Info: AES-128-CBC,A22B0DBE3DF7602DC4D7BF5C1CA06BE2

Kl4tqhGsD2zyU1SBRTzPN80LRHNiakebnZnpKd/RsZDGY3T6B+DDvFAaaWnD1px0
QzO+nTWU/qsaW5Cs8bj/4gmyhzwnF1qMSN9j+2LBOGa+Vy/nIYtJVsfcU/11oH+X
qWz6SuZM3udGuuzU2TDhnEmkvHywpOP80WXgmCIkjgI2pIP+t8CvZ08HHl5i+4Os
gbFBcpM9SMOAG5gn2J38AZnLpFZxBu6RwYAR9dBOVyMsKlIAUp66QniShO0nNJdg
wBcyYWv1BFre/F35+jWz08WQj/GseJso2BuBgoj3teCYx3R/tRWu+RNlEDNBtWWo
UAiixD1D1KWa/1npUCdD5pEfWY6ZKDY8MYdveVopc+GnSLSExxZhldFwGSCHPx+x
CpjbyqxZiMRfwAahFtEKStSNvzJgiuYK/ncb+fFxfVYRtfLBvlQnwClAQKkXBdIe
vSzaeY8qpv7cZ2ojSvuOySjoMZdOx7iCVqvU6oGkC+Mxcob5AxVThiiVxbP0YqIu
bIp2RI7Z/aqsqWrz8QYsgP3/OHwLqvw37ZDJzRPqnv4XQ8fGqKzkoJUNA5VYZ1iE
oGTQ3vaRVySLBFOS1a/WTBlnHCehuI+CtVa7DP6mkvAPhSXyplGBbJhN2xQsc+K3
WBy0DH0OWVVt2WkI93r/vc0AvBURwW0Apdksahl2lDgVZpMUy6kuZ+eBJtbu/Bp8
OJiqYJILQDeNc3V5m+sqmZRK+n5GuF5c2h35Ry+7I9SVtK3knF3NXoT6PqsPs7ds
CdEkvnWjq/49fyKd4vbEY3NcViWsT3fce5Vhh3TzOI5trZ1r4XTlRaKKfqef11sP
-----END RSA PRIVATE KEY-----
```

Uma vez gerada a chave, procedeu-se à divisão do segredo propriamente dita:

```
user@CSI:~/Aulas/Aula2/ShamirSharing$ python createSharedSecret-app.py 8 5 1 key.pem
Private key passphrase: olaola
Secret: Agora temos um segredo extremamente confidencial
Component: 1
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjEtZDVkYTdjMGQzN2UwNGJlM2ViNTQzMTAwY2ZlNWVlNWJjNzQ5MGZlNjU4NDI4YmQ1M2NiNzkzMWNmMzM5NDNmYTg2ZWMwZDE3ZGZkNTUzYWY3Nzg2NzI4NWUyOWJhZWVmIiwgIjEiLCA1LCA4LCAiNWE1YjhiNWRmNTNhMWIyOGQ3YTRlYmUxNjc4NWRiMjZmMWFmNjZmOWFmNWJmMjIyM2FkZWU2MzQ5YTA0ODAzZSJdfQ.PeZ-hregcV8jPnahkeS__hi_neUk-xelVs8WcrVoQkDx0wXIGcCZtWFbVjbLqeYaKMmm1Xog7qDzmSZWbXDkqi1Po-5yrKuccNE2LHqu0sts5mcMX2JqLsix3D0FD1RUAd_zc82aDg9HoIpVqxDhlyQQRdyC6PrJLT9AK2svddk
Component: 2
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjItMmZhZGI5ZjU5NzMxNGM0NDZhMDFiOGYxOWJkMjJmNjhhMDA3YjA5YzBlNTMyYjQ4YTAwMzRiYzQ4ZDNlMGFhYWY3NTkwMDJiZjE0MTA2MWM5NTdkZjIxZmUyZDY5MzQ0IiwgIjEiLCA1LCA4LCAiNmZkZDFkNGRlN2YxOTc3MGRiYTg5ZTE2ZmFiOTU0OTY1MGY0NWFlMWQyYTFmYTczMWNlMGRlNWYxYzNhODY4NSJdfQ.YHUZMfuK57vgr8Q_O7iztOnVjyLnhS2DM1KElA4mHb1SmCEtMdlSD55GLuL8XBOvMDb75rQSMpPG7p9kp8oqhlysk2de4JSsvpxDgJmOO547pT8P-UOQAV_rj2SwDRrXBsQjvAqXpFGNnJQgjEtCqx_8qga8FJftDnyFL2Pyhls
Component: 3
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjMtYTZiOTRmNTIxOWUxZDZlZTczZDUxMmJjZmE5YjdlMjYxZDdiOWNmNzEzNGQwNzFlYTRkNTQ1ZmNkOTJiMmI5YTVkYmVmYmUyZDY1NTVjZmJhMDMwZjE3OWY0N2RhOWFiIiwgIjEiLCA1LCA4LCAiMDVlNDM2MjE1MTY2N2E5NDFhNGNiMjYwNTljMWFkNjgwZGJjOTZkZmZhYTNlZDhkMzBhZGY3NDRkMmVkNThlYyJdfQ.O6wq9bF6BVeEE4iGG76CoglSjEFNAjeT6ZG3AnBMXV05opP9E-FevayCnT97h21V09LHjV-OI9ZtUMoNHF8IazM7Fuxho-0A3XX17cR49dv3sxSg_mKM4WiHpARiVW-2ovQT9L3mGFVO0A-l5SnCsBT12SeuvC-pxs27MFFEkMc
Component: 4
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtZGI4MGY0Zjc1ZDI2ODlmM2NlZjA2OGExNTQwOWQ3YjgzODZmMDY4NzMxMGJkOTk3NzRmMWU0YmIyN2NiNzY2YTM1YmJjZWU2YWI3Y2QzNDllMDhkMDkwZmYxY2ExMzU3IiwgIjEiLCA1LCA4LCAiYWQyNWRkNWIyYTgyZTBjZjQ4ZTY0YzQzNzg0MjdmNzQ5N2QzYTM2YmM3M2I0ZjExNDM3YmVlMmI5OGNiOGZlNiJdfQ.gXHDyHvFWmXMlghPnFoLdHeFVOzITotnhUqsydY26jGs3-1IlM5yXeNshGJGG18OdZV13PhHCGRhxU_S3R1y1h0CThpeA89pEroobS5G1_dPoGR3fhfUHiV3GcNtj2X902R2EO3AL8kY61OeW4rMVlko4FxjjtXxG8-m22DG-00
Component: 5
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjUtYjczM2Y2NjgwMDlhNDAxMDdkM2IwNzUxNTY0MzliZGFiNDllMDdmYjZlOWIwZWQ0NjE2NDQ0NDk3Y2Y5MjAzOWQ4ODc1OTA1NmFlOTg3YjQwYjg3NWM5YmZlY2E3YmYxIiwgIjEiLCA1LCA4LCAiYTVjYWY0ZDIxNmM2M2NkOTZhNTE2NzlkNjg5ZDkzMDY0Y2QwMzhjMTE4MjY5NzY3NTJhMDQ3YzYyMTVkOTU1MSJdfQ.EPhHSinkN_XpzgTLl0q57Ty8dMPdgYU7Z1RwANYJQnskcdVgqyow7ubtCD3eO-ty_iKt3TGjGAoHliW2ZTe7ir4ZPqRtETQ158wD4cPtr9og-WU8g8CRuwzPJ7xGZmnncGYr4oTeodZagYnlRCWWQZA0PWasMOzL2G8UQLo6Jgs
Component: 6
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtNmJhZDMxZDRhNjNlMTBhYWJjNjE1ZGYzZjVjZDhjZTEyMGI2YTUyMjEwMzVjNGQ3ZTI3ZTNhNDY4ZjlkYzNhNjdjZjM4YjMwZWM5NTNjOTY0MjFjOWIxNjg5NjMxOGIxIiwgIjEiLCA1LCA4LCAiZjgwOGRlYmMxMzJjNGFhNjMwMWZiYWExNDFjOGE0MGFlMjcwOTU1YTY2OWQyN2I1MjJjYWNlOGFhZDljOTA4OSJdfQ.hk8wcqCB9QpI0en9FYZc6fu3sRCPjzsqOgNQ_i3T9ZNpr79Jm9fK4rWYCEZRXWm13Og199tAMAqjDTXaaZti6ToYZLdNYTTfIgS-DC7WBTtRaHhPJ7e5flrFvP0mffXJ7LsUK1kwn0_9ZfsyfbHSO8Kd_KAAy6Sfwkg8fgZzTNE
Component: 7
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjctNzM3MzE4MWJmMjc5NGZkMzA1ZDRmZTI0NmQ4YWNmYjZkNjU4Y2FlODk3NDZjYjg1OTdkODU1YTVjOWIyNjBjYjM3NmM2NzdlZTY0MTU3ZmMxMTUwZmViNjQ5NGRhODVlIiwgIjEiLCA1LCA4LCAiYzY1NDFlNzRiMzg4NTM4Nzc0YjRiOWMwMWZlMTNmMzU4ZWJlNmM0NTE2MDE5MjdhMTU3ZjBkOGMwOWNkMDY0YyJdfQ.ldvYUcQ9mEhEnaxYfKm-xnmnWgTvIDCAQBkzsC0oWw9tTlKCTU20qS9pSUUl7xMdYXQHkKjEDtF-rGkTvYoLz0vR44uzRSJ9zdjRDOs5l0LoZYx7uQtLTsrKN_Kee4qinGtdiIAuNUoRdFprcEaDSWnsbNE2krxsrRIS9GmQvMw
Component: 8
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtOTFiN2FjY2E4YzE5OGU0NDBlY2M5YmYyM2ViY2ViZGVmYTE2NGY1YmMyNjhhNGEyNDg1MWRlYWY0ODNmNWQ0MGY5ZjgwMTI4ZWI3NmUzYTA3MjMwNGNmMDQwMTk3MjY3IiwgIjEiLCA1LCA4LCAiYmY1N2FlMzNlYjg1ZWY5YWNlY2QzMDQ0MDZkZmE4OGJjZDQ5YWU5YzM3YzljN2I2Y2E5NTM5ZjhkMWFkMWZkYyJdfQ.XyXI85O-DbdF5ID1WiZmnKBB-952wbbm9impvtLsIb2LPPTs49IbMtZcjhsZXdzdXaOBi6pc6pgbjp8zMpaDPRnOgkxU3emzYK_wQl9x2dU_sMn1zBmEZG3A58_ARvDnCWduGATBi8Q7p7u56K0tEanGlfqCa3hnvj72UsgV938
```
Relativamente aos ficheiros _recoverSecretFromComponents-app.py_ e _recoverSecretFromAllComponents-app.py_, estes têm como principal objetivo reconstruir o segredo, no entanto, a sua utilização apresenta algumas diferenças. Com o intuito de perceber em que diferem estes dois programas é necessário executá-los para que, a partir dos _outputs_, seja possível tirar as conclusões pretendidas. Proceda-se então à resolução da alínea _B_.

**B**
Antes de se proceder à execução dos programas acima mencionados, comece-se por construir o certificado associado à chave gerada. Este certificado servirá de auxílio na recuperação do segredo. Assim, para construir o certificado associado à chave privada criada, executou-se o seguinte comando:

```
openssl req -key key.pem -new -x509 -days 365 -out key.cert
```
```
-----BEGIN CERTIFICATE-----
MIICezCCAeSgAwIBAgIJAPWz726Bg47zMA0GCSqGSIb3DQEBCwUAMFUxCzAJBgNV
BAYTAlBUMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBX
aWRnaXRzIFB0eSBMdGQxDjAMBgNVBAMMBUNoYXZlMB4XDTE5MDIxMzE4MjIwMFoX
DTIwMDIxMzE4MjIwMFowVTELMAkGA1UEBhMCUFQxEzARBgNVBAgMClNvbWUtU3Rh
dGUxITAfBgNVBAoMGEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDEOMAwGA1UEAwwF
Q2hhdmUwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAKndWGTZSVMy7A06gAUH
iR52a0k6PpgSfwO+h076PWyVYmjVLpS61LJn2AHaTLvUHX1AGiye4bNpfAQskKz7
l4/h6VIv82HRPsU3tr/BjunRw40KoO14f0n5McgGeGrEYnJMYd428hMlrZiJh713
G4z50cz5M6DWlK9uVm5Z76F7AgMBAAGjUzBRMB0GA1UdDgQWBBSkgvq4Ycc3xSUl
017X4614gQxMrTAfBgNVHSMEGDAWgBSkgvq4Ycc3xSUl017X4614gQxMrTAPBgNV
HRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4GBABkiylGdUi6fxRhhyvmoUY3C
vx3y7Pxe/s5YzcaKYtgPo094tjilKkty/NYR/S8vc9Al6I03OJfJNA2eh8RHMaU0
xujoWMDja1UdyPB9HSbpGJfbvMxMmnwlOVNUYQpQXSLHEfPBJqNoEz3u2ZMQMjmA
rEt+dCBwm2NL8ga8peTS
-----END CERTIFICATE-----
```

Após a criação do certificado já é possível recuperar o segredo, para isso irá recorrer-se à execução dos programas _recoverSecretFromAllComponents-app.py_ e o _recoverSecretFromComponents-app.py_. Deste modo, será também possível compreender a diferença entre cada um deles.

Comece-se por executar o _recoverSecretFromComponents-app.py_.

```
user@CSI:~/Aulas/Aula2/ShamirSharing$ python recoverSecretFromComponents-app.py 5 1 key.cert
Component 1: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtZGI4MGY0Zjc1ZDI2ODlmM2NlZjA2OGExNTQwOWQ3YjgzODZmMDY4NzMxMGJkOTk3NzRmMWU0YmIyN2NiNzY2YTM1YmJjZWU2YWI3Y2QzNDllMDhkMDkwZmYxY2ExMzU3IiwgIjEiLCA1LCA4LCAiYWQyNWRkNWIyYTgyZTBjZjQ4ZTY0YzQzNzg0MjdmNzQ5N2QzYTM2YmM3M2I0ZjExNDM3YmVlMmI5OGNiOGZlNiJdfQ.gXHDyHvFWmXMlghPnFoLdHeFVOzITotnhUqsydY26jGs3-1IlM5yXeNshGJGG18OdZV13PhHCGRhxU_S3R1y1h0CThpeA89pEroobS5G1_dPoGR3fhfUHiV3GcNtj2X902R2EO3AL8kY61OeW4rMVlko4FxjjtXxG8-m22DG-00
Component 2: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjUtYjczM2Y2NjgwMDlhNDAxMDdkM2IwNzUxNTY0MzliZGFiNDllMDdmYjZlOWIwZWQ0NjE2NDQ0NDk3Y2Y5MjAzOWQ4ODc1OTA1NmFlOTg3YjQwYjg3NWM5YmZlY2E3YmYxIiwgIjEiLCA1LCA4LCAiYTVjYWY0ZDIxNmM2M2NkOTZhNTE2NzlkNjg5ZDkzMDY0Y2QwMzhjMTE4MjY5NzY3NTJhMDQ3YzYyMTVkOTU1MSJdfQ.EPhHSinkN_XpzgTLl0q57Ty8dMPdgYU7Z1RwANYJQnskcdVgqyow7ubtCD3eO-ty_iKt3TGjGAoHliW2ZTe7ir4ZPqRtETQ158wD4cPtr9og-WU8g8CRuwzPJ7xGZmnncGYr4oTeodZagYnlRCWWQZA0PWasMOzL2G8UQLo6Jgs
Component 3: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtNmJhZDMxZDRhNjNlMTBhYWJjNjE1ZGYzZjVjZDhjZTEyMGI2YTUyMjEwMzVjNGQ3ZTI3ZTNhNDY4ZjlkYzNhNjdjZjM4YjMwZWM5NTNjOTY0MjFjOWIxNjg5NjMxOGIxIiwgIjEiLCA1LCA4LCAiZjgwOGRlYmMxMzJjNGFhNjMwMWZiYWExNDFjOGE0MGFlMjcwOTU1YTY2OWQyN2I1MjJjYWNlOGFhZDljOTA4OSJdfQ.hk8wcqCB9QpI0en9FYZc6fu3sRCPjzsqOgNQ_i3T9ZNpr79Jm9fK4rWYCEZRXWm13Og199tAMAqjDTXaaZti6ToYZLdNYTTfIgS-DC7WBTtRaHhPJ7e5flrFvP0mffXJ7LsUK1kwn0_9ZfsyfbHSO8Kd_KAAy6Sfwkg8fgZzTNE
Component 4: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjctNzM3MzE4MWJmMjc5NGZkMzA1ZDRmZTI0NmQ4YWNmYjZkNjU4Y2FlODk3NDZjYjg1OTdkODU1YTVjOWIyNjBjYjM3NmM2NzdlZTY0MTU3ZmMxMTUwZmViNjQ5NGRhODVlIiwgIjEiLCA1LCA4LCAiYzY1NDFlNzRiMzg4NTM4Nzc0YjRiOWMwMWZlMTNmMzU4ZWJlNmM0NTE2MDE5MjdhMTU3ZjBkOGMwOWNkMDY0YyJdfQ.ldvYUcQ9mEhEnaxYfKm-xnmnWgTvIDCAQBkzsC0oWw9tTlKCTU20qS9pSUUl7xMdYXQHkKjEDtF-rGkTvYoLz0vR44uzRSJ9zdjRDOs5l0LoZYx7uQtLTsrKN_Kee4qinGtdiIAuNUoRdFprcEaDSWnsbNE2krxsrRIS9GmQvMw
Component 5: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtOTFiN2FjY2E4YzE5OGU0NDBlY2M5YmYyM2ViY2ViZGVmYTE2NGY1YmMyNjhhNGEyNDg1MWRlYWY0ODNmNWQ0MGY5ZjgwMTI4ZWI3NmUzYTA3MjMwNGNmMDQwMTk3MjY3IiwgIjEiLCA1LCA4LCAiYmY1N2FlMzNlYjg1ZWY5YWNlY2QzMDQ0MDZkZmE4OGJjZDQ5YWU5YzM3YzljN2I2Y2E5NTM5ZjhkMWFkMWZkYyJdfQ.XyXI85O-DbdF5ID1WiZmnKBB-952wbbm9impvtLsIb2LPPTs49IbMtZcjhsZXdzdXaOBi6pc6pgbjp8zMpaDPRnOgkxU3emzYK_wQl9x2dU_sMn1zBmEZG3A58_ARvDnCWduGATBi8Q7p7u56K0tEanGlfqCa3hnvj72UsgV938
Recovered secret: Agora temos um segredo extremamente confidencialuser@CSI:~/Aulas/Aula2/ShamirSharing$
```

Execute-se agora o *recoverSecretFromAllComponents-app.py*.

```
user@CSI:~/Aulas/Aula2/ShamirSharing$ python recoverSecretFromAllComponents-app.py 8 1 key.cert
Component 1: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjEtZDVkYTdjMGQzN2UwNGJlM2ViNTQzMTAwY2ZlNWVlNWJjNzQ5MGZlNjU4NDI4YmQ1M2NiNzkzMWNmMzM5NDNmYTg2ZWMwZDE3ZGZkNTUzYWY3Nzg2NzI4NWUyOWJhZWVmIiwgIjEiLCA1LCA4LCAiNWE1YjhiNWRmNTNhMWIyOGQ3YTRlYmUxNjc4NWRiMjZmMWFmNjZmOWFmNWJmMjIyM2FkZWU2MzQ5YTA0ODAzZSJdfQ.PeZ-hregcV8jPnahkeS__hi_neUk-xelVs8WcrVoQkDx0wXIGcCZtWFbVjbLqeYaKMmm1Xog7qDzmSZWbXDkqi1Po-5yrKuccNE2LHqu0sts5mcMX2JqLsix3D0FD1RUAd_zc82aDg9HoIpVqxDhlyQQRdyC6PrJLT9AK2svddk
Component 2: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjItMmZhZGI5ZjU5NzMxNGM0NDZhMDFiOGYxOWJkMjJmNjhhMDA3YjA5YzBlNTMyYjQ4YTAwMzRiYzQ4ZDNlMGFhYWY3NTkwMDJiZjE0MTA2MWM5NTdkZjIxZmUyZDY5MzQ0IiwgIjEiLCA1LCA4LCAiNmZkZDFkNGRlN2YxOTc3MGRiYTg5ZTE2ZmFiOTU0OTY1MGY0NWFlMWQyYTFmYTczMWNlMGRlNWYxYzNhODY4NSJdfQ.YHUZMfuK57vgr8Q_O7iztOnVjyLnhS2DM1KElA4mHb1SmCEtMdlSD55GLuL8XBOvMDb75rQSMpPG7p9kp8oqhlysk2de4JSsvpxDgJmOO547pT8P-UOQAV_rj2SwDRrXBsQjvAqXpFGNnJQgjEtCqx_8qga8FJftDnyFL2Pyhls
Component 3: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjMtYTZiOTRmNTIxOWUxZDZlZTczZDUxMmJjZmE5YjdlMjYxZDdiOWNmNzEzNGQwNzFlYTRkNTQ1ZmNkOTJiMmI5YTVkYmVmYmUyZDY1NTVjZmJhMDMwZjE3OWY0N2RhOWFiIiwgIjEiLCA1LCA4LCAiMDVlNDM2MjE1MTY2N2E5NDFhNGNiMjYwNTljMWFkNjgwZGJjOTZkZmZhYTNlZDhkMzBhZGY3NDRkMmVkNThlYyJdfQ.O6wq9bF6BVeEE4iGG76CoglSjEFNAjeT6ZG3AnBMXV05opP9E-FevayCnT97h21V09LHjV-OI9ZtUMoNHF8IazM7Fuxho-0A3XX17cR49dv3sxSg_mKM4WiHpARiVW-2ovQT9L3mGFVO0A-l5SnCsBT12SeuvC-pxs27MFFEkMc
Component 4: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtZGI4MGY0Zjc1ZDI2ODlmM2NlZjA2OGExNTQwOWQ3YjgzODZmMDY4NzMxMGJkOTk3NzRmMWU0YmIyN2NiNzY2YTM1YmJjZWU2YWI3Y2QzNDllMDhkMDkwZmYxY2ExMzU3IiwgIjEiLCA1LCA4LCAiYWQyNWRkNWIyYTgyZTBjZjQ4ZTY0YzQzNzg0MjdmNzQ5N2QzYTM2YmM3M2I0ZjExNDM3YmVlMmI5OGNiOGZlNiJdfQ.gXHDyHvFWmXMlghPnFoLdHeFVOzITotnhUqsydY26jGs3-1IlM5yXeNshGJGG18OdZV13PhHCGRhxU_S3R1y1h0CThpeA89pEroobS5G1_dPoGR3fhfUHiV3GcNtj2X902R2EO3AL8kY61OeW4rMVlko4FxjjtXxG8-m22DG-00
Component 5: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjUtYjczM2Y2NjgwMDlhNDAxMDdkM2IwNzUxNTY0MzliZGFiNDllMDdmYjZlOWIwZWQ0NjE2NDQ0NDk3Y2Y5MjAzOWQ4ODc1OTA1NmFlOTg3YjQwYjg3NWM5YmZlY2E3YmYxIiwgIjEiLCA1LCA4LCAiYTVjYWY0ZDIxNmM2M2NkOTZhNTE2NzlkNjg5ZDkzMDY0Y2QwMzhjMTE4MjY5NzY3NTJhMDQ3YzYyMTVkOTU1MSJdfQ.EPhHSinkN_XpzgTLl0q57Ty8dMPdgYU7Z1RwANYJQnskcdVgqyow7ubtCD3eO-ty_iKt3TGjGAoHliW2ZTe7ir4ZPqRtETQ158wD4cPtr9og-WU8g8CRuwzPJ7xGZmnncGYr4oTeodZagYnlRCWWQZA0PWasMOzL2G8UQLo6Jgs
Component 6: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtNmJhZDMxZDRhNjNlMTBhYWJjNjE1ZGYzZjVjZDhjZTEyMGI2YTUyMjEwMzVjNGQ3ZTI3ZTNhNDY4ZjlkYzNhNjdjZjM4YjMwZWM5NTNjOTY0MjFjOWIxNjg5NjMxOGIxIiwgIjEiLCA1LCA4LCAiZjgwOGRlYmMxMzJjNGFhNjMwMWZiYWExNDFjOGE0MGFlMjcwOTU1YTY2OWQyN2I1MjJjYWNlOGFhZDljOTA4OSJdfQ.hk8wcqCB9QpI0en9FYZc6fu3sRCPjzsqOgNQ_i3T9ZNpr79Jm9fK4rWYCEZRXWm13Og199tAMAqjDTXaaZti6ToYZLdNYTTfIgS-DC7WBTtRaHhPJ7e5flrFvP0mffXJ7LsUK1kwn0_9ZfsyfbHSO8Kd_KAAy6Sfwkg8fgZzTNE
Component 7: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjctNzM3MzE4MWJmMjc5NGZkMzA1ZDRmZTI0NmQ4YWNmYjZkNjU4Y2FlODk3NDZjYjg1OTdkODU1YTVjOWIyNjBjYjM3NmM2NzdlZTY0MTU3ZmMxMTUwZmViNjQ5NGRhODVlIiwgIjEiLCA1LCA4LCAiYzY1NDFlNzRiMzg4NTM4Nzc0YjRiOWMwMWZlMTNmMzU4ZWJlNmM0NTE2MDE5MjdhMTU3ZjBkOGMwOWNkMDY0YyJdfQ.ldvYUcQ9mEhEnaxYfKm-xnmnWgTvIDCAQBkzsC0oWw9tTlKCTU20qS9pSUUl7xMdYXQHkKjEDtF-rGkTvYoLz0vR44uzRSJ9zdjRDOs5l0LoZYx7uQtLTsrKN_Kee4qinGtdiIAuNUoRdFprcEaDSWnsbNE2krxsrRIS9GmQvMw
Component 8: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtOTFiN2FjY2E4YzE5OGU0NDBlY2M5YmYyM2ViY2ViZGVmYTE2NGY1YmMyNjhhNGEyNDg1MWRlYWY0ODNmNWQ0MGY5ZjgwMTI4ZWI3NmUzYTA3MjMwNGNmMDQwMTk3MjY3IiwgIjEiLCA1LCA4LCAiYmY1N2FlMzNlYjg1ZWY5YWNlY2QzMDQ0MDZkZmE4OGJjZDQ5YWU5YzM3YzljN2I2Y2E5NTM5ZjhkMWFkMWZkYyJdfQ.XyXI85O-DbdF5ID1WiZmnKBB-952wbbm9impvtLsIb2LPPTs49IbMtZcjhsZXdzdXaOBi6pc6pgbjp8zMpaDPRnOgkxU3emzYK_wQl9x2dU_sMn1zBmEZG3A58_ARvDnCWduGATBi8Q7p7u56K0tEanGlfqCa3hnvj72UsgV938
Recovered secret: Agora temos um segredo extremamente confidencial
```

Com o intuito de perceber melhor a diferença entre os programas acima executados, efetuou-se o seguinte exemplo.

```
user@CSI:~/Aulas/Aula2/ShamirSharing$ python recoverSecretFromAllComponents-app.py 5 1 key.cert
Component 1: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtOTFiN2FjY2E4YzE5OGU0NDBlY2M5YmYyM2ViY2ViZGVmYTE2NGY1YmMyNjhhNGEyNDg1MWRlYWY0ODNmNWQ0MGY5ZjgwMTI4ZWI3NmUzYTA3MjMwNGNmMDQwMTk3MjY3IiwgIjEiLCA1LCA4LCAiYmY1N2FlMzNlYjg1ZWY5YWNlY2QzMDQ0MDZkZmE4OGJjZDQ5YWU5YzM3YzljN2I2Y2E5NTM5ZjhkMWFkMWZkYyJdfQ.XyXI85O-DbdF5ID1WiZmnKBB-952wbbm9impvtLsIb2LPPTs49IbMtZcjhsZXdzdXaOBi6pc6pgbjp8zMpaDPRnOgkxU3emzYK_wQl9x2dU_sMn1zBmEZG3A58_ARvDnCWduGATBi8Q7p7u56K0tEanGlfqCa3hnvj72UsgV938
Component 2: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjctNzM3MzE4MWJmMjc5NGZkMzA1ZDRmZTI0NmQ4YWNmYjZkNjU4Y2FlODk3NDZjYjg1OTdkODU1YTVjOWIyNjBjYjM3NmM2NzdlZTY0MTU3ZmMxMTUwZmViNjQ5NGRhODVlIiwgIjEiLCA1LCA4LCAiYzY1NDFlNzRiMzg4NTM4Nzc0YjRiOWMwMWZlMTNmMzU4ZWJlNmM0NTE2MDE5MjdhMTU3ZjBkOGMwOWNkMDY0YyJdfQ.ldvYUcQ9mEhEnaxYfKm-xnmnWgTvIDCAQBkzsC0oWw9tTlKCTU20qS9pSUUl7xMdYXQHkKjEDtF-rGkTvYoLz0vR44uzRSJ9zdjRDOs5l0LoZYx7uQtLTsrKN_Kee4qinGtdiIAuNUoRdFprcEaDSWnsbNE2krxsrRIS9GmQvMw
Component 3: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtNmJhZDMxZDRhNjNlMTBhYWJjNjE1ZGYzZjVjZDhjZTEyMGI2YTUyMjEwMzVjNGQ3ZTI3ZTNhNDY4ZjlkYzNhNjdjZjM4YjMwZWM5NTNjOTY0MjFjOWIxNjg5NjMxOGIxIiwgIjEiLCA1LCA4LCAiZjgwOGRlYmMxMzJjNGFhNjMwMWZiYWExNDFjOGE0MGFlMjcwOTU1YTY2OWQyN2I1MjJjYWNlOGFhZDljOTA4OSJdfQ.hk8wcqCB9QpI0en9FYZc6fu3sRCPjzsqOgNQ_i3T9ZNpr79Jm9fK4rWYCEZRXWm13Og199tAMAqjDTXaaZti6ToYZLdNYTTfIgS-DC7WBTtRaHhPJ7e5flrFvP0mffXJ7LsUK1kwn0_9ZfsyfbHSO8Kd_KAAy6Sfwkg8fgZzTNE
Component 4: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjUtYjczM2Y2NjgwMDlhNDAxMDdkM2IwNzUxNTY0MzliZGFiNDllMDdmYjZlOWIwZWQ0NjE2NDQ0NDk3Y2Y5MjAzOWQ4ODc1OTA1NmFlOTg3YjQwYjg3NWM5YmZlY2E3YmYxIiwgIjEiLCA1LCA4LCAiYTVjYWY0ZDIxNmM2M2NkOTZhNTE2NzlkNjg5ZDkzMDY0Y2QwMzhjMTE4MjY5NzY3NTJhMDQ3YzYyMTVkOTU1MSJdfQ.EPhHSinkN_XpzgTLl0q57Ty8dMPdgYU7Z1RwANYJQnskcdVgqyow7ubtCD3eO-ty_iKt3TGjGAoHliW2ZTe7ir4ZPqRtETQ158wD4cPtr9og-WU8g8CRuwzPJ7xGZmnncGYr4oTeodZagYnlRCWWQZA0PWasMOzL2G8UQLo6Jgs
Component 5: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtZGI4MGY0Zjc1ZDI2ODlmM2NlZjA2OGExNTQwOWQ3YjgzODZmMDY4NzMxMGJkOTk3NzRmMWU0YmIyN2NiNzY2YTM1YmJjZWU2YWI3Y2QzNDllMDhkMDkwZmYxY2ExMzU3IiwgIjEiLCA1LCA4LCAiYWQyNWRkNWIyYTgyZTBjZjQ4ZTY0YzQzNzg0MjdmNzQ5N2QzYTM2YmM3M2I0ZjExNDM3YmVlMmI5OGNiOGZlNiJdfQ.gXHDyHvFWmXMlghPnFoLdHeFVOzITotnhUqsydY26jGs3-1IlM5yXeNshGJGG18OdZV13PhHCGRhxU_S3R1y1h0CThpeA89pEroobS5G1_dPoGR3fhfUHiV3GcNtj2X902R2EO3AL8kY61OeW4rMVlko4FxjjtXxG8-m22DG-00
Error: Invalid number of components
```

Este exemplo permite concluir que o programa *recoverSecretFromAllComponents-app.py* para recuperar o segredo necessita que se junte o número de partes pelo qual o segredo foi dividido, não sendo possível recuperar o segredo se apenas se juntarem as partes relativas ao quorum.

Assim, após a execução e análise dos programas *recoverSecretFromComponents-app.py* e *recoverSecretFromAllComponents-app.py* é então possível indicar qual a diferença entre ambos. Enquanto o programa *recoverSecretFromComponents-app.py* para reconstruir o segredo necessita, pelo menos, da quantidade definida como sendo o *quorum*, o programa *recoverSecretFromAllComponents-app.py* para reconstruir o segredo necessita de todas as partes, ou seja, mesmo o _quorum_ sendo de 5 se der apenas 5 chaves distintas o segredo não será recuperado.

Tendo em conta a diferença existente é então importante referir em que situações poderá ser necessário utilizar *recoverSecretFromAllComponents-app.py* em vez de *recoverSecretFromComponents-app.py*. Uma vez que os esquemas de partilha/divisão de segredo permitem alcançar altos níveis de confidencialidade e confiabilidade, de acordo com as necessidades do segredo em causa, a utilização do programa *recoverSecretFromAllComponents-app.py* em vez de *recoverSecretFromComponents-app.py* prevalece-rá quando se pretender uma confidencialidade e confiabilidade quase absoluta, uma vez que, neste caso, é necessário a junção de todas as partes para reconstruir o segredo.

Vejamos, de seguida, um exemplo prático de quando se recorre a um ou a outro programa:

**Cenário**

> Pense-se nas transferências efetuadas nos bancos em que a direção é composta por 8 elementos:
```python
def valor_a_transferir(valortransf):
    valor= valor estipulado pelo banco como sendo elevado
    if valortransf<valor:
        return recoverSecretFromComponents-app.py 5 uid chave
    else:
        return recoverSecretFromAllComponents-app.py 8 uid chave
```

Deste modo se a transferência tiver um valor muito elevado será necessário a participação de todos os elementos, caso contrário, apenas a parte estipulada pelo quorum.

### 3\. Authenticated Encryption

#### Pergunta P3.1

**Funções Necessárias:**
- VerificarAnuidade(uid) , retorna True ou False consoante o uid tiver ou não realizado o pagamento da anuidade do serviço
- Data(), retorna a data atual no formato ano.mes.dia
- GerarKey(data,uid), retorna a chave correspondente à data e ao uid inseridos. 

```python
def cifrar(plaintext,etiqueta,uid,passphrase):
    if VerificarAnuidade(uid) == False:
        print('Para utilizar o serviço tem de pagar a anuidade do serviço')
        return -1
    data=Data()
    key=GerarKey(data,uid)
    criptograma_plaintext=AES.encrypt(plaintext,key)
    k=KDF(passphrase)
    mac_plaintext=hmac(k,plaintext)
    mac_etiqueta=hmac(k,etiqueta)
    Criptograma=[etiqueta,criptograma_plaintext,mac_plaintext,mac_etiqueta,data]
    return Criptograma
```

```python
def decifrar(Criptograma,uid,passphrase):
    if VerificarAnuidade(uid) == False:
        print('Para utilizar o serviço tem de pagar a anuidade do serviço')
        return -1
    criptograma_plaintext=Criptograma[1]
    mac_plaintext=Criptograma[2]
    mac_etiqueta=Criptograma[3]
    data=Criptograma[4]
    
    k=KDF(passphrase)
    
    #Autenticação do plaintext
    MAC_Plaintext=hmac(k,plaintext)
    if MAC_Plaintext!=mac_plaintext:
        return erro
        
    #Autenticação da etiqueta
    MAC_Etiqueta=hmac(k,plaintext)
    if MAC_Etiqueta!=mac_etiqueta:
        return erro
        
    #Decifrar
    key=GerarKey(data,uid)
    plaintext=AES.decrypt(criptograma_plaintext,key)
    return plaintext      
```


### 4\. Algoritmos e Tamanhos de Chave

#### Pergunta P4.1

Para a resolução desta pergunta foi necessário consultar o site https://webgate.ec.europa.eu/tl-browser/ que disponibiliza a lista de Entidades com serviços qualificados de confiança, de acordo com o Regulamento EU 910/2014 (eIDAS). Assim, com o intuito de identificar os algoritmos e tamanhos de chave utilizados nos certificados das Entidades de Certificação (EC) que emitem certificados digitais qualificados da Austria analisaram-se as EC's *PrimeSign GmbH* e *Swisscom Root CA 4*.

##### PrimeSign GmbH

Começamos pela EC *[PrimeSign GmbH](https://webgate.ec.europa.eu/tl-browser/#/tl/AT/5)* que emite o certificado *[CRYPTAS-PrimeSign Qualified Root CA](https://webgate.ec.europa.eu/tl-browser/#/tl/AT/5/0)*.

Seguindo as instruções dadas na nota 2 obtém-se a seguinte informação do certificado *CRYPTAS-PrimeSign Qualified Root CA*:

```
user@CSI:~$ openssl x509 -in cert.crt -text -noout
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            5e:84:57:be:ad:2d:61:d0:43:7f:6c:3b:d0:f0:8a:2f:90:67:1d:2c
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = AT, O = PrimeSign GmbH, CN = CRYPTAS-PrimeSign Qualified Root CA
        Validity
            Not Before: Jun 20 14:51:47 2016 GMT
            Not After : Jun 20 14:51:47 2036 GMT
        Subject: C = AT, O = PrimeSign GmbH, CN = CRYPTAS-PrimeSign Qualified Root CA
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (4096 bit)
                Modulus:
                    00:c1:01:2f:aa:17:80:06:f8:7a:1c:49:b5:c6:34:
                    8a:f5:89:47:ab:6f:b4:59:26:1c:82:f8:12:03:cc:
                    38:0e:70:6f:10:d2:b6:c8:b5:f4:1b:35:e4:ff:64:
                    4a:55:05:06:3d:4b:a8:fd:fc:51:92:67:c0:7e:6e:
                    01:a1:28:0f:22:78:67:24:e6:78:00:94:fb:01:58:
                    a9:d2:fd:2a:71:52:36:fa:a3:d5:09:20:9c:34:d7:
                    8c:9c:d2:5b:b5:96:66:4f:ac:2c:de:87:7a:24:58:
                    9d:0c:88:2b:e2:75:fb:87:8f:c9:d6:6f:78:a7:2e:
                    b7:78:99:41:dd:e8:01:a3:e2:36:91:11:c9:c8:21:
                    52:73:e3:f1:49:4f:75:aa:7c:da:43:fa:ed:c1:f1:
                    20:77:e9:2e:a4:e8:28:c4:00:f1:2f:99:dd:bc:ab:
                    c5:e8:54:e1:f3:e0:83:46:e2:b9:df:4e:6c:cd:53:
                    77:d2:84:af:7a:71:7e:72:8a:93:0f:2b:80:35:00:
                    e7:59:06:ac:36:42:b6:b0:68:02:4c:c7:85:fb:6b:
                    b3:79:44:61:ab:ec:1c:88:cc:62:d6:24:96:58:c3:
                    05:1f:39:9a:34:43:a4:4a:e2:2a:7c:b5:4c:01:75:
                    7a:18:b9:ba:46:54:c7:17:0b:54:d1:ea:b3:84:79:
                    47:66:3e:69:0e:a5:5e:cc:72:2a:14:87:fe:8e:9c:
                    ce:48:e6:ad:32:25:21:33:ec:b6:73:d0:b0:83:70:
                    5b:24:09:2f:7c:17:98:5b:d1:6e:82:ec:00:67:13:
                    0d:9c:bf:8b:60:3e:4d:25:9c:d6:67:82:12:c2:2e:
                    b1:8e:4e:3c:85:e4:46:8c:01:ef:42:00:6a:49:ef:
                    fd:5d:d5:2c:52:da:c4:e4:e7:61:65:43:c7:c3:13:
                    57:0f:d7:f7:3d:5c:cd:d1:ec:90:94:b8:01:58:17:
                    e5:24:e2:de:47:eb:15:4a:98:f2:e6:ae:75:0d:ac:
                    3d:60:27:73:d9:59:2b:46:02:e0:97:70:71:4f:81:
                    f0:5a:1c:e5:7b:11:3c:5b:04:98:8d:44:8b:3a:ec:
                    a5:5d:a2:14:f4:ca:b3:40:8d:32:10:8a:3c:9f:8b:
                    2b:fe:11:45:cc:cd:36:f2:91:b3:3b:65:f5:29:ec:
                    d2:78:f3:a9:97:3b:13:f4:c1:3c:50:ef:1c:73:cf:
                    c2:c7:a9:bc:04:46:41:58:8b:27:09:3c:3e:ef:a2:
                    e1:d3:77:a2:d0:73:fb:6d:d6:56:1f:59:61:a2:d3:
                    e3:de:21:4d:a2:4a:4a:bc:f9:24:0b:16:a8:4f:f0:
                    46:6d:dc:bb:6e:3c:b2:74:c9:e7:9d:8a:ac:e8:98:
                    f8:fd:7f
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Basic Constraints: critical
                CA:TRUE
            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
            X509v3 Certificate Policies: 
                Policy: 1.2.40.0.39.1.1.1.1.0.0
                  CPS: https://tc.prime-sign.com/cps/

            X509v3 Subject Key Identifier: 
                12:FB:A4:FA:1C:29:AF:9A:1F:9F:24:FA:FC:72:A6:AF:8E:7C:6E:C9
    Signature Algorithm: sha256WithRSAEncryption
         72:4f:ce:6a:e4:a9:d6:65:06:44:4f:f4:10:d1:1e:8d:fd:f4:
         09:93:42:86:f9:f7:4a:27:9d:ab:34:66:da:1c:74:49:48:47:
         b0:13:1b:55:36:98:cd:36:94:fd:77:08:ed:ab:c3:06:49:69:
         6b:65:9e:b4:8b:79:b5:49:f0:10:c0:62:c2:a0:fc:48:6d:45:
         5f:97:48:ec:98:a6:d9:cd:cb:f2:a2:66:a1:49:03:4e:ff:bc:
         c7:dc:c5:0a:da:7c:bf:41:88:c6:8a:ce:b6:f0:62:6e:db:93:
         41:59:66:20:4a:ac:2b:4b:ee:9c:0e:a7:4a:1d:e2:17:b3:68:
         a9:20:cc:40:22:fe:d0:bf:6e:28:99:fc:ec:5e:6b:88:d3:e5:
         a3:ee:2b:a0:a8:0a:7a:74:59:73:d1:80:b6:99:ce:e1:c0:e2:
         05:37:f6:49:71:de:11:1c:d6:9e:b7:30:07:0c:01:08:86:8d:
         31:9e:db:1a:7e:43:97:90:4b:93:09:ce:61:cf:b9:2a:80:68:
         d9:0d:bb:0b:ff:cd:79:0a:59:ee:43:0a:ad:dc:16:c1:76:10:
         d1:2b:c2:a9:6e:78:63:b0:9b:5a:dd:88:89:64:f8:7c:c2:cf:
         fc:a4:8a:48:2e:80:5d:d2:fe:98:d8:0a:33:18:73:5d:2d:5c:
         6f:9e:f2:4f:a1:af:f0:ed:0f:7f:e1:1e:0a:43:4e:ee:69:9a:
         c0:fa:ba:8d:61:c8:d6:d0:5a:af:92:27:8d:b0:b3:b1:fb:79:
         69:36:57:0d:5b:56:2f:d1:d8:63:1d:3f:ed:23:71:63:89:8d:
         f7:c7:54:de:b4:c8:13:cd:e8:0b:0f:f1:4f:c0:c8:4f:c6:d1:
         6f:f2:6a:55:8a:de:32:06:90:fc:a2:bb:bb:a0:23:e7:65:e3:
         91:68:55:2c:a4:b5:3c:87:79:06:42:61:ce:6e:85:7b:b9:4a:
         f8:44:93:44:48:17:47:ef:3f:60:57:fa:b7:d9:a8:94:1e:40:
         65:d3:8c:25:41:1b:34:6c:f6:07:ae:36:80:a0:a0:c9:11:6a:
         ad:0b:cf:a6:a9:74:8e:84:16:e6:48:6a:63:ed:9b:85:66:49:
         6a:8b:da:da:f5:29:97:62:36:b3:7e:be:01:a1:51:46:14:b7:
         c0:7d:7c:f7:0d:84:73:45:cc:6c:25:3f:c5:ac:ac:5f:e3:c5:
         2a:dc:c2:83:c3:b2:a4:fe:6e:2f:2e:0a:25:fd:e5:5c:92:2a:
         0f:1f:e1:01:a4:eb:23:0e:9e:89:44:21:e7:8c:30:48:94:a3:
         ef:09:51:49:ae:d0:fc:c1:8e:b3:c0:c3:4e:98:8b:14:8b:7c:
         88:ad:9b:4d:80:e7:db:8e
```

Donde se tiram as seguintes informações:


| Algoritmo de Assinatura | Tamanho da Chave Pública |
| ------------- | ------------- |
| Sha256 with RSA encryption | 4096 bits |

Tendo em conta que o certificado é válido até 20 de Junho de 2036 e que a chave pública utilizada é o RSA com 4096 bits e tendo como referência as recomendações apresentadas na aula teórica, conclui-se que este certificado é adequado, uma vez que as recomendações referem que para o certificado ser seguro a chave RSA tem de ter mais de 3000 bits e, para este certificado, a chave pública utilizada apresenta 4096 bits.


##### Swisscom Root CA 4

Acabamos com a EC *[Swisscom Root CA 4](https://webgate.ec.europa.eu/tl-browser/#/tl/AT/6)* cujo certificado emitido nas condições pedidas é para a entidade *[Swisscom Diamant EU CA 4](https://webgate.ec.europa.eu/tl-browser/#/tl/AT/6/0)*.

Este certificado tem a finalidade de garantir identidade de computadores remotos e de proteger alterações feitas aos softwares.

Novamente, seguindo as instruções dadas na nota 2, obtém-se a seguinte informação do certificado:

```
user@CSI:~$ openssl x509 -in cert1.crt -text -noout
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            a1:47:25:33:ba:f7:d0:0f:66:74:d3:e4:7e:f7:77:2e
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = ch, O = Swisscom, OU = Digital Certificate Services, CN = Swisscom Root CA 2
        Validity
            Not Before: May 18 08:44:46 2017 GMT
            Not After : May 18 08:44:46 2027 GMT
        Subject: 2.5.4.97 = VATAT-U64741248, C = AT, O = Swisscom IT Services Finance S.E., OU = Digital Certificate Services, CN = Swisscom Diamant EU CA 4
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:ba:6c:e3:5c:fb:ce:72:9f:cf:b6:18:2c:e2:a1:
                    cd:fe:d4:54:dd:a6:96:8b:e5:5d:71:1b:04:21:67:
                    14:fc:d0:92:af:23:93:8b:d3:0e:8a:c6:04:af:ae:
                    59:4d:52:a2:3a:92:06:20:e8:8f:c0:fe:2f:60:f7:
                    8f:04:9b:5d:8f:35:e5:37:68:ea:37:21:de:db:59:
                    32:2d:2d:45:47:93:bd:61:ae:26:4c:76:85:29:a2:
                    ee:bf:df:2b:21:16:bc:9f:6d:fd:70:87:e1:27:3a:
                    b6:b0:da:90:a1:97:ff:ad:69:3e:97:7b:b6:a4:af:
                    91:27:2a:26:1f:78:30:04:c6:85:e6:c0:16:b6:8e:
                    a3:38:1f:e8:c8:74:17:e7:85:a8:b0:05:c3:76:4f:
                    a3:fa:bb:ef:9e:dd:94:46:b8:9c:ca:19:2b:ad:82:
                    7c:75:cc:db:df:c5:b7:0c:93:f7:15:9c:d0:0b:14:
                    6c:e4:11:d4:1a:ea:40:e3:5f:81:da:b1:c3:88:89:
                    69:ae:fd:27:c4:d6:54:c8:5e:f8:1f:31:46:54:de:
                    77:65:0d:cf:5a:37:82:03:e0:9f:10:fb:7e:e8:0e:
                    a9:c5:2e:72:6f:f2:6f:08:fa:8a:fc:78:65:4b:72:
                    57:9d:46:ac:39:7f:21:86:88:7f:e4:f0:82:46:5c:
                    9e:3b
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Authority Key Identifier: 
                keyid:4D:26:20:22:89:4B:D3:D5:A4:0A:A1:6F:DE:E2:12:81:C5:F1:3C:2E

            Authority Information Access: 
                CA Issuers - URI:http://aia.swissdigicert.ch/sdcs-root2.crt

            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:0
            X509v3 Certificate Policies: 
                Policy: 2.16.756.1.83.100.4.1
                  CPS: http://www.swissdigicert.ch/cps/

            X509v3 CRL Distribution Points: 

                Full Name:
                  URI:http://crl.swissdigicert.ch/sdcs-root2.crl

            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
            qcStatements: 
                0.0......F..0......F..
            X509v3 Subject Key Identifier: 
                8B:01:D7:DE:C7:92:B2:E4:5B:24:9E:B6:8F:49:3A:AF:A9:C6:72:DD
    Signature Algorithm: sha256WithRSAEncryption
         7d:7d:2f:7a:4c:13:88:f9:c5:82:bb:0a:38:8c:a1:7c:6d:e4:
         03:76:af:53:b8:21:87:34:5d:bb:6d:06:d4:17:99:b7:be:da:
         3c:62:e1:03:e3:8f:f0:a2:a2:c5:df:44:d2:a1:48:f9:00:75:
         3a:08:4b:52:71:17:62:5f:85:99:f7:ec:53:a7:cb:38:d8:66:
         13:44:a1:cc:a1:04:c3:4d:ba:f5:3e:ec:62:a2:dd:fa:e5:0b:
         28:bc:d4:2f:46:46:35:0d:d7:95:45:5c:75:eb:ae:9e:21:e9:
         ca:35:ac:08:d7:78:b7:89:ac:6c:3d:d9:e2:57:d5:af:9f:bc:
         0a:10:4f:8e:ef:b2:f5:f0:63:ab:e0:09:c8:17:e6:60:a3:5e:
         e3:dc:81:77:c5:db:bf:7f:a1:2e:23:87:6d:b5:aa:d2:99:2d:
         03:b6:21:15:97:3c:e0:8a:2a:73:58:9a:66:69:74:67:d9:79:
         c4:1f:52:6c:bc:3e:57:73:cc:6d:8d:15:8b:84:43:b5:f8:1f:
         e1:05:4c:1e:b9:2d:ea:b5:b5:74:9d:4a:4e:11:69:16:7f:c9:
         39:83:00:24:8e:b1:39:68:2e:39:d1:10:b4:6a:fb:d1:61:a5:
         ee:58:2e:a8:fd:74:a0:6a:88:8e:57:09:af:ec:2a:c0:73:75:
         ab:af:23:6b:a6:f6:74:5c:b8:54:e8:f6:7b:69:87:4b:1d:04:
         4a:e1:1d:7f:41:23:61:ae:f7:d8:23:91:d4:54:96:83:1c:8f:
         4e:d3:70:19:3f:66:b7:03:ca:59:f0:c2:41:6f:50:83:f3:07:
         81:e9:03:d8:ad:67:81:e8:65:48:92:cc:ac:16:d6:98:09:1f:
         bc:b7:c2:46:0c:16:b7:57:44:65:76:81:98:9f:72:62:08:1b:
         bf:3c:a1:1e:29:22:61:ad:bf:5f:24:9b:c7:da:5f:2c:c8:7a:
         46:23:60:c7:a9:65:73:bd:6b:0f:90:4d:3d:50:b3:53:23:9f:
         b2:68:df:13:7d:8d:aa:2e:e3:0f:46:f9:c4:c0:c8:c8:00:d6:
         30:c7:d5:04:c0:7c:bb:9c:a7:50:a6:07:57:4b:ef:f1:02:db:
         5c:51:8e:05:59:6b:f0:69:b8:c2:60:96:43:e3:6b:6d:09:09:
         42:ea:15:97:76:c3:2f:49:46:99:c2:5f:c4:16:21:99:75:9b:
         0d:41:18:f9:30:2b:e4:59:37:c3:ca:6d:13:2c:9e:d8:0c:5b:
         78:d4:0c:d7:0f:29:67:9d:63:56:09:91:3e:b6:77:54:86:29:
         60:cb:14:bc:b2:f4:9b:b0:cc:ab:fe:8d:d5:f4:6e:93:59:fd:
         26:40:6f:97:81:80:78:0b
```

Uma vez mais, verificámos o seguinte:

| Algoritmo de Assinatura | Tamanho da Ch. Pública |
| ------------- | ------------- |
| Sha256 with RSA encryption | 2048 bits |

Uma vez que o certificado é válido até 18 Maio de 2027 e que a chave pública utilizada é o RSA com 2048 bits, tendo como referência as recomendações apresentadas na aula teórica, conclui-se que este certificado, segundo algumas recomendações é adequado. No entanto, segundo a recomendação BSI (Alemanha) a chave deveria apresentar um tamanho de 3000 bits. 

Ainda assim, pode concluir-se que o certificado analisado é adequado, uma vez que segue a maioria das recomendações apresentadas.

### Referências
<http://www.issihosts.com/haveged/index.html>

<https://myonlineusb.wordpress.com/2011/06/10/what-is-the-difference-between-devrandom-and-devurandom/>
