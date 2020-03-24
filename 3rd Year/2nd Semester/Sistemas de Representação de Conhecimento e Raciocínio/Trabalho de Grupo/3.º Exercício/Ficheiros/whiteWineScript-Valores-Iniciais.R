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
formula.white01 <- quality ~ alcohol
formula.white02 <- quality ~ volatile.acidity + alcohol
formula.white03 <- quality ~ volatile.acidity + residual.sugar + alcohol
formula.white04 <- quality ~ volatile.acidity + residual.sugar + density + alcohol
formula.white05 <- quality ~ volatile.acidity + residual.sugar + density + pH + alcohol
formula.white06 <- quality ~ volatile.acidity + residual.sugar + density + pH + sulphates + alcohol
formula.white07 <- quality ~ volatile.acidity + residual.sugar + free.sulfur.dioxide + density + pH + sulphates + alcohol
formula.white08 <- quality ~ fixed.acidity + volatile.acidity + residual.sugar + free.sulfur.dioxide + density + pH + sulphates + alcohol
formula.white09 <- quality ~ fixed.acidity + volatile.acidity + residual.sugar + free.sulfur.dioxide + total.sulfur.dioxide + density + pH + sulphates + alcohol
formula.white10 <- quality ~ fixed.acidity + volatile.acidity + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + density + pH + sulphates + alcohol   
formula.white11 <- quality ~ fixed.acidity + volatile.acidity + citric.acid + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + density + pH + sulphates + alcohol
##
#######################################################################

# dividir os dados iniciais em casos para treino...
treinoWhite <- dadosWhite[1:1960, ]
# ... e casos para teste:
testeWhite <- dadosWhite[1960:4898, ]
#######################################################################
##
teste.white01 <- subset(testeWhite, select = c("alcohol"))
teste.white02 <- subset(testeWhite, select = c("volatile.acidity", "alcohol"))
teste.white03 <- subset(testeWhite, select = c("volatile.acidity" , "residual.sugar" , "alcohol"))
teste.white04 <- subset(testeWhite, select = c("volatile.acidity" , "residual.sugar" , "density" , "alcohol"))
teste.white05 <- subset(testeWhite, select = c("volatile.acidity" , "residual.sugar" , "density" , "pH" , "alcohol"))
teste.white06 <- subset(testeWhite, select = c("volatile.acidity" , "residual.sugar" , "density" , "pH" , "sulphates" , "alcohol"))
teste.white07 <- subset(testeWhite, select = c("volatile.acidity" , "residual.sugar" , "free.sulfur.dioxide" , "density" , "pH" , "sulphates" , "alcohol"))
teste.white08 <- subset(testeWhite, select = c("fixed.acidity" , "volatile.acidity" , "residual.sugar" , "free.sulfur.dioxide" , "density" , "pH" , "sulphates" , "alcohol"))
teste.white09 <- subset(testeWhite, select = c("fixed.acidity" , "volatile.acidity" , "residual.sugar" , "free.sulfur.dioxide" , "total.sulfur.dioxide" , "density" , "pH" , "sulphates" , "alcohol"))
teste.white10 <- subset(testeWhite, select = c("fixed.acidity" , "volatile.acidity" , "residual.sugar" , "chlorides" , "free.sulfur.dioxide" , "total.sulfur.dioxide" , "density" , "pH" , "sulphates" , "alcohol"))
teste.white11 <- subset(testeWhite, select = c("fixed.acidity" , "volatile.acidity" , "citric.acid" , "residual.sugar" , "chlorides" , "free.sulfur.dioxide" , "total.sulfur.dioxide" , "density" , "pH" , "sulphates" , "alcohol"))
##
#######################################################################
##
# treinar a rede neuronal para usar as variaveis de input e output, Isto serveria então de exemplo
rnacredito.white01 <- neuralnet( formula.white01, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white02 <- neuralnet( formula.white02, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white03 <- neuralnet( formula.white03, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white04 <- neuralnet( formula.white04, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white05 <- neuralnet( formula.white05, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white06 <- neuralnet( formula.white06, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white07 <- neuralnet( formula.white07, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white08 <- neuralnet( formula.white08, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white09 <- neuralnet( formula.white09, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white10 <- neuralnet( formula.white10, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.white11 <- neuralnet( formula.white11, treinoWhite, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
##
#######################################################################
plot(rnacredito.red04, rep = "best")
##
#######################################################################
rnacredito.white01.resultados <- compute(rnacredito.white01, teste.white01)
rnacredito.white02.resultados <- compute(rnacredito.white02, teste.white02)
rnacredito.white03.resultados <- compute(rnacredito.white03, teste.white03)
rnacredito.white04.resultados <- compute(rnacredito.white04, teste.white04)
rnacredito.white05.resultados <- compute(rnacredito.white05, teste.white05)
rnacredito.white06.resultados <- compute(rnacredito.white06, teste.white06)
rnacredito.white07.resultados <- compute(rnacredito.white07, teste.white07)
rnacredito.white08.resultados <- compute(rnacredito.white08, teste.white08)
rnacredito.white09.resultados <- compute(rnacredito.white09, teste.white09)
rnacredito.white10.resultados <- compute(rnacredito.white10, teste.white10)
rnacredito.white11.resultados <- compute(rnacredito.white11, teste.white11)

resultados.white.01 <- data.frame(atual.white01 = testeWhite$quality, previsao.white01 = rnacredito.white01.resultados$net.result)
resultados.white.02 <- data.frame(atual.white02 = testeWhite$quality, previsao.white02 = rnacredito.white02.resultados$net.result)
resultados.white.03 <- data.frame(atual.white03 = testeWhite$quality, previsao.white03 = rnacredito.white03.resultados$net.result)
resultados.white.04 <- data.frame(atual.white04 = testeWhite$quality, previsao.white04 = rnacredito.white04.resultados$net.result)
resultados.white.05 <- data.frame(atual.white05 = testeWhite$quality, previsao.white05 = rnacredito.white05.resultados$net.result)
resultados.white.06 <- data.frame(atual.white06 = testeWhite$quality, previsao.white06 = rnacredito.white06.resultados$net.result)
resultados.white.07 <- data.frame(atual.white07 = testeWhite$quality, previsao.white07 = rnacredito.white07.resultados$net.result)
resultados.white.08 <- data.frame(atual.white08 = testeWhite$quality, previsao.white08 = rnacredito.white08.resultados$net.result)
resultados.white.09 <- data.frame(atual.white09 = testeWhite$quality, previsao.white09 = rnacredito.white09.resultados$net.result)
resultados.white.10 <- data.frame(atual.white10 = testeWhite$quality, previsao.white10 = rnacredito.white10.resultados$net.result)
resultados.white.11 <- data.frame(atual.white11 = testeWhite$quality, previsao.white11 = rnacredito.white11.resultados$net.result)

resultados.white.01$previsao.white01 <- round(resultados.white.01$previsao.white01, digits=0)
resultados.white.02$previsao.white02 <- round(resultados.white.02$previsao.white02, digits=0)
resultados.white.03$previsao.white03 <- round(resultados.white.03$previsao.white03, digits=0)
resultados.white.04$previsao.white04 <- round(resultados.white.04$previsao.white04, digits=0)
resultados.white.05$previsao.white05 <- round(resultados.white.05$previsao.white05, digits=0)
resultados.white.06$previsao.white06 <- round(resultados.white.06$previsao.white06, digits=0)
resultados.white.07$previsao.white07 <- round(resultados.white.07$previsao.white07, digits=0)
resultados.white.08$previsao.white08 <- round(resultados.white.08$previsao.white08, digits=0)
resultados.white.09$previsao.white09 <- round(resultados.white.09$previsao.white09, digits=0)
resultados.white.10$previsao.white10 <- round(resultados.white.10$previsao.white10, digits=0)
resultados.white.11$previsao.white11 <- round(resultados.white.11$previsao.white11, digits=0)

rmse(c(testeWhite$quality),c(resultados.white.01$previsao))
rmse(c(testeWhite$quality),c(resultados.white.02$previsao))
rmse(c(testeWhite$quality),c(resultados.white.03$previsao))
rmse(c(testeWhite$quality),c(resultados.white.04$previsao))
rmse(c(testeWhite$quality),c(resultados.white.05$previsao))
rmse(c(testeWhite$quality),c(resultados.white.06$previsao))
rmse(c(testeWhite$quality),c(resultados.white.07$previsao))
rmse(c(testeWhite$quality),c(resultados.white.08$previsao))
rmse(c(testeWhite$quality),c(resultados.white.09$previsao))
rmse(c(testeWhite$quality),c(resultados.white.10$previsao))
rmse(c(testeWhite$quality),c(resultados.white.11$previsao))
