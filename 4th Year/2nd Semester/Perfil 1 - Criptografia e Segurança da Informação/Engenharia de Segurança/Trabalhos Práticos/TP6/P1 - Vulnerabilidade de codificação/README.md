# Pergunta 1 - *Common Weakness Enumeration* (CWE)

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Pergunta P1.1**](#pergunta-p11---common-weakness-enumeration-cwe) - ***Common Weakness Enumeration* (CWE)**
   
    - Análise das três primeiras *Weakness* do *ranking* do CWE
    - Análise da *Weakness* N.º 9 do *ranking* do CWE
    
2. [**Pergunta P1.2**](#pergunta-p12---source-lines-of-code-sloc) - ***Source Lines Of Code* (SLOC)**
   - Análise do número de linhas de código de um pacote/plataforma de *software*
    - Estimativa de número de *bugs* a partir desse número de linhas de código
    - Possíveis Vulnerabilidades

3. [**Pergunta P1.3**](#pergunta-p13---tipos-de-vulnerabilidades-em-todo-o-ciclo-do-software-e-exemplos-associados) - Tipos de vulnerabilidades em todo o ciclo do *software* e exemplos associados

4. [**Pergunta P1.4**](#pergunta-p14---vulnerabilidades-dia-zero) - Vulnerabilidades **dia-zero**

---

## Resolução da Pergunta 1

### Pergunta P1.1 - ***Common Weakness Enumeration* (CWE)**

Usando como base o **The CWE Top 25** de 2019 https://cwe.mitre.org/top25/, somos capazes de responder às seguinte perguntas práticas.

<br/>

#### Alínea I. Características das três primeiras *Weakness* do *ranking*

| ID da *Weakness*                                             | Descrição                                                    | Plataformas Aplicáveis                                       | Consequências mais comuns                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **ID** [**CWE-119**](https://cwe.mitre.org/data/definitions/119.html) | ***Improper Restriction of Operations within the Bounds of a Memory Buffer***<br /><br/>*Weakness* presente quando estamos a lidar com um *buffer* presente numa aplicação e conseguimos ler/escrever num espaço de memória para além do que foi alocado a esse *buffer*. | **Linguagens de Programação**: Mais dominante em linguagens de baixo nível - C, C++ e *Assembly*. <br /><br />**Tecnologias**: Não Aplicáveis. | Execução de código ou comandos não autorizados; Leitura de memória, bem como informação sensível; Alterar o fluxo de controlo; Colocar o sistema indisponível. |
| **ID** [**CWE-79**](https://cwe.mitre.org/data/definitions/79.html) | ***Improper Neutralization of Input During Web Page Generation ('Cross-site Scripting')***<br /><br />*Weakness* presente quando uma  *web app* não neutraliza ou neutraliza de forma incorreta o *input* dado pelo utilizador. <br />Como o *ouput* destas páginas é veiculado a outros utilizador, tornam-se vulneráveis a esta fraqueza. | **Linguagens de Programação:** Indeterminadas.<br /><br />**Tecnologias:** Todas as tecnologias *web* podem estar vulneráveis a este tipo de ataques. | Obtenção de informação armazenada nos *cookies*; Execução de código ou comandos não autorizados; Envio de pedidos fingindo ser a vítima. |
| **ID** [**CWE-20**](https://cwe.mitre.org/data/definitions/20.html) | ***Improper Input Validation***<br /><br />*Weakness* presente quando uma *web app* não valida o *input* vindo do utilizador, podendo afetar o fluxo de controlo ou o fluxo de dados do programa em si.<br />**Apesar de similar à anterior em termos de descrição, esta *weakness* interfere nos servidores onde o *software* se encontra alojado, enquanto que a anterior pode chegar a afetar diretamente os dispositivos dos clientes do *software*.** | **Linguagens de Programação:** Indeterminadas.<br /><br />**Tecnologias:** Não Aplicáveis. | *Denial of Service*; Leitura de memória, bem como ficheiros ou pastas; Execução de código ou comandos não autorizados. |

<br/>

#### Alínea II. Características da *Weakness* N.º 9 do *ranking*

| ID da *Weakness*                                             | Descrição                                                    | Plataformas Aplicáveis                                       | Consequências mais comuns                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **ID** [**CWE-190**](https://cwe.mitre.org/data/definitions/190.html) | ***Integer Overflow or Wraparound***<br /><br />Cálculo que pode originar um excesso de número inteiro ou envolvente.<br />Este *overflow* acontece quando um valor inteiro é incrementado para um valor demasiado grande para ser armazenado. <br />Quando isto acontece, esse valor pode "estourar" e virar um número muito pequeno e até mesmo negativo. | **Linguagens de Programação:** Indeterminadas.<br /><br />**Tecnologias:** Não Aplicáveis. | *Denial of Service*; Modificação da memória; Execução de código ou comandos não autorizados. |

<br/>

**Veja-se um exemplo demonstrativo de como esta *Weakness* pode ocorrer:**

```c
img_t table_ptr; / * struct contendo dados img, 10kB cada * /
int num_imgs;
...
num_imgs = get_num_imgs ();
table_ptr = (img_t *) malloc (sizeof (img_t) * num_imgs);
...
```

Pela análise do código conseguimos perceber que se quer criar/alocar uma tabela de tamanho ```num_imgs```. 

Tendo em conta que esse ```num_imgs``` vai crescendo, o cálculo que determina o tamanho da lista terá também de ser feito calculado. O que acontece é pode chegar a um momento em que esse cálculo acabe por "estourar", resultando numa lista muito pequena a ser alocada.
Se o código C que vier a seguir a estes cálculos operar assumindo um determinado número de imagens, este cálculo errado poderá produzir muitos tipos de *out-of-bounds problems*.

<br/>

**Veja-se outro exemplo demonstrativo:**

```c
bytes int curtos = 0;
char buf [SOMEBIGNUM];

while (bytesRec < MAXGET) {
bytesRec + = getFromInput (buf + bytesRec);
}
```

Neste caso, o valor de ```bytesRec``` pode também ele "estourar", criando um valor continuamente menor que ```MAXGET```, levando a que exista um comportamento de *loop* indefinido.

<br/>

**Este tipos de *overflows* são muito comuns no contexto da linguagem C, estando eles associados à insuficiência de memória por parte destas variáveis.**

---

### Pergunta P1.2 - ***Source Lines Of Code* (SLOC)**

A ideia desta pergunta passa por analisar os dados fornecidos relativamente ao número de linhas de código de um determinado pacote/plataforma de *software*, de modo a estabelecer uma estimativa do número de *bugs* dos mesmos e possíveis vulnerabilidades.

<br/>

#### Alínea I. Estimativa número de *bugs*

Estima-se que qualquer pacote de de *software* tem uma média de 5 a 50 bugs por cada 1.000 linhas de código fonte (1.000 *Source Lines Of Code*) , alguns dos quais dados como vulnerabilidades.

<br/>

**Para estes valores existe um limite inferior que está associado a *softwares* mais normais e um limite superior associado a *softwares* desenvolvidos através de métodos mais rigorosos:**

- **Limite Inferior:** 50 *bugs* por cada 1.000 linhas de código fonte;
- **Limite Superior:** 5 *bugs* por casa 1.000 linhas de código fonte.

Isso deixa desde logo a ideia de que esta estimativa varia muito de acordo com o nível de testes de um *software* e até mesmo a linguagem de programação associada ao mesmo. Tendo-se isto definido, é possível estabelecer uma regra de três simples e determinar os valores para estes limites.

 <br/>

| Pacote/Plataforma de *software*      | ≅ Linhas de Código | Limite Inferior | Limite Superior |
| ------------------------------------ | ------------------ | --------------- | --------------- |
| Facebook                             | 62 milhões         | 310 000         | 3 100 000       |
| *Software* de automóveis             | 100 milhões        | 500 000         | 5 000 000       |
| Linux 3.1                            | 15 milhões         | 75 000          | 750 000         |
| Todos os serviços Internet da Google | 2 biliões          | 10 000 000      | 100 000 000     |

<br/>

#### Alínea II. Possíveis Vulnerabilidades

Sabe-se que o número de *bugs* e o número de vulnerabilidades estão internamente ligados. Basta pensar em grandes aplicações, com maior número de linhas de código fonte, para perceber que estão mais suscetíveis a apresentar um maior número de *bugs*, pelo simples facto de serem aplicações mais complexas em termos de desenvolvimento.

<br/>No entanto, não é possível estabelecer uma ligação direta entre todos estes valores, pelo simples facto de que não existe uma estimativa em termos de vulnerabilidades que possa ser determinada a partir do número de linhas de código fonte e/ou número de *bugs*.

---

### Pergunta P1.3 - Tipos de vulnerabilidades em todo o ciclo do *software* e exemplos associados

**Vulnerabilidades de Projeto** são problemas introduzidos no projeto na fase do planeamento do mesmo tal como:

- [Improper Neutralization of Input During Web Page Generation ('Cross-site Scripting')](https://cwe.mitre.org/data/definitions/79.html) - Esta vulnerabilidade acontece quando não existe a filtração e neutralização do *input* introduzido pelo utilizador, por exemplo num *web request*. Assim a aplicação Web dinamicamente gera uma página com este *input* não confiável e com instruções para executar por exemplo *JavaScript*, *ActiveX*, *Flash* que possa ser malicioso. A vítima assim no seu *browser* corre este código existindo assim **Cross-site Scripting** violando o princípio de que os *scripts* dum domínio não devem poder aceder a recursos ou correr código noutro domínio/computador.
- [Weak Encoding for Password](https://cwe.mitre.org/data/definitions/261.html) - Colocar uma máscara na *password* como por exemplo colocar um *encoding* de forma a proteger a *password* é um erro grande. Guardar a *password* em texto limpo e de forma a remediar este erro já preocupante, mudar o *encoding* para por exemplo *BASE64*. Isto não protege a palavra-passe e é uma vulnerabilidade a ser evitada ou corrigida, logo na fase de planeamento.

**Vulnerabilidades de codificação** são problemas introduzidos no projeto na fase de programação do *software*:
- [Absolute Path Traversal](https://cwe.mitre.org/data/definitions/36.html) - O programa utiliza *input* externo para construir um caminho de diretoria que devia estar restrito, dado que não foi neutralizado e filtrado o *input* antes de efetuar o código. 
- [Not Using Password Aging](https://cwe.mitre.org/data/definitions/262.html) - Não existir nenhum mecanismo colocado para verificar a idade das *passwords* de forma a incentivar o utilizador a trocar segundo as recomendações de especialistas em segurança. Mesmo assim tem de se pensar que a janela de renovação não seja muito curta, senão traz uma possibilidade maior dos utilizadores colocarem *passwords* fracas ou previsíveis. Assim, é também importante *passwords* similares às anteriores.

**Vulnerabilidades Operacionais** são problemas causados pelo sistema onde o *software* está a correr ou a sua configuração (A categoria está obsoleta pelo MITRE, mas pegamos em vulnerabilidades que acreditamos estar neste ramo):
- [Incorrect User Management](https://cwe.mitre.org/data/definitions/286.html) - O *software* não faz a gestão apropriadamente do utilizador no ambiente da empresa e sistema operativo. Assim os utilizadores podem ter acesso a ler/alterar/apagar dados sensíveis do sistema.
- [Privilege Chaining](https://cwe.mitre.org/data/definitions/268.html) - Seguindo o mesmo problema da gestão de privilégios e utilizadores, dois privilégios distintos podem ser combinados duma maneira que cria uma cadeia de permissões que deixam uma entidade acionar procedimentos inseguros, que não aconteceriam se não existisse a possibilidade e facilidade de criar cadeias de privilégios e permissões.

---

### Pergunta P1.4 - Vulnerabilidades dia-zero

As vulnerabilidades de **dia-zero** são vulnerabilidades que não têm um *patch* para corrigir disponível, fazendo com que seja uma falha de segurança para qualquer *hacker* explorar e atacar, dado que toda a gente usando esse produto afetado está exposto dada a falta de correção da vulnerabilidade.

De forma análoga, uma vulnerabilidade que não seja **day-zero** é uma falha que foi encontrada pela comunidade e/ou pelo fabricante, mas já corrigida através dum *patch*. De qualquer forma, não deixa de ser uma vulnerabilidade dado que apenas aqueles que tenham o produto atualizado para a versão mais recente é que estão protegidos de possíveis *exploits* advindos dessa vulnerabilidade.

O caso mais infame e recente foi a vulnerabilidade **HeartBleed** que afetou a biblioteca de segurança *open source* **OpenSSL**. Quando esta vulnerabilidade **dia-zero** no dia 1 de Abril de 2014, estimou-se que 17%, ou meio milhão de servidores Web que estavam certificados como seguros, estavam na verdade vulneráveis a *exploits* relacionados com esta vulnerabilidade, até ter existido o *patch* que demorou 7 dias a ser efetuado.

---

## Notas/Observações Finais

Não existem observações finais para este Trabalho Prático.
