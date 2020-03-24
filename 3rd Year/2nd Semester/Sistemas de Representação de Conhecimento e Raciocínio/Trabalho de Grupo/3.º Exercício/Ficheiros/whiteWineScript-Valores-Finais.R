#######################################################################
## Bibliotecas a utilizar
library( neuralnet )
library( hydroGOF )
library( leaps )
library( arules )
##
#######################################################################
## ler dataset de um ficheiro csv
dadosWhite <- read.csv("C:\\Users\\User\\Documents\\SRCR\\TP3\\winequality-white-normal.csv",header=TRUE, sep=";",dec=".")
##
#######################################################################
## definição de uma fórumla geral (com todos os atributos) para calcular os atributos mais significativos
formula00 <- quality ~ fixed.acidity + volatile.acidity + citric.acid + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + density + pH + sulphates + alcohol
##
#######################################################################
# seleção de variáveis mais significativas - white wine
selecao.white <- regsubsets(formula00,dadosWhite,nvmax=15,method = "backward")
summary(selecao.white)
##
#######################################################################
##
## As diferentes fórmulas foram definidas a partir da tabela acima calculada (atributos mais significativos)
formula.white08 <- quality ~ volatile.acidity + residual.sugar + alcohol
##
#######################################################################
# dividir os dados iniciais em casos para treino...
treinoWhite <- dadosWhite[1:1960, ]
# ... e casos para teste:
testeWhite <- dadosWhite[1960:4898, ]
#######################################################################
##
teste.white08 <- subset(testeWhite, select = c("volatile.acidity" , "residual.sugar", "alcohol"))
##
#######################################################################
##
# treinar a rede neuronal para usar as variaveis de input e output, Isto serveria então de exemplo
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "sag", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=2)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.05, algorithm = "rprop+", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4,2), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=2)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4,2), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4,2), lifesign = "full", threshold = 0.1, algorithm = "sag", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4,2), lifesign = "full", threshold = 0.05, algorithm = "rprop+", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(5), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(5), lifesign = "full", threshold = 0.1, algorithm = "sag", rep=2)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(5), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(3,2), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(4,2), lifesign = "full", threshold = 0.05, algorithm = "sag", rep=3)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(5,2), lifesign = "full", threshold = 0.1, algorithm = "slr", rep=1)
rnacredito.white08 <- neuralnet( formula.white03, treinoWhite, hidden = c(5,3), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
##
#######################################################################
plot(rnacredito.red04, rep = "best")
##
#######################################################################
rnacredito.white08.resultados <- compute(rnacredito.white08, teste.white08)

resultados.white.08 <- data.frame(atual.white08 = testeWhite$quality, previsao.white08 = rnacredito.white08.resultados$net.result)

resultados.white.08$previsao.white08 <- round(resultados.white.08$previsao.white08, digits=0)

rmse(c(testeWhite$quality),c(resultados.white.08$previsao))
