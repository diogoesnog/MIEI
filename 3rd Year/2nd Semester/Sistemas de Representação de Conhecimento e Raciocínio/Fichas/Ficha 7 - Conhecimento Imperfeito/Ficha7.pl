% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).
:- dynamic '-'/1.

% i)
jogo(1,aa,500).
-jogo(Id,Arb,Ajc) :- nao(jogo(Id,Arb,Ajc)), nao(excecao(jogo(Id,Arb,Ajc))).

% ii)
jogo(2,bb,desc).
excecao(jogo(N,A,V)) :- jogo(N,A,desc).
nulointerdito(desc).

% iii)
jogo(3,cc,desc).
excecao(jogo(3,cc,500)).
excecao(jogo(3,cc,2500)).

% iv)
jogo(4,dd,desc).
excecao(jogo(I,A,Ajudas)) :- Ajudas >=250, Ajudas <=750. 

% v)
jogo(5,ee,des).
excecao(jogo(N,A,V)) :- jogo(N,A,valor).

nulointerdito(valor.)

% vi)




% Extensao do meta-predicado nao: Questao -> {V,F}
nao(Questao) :- Questao, !, fail.
nao(Questao).

%-------------------------------------------------------------------------------------------------
% Extensao do meta-predicado demo: Questao,Resposta -> {V,F}
demo( Questao,verdadeiro ) :-
    Questao.
demo( Questao,falso ) :-
    -Questao.
demo( Questao,desconhecido ) :-
    nao( Questao ),
    nao( -Questao ).