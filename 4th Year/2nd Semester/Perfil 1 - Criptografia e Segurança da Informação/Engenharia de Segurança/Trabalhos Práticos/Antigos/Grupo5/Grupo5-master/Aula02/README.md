# Trabalho Prático 0 - 11/Fev/2019



## 1. Números aleatórios/pseudoaleatórios



### Pergunta P1.1

Para responder a esta questão, torna-se necessário evidenciar a diferença entre a geração de números pseudoaleatórios com o recurso ao dispositivo `/dev/random` e ao `/dev/urandom`. Estes são ficheiros especiais do sistema *Linux* que têm acesso ao ruído presente no sistema operativo, utilizando a entropia disponível para gerar *bytes* ou uma *seed* pseudoaleatórios, respetivamente.

Por um lado, o dispositivo `/dev/random` requer espera pelo resultado (*bytes*), pois utiliza uma *entropy pool*. Assim, este mecanismo pode bloquear enquanto não for possível gerar dados aleatórios suficientes. Contudo, a realização de chamadas ao sistema operativo permite aumentar a entropia disponível e, consequentemente, possibilitar a geração da quantidade de *bytes* solicitada. Faz sentido utilizar este dispositivo quando são exigidos maiores níveis de qualidade na aleatoriedade.

Por outro lado, o dispositivo `/dev/urandom` não bloqueia devido à reduzida entropia disponível. Este mecanismo retorna valores independentemente de existir entropia suficiente, caso em que, teoricamente, estes são vulneráveis a ataques criptográficos. Neste caso, a entropia apenas é utilizada para gerar uma *seed*, com qualidade superior ou inferior (de acordo com a entropia disponível). De seguida, os *bytes* do resultado são gerados por um *pseudorandom number generator*.

O comando apresentado no início (`openssl rand -base64 1024`) permite gerar *bytes* pseudoaleatórios, após fornecer, uma vez, uma *seed* ao *pseudorandom number generator*, e codifica os mesmos em *base64*. É utilizado o ficheiro `$HOME/.rnd` ou `.rnd` (poderiam ainda considerar-se ficheiros adicionais passados como argumento) para gerar a *seed*.

Os tempos de execução obtidos para cada um dos comandos propostos são apresentados na tabela que se segue:

|                 Comando utilizado                  | Tempo de resolução |
| :------------------------------------------------: | :----------------: |
|            `openssl rand -base64 1024`             |     0.024 seg      |
|  `head -c 32 /dev/random \| openssl enc -base64`   |     0.010 seg      |
|  `head -c 64 /dev/random \| openssl enc -base64`   |     0.011 seg      |
| `head -c 1024 /dev/random \| openssl enc -base64`  |   11 min 23 seg    |
| `head -c 1024 /dev/urandom \| openssl enc -base64` |     0.151 seg      |

Através dos resultados obtidos, verifica-se que na geração de números pseudoaleatórios de tamanhos reduzidos (32 e 64 *bits*) não se evidencia o reduzido de desempenho na utilização do dispositivo `/dev/random`. Contudo, quando se solicita a geração de um número pseudoaleatório de tamanho superior, verifica-se uma grande diferença de desempenho em relação à utilização do `/dev/urandom` (11 minutos e 23 segundos em relação a menos de 1 segundo). Salienta-se ainda um desempenho ligeiramente superior, em relação à utilização do dispositivo `/dev/urandom`, na implementação do *openssl*.



### Pergunta P1.2

O projeto [haveged](http://www.issihosts.com/haveged/index.html) é uma adaptação do algoritmo [HAVEGE](http://www.irisa.fr/caps/projects/hipsor/), que pretende implementar um gerador de números aleatórios imprevisível, através da exploração de modificações dos estados internos e voláteis do *hardware* como fonte de incerteza. Este *daemon* foi criado com o objetivo de remediar condições de baixa entropia nos dispositivos de aleatoriedade *Linux*. Assim, espera-se que a instalação deste tenha um impacto positivo no desempenho dos geradores de números pseudoaleatórios previamente utilizados.

Após a instalação do *daemon* **haveged** e repetição dos comandos indicados na pergunta anterior, obtiveram-se as seguintes medições dos tempos de execução:

|                 Comando utilizado                  | Tempo de resolução |
| :------------------------------------------------: | :----------------: |
|            `openssl rand -base64 1024`             |     0.011 seg      |
|  `head -c 32 /dev/random \| openssl enc -base64`   |     0.010 seg      |
|  `head -c 64 /dev/random \| openssl enc -base64`   |     0.011 seg      |
| `head -c 1024 /dev/random \| openssl enc -base64`  |     0.109 seg      |
| `head -c 1024 /dev/urandom \| openssl enc -base64` |     0.013 seg      |

Conforme esperado, os tempos de execução diminuíram, de forma geral, com especial relevância para o gerador que se baseia no dispositivo `/dev/random`, com o tamanho de 1024 *bits* (passou de 11 minutos e 23 segundos para menos de 1 segundo). Relativamente aos tamanhos inferiores (32 e 64 *bits*), não se verificou melhoria de performance, uma vez que estes comprimentos são demasiado reduzidos para a diferença ser visível.



### Pergunta P1.3

O programa foi executado através do comando `python generateSecret-app.py 1024`, tendo dado origem ao seguinte *output*:

```
npaZnOORSpWsz4KlFbpIE8E5AnzWRX70gU3n8seafJI4ISqYWsV2wCX13eJl2cUvADWhzaGyiTTy8W9hhcwoXLdNgJlshP4Tb89PlnMELxte20M0RcKcy0IS0j376x7Jqf37Td4Jgzs6TnTsacFbv3HRC8j8Ni7K8YbCcCX129QuTD1KGPXVLt1UpWysNtSVgOESRimHtBk2tX7anHwNVA0X3wOVyzR5iUl5jLcMLkG0n0vBFS5BBycliN0G6EYbNlnhnfWBpu4XZdn0iTQok45Ns3tR0JaTLJLsrlGv9tyU38Q4LmtWvoT0yV4x6ipfmH6issoSozontfrm8B4RNWJXSbHgDRsAkaJLou2QTqekWJZzZSe1YkKjPIrNBJnDUuQqCNleydMcakqbiaVD4MbKwLwzZxQ8Egr4qQGnEbtE3M2mf807XfYfLICIl1ZIpGYSgRewduQDYQOumAWs9x1KoNe6fGwamOdjV6spU2cKGPVA3hY7VshKsCA4EVeHrE6hCMITqys38TYeb7xo7AKadodXbOmGtIRSgdHTArCgnOkqwrliEtRhdJgSrHK9HpLwjfXKOucKDLfD9xtsTi2MCoGJKeHlX1T6bov8enfzelHlVMTLd7gVfA3jUcKQWlQnW1eCoQkLD5jMLDXeXuMqzPsv7wPvQU5lcPFrVIdZ07rwCsCwuDK8tmeK06hcTBD31QXnXeRl97KUaxapE58BZPeMhiUoEhfLBo4pZLgH89PsPGAR12MlyUSrKjzd0D8l2jTlA1cN4Ydkyr6KzDnlgXTyvuAh2vNpYXaUVANAF1Rjdd4zgoPDHkgJPanDKEfywCWijrVJHyepjndXWum30Z2Z8kmSlCAWBSQpLX28LHpTtT7jZ9nCR75ATTFO33QBWhV5C1h4qyKKAOnuKMN873SfN4vr0TBbrfF9rxVYKLBqHRrGpr16NQfvgmJ77Pf5cAc0QIc5mv10EhJGlpQwW4mpmHoK9pVDickQzCQbHG9ggPnZr7qBElL3yY33

```

Verifica-se que, de facto, o *output* gerado apenas contém letras e números. Isto deve-se à implementação da função `generateSecret` do módulo `shamirsecret`. Primeiramente, o algoritmo começa por gerar uma sequência de *bytes* pseudoaleatórios com o comprimento em falta no segredo (`s`). De seguida, é avaliado se cada um dos *bytes* é uma letra (`string.ascii_letters`) ou dígito (`string.digits`) e se o comprimento final do segredo ainda não foi atingido, caso em que se concatena o respetivo *byte* ao segredo. Enquanto o comprimento solicitado para o segredo não for atingido, o processo referido anteriormente é repetido.

O código descrito a cima é apresentado de seguida:

```python
def generateRandomData(length):
    return os.urandom(length)

def generateSecret(secretLength):
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

Para não limitar o *output* a letras e dígitos realizaram-se as seguintes alterações:

```
import base64
def generateSecret(secretLength):
	return base64.b64encode(utils.generateRandomData(secretLength))
```

De facto, já não se limita a que apenas os *bytes* que representem letras e dígitos sejam considerados. Assim, torna-se necessário transformar os *bytes* resultantes em *bytes* imprimíveis, realizado através da função `base64.b64encode`. Este facto pode ser testado executando o programa com a nova função, através do qual se obtém o seguinte *output*:

```
$ python generateSecret-app.py 1024
6w49b2/mpSvWjJVn3Hxdhe8IJmzjbiRIYafIVzQ43Vm3axA6QEy+VCdN0q6e+K6NH4u6E22kEci8H1cH6gxy9JVXKyf2Q5b9/1yqkfBTi7hn8Yo6vJx1coytLWRqMooe+jRfn6g0OH8D8GIry+B9AooYjZSyiPbVYXLjHin4U75UH+MyEyOv1fzvmJGr0fModImzh1IH98yNIm+tNMN54zOyKYPBokoTdU6u3k+YozCt0sHvHpbLoD+QBHInlLa5S2J4hRYS8Xq5fOqBczGD2yWowNxy7wxFQRjrTkUEyPLc1UDx1YAdOdt4fg/mPEOkD4IC6dWt4/W1a7HJGHic/pEFYBkwUM4Z5nMNbhEV3lEHw9zMwvN8DZws8c/YksMaG9BxMqLpMB0Zxb0MsKUrFOgDIBIXrEBtYM1JZ0V7zk42bXRiLc1RlF8PnfNVYK+s+MUaQ9nYedzvJNMyX7B0UEECcD+hqjr5yFdnIVmtMtbui3ROyzQktT+HYEm+J+0i34J+hjXpxPBzjcpx48Sgqw9fqn5Py9hxWq+xybJGTQ+7Fp7JCP1pHEYc7Jb6yAxc88JXEBlVut9ytDi/oV4gQ3oSFfk/P41ei463BGVuzpRZaJrXWAPwmMqlOdItK8RgeKXn8DL5PpndzYbebfewaiD4IqfpaEXpKFyxwOezpS8gGFmBh1gDS24KsnHm0/HWjeiE4hYxFP9z02l9HPRTAyWv3WtEp+k6LADHbB4e0/6SgB3GWg8rbSY6wG2oH3tamloz5U7P2yrkbFHMSqPLdmUMZLlCwPf+KQjZcRU5dFluBIFHhPX+aUCk7ZPBtQojhoFawEwJ56HqnBLwt1ckGt+n04m3Ij9+y0dRVOoqz0S1ajyeimJIVfcLx0ElNjJCEVLRCRgcHbR3e5bSJPGFItIQan/x3c7qVaMZOorcZ7fnpr1L4g1NK+tGtHTMwHWWDluXIlhk1lzNVIy4KEtkJiSjq8V3zBnBsPliXM1mP/NVWhMArY/9+S5l1TM6gV8ROqwcT99IqWsTSSeSB55hLyqKlxpWeN7rMvvJMIgaAv4ZIf8Rci8c6aqTaI07Vvi54zLVJ1JxoN1hYxFmI3kg1Coya+QPO8MfB7/ILX1TrdqDXGHXudrfuuitYT7CjA6wRggAmbtZtLT8B+Nbii94sDxoGPis4voWevUOYk1RVWY9STLHD+S7jBDXZy01oX6nYexkIJPQwxmexfVlx2crMfNI3BZ9eaejJIJAT2HNTOnDV9h3ODRTahyyWNFAjdhPrFhpQO4Q4RbEoWSdUr72BXCeV14f5etwNFntEOUcOgKc5rVk0meVjdrX6w3LI5nN5paUioNA/8/WtvAinQjHNw==
```



## 2. Partilha/Divisão de segredo (Secret Sharing/Splitting)



### Pergunta P2.1 - A

Primeiramente, gerou-se a chave privada, que será utilizada para assinar os objetos JWT que são devolvidos no processo de divisão do segredo. Para isso, executou-se o seguinte comando:

```
$ openssl genrsa -aes128 -out mykey.pem 1024
[...]

$ cat mykey.pem 
-----BEGIN RSA PRIVATE KEY-----
Proc-Type: 4,ENCRYPTED
DEK-Info: AES-128-CBC,ACFC33DAA065C77BFF48C4629FAE4015

Pl1iQWyktkEkVVgYcK3Tgy1gs2fN83CFoJJNpBWA50Ot7O3wCSR8qds1bHUBPouN
FbZD5Fg1AjKfBJI37p1bO9R3irt3ngELZvmzplSRvZvde0nsfY8qeJwry+P1t7cn
xhdk+keMPRxwtIOwGLS1Z4bhdgDqpmfp+88YflWu4Ut5f4G6JigUXCkXRdP/eln9
x85d3p1aoCtLEqr++h22o7XcAr8g6q5Shu4KBDT1aLGQodeNrkx68m2NAyLjJVCn
PwaLTuxQAOW3Zd7AdphPVcIm3F4avsiaULA9AxMLAW8ymXlYAhGOTCSXSpHUfrrc
ISqBmg35N4yUtQuJWYiM+ssZ54PAVvnNB9+NRxx+kG33Yc7Shcxz5On5pLXWwrw9
kynBmYnOKM+3m/swHGxKJua2LW17IUqo1gO6Jm1ecbsi54LbNSwfIER13ccEi5BW
cOGBzN/g4/d5PnNgGi5xyYfJJ/TuAvFxWM1JscqjTxjrS6A0KMtvvG98e3/qjBnm
luH0wwaDOLzzOp3ZoB2o/Wgf3A4qHpeHw1SPQA3wYZNDiBcyTBu+34QqGoFjwmnj
R4JSS5NwCq3EUsidDLc21oUZtQlFVqBJutK11mX3gW3oIDHFRwCuetm+9LAf2XYV
CPmkYtljkv2lGd4OvyvSc6ewHD8QtPslRaPGsxVDIsv+jAfpopcqKKPeS13sum1M
4kqSE2b4UZEDh/jKf9wf/wxFHeIXd+00E/Fy94ifx55/qSDaG/2lrNYJIXToEJ/0
zxmrS72byFba4uKyNdte4nLx1mwZYTsvETv7CJCWJPNSmIIbjwT0y13fUJ40zM2T
-----END RSA PRIVATE KEY-----
```

De seguida, utilizou-se a chave privada para gerar o certificado com a respetiva chave pública, que será utilizado posteriormente para recuperar o segredo partilhado:

```
$ openssl req -key mykey.pem -new -x509 -days 365 -out mykey.crt
$ cat mykey.crt 
-----BEGIN CERTIFICATE-----
MIICYTCCAcqgAwIBAgIJAPJYZFufsTN4MA0GCSqGSIb3DQEBCwUAMEgxCzAJBgNV
BAYTAlB0MRMwEQYDVQQIDApTb21lLVN0YXRlMQowCAYDVQQHDAFCMQswCQYDVQQK
DAJVTTELMAkGA1UEAwwCRzUwHhcNMTkwMjEzMTAwNTI4WhcNMjAwMjEzMTAwNTI4
WjBIMQswCQYDVQQGEwJQdDETMBEGA1UECAwKU29tZS1TdGF0ZTEKMAgGA1UEBwwB
QjELMAkGA1UECgwCVU0xCzAJBgNVBAMMAkc1MIGfMA0GCSqGSIb3DQEBAQUAA4GN
ADCBiQKBgQClrkt3CPD8pLwXvtwSuusp/YzPBRrX6lyEh46yO1631ffwG0P5rASI
RxWkRUqUOcw46xosah1mqN8gz5aRsqIptKYJ9w2Q5hEk8lv1jNs0yG+nXxmsssrD
iKKdi7iHYWq8H6VAn7xzO6/8Q4XL3h+1u6lIM1brPzt2Qh23Runh6wIDAQABo1Mw
UTAdBgNVHQ4EFgQUknuoX33nwF2WlglH/BMvnyAGVoUwHwYDVR0jBBgwFoAUknuo
X33nwF2WlglH/BMvnyAGVoUwDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsF
AAOBgQB56DEZYk9dhu6KXkj7c5dkpdNS7r0PfJiAVVN80cnlkIK1NN+ubeUUXt0g
+vhsE5UDSL+cp1WoUc7sHPBZ4Zz9sMXQrZtU7ltKnw+yOTUWBbdPdfbtYjkJ22Hc
qdaT22JcFrDABrQHS4AVUNDtVKYLdWUJmZmB7jDbcHyqx+X6kA==
-----END CERTIFICATE-----
```

Por fim, tendo disponível a chave privada, pode-se realizar a divisão do segredo em 8 partes (`number_of_shares`), com um *quorum* de 5 (`quorum`) e identificador do segredo (`uid`):


```
$ python createSharedSecret-app.py 8 5 1 mykey.pem 
Private key passphrase: 1234
Secret: Agora temos um segredo extremamente confidencial
Component: 1
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjEtNzhkMGJiMTljMmM1MGYxOGQwMGU1MGQyOGQ2NjM4MzQ0ZDQzZTU2MTNkMmMxZThjODQxYzQ2NGZkN2M1YmZlNjJiMmJjYWQzYWVlMGNkZjhiNzdjYzgyNjk3YWIyZWJhIiwgIjEiLCA1LCA4LCAiMWE4ZTViZDhlNmI1MGE3MWYxOTU3NmYxMmUxODY0MzUyYTY4YzkwNGUzNGRiYzc2Y2VkM2U1OWRjMTE0NTk3ZiJdfQ.nAr0zbfNK7L8ofPtJk7H7pxezGrA1kEnJR3E8SFhE-UlBKN2AVX4gBDUB1IZHOhA03Qcdo04hXwTW8ApK1XFQTt_RVc4ysmccCiuL1fCQYIqM2-qYfvfUGblHxgOMJtTeBRjCenbUpIlocibUwytOn-aNJbCZBUrRO3r9_cwEVk
Component: 2
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjItYTcwYTViYWQ0NmYyOWRiNWJlYmVmYzM0M2VlMjhjNGM2Njg2NmFmNmY4YjM0NjQwYTNiMDFmZjFkMjY2YWVkMTI5MmYyNmM4OGZmNGMxOWEwZTAxNTg2YzBkMTY1YyIsICIxIiwgNSwgOCwgIjVkYjRiODM0NDQ5N2IyMjMyMGJkNzA1ZmZkMzk4ZDNiMGI3M2IzYWViMDUzNzU1NWU0YzE0OGFlNTE5MjQ0OTUiXX0.hBXP3JVsOfJHOv3tVfvjyrvH2QlODYRg9GDavCQiKaqyk9De941f39-1j5kPQy1iS5m8hROzuCs9U6HysmiSSRaRSTGFvihpP-aMvlmGyWRyhJXIYz-S8AXRWO7qxzXpmDTqFnsDTC1w9Z-XziycJxfg0MiHbmupVOzI29b_exc
Component: 3
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjMtYjMyYjk1MWY2NjkyYTJmMTU5MDJkNzdjYTIxY2JjNzk5ZjFiZTk5OGE0ZmVlNzU3ZTMxNzgyOWNhMTc2ZjY5ZGJkZWI0YTUzODRkYWVkOWVhOGY2ZjMzNzczMzk5NjJlIiwgIjEiLCA1LCA4LCAiMTYyYmY3ZjE4NGY1N2Y3ODcwNzMyYzhjOGJmZTZlZWNhYzc4YmU4Y2VkNjcwNjUyOGVlMDY0Mzc0YzNlZjkyZSJdfQ.ai3LZ0uwuew6RBSOcw0IQMHe7jjxWFzQRWbtmYtApzSkrTA_Kyi91G0jGHUr_8jCmXTNNPzFEkgekIVZ0FgsL22J75hMVJ3A9vcL04YOzkN8eE_tZu2JREk-g5BlQucjydPC7LNbyGjtTH4d2val3OLUqIShRPc8B-lVmHr6HOo
Component: 4
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtODZmNWFiNjU0ZTZjZjFhMzUzMjQ0NWRjZGJjMzE3YjYxY2I4YzM1YTYzMTkwZDk2MmI0ZmQ2NDk3MDgyNDFjNDEwZTlhMWU1NzljYjY3OThjNmU3ZjIyM2U0MDkyZjhkIiwgIjEiLCA1LCA4LCAiZDM0NDUyNTRjNjgxYTYyMjcwZmRjMmMxZWM3YTA3MTk2ZWE5YmQyNjEwMThiZTM1ODY5YTcxNmQ4NzRlNDBlZCJdfQ.ngeKqowlWXfZFDzzHL1smCHjMjQ94xi8bHtIOOdtoEDSs037YFtejGQx2iiHbDXHMAxkFMi7kK_AyajVkoJT0oDQLJ84ytOJhoWse-medGYErSF5c1VY-09pIY9o-6PiYIm6loSjF2DCzx66cU_2F8OdoCgQC_34qdFORBw4XPY
Component: 5
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjUtOGVmMmI1NDZkZTcyZmRkNTljMzQ0NzRmYjI5MmZhYjczNzk5ZTg3YTU1ZDFjMmU1NjNmMDA5NjY4Y2EyNTc2NWFiOTQ4OGI5ZmYxNmI1ZTQyMTYyYzRhYTk5ODI2ZGE4IiwgIjEiLCA1LCA4LCAiM2U1YTc3NzhjYjY0ZWUzZTk3YjJkZWU0ODc5YTA3M2Y3NjI3NDJiMWMzNDY2ZmE1YzA1MDkxNzBhM2EyN2M4MiJdfQ.Pg1rCrP5FrdOYAlMc1vDFe9tvESnLnkjFjPo8wXaJpKz22iq1LpTfqw4SzurjKHAD4baMEZ0dRO-GAcpiLtTEKPsjsOrWAwkp_-cLeQVTCwe-xx9fm-tFV6VTZh1WGw57VwYkm7Absj5Pkqfl-x0TcfbH94w5jp-APGr0bQlUIk
Component: 6
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtZmE2NjMyZjZhYTFhMzQzYzhiMGJhYWIxYzQ4YjIwYWRmZDI0NGUxY2FhNjNlZTM5NjI2NmJmZjBjNzY0ODNmOTMxNTUxZjAwMmUxZGNmZTAzMGJhYTM4NTEyZDllMWU0IiwgIjEiLCA1LCA4LCAiMjAyOTJhYjE0YjUxNjIzMmJkYmFjZjRhYjE5YWZhNzc0YTFmNzdiMTIzN2UyNzRmMjFiNjc2YWJiYTYwZTA4MSJdfQ.W-_nZ8giHCHfbZRWN4Ks_meQ58Hii8ple-hNu13cd_pOHcCL9lEBRjj2laK8EFlGr61apstknYP3qnKUfRzjRL7of-AdZNuPQdq5V_h5nk1UUUy7pVh3YVYRn1qzlraLJwZfVH0bvYFliaoDMktMKW_aPKhP7BZIAehswDUn0C0
Component: 7
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjctMTRlOWJjYzA1ZWIwNGYxZWQ1NGFkMDg5N2M0N2Y5ODcxNWM1MDliZjk2YmFjMDk1ODZlZGUzYTE5NjM1NTEyODA3OGQ1MjM4ZTFlZDUxMTdiODE0Mzk5OTczNzIyMmY1IiwgIjEiLCA1LCA4LCAiYWYyZDBkOWY5MzkwN2EwZjEwZTQ4OTg1ODllYjVjOWE1MTlmMTQ2ZTkwMTY3YzExN2VmOTdkY2FmMzdhZDI1ZiJdfQ.TguKFy0k_j0azxh6EoecmjjYIMo6lFyAaVs6sswOzXK4HA4WULBez1cheIJt99ZothvLCvXgu_ouebe_E4uXZYrx9QNCHkgGqV7NEwiV2Z9TfMAIx-RO9mokBpieOA9iZPA76XIUt_H3mG6lHZP_CLmliqWAb1O_dgS71MHeArY
Component: 8
eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtNDY2ZDAzMDhjMzViNTY1NThmNTlhYjA3MTEwM2E5ZWFjNGYxNTEzYjU5NzFiNTBjYmM4YWEzZWYxMjYwODVjZTU1OTdkZDM2YjczZDc5NDBjNTY1YTNmYTgyZGJkMjQ4IiwgIjEiLCA1LCA4LCAiZjE5YWVjZjkwZjQyNzY5YTI2Y2QxMjk1MmFlYWY0YmNhNmQxMzlhNWRjNjRmZmVhOGM1NjM1ZThiNmM3Y2UwZiJdfQ.TAyVaXaztTIU1mQm8fbCLii8Ag21EvLRv8fRjq38aB2PlMB7jeltcy_7MVl1m1N1AL2hVVe_pJfLbJuEnIXJj_SCvZrGKQnJ0MpixU-ojWFAaHliXGNtzoQ2Lj5O8ZHjJ3XmBs9m8dZ0gK053YVxGmNzfhL2KRLnMgNk0l4dBjE
```

Assim, este resultado poderá ser dividido por 8 entidades, sendo que são necessárias 5 delas para aceder ao segredo.



### Pergunta P2.1 - B

A execução do programa  `recoverSecretFromComponents-app.py`, com um número de componentes inferior ao `quorum` definido na partilha do segredo, resulta num erro de execução:

```
$ python recoverSecretFromComponents-app.py 1 1 mykey.crt 
Component 1: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjEtNzhkMGJiMTljMmM1MGYxOGQwMGU1MGQyOGQ2NjM4MzQ0ZDQzZTU2MTNkMmMxZThjODQxYzQ2NGZkN2M1YmZlNjJiMmJjYWQzYWVlMGNkZjhiNzdjYzgyNjk3YWIyZWJhIiwgIjEiLCA1LCA4LCAiMWE4ZTViZDhlNmI1MGE3MWYxOTU3NmYxMmUxODY0MzUyYTY4YzkwNGUzNGRiYzc2Y2VkM2U1OWRjMTE0NTk3ZiJdfQ.nAr0zbfNK7L8ofPtJk7H7pxezGrA1kEnJR3E8SFhE-UlBKN2AVX4gBDUB1IZHOhA03Qcdo04hXwTW8ApK1XFQTt_RVc4ysmccCiuL1fCQYIqM2-qYfvfUGblHxgOMJtTeBRjCenbUpIlocibUwytOn-aNJbCZBUrRO3r9_cwEVk
Error: The number of shares is less than quorum 
```



Além disso, a execução do mesmo programa com um número de partes superior ou igual ao `quorum` estabelecido permite aceder ao segredo, desde que estas tenham sido geradas na partilha inicial e não se repitam. Este facto pode ser comprovado através do seguinte *output*:


```
$ python recoverSecretFromComponents-app.py 5 1 mykey.crt 
Component 1: # Componente 1 eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjEtNzhkMGJiMTljMmM1MGYxOGQwMGU1MGQyOGQ2NjM4MzQ0ZDQzZTU2MTNkMmMxZThjODQxYzQ2NGZkN2M1YmZlNjJiMmJjYWQzYWVlMGNkZjhiNzdjYzgyNjk3YWIyZWJhIiwgIjEiLCA1LCA4LCAiMWE4ZTViZDhlNmI1MGE3MWYxOTU3NmYxMmUxODY0MzUyYTY4YzkwNGUzNGRiYzc2Y2VkM2U1OWRjMTE0NTk3ZiJdfQ.nAr0zbfNK7L8ofPtJk7H7pxezGrA1kEnJR3E8SFhE-UlBKN2AVX4gBDUB1IZHOhA03Qcdo04hXwTW8ApK1XFQTt_RVc4ysmccCiuL1fCQYIqM2-qYfvfUGblHxgOMJtTeBRjCenbUpIlocibUwytOn-aNJbCZBUrRO3r9_cwEVk
Component 2: # Componente 2 eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjItYTcwYTViYWQ0NmYyOWRiNWJlYmVmYzM0M2VlMjhjNGM2Njg2NmFmNmY4YjM0NjQwYTNiMDFmZjFkMjY2YWVkMTI5MmYyNmM4OGZmNGMxOWEwZTAxNTg2YzBkMTY1YyIsICIxIiwgNSwgOCwgIjVkYjRiODM0NDQ5N2IyMjMyMGJkNzA1ZmZkMzk4ZDNiMGI3M2IzYWViMDUzNzU1NWU0YzE0OGFlNTE5MjQ0OTUiXX0.hBXP3JVsOfJHOv3tVfvjyrvH2QlODYRg9GDavCQiKaqyk9De941f39-1j5kPQy1iS5m8hROzuCs9U6HysmiSSRaRSTGFvihpP-aMvlmGyWRyhJXIYz-S8AXRWO7qxzXpmDTqFnsDTC1w9Z-XziycJxfg0MiHbmupVOzI29b_exc
Component 3: # Componente 4 eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtODZmNWFiNjU0ZTZjZjFhMzUzMjQ0NWRjZGJjMzE3YjYxY2I4YzM1YTYzMTkwZDk2MmI0ZmQ2NDk3MDgyNDFjNDEwZTlhMWU1NzljYjY3OThjNmU3ZjIyM2U0MDkyZjhkIiwgIjEiLCA1LCA4LCAiZDM0NDUyNTRjNjgxYTYyMjcwZmRjMmMxZWM3YTA3MTk2ZWE5YmQyNjEwMThiZTM1ODY5YTcxNmQ4NzRlNDBlZCJdfQ.ngeKqowlWXfZFDzzHL1smCHjMjQ94xi8bHtIOOdtoEDSs037YFtejGQx2iiHbDXHMAxkFMi7kK_AyajVkoJT0oDQLJ84ytOJhoWse-medGYErSF5c1VY-09pIY9o-6PiYIm6loSjF2DCzx66cU_2F8OdoCgQC_34qdFORBw4XPY
Component 4: # Componente 8 eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtNDY2ZDAzMDhjMzViNTY1NThmNTlhYjA3MTEwM2E5ZWFjNGYxNTEzYjU5NzFiNTBjYmM4YWEzZWYxMjYwODVjZTU1OTdkZDM2YjczZDc5NDBjNTY1YTNmYTgyZGJkMjQ4IiwgIjEiLCA1LCA4LCAiZjE5YWVjZjkwZjQyNzY5YTI2Y2QxMjk1MmFlYWY0YmNhNmQxMzlhNWRjNjRmZmVhOGM1NjM1ZThiNmM3Y2UwZiJdfQ.TAyVaXaztTIU1mQm8fbCLii8Ag21EvLRv8fRjq38aB2PlMB7jeltcy_7MVl1m1N1AL2hVVe_pJfLbJuEnIXJj_SCvZrGKQnJ0MpixU-ojWFAaHliXGNtzoQ2Lj5O8ZHjJ3XmBs9m8dZ0gK053YVxGmNzfhL2KRLnMgNk0l4dBjE
Component 5: # Componente 6 eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtZmE2NjMyZjZhYTFhMzQzYzhiMGJhYWIxYzQ4YjIwYWRmZDI0NGUxY2FhNjNlZTM5NjI2NmJmZjBjNzY0ODNmOTMxNTUxZjAwMmUxZGNmZTAzMGJhYTM4NTEyZDllMWU0IiwgIjEiLCA1LCA4LCAiMjAyOTJhYjE0YjUxNjIzMmJkYmFjZjRhYjE5YWZhNzc0YTFmNzdiMTIzN2UyNzRmMjFiNjc2YWJiYTYwZTA4MSJdfQ.W-_nZ8giHCHfbZRWN4Ks_meQ58Hii8ple-hNu13cd_pOHcCL9lEBRjj2laK8EFlGr61apstknYP3qnKUfRzjRL7of-AdZNuPQdq5V_h5nk1UUUy7pVh3YVYRn1qzlraLJwZfVH0bvYFliaoDMktMKW_aPKhP7BZIAehswDUn0C0
Recovered secret: Agora temos um segredo extremamente confidencial
```



Quanto ao programa `recoverSecretFromAllComponents-app.py`, verifica-se que a única diferença em relação ao anterior é a necessidade da inserção de todas as componentes geradas na partilha do segredo. Na prática, isto traduz-se na invocação da função `recoverSectretFromComponents` com o argumento `allComponents` a `True`.

De facto, através da execução deste programa com um número de componentes igual ao `quorum`, verifica-se que não se consegue aceder ao segredo:

```
$ python recoverSecretFromAllComponents-app.py 5 1 mykey.crt 
Component 1: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjEtNzhkMGJiMTljMmM1MGYxOGQwMGU1MGQyOGQ2NjM4MzQ0ZDQzZTU2MTNkMmMxZThjODQxYzQ2NGZkN2M1YmZlNjJiMmJjYWQzYWVlMGNkZjhiNzdjYzgyNjk3YWIyZWJhIiwgIjEiLCA1LCA4LCAiMWE4ZTViZDhlNmI1MGE3MWYxOTU3NmYxMmUxODY0MzUyYTY4YzkwNGUzNGRiYzc2Y2VkM2U1OWRjMTE0NTk3ZiJdfQ.nAr0zbfNK7L8ofPtJk7H7pxezGrA1kEnJR3E8SFhE-UlBKN2AVX4gBDUB1IZHOhA03Qcdo04hXwTW8ApK1XFQTt_RVc4ysmccCiuL1fCQYIqM2-qYfvfUGblHxgOMJtTeBRjCenbUpIlocibUwytOn-aNJbCZBUrRO3r9_cwEVk
Component 2: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjItYTcwYTViYWQ0NmYyOWRiNWJlYmVmYzM0M2VlMjhjNGM2Njg2NmFmNmY4YjM0NjQwYTNiMDFmZjFkMjY2YWVkMTI5MmYyNmM4OGZmNGMxOWEwZTAxNTg2YzBkMTY1YyIsICIxIiwgNSwgOCwgIjVkYjRiODM0NDQ5N2IyMjMyMGJkNzA1ZmZkMzk4ZDNiMGI3M2IzYWViMDUzNzU1NWU0YzE0OGFlNTE5MjQ0OTUiXX0.hBXP3JVsOfJHOv3tVfvjyrvH2QlODYRg9GDavCQiKaqyk9De941f39-1j5kPQy1iS5m8hROzuCs9U6HysmiSSRaRSTGFvihpP-aMvlmGyWRyhJXIYz-S8AXRWO7qxzXpmDTqFnsDTC1w9Z-XziycJxfg0MiHbmupVOzI29b_exc
Component 3: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjQtODZmNWFiNjU0ZTZjZjFhMzUzMjQ0NWRjZGJjMzE3YjYxY2I4YzM1YTYzMTkwZDk2MmI0ZmQ2NDk3MDgyNDFjNDEwZTlhMWU1NzljYjY3OThjNmU3ZjIyM2U0MDkyZjhkIiwgIjEiLCA1LCA4LCAiZDM0NDUyNTRjNjgxYTYyMjcwZmRjMmMxZWM3YTA3MTk2ZWE5YmQyNjEwMThiZTM1ODY5YTcxNmQ4NzRlNDBlZCJdfQ.ngeKqowlWXfZFDzzHL1smCHjMjQ94xi8bHtIOOdtoEDSs037YFtejGQx2iiHbDXHMAxkFMi7kK_AyajVkoJT0oDQLJ84ytOJhoWse-medGYErSF5c1VY-09pIY9o-6PiYIm6loSjF2DCzx66cU_2F8OdoCgQC_34qdFORBw4XPY
Component 4: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjgtNDY2ZDAzMDhjMzViNTY1NThmNTlhYjA3MTEwM2E5ZWFjNGYxNTEzYjU5NzFiNTBjYmM4YWEzZWYxMjYwODVjZTU1OTdkZDM2YjczZDc5NDBjNTY1YTNmYTgyZGJkMjQ4IiwgIjEiLCA1LCA4LCAiZjE5YWVjZjkwZjQyNzY5YTI2Y2QxMjk1MmFlYWY0YmNhNmQxMzlhNWRjNjRmZmVhOGM1NjM1ZThiNmM3Y2UwZiJdfQ.TAyVaXaztTIU1mQm8fbCLii8Ag21EvLRv8fRjq38aB2PlMB7jeltcy_7MVl1m1N1AL2hVVe_pJfLbJuEnIXJj_SCvZrGKQnJ0MpixU-ojWFAaHliXGNtzoQ2Lj5O8ZHjJ3XmBs9m8dZ0gK053YVxGmNzfhL2KRLnMgNk0l4dBjE
Component 5: eyJhbGciOiAiUlMyNTYifQ.eyJvYmplY3QiOiBbIjYtZmE2NjMyZjZhYTFhMzQzYzhiMGJhYWIxYzQ4YjIwYWRmZDI0NGUxY2FhNjNlZTM5NjI2NmJmZjBjNzY0ODNmOTMxNTUxZjAwMmUxZGNmZTAzMGJhYTM4NTEyZDllMWU0IiwgIjEiLCA1LCA4LCAiMjAyOTJhYjE0YjUxNjIzMmJkYmFjZjRhYjE5YWZhNzc0YTFmNzdiMTIzN2UyNzRmMjFiNjc2YWJiYTYwZTA4MSJdfQ.W-_nZ8giHCHfbZRWN4Ks_meQ58Hii8ple-hNu13cd_pOHcCL9lEBRjj2laK8EFlGr61apstknYP3qnKUfRzjRL7of-AdZNuPQdq5V_h5nk1UUUy7pVh3YVYRn1qzlraLJwZfVH0bvYFliaoDMktMKW_aPKhP7BZIAehswDUn0C0
Error: Invalid number of components
```



Concluindo, o programa `recoverSecretFromAllComponents-app.py` será fundamental caso o nível de criticidade de uma mensagem aumente em relação ao previsto na sua geração. De facto, indisponibilizando o programa `recoverSecretFromComponents-app.py` e permitindo apenas o acesso ao primeiro, garante-se que a mensagem partilhada só poderá ser acedida com a intervenção de todas as partes, mesmo que `quorum` associado seja inferior ao número de componentes.





## 3. Authenticated Encryption



### Pergunta P3.1

Tendo em conta o cenário identificado, considera-se a existência de algumas funções auxiliares, com as seguintes assinaturas:

+ `today()`, que retorna a data presente
+ `geracao_aleatoria(n)`, que retorna uma *string* pseudoaleatória com `n` *bit*
+ `geracao_chave_mac(palavra_chave, salt)`, que retorna uma chave obtida a partir da palavra-chave e do `salt`

Deste modo, propõe-se a seguinte implementação, com o objetivo de garantir confidencialidade, integridade e autenticidade do segredo. Além disso, para a etiqueta, apenas se assegura a integridade e autenticidade.

```python
def cifrar(texto_limpo, etiqueta, palavra_chave):
	crypto = cifra(texto_limpo)
	data = today()
	salt = geracao_aleatoria(16)
	chave = geracao_chave_mac(palavra_chave, salt)
	mac = hmac(chave, crypto + etiqueta + data)
	return (crypto, etiqueta, data, mac, salt)

def decifrar(criptograma, data_limite, palavra_chave):
	texto_limpo = None
	etiqueta = None
	(crypto, etiqueta, data, mac, salt) = criptograma
	chave = geracao_chave_mac(palavra_chave, salt)
	new_mac = hmac(chave, crypto + etiqueta + data)
	if mac == new_mac:
		if today() > data_limite:
			segredo = None
		else:
			segredo = decifra(crypto, obtem_chave(data))
	else:
		etiqueta = None

	return etiqueta, segredo
```





## 4. Algoritmos e tamanhos de chaves



### Pergunta P4.1 - Itália (ECs "Banca d'Italia" e "Ministero della Difesa")

A entidade de certificação "Banca d'Italia" emite certificados com as seguintes características:

- **Algoritmo de assinatura**: RSA com SHA256
- **Algoritmo de chave pública**: RSA
- **Tamanho da chave**: 4096 bit

Estes factos podem ser comprovados com base na análise do *output* obtido através da execução do comando `openssl x509 -in cert.crt -text -noout` sobre o conteúdo *Base 64-encoded* do respetivo certificado:

```
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number: 1204168849 (0x47c62891)
        Signature Algorithm: sha256WithRSAEncryption  <------
        Issuer: C = IT, O = Banca d'Italia/00950501007, OU = Servizi di certificazione, CN = Banca d'Italia
        Validity
            Not Before: Nov 24 08:43:33 2014 GMT
            Not After : Nov 24 09:13:33 2034 GMT
        Subject: C = IT, O = Banca d'Italia/00950501007, OU = Servizi di certificazione, CN = Banca d'Italia
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption       <------
                RSA Public-Key: (4096 bit)            <------
                Modulus:
                    00:ec:b5:44:63:77:63:83:9d:6a:44:54:0d:29:5e:
                    [...]
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:1
            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
            X509v3 Certificate Policies: 
                Policy: 1.3.76.38.1.1.1
                  CPS: http://www.bancaditalia.it/firmadigitale

            X509v3 CRL Distribution Points: 

                Full Name:
                  URI:ldap://ldap.firmadigitale.bancaditalia.it/cn=WinCombined1,cn=Banca%20d'Italia,ou=Servizi%20di%20certificazione,o=Banca%20d'Italia/00950501007,c=IT?certificateRevocationList
                  URI:http://www.firmadigitale.bancaditalia.it/crl/crl1.crl

                Full Name:
                  DirName:C = IT, O = Banca d'Italia/00950501007, OU = Servizi di certificazione, CN = Banca d'Italia, CN = CRL1

            X509v3 Subject Key Identifier: 
                BE:09:DE:0F:DA:AE:81:7F:D9:83:69:2B:48:14:50:B4:87:72:F6:81
    Signature Algorithm: sha256WithRSAEncryption       <------
         4b:d2:6c:a2:19:1b:83:a2:9c:53:bc:76:e1:cb:81:d0:d5:a4:
         [...]
```


A entidade de certificação "Ministero della Difesa" emite certificados com as seguintes características:

- **Algoritmo de assinatura**: RSA com SHA256
- **Algoritmo de chave pública**: RSA
- **Tamanho da chave**: 4096 bit

Estes factos podem ser comprovados com base na análise do *output* obtido através da execução do comando `openssl x509 -in cert.crt -text -noout` sobre o conteúdo *Base 64-encoded* do respetivo certificado:

```
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number: 6936921824674324395 (0x6044e5a56a5e1fab)
        Signature Algorithm: sha256WithRSAEncryption   <------
        Issuer: C = IT, O = Ministero della Difesa, OU = S.M.D. - C.do C4 Difesa, serialNumber = 97355240587, CN = Ministero della Difesa - CA di Firma Digitale
        Validity
            Not Before: Jul 15 08:11:41 2014 GMT
            Not After : Jul 15 08:11:41 2044 GMT
        Subject: C = IT, O = Ministero della Difesa, OU = S.M.D. - C.do C4 Difesa, serialNumber = 97355240587, CN = Ministero della Difesa - CA di Firma Digitale
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption        <------
                RSA Public-Key: (4096 bit)             <------
                Modulus:
                    00:c7:91:49:da:58:d2:68:ca:80:5b:1d:77:37:76:
                    [...]
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            Authority Information Access: 
                OCSP - URI:http://ocsppkiff.difesa.it/

            X509v3 Subject Key Identifier: 
                E0:39:51:60:B3:30:50:53:A5:32:62:21:BB:B2:88:21:D3:B7:05:13
            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:0
            X509v3 Certificate Policies: 
                Policy: 1.3.6.1.4.1.14031.2.1.1
                  CPS: http://www.pki.difesa.it/ManualeOperativoDifesa.pdf

            X509v3 CRL Distribution Points: 

                Full Name:
                  URI:http://www.pki.difesa.it/cafirmadigitale.crl

                Full Name:
                  URI:ldap://ldappkiff.difesa.it:389/CN=Ministero%20della%20Difesa%20-%20CA%20di%20Firma%20Digitale,OU=S.M.D.%20-%20C.do%20C4%20Difesa,O=Ministero%20della%20Difesa,C=IT

            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
    Signature Algorithm: sha256WithRSAEncryption       <------
         71:9d:8c:a7:74:40:5c:db:9d:70:2d:b9:78:56:aa:be:d9:a7:
         [...]
```

A análise dos certificados de ambas as entidades permite concluir que os algoritmos e os comprimentos de chaves utilizados são iguais. Efetivamente, a utilização do algoritmo RSA com 4096 bit vai de encontro às recomendações realizadas pela *European Union Agency for Network and Information Security* (ENISA), que estima que este algoritmo com um tamanho de chaves maior ou igual a 3072 bit mantenha as suas características de segurança por 10-50 anos. Da mesma forma, prevê que a utilização da função de hash criptográfica SHA256 se mantenha segura pelo mesmo intervalo de tempo.

Mais ainda, é de salientar que as datas de validade dos certificados das ECs "Banca d'Italia" e "Ministero della Difesa" (2034-11-24 e 2044-07-15, respetivamente) se encontram inseridas no intervalo de tempo previamente especificado, em que os algoritmos inerentes às mesmas são considerados seguros.

Contudo, pode-se realçar como aspeto menos positivo a redução de eficiência no algoritmo RSA, quando se utilizam chaves com tamanho superior a 3072 bit. Desta forma, propõe-se que em iterações futuras se pondere a utilização de curvas elípticas, uma vez que permite obter o mesmo nível de segurança com chaves de tamanho inferior. De facto, a utilização de chaves com 256 bit bastaria para igualar o nível de segurança conseguido pelo RSA com chaves de 3072 bit.



## Referências

[Wikipedia - */dev/random*](https://en.wikipedia.org/wiki//dev/random?fbclid=IwAR3oZenGHfHH0Zq5myM0nq90_IBgkuNUQ_VTqCoIl1K2BoY23Y3W0YrPiLw)

[stackoverflow - *differences between random and urandom*](https://stackoverflow.com/questions/23712581/differences-between-random-and-urandom)

[ENISA - *Algorithms, key size and parameters report 2014*](https://www.enisa.europa.eu/publications/algorithms-key-size-and-parameters-report-2014)
