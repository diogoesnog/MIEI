#######################################################################
## Bibliotecas a utilizar
library( neuralnet )
library( hydroGOF )
library( leaps )
library( arules )
##
#######################################################################
## ler dataset de um ficheiro csv
dadosRed <- read.csv("C:\\Users\\diogo\\Google Drive\\Universidade\\Engenharia Informática\\3º Ano\\2º Semestre\\SRCR\\Trabalho de Grupo\\3.º Exercício\\Ficheiros\\winequality-red-normal.csv",header=TRUE, sep=";",dec=".")
##
#######################################################################
## definição de uma fórumla geral (com todos os atributos) para calcular os atributos mais significativos
formula00 <- quality ~ fixed.acidity + volatile.acidity + citric.acid + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + density + pH + sulphates + alcohol
##
#######################################################################
# seleção de variáveis mais significativas - red wine (não há necessidade de alterar parametros aqui, creio que também não é necessário explicar no relatório)
selecao.red <- regsubsets(formula00,dadosRed,nvmax=15,method = "backward")
summary(selecao.red)
##
# seleção de variáveis mais significativas - white wine
##
#######################################################################
##
## As diferentes fórmulas foram definidas a partir da tabela acima calculada (atributos mais significativos)
formula.red03 <- quality ~ volatile.acidity + sulphates + alcohol
##
#######################################################################
# dividir os dados iniciais em casos para treino...
treinoRed <- dadosRed[1:640, ]
# ... e casos para teste:
testeRed <- dadosRed[641:1599, ]
#######################################################################
##
teste.red03 <- subset(testeRed, select = c("volatile.acidity","sulphates","alcohol"))
######################################################################
##
# treinar a rede neuronal para usar as variaveis de input e output, Isto serveria então de exemplo
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "sag", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=2)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.05, algorithm = "rprop+", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4,2), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=2)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4,2), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4,2), lifesign = "full", threshold = 0.1, algorithm = "sag", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4,2), lifesign = "full", threshold = 0.05, algorithm = "rprop+", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(5), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(5), lifesign = "full", threshold = 0.1, algorithm = "sag", rep=2)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(5), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(3,2), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4,2), lifesign = "full", threshold = 0.05, algorithm = "sag+", rep=3)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(5,2), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(5,3), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
##
#######################################################################
rnacredito.red03.resultados <- compute(rnacredito.red03, teste.red03)

resultados.red.03 <- data.frame(atual.red03 = testeRed$quality, previsao.red03 = rnacredito.red03.resultados$net.result)

resultados.red.03$previsao.red03 <- round(resultados.red.03$previsao.red03, digits=0)

rmse(c(testeRed$quality),c(resultados.red.03$previsao))

