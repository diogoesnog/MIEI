% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).
:- dynamic '-'/1.


% Extensao do meta-predicado nao: Questao -> {V,F}
nao(Questao) :- Questao, !, fail.
nao(Questao).

% Extensao do meta-predicado demo: Questao,Resposta -> {V,F}
demo( Questao,verdadeiro ) :-
    Questao.
demo( Questao,falso ) :-
    -Questao.
demo( Questao,desconhecido ) :-
    nao( Questao ),
    nao( -Questao ).

O filho do Eurico nasceu no dia 5 de maio de 2010?
demo(nascimento(F,5/5/2010),filho(Eurico,F),R).

A virgula é uma conjunção. Neste caso, temos um conjunto de subquestoes, 
impostas pela virgula. O nosso predicado demo não tem a capacidade
para tratar de mais do que uma questão ao mesmo tempo.