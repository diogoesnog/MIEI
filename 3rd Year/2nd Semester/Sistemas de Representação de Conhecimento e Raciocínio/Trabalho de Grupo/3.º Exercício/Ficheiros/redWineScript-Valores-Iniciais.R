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
formula.red01 <- quality ~ alcohol
formula.red02 <- quality ~ volatile.acidity + alcohol
formula.red03 <- quality ~ volatile.acidity + sulphates + alcohol
formula.red04 <- quality ~ volatile.acidity + total.sulfur.dioxide + sulphates + alcohol
formula.red05 <- quality ~ volatile.acidity + chlorides + total.sulfur.dioxide + sulphates + alcohol
formula.red06 <- quality ~ volatile.acidity + chlorides + total.sulfur.dioxide + pH + sulphates + alcohol
formula.red07 <- quality ~ volatile.acidity + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + pH + sulphates + alcohol
formula.red08 <- quality ~ volatile.acidity + citric.acid + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + pH + sulphates + alcohol
formula.red09 <- quality ~ volatile.acidity + citric.acid + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + pH + sulphates + alcohol
formula.red10 <- quality ~ fixed.acidity + volatile.acidity + citric.acid + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + pH + sulphates + alcohol   
formula.red11 <- quality ~ fixed.acidity + volatile.acidity + citric.acid + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide + density + pH + sulphates + alcohol
##
#######################################################################
# dividir os dados iniciais em casos para treino...
treinoRed <- dadosRed[1:640, ]
# ... e casos para teste:
testeRed <- dadosRed[641:1599, ]

#######################################################################
##
teste.red01 <- subset(testeRed, select = c("alcohol"))
teste.red02 <- subset(testeRed, select = c("volatile.acidity","alcohol"))
teste.red03 <- subset(testeRed, select = c("volatile.acidity","sulphates","alcohol"))
teste.red04 <- subset(testeRed, select = c("volatile.acidity","total.sulfur.dioxide","sulphates","alcohol"))
teste.red05 <- subset(testeRed, select = c("volatile.acidity","chlorides","total.sulfur.dioxide","sulphates","alcohol"))
teste.red06 <- subset(testeRed, select = c("volatile.acidity","chlorides","total.sulfur.dioxide","pH","sulphates","alcohol"))
teste.red07 <- subset(testeRed, select = c("volatile.acidity","chlorides","free.sulfur.dioxide","total.sulfur.dioxide","pH","sulphates","alcohol"))
teste.red08 <- subset(testeRed, select = c("volatile.acidity","citric.acid","chlorides","free.sulfur.dioxide","total.sulfur.dioxide","pH","sulphates","alcohol"))
teste.red09 <- subset(testeRed, select = c("volatile.acidity","citric.acid","residual.sugar","chlorides","free.sulfur.dioxide","total.sulfur.dioxide","pH","sulphates","alcohol"))
teste.red10 <- subset(testeRed, select = c("fixed.acidity","volatile.acidity","citric.acid","residual.sugar","chlorides","free.sulfur.dioxide","total.sulfur.dioxide","pH","sulphates","alcohol"))
teste.red11 <- subset(testeRed, select = c("fixed.acidity","volatile.acidity","citric.acid","residual.sugar","chlorides","free.sulfur.dioxide","total.sulfur.dioxide","density","pH","sulphates","alcohol"))
#######################################################################
##
# treinar a rede neuronal para usar as variaveis de input e output, Isto serveria então de exemplo
rnacredito.red01 <- neuralnet( formula.red01, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red02 <- neuralnet( formula.red02, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red03 <- neuralnet( formula.red03, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red04 <- neuralnet( formula.red04, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red05 <- neuralnet( formula.red05, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red06 <- neuralnet( formula.red06, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red07 <- neuralnet( formula.red07, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red08 <- neuralnet( formula.red08, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red09 <- neuralnet( formula.red09, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red10 <- neuralnet( formula.red10, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
rnacredito.red11 <- neuralnet( formula.red11, treinoRed, hidden = c(4), lifesign = "full", threshold = 0.1, algorithm = "rprop+", rep=1)
##
#######################################################################
plot(rnacredito.red04, rep = "best")
##
#######################################################################
rnacredito.red01.resultados <- compute(rnacredito.red01, teste.red01)
rnacredito.red02.resultados <- compute(rnacredito.red02, teste.red02)
rnacredito.red03.resultados <- compute(rnacredito.red03, teste.red03)
rnacredito.red04.resultados <- compute(rnacredito.red04, teste.red04)
rnacredito.red05.resultados <- compute(rnacredito.red05, teste.red05)
rnacredito.red06.resultados <- compute(rnacredito.red06, teste.red06)
rnacredito.red07.resultados <- compute(rnacredito.red07, teste.red07)
rnacredito.red08.resultados <- compute(rnacredito.red08, teste.red08)
rnacredito.red09.resultados <- compute(rnacredito.red09, teste.red09)
rnacredito.red10.resultados <- compute(rnacredito.red10, teste.red10)
rnacredito.red11.resultados <- compute(rnacredito.red11, teste.red11)

resultados.red.01 <- data.frame(atual.red01 = testeRed$quality, previsao.red01 = rnacredito.red01.resultados$net.result)
resultados.red.02 <- data.frame(atual.red02 = testeRed$quality, previsao.red02 = rnacredito.red02.resultados$net.result)
resultados.red.03 <- data.frame(atual.red03 = testeRed$quality, previsao.red03 = rnacredito.red03.resultados$net.result)
resultados.red.04 <- data.frame(atual.red04 = testeRed$quality, previsao.red04 = rnacredito.red04.resultados$net.result)
resultados.red.05 <- data.frame(atual.red05 = testeRed$quality, previsao.red05 = rnacredito.red05.resultados$net.result)
resultados.red.06 <- data.frame(atual.red06 = testeRed$quality, previsao.red06 = rnacredito.red06.resultados$net.result)
resultados.red.07 <- data.frame(atual.red07 = testeRed$quality, previsao.red07 = rnacredito.red07.resultados$net.result)
resultados.red.08 <- data.frame(atual.red08 = testeRed$quality, previsao.red08 = rnacredito.red08.resultados$net.result)
resultados.red.09 <- data.frame(atual.red09 = testeRed$quality, previsao.red09 = rnacredito.red09.resultados$net.result)
resultados.red.10 <- data.frame(atual.red10 = testeRed$quality, previsao.red10 = rnacredito.red10.resultados$net.result)
resultados.red.11 <- data.frame(atual.red11 = testeRed$quality, previsao.red11 = rnacredito.red11.resultados$net.result)

resultados.red.01$previsao.red01 <- round(resultados.red.01$previsao.red01, digits=0)
resultados.red.02$previsao.red02 <- round(resultados.red.02$previsao.red02, digits=0)
resultados.red.03$previsao.red03 <- round(resultados.red.03$previsao.red03, digits=0)
resultados.red.04$previsao.red04 <- round(resultados.red.04$previsao.red04, digits=0)
resultados.red.05$previsao.red05 <- round(resultados.red.05$previsao.red05, digits=0)
resultados.red.06$previsao.red06 <- round(resultados.red.06$previsao.red06, digits=0)
resultados.red.07$previsao.red07 <- round(resultados.red.07$previsao.red07, digits=0)
resultados.red.08$previsao.red08 <- round(resultados.red.08$previsao.red08, digits=0)
resultados.red.09$previsao.red09 <- round(resultados.red.09$previsao.red09, digits=0)
resultados.red.10$previsao.red10 <- round(resultados.red.10$previsao.red10, digits=0)
resultados.red.11$previsao.red11 <- round(resultados.red.11$previsao.red11, digits=0)

rmse(c(testeRed$quality),c(resultados.red.01$previsao))
rmse(c(testeRed$quality),c(resultados.red.02$previsao))
rmse(c(testeRed$quality),c(resultados.red.03$previsao))
rmse(c(testeRed$quality),c(resultados.red.04$previsao))
rmse(c(testeRed$quality),c(resultados.red.05$previsao))
rmse(c(testeRed$quality),c(resultados.red.06$previsao))
rmse(c(testeRed$quality),c(resultados.red.07$previsao))
rmse(c(testeRed$quality),c(resultados.red.08$previsao))
rmse(c(testeRed$quality),c(resultados.red.09$previsao))
rmse(c(testeRed$quality),c(resultados.red.10$previsao))
rmse(c(testeRed$quality),c(resultados.red.11$previsao))
