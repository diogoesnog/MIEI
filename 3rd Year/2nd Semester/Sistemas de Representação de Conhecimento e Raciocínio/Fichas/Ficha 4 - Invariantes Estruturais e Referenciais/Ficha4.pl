% Resolução da Ficha Prática n.º 4

%---- Predicados necessários para o teste dos invariantes. ----%

% Extensao do predicado filho: Filho,Pai -> {V,F}
filho(joao,jose).
filho(jose,manuel).
filho(carlos,jose).

% Extensao do predicado pai: Pai,Filho -> {V,F}
pai(paulo,filipe).
pai(paulo,maria).

% Extensao do predicado avo: Avo,Neto -> {V,F}
avo(antonio,nadia).


pai(P,F) :- filho(F,P).
avo(A,N) :- filho(N,X), pai(A,X).  
neto(N,A) :- avo(A,N).

%--------------------------------------------------------------% 

% Alínea (i)
+filho( F,P ) :: (findall((F,P),(filho( F,P )),S),
                  comprimento(S,N), 
				  N == 1).

% Alínea (ii)
+pai( P,F ) :: (findall((P,F),(pai( P,F )),S),
                  comprimento(S,N), 
				  N == 1).

% Alínea (iii)
+neto( N,A ) :: (findall((N,A),(neto( N,A )),S),
                  comprimento(S,N), 
				  N == 1).


