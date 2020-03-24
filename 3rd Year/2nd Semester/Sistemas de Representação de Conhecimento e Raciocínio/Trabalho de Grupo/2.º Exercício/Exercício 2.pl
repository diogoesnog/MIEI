%----------------------------------------------------------------------------------------- SICStus PROLOG -----------------------------------------------------------------------------------------%

% Declarações Iniciais
:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).


% Definicões Iniciais
:- op( 900,xfy,'::' ).
:- dynamic utente/4.
:- dynamic prestador/4.
:- dynamic cuidado/5.
:- dynamic excecao/1.
:- dynamic nulo/1.
:- dynamic '-'/1.

%-------------------------------------------------------------------------------------- Conhecimento Perfeito -------------------------------------------------------------------------------------%

%-------------------------------------------------------------------------------------- Conhecimento Positivo -------------------------------------------------------------------------------------%

utente(6472,'Diogo Nogueira',20,'Fafe').
prestador(4343,'Navarro Silva','Dermatologia','Hospital Privado de Guimaraes').
cuidado(date(2018,11,12),6472,4343,'Carie',12).

%-------------------------------------------------------------------------------------- Conhecimento Negativo -------------------------------------------------------------------------------------%

-utente(1000,'Joaquim Nogueira',30,'Fanalicao').
-prestador(6666,'Joao Rodrigues','Agente','Hospital Privado de Guimaraes').
-cuidado(date(2018,11,12),3333,5555,'Carie',12).

%------------------------------------------------------------------------------------- Conhecimento Imperfeito ------------------------------------------------------------------------------------%

%-------------------------------------------------------------------------------- Conhecimento Incerto/Desconhecido -------------------------------------------------------------------------------%

% Desconhecimento da morada do Utente.
utente(6000,'Rodrigo Pires',60,morada_desconhecida).

% Exceção aasociada.
excecao(utente(IdU,Nome,Idade,Morada)) :- utente(IdU,Nome,Idade,morada_desconhecida).

% Extensão do predicado que permite a evolução do conhecimento imperfeito incerto: Termo -> {V,F}
evolucaoIncertoMorada(utente(IDU,Nome,Idade,Morada)) :- demo(utente(IDU,Nome,Idade,Morada), desconhecido),
														solucoes( ( excecao(utente(IDU,Nome,Idade,Morada)) :- utente(IDU,Nome,Idade,X)) , 
														(utente(IDU,Nome,Idade,X), nao(nulo(X)) ) , L), removeLista(L), remocao(utente(IDU,Nome,Idade,X)),
														evolucao(utente(IDU,Nome,Idade,Morada)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento da idade do Utente.
utente(6001,'Rodrigo Pires',idade_desconhecida,'Braga').

% Excecao associada.
excecao(utente(IdU,Nome,Idade,Morada)) :- utente(IdU,Nome,idade_desconhecida,Morada).

% Desconhecimento da idade do Utente, sabendo que não é 50.
utente(7770,'Allan Xavier',idade_desco,'Braga').

% Exceção associada.
excecao(utente(IdU,Nome,Idade,Morada)) :- utente(IdU,Nome,idade_desco,Morada).

% Negação.
-utente(7770,'Allan Xavier', 50,'Braga').

% Extensão do predicado que permite a evolução do conhecimento imperfeito incerto: Termo -> {V,F}
evolucaoIncertoIdade(utente(IDU,Nome,Idade,Morada)) :- demo(utente(IDU,Nome,Idade,Morada), desconhecido),
													   solucoes( ( excecao(utente(IDU,Nome,Idade,Morada)) :- utente(IDU,Nome,X,Morada)) , 
					  								   (utente(IDU,Nome,X,Morada), nao(nulo(X)) ) , L), removeLista(L),
													   remocao(utente(IDU,Nome,X,Morada)),
													   evolucao(utente(IDU,Nome,Idade,Morada)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento do nome do Utente.
utente(6002,nome_desconhecido,30,'Braga').

% Exceção associada,
excecao(utente(IdU,Nome,Idade,Morada)) :- utente(IdU,nome_desconhecido,Idade,Morada).

% Extensão do predicado que permite a evolução do conhecimento imperfeito desconhecido incerto: Termo -> {V,F}
evolucaoIncertoNome(utente(IDU,Nome,Idade,Morada)) :- demo(utente(IDU,Nome,Idade,Morada), desconhecido),
													  solucoes( ( excecao(utente(IDU,Nome,Idade,Morada)) :- utente(IDU,X,Idade,Morada)) , 
													  (utente(IDU,X,Idade,Morada), nao(nulo(X)) ) , L),
													  removeLista(L),
													  remocao(utente(IDU,X,Idade,Morada)),
													  evolucao(utente(IDU,Nome,Idade,Morada)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento do nome do Prestador.
prestador(9003,nome_nao_sei,'Dentista','Classaude Porto').

% Exceção associada.
excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,nome_nao_sei,Especialidade,Instituicao).

% Extensão do predicado que permite a evolucao do conhecimento imperfeito desconhecido: Termo -> {V,F}
evolucaoIncertoNome(prestador(IDP,Nome,Especialidade,Instituicao)) :- demo(prestador(IDP,Nome,Especialidade,Instituicao), desconhecido),
																solucoes( ( excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,X,Especialidade,Instituicao)) , 
					  											(prestador(IDP,X,Especialidade,Instituicao), nao(nulo(X)) ) , L), removeLista(L),
															    remocao(prestador(IDP,X,Especialidade,Instituicao)),
																evolucao(prestador(IDP,Nome,Especialidade,Instituicao)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento da especialidade do Prestador.
prestador(9001,'Rui Alberto',especialidade_desconhecida,'Hospital').

% Exceção associada.
excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,Nome,especialidade_desconhecida,Instituicao).

% Extensão do predicado que permite a evolução do conhecimento imperfeito incerto: Termo -> {V,F}
evolucaoIncertoEspecialidade(prestador(IDP,Nome,Especialidade,Instituicao)) :- demo(prestador(IDP,Nome,Especialidade,Instituicao), desconhecido),
																			solucoes( ( excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,Nome,X,Instituicao)) , 
					  														(prestador(IDP,Nome,X,Instituicao), nao(nulo(X)) ) , L), removeLista(L), remocao(prestador(IDP,Nome,X,Instituicao)),
																			evolucao(prestador(IDP,Nome,Especialidade,Instituicao)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento da instituicão do Prestador, sabendo que não é Classaude Porto.
prestador(9002,'Rui Alberto','Dentista',instituicao_desconhecida).

% Exceção associada.
excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,Nome,Especialidade,instituicao_desconhecida).

% Negação.
-prestador(9002,'Rui Alberto','Dentista','Classaude Porto').

% Extensão do predicado que permite a evolução do conhecimento imperfeito incerto: Termo -> {V,F}
evolucaoIncertoInstituicao(prestador(IDP,Nome,Especialidade,Instituicao)) :- demo(prestador(IDP,Nome,Especialidade,Instituicao), desconhecido),
																	  solucoes( ( excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,Nome,Especialidade,X)) , 
																	  (prestador(IDP,Nome,Especialidade,Instituicao), nao(nulo(X)) ) ,  L),
																	  removeLista(L),remocao(prestador(IDP,Nome,Especialidade,X)),
																	  evolucao(prestador(IDP,Nome,Especialidade,Instituicao)).


%------------------------------------------------------------------------------------- Conhecimento Impreciso -------------------------------------------------------------------------------------%

% Desconhecimento do nome do Utente, sabendo-se que é Joaquim Nogueira ou João Nogueira.
excecao(utente(1001,'Joaquim Nogueira',23,'Lisboa')).
excecao(utente(1001,'João Nogueira',23,'Lisboa')).

% Extensão do predicado que permite a evolucao do conhecimento imperfeito impreciso: Termo -> {V,F}
evolucaoImpreciso(utente(IDU,Nome,Idade,Cidade)) :- demo(utente(IDU,Nome,Idade,Cidade),desconhecido),
													solucoes(excecao(utente(IDU,N,I,C)), excecao(utente(IDU,N,I,C)),L),
													removeLista(L),
													evolucao(utente(IDU,Nome,Idade,Cidade)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento da especialidade exercida pelo Dr. Afonso Alves na clínica Classaude Porto, sabendo-se que é Nutricionismo, Ortopedia ou Psicologia.
excecao(prestador(9011,'Afonso Alves','Nutricionismo','Classaude Porto')).
excecao(prestador(9011,'Afonso Alves','Ortopedia','Classaude Porto')).
excecao(prestador(9011,'Afonso Alves','Psicologia','Classaude Porto')).

% Extensão do predicado que permite a evolucao do conhecimento imperfeito impreciso: Termo -> {V,F}
evolucaoImpreciso(prestador(IDP,Nome,Especialidade,Instituicao)):- demo(prestador(IDP,Nome,Especialidade,Instituicao),desconhecido),
																   solucoes(excecao(prestador(IDP,N,E,I)), excecao(prestador(IDP,N,E,I)),L),
																   removeLista(L),
																   evolucao(prestador(IDP,Nome,Especialidade,Instituicao)).

%--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

% Desconhecimento do custo de uma consutla no nome de Sara Costa, ocorrida no Hospital Privado de Guimarães, no dia 25 de Janeiro de 2018 pelo dentista João Araújo, sabendo-se que este custo é
% 30, 40 ou 45.
excecao(cuidado(date(2018,01,25),6252,3127,'Carie',30)).
excecao(cuidado(date(2018,01,25),6252,3127,'Carie',40)).
excecao(cuidado(date(2018,01,25),6252,3127,'Carie',45)).

% Extensão do predicado que permite a evolucao do conhecimento imperfeito impreciso: Termo -> {V,F}
evolucaoImpreciso(cuidado(Data,IDU,IDP,Descricao,Custo)):- demo(cuidado(Data,IDU,IDP,Descricao,Custo),desconhecido),
														   solucoes(  excecao(cuidado(D,IDU,IDP,Desc,C)),excecao(cuidado(D,IDU,IDP,Desc,C)) , L),
														   removeLista(L),
														   evolucao(cuidado(Data,IDU,IDP,Descricao,Custo)).



%------------------------------------------------------------------------------------- Conhecimento Interdito -------------------------------------------------------------------------------------%

% Impossibilidade de se saber uma determinada instituicão correspondente a um determinado Prestador.
prestador(1005,'Ricardo Almeida','Psiquiatria',instituicao_interdita).
excecao(prestador(IDP,Nome,Especialidade,Instituicao)) :- prestador(IDP,Nome,Especialidade,instituicao_interdita).
nulo(instituicao_interdita).

% Impossibilidade de se saber um determinado nome correspondente a um determinado Utente.
utente(9999,nome_interdito, 19, 'Fafe').
excecao(utente(ID,Nome,Idade,Cidade)) :- utente(ID,nome_interdito,Idade,Cidade).
nulo(nome_interdito).

%------------------------------------------------------------------------------------------- Invariantes ------------------------------------------------------------------------------------------%

%--------------------------------------------------------------------------------------- Conhecimento Perfeito ------------------------------------------------------------------------------------%

%-------------------------------------------------------------------------------------- Conhecimento Positivo -------------------------------------------------------------------------------------%

% Não permitir adicionar conhecimento quando se tem o conhecimento perfeito negativo oposto.
+utente(Id,N,I,M) :: nao(-utente(Id,N,I,M)).

+prestador(Id,N,E,I) :: nao(-prestador(Id,N,E,I)).

+cuidado(D,IU,IP,D,C) :: nao(-cuidado(D,IU,IP,D,C)).

% Impossivel adicionar exceções a conhecimento positivo.
+excecao(T) :: nao(T).


%--------------------------------------------------------------------------------------- Conhecimento Negativo -----------------------------------------------------------------------------------%

% Não permitir adicionar conhecimento se houver o conhecimento positivo perfeito oposto.
+(-T) :: nao(T).

% Não permitir adicionar conhecimento negativo repetido.
+(-T) :: (findall( T,(-T),S), comprimento(S,N), N < 2).

%-------------------------------------------------------------------------------------- Conhecimento Imperfeito ----------------------------------------------------------------------------------%

%--------------------------------------------------------------------------------------- Conhecimento Incerto ------------------------------------------------------------------------------------%

% Não permitir a adição de exceções que sejam repetidas.
+(excecao(T)) :: (findall( xcecao(T),excecao(T),S),comprimento(S,N), N < 2).

+(excecao(-T)) :: (findall(excecao(T),excecao(-T),S),comprimento(S,N), N < 2).

%-------------------------------------------------------------------------------------- Conhecimento Negativo -------------------------------------------------------------------------------------%

% Conhecimento Negativo - Negação Por Falha:
-utente(IdU, Nome, Idade, Morada) :- nao(utente(IdU,Nome,Idade,Morada)), nao(excecao(utente(IdU, Nome, Idade, Morada))).

-prestador(IDP,Nome,Especialidade,Instituicao) :- nao(prestador(IDP,Nome,Especialidade,Instituicao)), nao(excecao(prestador(IDP,Nome,Especialidade,Instituicao))).

-cuidado(Data,IDU,IDP,Desc,Custo) :- nao(cuidado(Data,IDU,IDP,Desc,Custo)), nao(excecao(cuidado(Data,IDU,IDP,Desc,Custo))).


%------------------------------------------------------------------------------------- Conhecimento Interdito -------------------------------------------------------------------------------------%

+utente(Id,Nome,I,C) :: ( solucoes( N, (utente(9999,N, 19, 'Fafe'), nao(nulo(N))), L), comprimento(L,R), R==0).


%-------------------------------------------------------------------------------------- Sistema de Inerência --------------------------------------------------------------------------------------%

% Extensao do meta-predicado demo: Questao,Resposta -> {V,F}
demo( Q,verdadeiro ) :- Q.
demo( Q,falso ) :- -Q.
demo( Q,desconhecido ) :- nao( Q ),nao( -Q ).


% Extenão do predicado demoComp: Lista, R -> {V,F,D}
demoComp([Q],R) :- demo(Q,R).
demoComp([Q1,ou,Q2|T], R) :-
	demo(Q1,R1),
	demoComp([Q2|T], R2),
	disjuncao(R1,R2,R).

demoComp([Q],R) :- demo(Q,R).
demoComp([Q1,e,Q2|T], R) :-
	demo(Q1,R1),
	demoComp([Q2|T], R2),
	conjuncao(R1,R2,R).


conjuncao(verdadeiro,verdadeiro,verdadeiro).
conjuncao(verdadeiro,desconhecido,desconhecido).
conjuncao(desconhecido,verdadeiro,desconhecido).
conjuncao(desconhecido,desconhecido,desconhecido).
conjuncao(falso,_,falso).
conjuncao(_,falso,falso).

disjuncao(verdadeiro,_,verdadeiro).
disjuncao(_,verdadeiro,verdadeiro).
disjuncao(falso,falso,falso).
disjuncao(falso,desconhecido,desconhecido).
disjuncao(desconhecido,falso,desconhecido).
disjuncao(desconhecido,desconhecido,desconhecido).



%-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

%---------------------------------------------------------------------------------- Base de Conhecimento Inicial ----------------------------------------------------------------------------------%
% Base de Conhecimento Utente (IDU,Nome,Idade,Cidade) -> {V,F,D}.
utente(1211,'Diogo Nogueira',21,'Porto').
utente(8374,'Tifany Silva',24,'Porto').
utente(3463,'Fabio Fontes',19,'Braga').
utente(2321,'Mariana Lino',20,'Guimaraes').
utente(9232,'Francisco Silva',21,'Braga').
utente(2372,'Cristina Lopes',22,'Fafe').
utente(7363,'Tiago Nogueira',18,'Porto').
utente(6252,'Sara Costa',18,'Porto').
utente(2373,'Joana Maria',28,'Braga').
utente(2324,'Joao Miguel',21,'Guimaraes').

% Base de Conhecimento Prestador:(IDP,Nome,Especialidade,Instituicao)->{V,F,D}.
prestador(3947,'Margarida Antunes','Dentista','Hospital Privado de Guimaraes').
prestador(3643,'Nuno Costa','Nutricao','Classaude Porto').
prestador(7364,'Ana Maria','Hidroterapia','Clinica Fisiatrica de Fafe').
prestador(3642,'Tomas Casimiro','Clínica Geral','Classaude Porto').
prestador(8675,'Maria Joana','Psiquiatria','Clinica Praxis Porto').
prestador(3742,'Joana Silva','Psicologia','Clinica Praxis Porto').
prestador(7864,'Ana Luisa','Dermatologia','Clinica Fisiatrica de Fafe').
prestador(7324,'Mariana Costa','Dentista','Clinica Fisiatrica de Fafe').
prestador(3127,'Joao Araujo','Dentista','Hospital Privado de Guimaraes').

% Base de Conhecimento Cuidado de Saúde (Data,IDU,IDP,Custo)->{V,F,D}.
cuidado(date(2017,10,25),8374,7324,'Consulta de rotina aparelho',20).
cuidado(date(2016,09,15),3463,7864,'Queimadura na cara',15).
cuidado(date(2018,11,12),6472,3742,'Consulta',50).
cuidado(date(2015,01,25),9232,8675,'Consulta agendada/rotina',55).
cuidado(date(2017,08,30),2372,3642,'Paciente com febre',15).
cuidado(date(2018,04,21),7363,7364,'Tratamento rotineiro',25).
cuidado(date(2016,06,08),6252,3643,'Consulta de iniciacao de tratamento dietetico',60).
cuidado(date(2017,12,24),2373,3947,'Remocao dos dentes do siso',55).
cuidado(date(2018,12,12),6472,4343,'Tratamento de eczema',60).

%------------------------------------------------------------------------------------------------%


%---------------------- Predicados de Evolução e Retrocesso de Conhecimento ---------------------%

% Inserção de Conhecimento.
insercao(Termo) :- assert(Termo).
insercao(Termo) :- retract(Termo),!,fail.

% Remoção de Conhecimento.
remocao(Termo) :- retract(Termo).
remocao(Termo) :- assert(Termo),!,fail.

% Teste.
teste([]).
teste([R|LR]) :- R,teste(LR).			

% Controlo da inserção de Conhecimento.
evolucao(Termo) :- findall(Invariante,+Termo::Invariante,Lista),
			            insercao(Termo),
			            teste(Lista).

% Controlo da remoção de Conhecimento.
retrocesso(Termo) :- Termo,
					 findall(Invariante,-Termo::Invariante,Lista),
			            remocao(Termo),
			            teste(Lista).	
%Soluções:
solucoes(X,Y,Z) :- findall(X,Y,Z).	            




%-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

%------------------------------------------------------------------------------------------ Invariantes -------------------------------------------------------------------------------------------%

% Não permitir a inserção de conhecimento repetido relativo ao Utente.
+utente(IdUt,Nome,Idade,Morada) :: (findall(IdUt,(utente(IdUt,_,_,_)),L),
								 comprimento(L,C), C =< 1).


% Não permitir a inserção de conhecimento repetido relativo ao Prestador.
+prestador(IdP,Nome,Especialidade,Instituicao) :: (findall(IdP,prestador(IdP,_,_,_),L),
												comprimento(L,C), C =< 1).


% Não permite a inserção de conhecimento que não exista na Base de Conhecimento.
+cuidado(D,IDU,IDP,C) :: (findall(IDU, utente(IDU,_,_,_), S),
						   comprimento(S,N), N == 1).
+cuidado(D,IDU,IDP,C) :: (findall(IDP, prestador(IDP,_,_,_), S),
						   comprimento(S,N), N == 1).


% Não permite a remoção de Utentes quando existe Cuidados de Saúde associados aos mesmos.
-utente(IDU,Nome,Idade,Morada) :: (findall(IDU,cuidado(_,IDU,_,_,_),L),
						 			comprimento(L,X),
									X == 0).

% Não permite a remoção de Prestadores quando existe Cuidados de Saúde associados aos mesmos.
-prestador(IDP,Nome,Especialidade,Instituicao) :: (findall(IDP,cuidado(_,_,IDP,_,_),L),
						 							comprimento(L,X),
						 							X == 0).



%-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------%

%------------------------------------------------------------------------------------ Predicados Auxiliares --------------------------------------------------------------------------------------%

% Permite calcular o comprimento de uma lista.
% Extensão do predicado comprimento : L, N ->{V,F}
comprimento([],0).
comprimento([X|L],R) :- comprimento(L,N), R is 1+N.

% Extensão do predicado removeLista : L ->{V,F}
removeLista([]).
removeLista([X|L]) :- retract(X),
					  removeLista(L).

% Extensao do meta-predicado nao: Questão -> {V,F}
nao(Q) :- Q, !, fail.
nao(Q).

