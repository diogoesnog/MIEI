% Resolução da Ficha Prática n.º 3

% Alínea (i)
% Extensão do predicado pertence: Elemento,Lista -> {V,F}
pertence(X,[X|L]).
pertence(X,[Y|L]) :- X\=Y, pertence(X,L).
