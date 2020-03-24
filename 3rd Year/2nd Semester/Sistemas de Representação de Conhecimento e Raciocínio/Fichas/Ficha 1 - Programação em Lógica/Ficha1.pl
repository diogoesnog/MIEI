% Resolução da Ficha Prática n.º 1

% Alínea (i), (ii) e (iii)
% Extensão do predicado filho: Filho,Pai -> {V,F}
filho(joao,jose).
filho(joao,jose).
filho(jose,manuel).
filho(carlos,jose).

% Alínea (iv) e (v)
% Extensão do predicado pai: Pai,Filho -> {V,F}
pai(paulo,filipe).
pai(paulo,maria).

% Alínea (vi)
% Extensão do predicado avo: Avo,Neto -> {V,F}
avo(antonio,nadia).

% Alínea (vii), (viii), (ix) e (x)
% Extensão do predicado masculino: Pessoa -> {V,F}
masculino(joao).
masculino(jose).
feminino(maria).
feminino(joana).

% Alínea (xi)
pai(P,F) :- filho(F,P).

% Alínea (xii)
avo(A,N) :- filho(N,X), pai(A,X).  

% Alínea (xiii)
% Extensão do predicado neto: Neto,Avo -> {V,F}
neto(N,A) :- avo(A,N).

% Alínea (xiv)
% Extensão do predicado descente: Descendente,Ascendente -> {V,F}
descendente(D,A) :- filho(D,A).
descendente(D,A) :- pai(D,A).
descendente(D,A) :- filho(D,X), descendente(X,A).
descendente(D,A) :- pai(A,X), descendente(D,X).

% Alínea (xv)
% Extensão do predicado descente: Descendente,Ascendente -> {V,F}
descendente(D,A,1) :- filho(D,A).
descendenteC(D,A,1) :- pai(A,D).
descendente(D,A,G) :- filho(D,X), descendente(X,A,N).
descendenteC(D,A,G) :- pai(A,X), descendenteC(D,X,N).
G is N+1.

% Alínea (xvii)
% Extensão do predicado bisavo: Bisavo,Bisneto -> {V,F}
bisavo(X,Y) :- neto(Y,A), pai(X,A).

% Alínea (xviii)
% Extensão do predicado trisavo: Trisavo,Trisneto -> {V,F}
trisavo(X,Y) :- bisavo(A,Y), pai(X,A).

% Alínea (xix)
% Extensão do predicado tetraneto: TetraNeto,Tetravo -> {V,F}
tetraneto(X,Y) :- trisavo(Y,D), filho(X,D).

