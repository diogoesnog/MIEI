<p align="center">
   <img width="200" height="182" src="https://upload.wikimedia.org/wikipedia/commons/9/93/EEUMLOGO.png">
</p>

<br>

# Módulo de Cartografia (COVID-19)

O trabalho prático da Unidade Curricular de Tecnologias e Aplicaçãos, consiste na criação de desenvolvimendo de um *Notebook* Jupyter que explora graficamente e geograficamente a informação sobre o COVID-19.

<br/>

**O que é a COVID-19?**

> COVID-19 é o nome, atribuído pela Organização Mundial da Saúde, à doença provocada pelo novo coronavírus SARS-COV-2, que pode causar infeção respiratória grave como a pneumonia. Este vírus foi identificado pela primeira vez em humanos, no final de 2019, na cidade chinesa de Wuhan, província de Hubei, tendo sido confirmados casos em outros países.

<p align = "center">
   <img src = "Conjunto de Dados/MapaMundialPaisesAfetados.gif" alt = "Evolução Casos"/>
</p>
<p align = "center"><b>Figura 1.</b> Evolução dos Casos a nível Mundial<br/><b>(GIF obtido através do QGIS com TimeManager)</b></p>



<br/>

**Qual o objetivo deste projeto?**

Este projeto surge como uma visão pessoal acerca da evolução da disseminação e dos efeitos do vírus, não só na saúde dos cidadãos mas também na economia geral do país.

--- 

## Origem dos Dados

Para este projeto prático, usaram-se vários *datasets* em modo CSV que vão de acordo com as necessidades impostas para o projeto. Não só os *datasets* previamente disponibilizades pelo docente da UC, mas também outros tantos existentes *online* em toda a comunidade do GitHub.

<br/>

**Em termos de informação, usaram-se os dados referentes aos seguintes repositórios:**

| Tipo     | Origem                                                       | Uso                                                          |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Mundial  | [Data on COVID-19 by Our World in Data](https://github.com/owid/covid-19-data/) | Dados usados para o controle da evolução do número de novos casos e mortes a nível mundial/global. |
| Mundial  | [COVID-19 Data Repository by the Center for Systems Science and Engineering (CSSE) at Johns Hopkins University](https://github.com/CSSEGISandData/COVID-19) | Dados usados para o controle da evolução do número de recuperados.<br /><br />**Apesar da preferência pelo *dataset* anterior, esse não contém dados relativos aos casos recuperados.** |
| Nacional | [Dados sobre COVID-19 em Portugal](https://github.com/jgrocha/covid-pt) | Dados usados para o controle da evolução da pandemia do COVID-19 a nível nacional. |
| Nacional | [Dados relativos à pandemia COVID-19 em Portugal](https://github.com/dssg-pt/covid19pt-data) | Este *dataset* acrescenta parâmetros necessários para o projeto em causa, facilitindo a sua projeção. |
| Nacional | [travelBI by Turismo de Portugal](https://travelbi.turismodeportugal.pt/) | Fonte *online* com dados essenciais relativos às receitas do turismo. |

---

## Esquema Estudo dos Dados

- **Dados Mundiais**
  - Panorama Geral da Pandemia;
  - Lista de Casos de COVID-19;
  - Evolução da Pandemia.

- **Dados Nacionais**
  - Panorama Geral da Pandemia;
  - Lista de Casos de COVID-19;
  - Evolução da Pandemia.

- **Dados Turismo**
  - Estudo do Impacto do COVID-19 nas Reservas de Voos;
  - Estudo das Candidaturas à Linha de Apoio à Tesouraria de Microempresas ligadas ao Turismo.

---

## Acerca dos Dados

Apesar dos dados recolhidos pelos repositórios anexados anteriormente, existiu ainda (tal como consta na tabela) um empurrão extra, que permitiu relacionar toda a informação digerida para o COVID-19 e estabelecer uma conclusão acerca do impacto desta pandemia a nível turístico.

Para obter estes dados extra em modo CSV foi necessário criar um *script* Python que conseguisse ir buscar a informação atualizada e cria-se os respetivos dados. Este script tem de nome [convertDataToCSV.py](https://github.com/diogoesnog/COVID-19/blob/master/Conjunto%20de%20Dados/Dados%20CSV/convertDataToCSV.py) e foi criado pensando-se na simplicidade em ter os dados sempre mais recentes, evitando-se trabalho excessivo na hora de recolher nova informação diária.

<br/>

**Como funciona o *script* Python?**

- Executa um ficheiro [dataCommands.sh](https://github.com/diogoesnog/COVID-19/blob/master/Conjunto%20de%20Dados/Dados%20CSV/dataCommands.sh) que contém todos os comandos em modo `curl` para os dados necessários;
  - Ao executar estes comandos obtém desde logo os dados em modo JSON, não processados.
- Através de Expressões Regulares, absorve apenas a informação necessária, ao mesmo tempo que a escreve a mesma num ficheiro CSV.
- Com todos os ficheiros CSV criados, os ficheiros JSON são eliminados de forma automática.
