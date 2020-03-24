% Resolução da Ficha Prática n.º 2

% Alínea (i)
soma(X,Y,R) :- R is X+Y.

% Alínea (ii)
somaVarios(X,Y,Z,R) :- R is X+Y+Z.

% Alínea (iii)
% Extensão do predicado somaValores: ConjuntoValores,Resultado -> {V,F}
somaValores([],0).
somaValores([X|L],R) :- somaValores(L,R1), R is X+R1.

% Alínea (iv)
operacao(X,Y,+,R) :- R is X+Y.
operacao(X,Y,*,R) :- R is X*Y.
operacao(X,Y,:,R) :- Y\=0, R is X/Y.
operacao(X,Y,-,R) :- R is X-Y.	

% Alínea (v)

subtracao(X,Y,R) :- R is X-Y.
multiplicacao(X,Y,R) :- R is X*Y.
divisao(X,Y,R) :- R is X/Y.

% Extensão do predicado subtracaoValores: ConjuntoValores,Resultado -> {V,F}
subtracaoValores([],0).
subtracaoValores([X|L],R) :- subtracaoValores(L,R1), R is X-R1.

% Extensão do predicado multiplicacaoValores: ConjuntoValores,Resultado -> {V,F}
multiplicacaoValores([],1).
multiplicacaoValores([X|L],R) :- multiplicacaoValores(L,R1), R is X*R1.

% Extensão do predicado divisaoValores: ConjuntoValores,Resultado -> {V,F}
divisaoValores([],1).
divisaoValores([X|L],R) :- divisaoValores(L,R1), R is X/R1, R1\=0.

operacaoValores([X|L],+,R) :- somaValores(L,R1), R is X+R1.
operacaoValores([X|L],-,R) :- subtracaoValores(L,R1), R is X-R1.
operacaoValores([X|L],*,R) :- multiplicacaoValores(L,R1), R is X*R1.
operacaoValores([X|L],:,R) :- divisaoValores(L,R1), R is X/R1.

% Alínea (vi)
maior(X,Y,R) :- X>Y, R is X.
maior(X,Y,R) :- X<=Y, R is Y.

% Alínea (vii)
maior(X,Y,Z,R) :- X>=Y, X>=Z, R is X.
maior(X,Y,Z,R) :- Y>=X, Y>=Z, R is Y.
maior(X,Y,Z,R) :- Z>=X, Z>=Y, R is Z.

% Alínea (ix)
menor(X,Y,R) :- X=<Y, R is X.
menor(X,Y,R) :- X>=Y, R is Y.

%Alínea (x)
menor(X,Y,Z,R) :- X=<Y, X=<Z, R is X.
menor(X,Y,Z,R) :- Y=<X, Y=<Z, R is Y.
menor(X,Y,Z,R) :- Z=<X, Z=<Y, R is Z.

