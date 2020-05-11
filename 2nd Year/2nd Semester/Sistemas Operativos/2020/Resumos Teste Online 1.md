# Resumos Teste Online 1

Este ficheiro README serve para resumir toda a matéria que supostamente será usada para criar o primeiro teste online da UC em tempos de pandemia de COVID-19. Dessa forma, consistirá em mais tópicos e menos texto, de modo a criar um entendimento mais imediato e eficaz, mas sempre com as justificações possíveis para cada tópico/sub tópico.

---

### Objetivos da Unidade Curricular

- Toda a ideia da UC está à volta da concorrência dos programas em C;
  - A sua eficácia, rapidez, segurança, etc;
  - Boa gestão dos recursos perante uma determinada carga;
  - Perceber como funcionam os sistemas em si.

---

### Programa da Unidade Curricular

<br/>

#### 1. Introdução 

- Um computador serve para executar programas/aplicações
- Facilita  a vida de um utilizador comum
- Um **Sistema Operativo** é um **programa** que atua como **intermediário** entre os *users* e o *hardware*
  - Sistema Operativo tem como função colocar o *hardware* à disposição dos programas e *users* de forma justa, protegida e acima de tudo eficiente
- Um **Sistema Operativo** pode ser visto como uma simulação de uma máquina virtual acima da real e como um gestor de recursos
- Um **Sistema Operativo** define a personalidade de um computador

<br/>

#### 2. Gestão de Processos

- Criar vários processos é CONVENINENTE e EFICIENTE 

  - Evitam-se esperas desnecessárias
  - Múltiplos CPUs
  - Aumenta-se a utilização de recursos a.k.a multiprogramação
- Um processo é um programa em execução
- Programa **Estático** VS Processo **Dinâmico**
- Invocar o mesmo programa duas vezes são dois processos **diferentes**
- Um Sistema Operativo deve criar, suspender e reiniciar a execução de processos
- Um Sistema Operativo tem muitos processos do sistema em si
- PROCESSOS COMPETEM POR RECURSOS

  - Precisam de tempo de CPU
  - Memória
  - Etc
- Sistema Operativos faz todo o escalonamento dos processos, ou seja, atribui os recursos pela ordem correspondente às políticas de escalonamento
- Escalonamento refere-se à colocação ordenada dos dados ou funções por níveis, segundo um determinado critério
- **IO/Bound** vs **CPU/Bound**

  - **IO/Bound** são sistemas que fazem uso intensivo da entrada/saída (I/O)
    - Tipo quando se copia um ficheiro para uma pen USB
    - Estes processos I/O fazem POUCO USO DA CPU
- **CPU/Bound** quando os processos usam muito CPU
  
    - Tipo jogos que usam recursos gráficos 3D alta complexidade
    - Quando o tempo de processamento depende mais do processador que das entradas e saídas
    - Atrapalha-se o tempo total de processamento
- Processos em UNIX são feitos pelo uso de fork() e afins
- Quando se cria um fork ambos os processos executam o mesmo programa
- AO USARMOS O **EXEC** ESTAMOS A SUBSTITUIR O PROGRAMA DO PROCESSO CORRENTE POR UM NOVO PROGRAMA
  
  - Por isso é que quando o exec é feito num programa qualquer, o mesmo termina mal o exec seja processado
- Um programa pode estar em execução (1), bloqueado (2), pronto a executar (3)
    - Tudo depende do escalonamento
- O escalonamento de processos é uma atividade organizacional feita pelo escalonador da CPU ou de um sistema distribuído, permitindo executar os processos mais viáveis e concorrentes, dando prioridade  a determinados tipos de processo, como os de IO/Bound e os CPU/Bound
    - Escolhe-se o processo que tem mais prioridade e menos tempo e coloca-o na memória principal, ficando os outros alocados em disco
    - Assim, o processador evita ficar ocioso
- Os processo ficam numa espécie de *ready list* para serem executados aos poucos
    - Quando um processo é escalonado, retira-se da *ready list* e coloca-se o mesmo a executar
- Um processo pode perder a CPU por vários motivos

| Algoritmo Escalonamento                | Uso                                                          |
| -------------------------------------- | ------------------------------------------------------------ |
| FCFS (*First Come, First Served*)      | 1. A *ready list* é uma FIFO (Primeiro a Entrar, Primeiro a Sair)<br />2.Os processos são colocados no fim da lista e o da frente é o selecionado<br />3. Simplicidade de Implementação |
| SJF (*Shortest Job First*)             | 1. Escalonar o processo mais curto primeiro<br />2. Possibilidades<br />- Desafectação forçada (SRTF) - interrompe-se o processo em execução se surgir um mais curto<br />- Coperativo - aguarda-se que o processo em causa termine mesmo estando um mais curto na *ready list*<br />3. Não se consegue adivinhar o tempo de processamento dos processos, apenas estimativas<br />4. Usa uma combinação de tempos reais e suas estimativas para fazer futuras previsões |
| SRTF (*Shortest Remaining Time First*) | 1. Interrompe-se o processo em execução se surgir um mais curto<br />2. Fila dos processos é organizada consoante o tempo estimado de execução <br />3. Forma semelhante ao SJF, sendo processados primeiros os menos *jobs* |
| *Preemptive Priority Scheduling*       | 1. Associa-se uma prioridade a cada processo (INTEIRO)<br />2. A ready queue é uma fila seriada por prioridades<br />3. Escalona sempre o processo na frente da fila<br />4. Se aparece um processo com maior prioridade do que o que está a executar faz a troca dos processos<br />PROBLEMA DE MORTE POR "FOME" - SOLUÇÃO AUMENTAR A PRIORIDADE DOS PROCESSOS POUCO A POUCO DE FORMA A QUE INEVITAVELMENTE EXECUTEM E TERMINEM |
| RR (*Round Robin*)                     | 1. Dá a cada processo um intervalo de tempo fixo de CPU de cada vez<br />2. Quando um processo esgota o seu quanto retira-o do CPU e volta a colocá-lo no fim da fila<br />3. Ignorando os overheads do escalonamento, cada um dos n processos CPU-bound terá (1/n) do tempo disponível de CPU |

<br/>

#### 3. Programação Concorrente

- Os processos podem COOPERAR ENTRE SI ou COMPETIR POR RECURSOS (CPU, MEMORIA, ETC)

  - Em ambos os casos estamos a falar de SINCRONIZAÇÃO

    - COOPERAÇÃO - esperar até que o evento seja assinalado

    - COMPETIÇÃO - esperar até que o recurso esteja disponível

- SINCRONIZAR É FAZER ESPERAR, ATRASAR DELIBERADAMENTE UM PROCESSO ATÉ QUE UM DETERMINADO EVENTO SURJA

  - ESPERA PASSIVA

| Comunicação                                                  | Sincronização                                                |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Escrita/leitura dos dados através de vários mecanismos (ficheiros, memória partilhada...) | Coordenação de eventos entre processos (semáforos, variáveis de condição, locks, etc) de modo a garantir ordem na ocorrência desses eventos - SÓ LEIO DEPOIS DE ESCREVERES |

HÁ MECANISMOS QUE TRATAM DOS DOIS ASPETOS - PIPELINES, MENSAGENS, SOCKETS...

<br/>

#### Mecanismos de Sincronização

- Nas aulas teóricas usam-se semáforos como introdução e treino mental de controlo de concorrência

- Nas aulas práticas se usam *pipes* e *fifos*, que combinam comunicação e sincronização no mesmo mecanismo

Exclusão mútua é a ténica usada em programação concorrente para evitar que dois processos ou threads tenham acesso simultaneo a um recurso compartilhado -> REGIÃO CRÍTICA