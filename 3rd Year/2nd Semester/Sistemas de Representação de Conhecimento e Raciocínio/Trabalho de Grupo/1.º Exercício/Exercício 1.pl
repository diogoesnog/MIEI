%--------------------------------------- SICStus PROLOG -----------------------------------------%

% Declarações Iniciais
:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

% Definicões Iniciais
:- op( 900,xfy,'::' ).
:- dynamic utente/4.
:- dynamic prestador/4.
:- dynamic cuidado/5.

%------------------------------------------------------------------------------------------------%



%--------------------------------- Base de Conhecimento Inicial ---------------------------------%

% Base de Conhecimento Utente (IDU,Nome,Idade,Cidade).
utente(6472,'Diogo Nogueira',20,'Fafe').
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

% Base de Conhecimento Prestador (IDP,Nome,Especialidade,Instituicao).
prestador(4343,'Navarro Silva','Dermatologia','Hospital Privado de Guimaraes').
prestador(3947,'Margarida Antunes','Dentista','Hospital Privado de Guimaraes').
prestador(3643,'Nuno Costa','Nutricao','Classaude Porto').
prestador(7364,'Ana Maria','Hidroterapia','Clinica Fisiatrica de Fafe').
prestador(3642,'Tomas Casimiro','Clínica Geral','Classaude Porto').
prestador(8675,'Maria Joana','Psiquiatria','Clinica Praxis Porto').
prestador(3742,'Joana Silva','Psicologia','Clinica Praxis Porto').
prestador(7864,'Ana Luisa','Dermatologia','Clinica Fisiatrica de Fafe').
prestador(7324,'Mariana Costa','Dentista','Clinica Fisiatrica de Fafe').
prestador(3127,'Joao Araujo','Dentista','Hospital Privado de Guimaraes').

% Base de Conhecimento Cuidado de Saúde (Data,IDU,IDP,Custo).
cuidado(date(2018,11,12),6472,4343,'Carie',12).
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

%------------------------------------------------------------------------------------------------%



%------------------------------------------ Invariantes -----------------------------------------%

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


%-------------------------------------------------------------------------------------------------%



%------------------------------------------ Predicados -------------------------------------------%


%------------------------------- Predicados de registo e remoção ---------------------------------%


% Extensão do predicado registar: Termo -> {V,F}
registar(T) :- evolucao(T).

% Extensão do predicado registarUtente: IdUt, Nome, Idade, Morada -> {V,F}
registarUtente(IdUt,Nome,Idade,Morada) :- 
		evolucao(utente(IdUt,Nome,Idade,Morada)).

% Extensão do predicado registarPrestador: IdP, Nome, Especialidade, Instituicao -> {V,F}
registarPrestador(IdP,Nome,Especialidade,Instituicao) :- 
		evolucao(prestador(IdUt,Nome,Idade,Morada)).

% Extensão do predicado registarCuidado: Data, IdUt, IdP, Descricao, Custo  -> {V,F}
registarCuidado(Data,IdUt,IdP,Descricao,Custo) :- 
		evolucao(cuidado(Data,IdUt,IdP,Descricao,Custo)).



% Extensão do predicado remover: Termo -> {V,F}
remover(T) :- retrocesso(T).

% Extensão do predicado removerUtente: IdUt, Nome, Idade, Morada -> {V,F}
removerUtente(IdUt,Nome,Idade,Morada) :- 
		retrocesso(utente(IdUt,Nome,Idade,Morada)).

% Extensão do predicado removerPrestador: IdP, Nome, Especialidade, Instituicao -> {V,F}
removerPrestador(IdP,Nome,Especialidade,Instituicao) :- 
		retrocesso(prestador(IdUt,Nome,Idade,Morada)).

% Extensão do predicado removerCuidado: Data, IdUt, IdP, Descricao, Custo  -> {V,F}
removerCuidado(Data,IdUt,IdP,Descricao,Custo) :- 
		retrocesso(cuidado(Data,IdUt,IdP,Descricao,Custo)).


%----------------------------- Predicados que listam Conhecimento --------------------------------%


%-------------------------- Identificar Utentes por critérios de seleção -------------------------%


% Extensão do predicado findUtentesN: Nome, R -> {V,F}
findUtentesN(Nome,R) :- 
		findall((IdU,Nome,Idade,Morada),utente(IdU,Nome,Idade,Morada),R).

% Extensão do predicado findUtentesI: Idade, R -> {V,F}
findUtentesI(Idade,R) :- 
		findall((IdU,Nome,Idade,Morada),utente(IdU,Nome,Idade,Morada),R).

% Extensão do predicado findUtentesM: Morada, R -> {V,F}
findUtentesM(Morada,R) :- 
		findall((IdU,Nome,Idade,Morada),utente(IdU,Nome,Idade,Morada),R).


%-------------------- Identificar instituições prestadoras de Cuidados de Saúde ------------------%


% Extensao do predicado findInstituicoes: R -> {V,F}.
findInstituicoes(R) :- findall(Instituicao,prestador(_,_,_,Instituicao),L), 
			removeDuplicados(L,R).


%----- Identificar Cuidados prestados por instituicão/cidade/datas prestadoras de Cuidados -------%


% Extensão do predicado cuidadoPorInst: Inst, R -> {V,F}
cuidadoPorInst(Inst,R) :- findall((IDP),prestador(IDP,_,_,Inst) , L),
					      cuiInstAux(L,R).

% Extensão do predicado cuiInstAux: L, R -> {V,F}
cuiInstAux([],[]).
cuiInstAux([IDP|T],R) :- findall((Data,IDU,IDP,D,C),cuidado(Data,IDU,IDP,D,C),L1),
						 concat(L1,L2,R),
					  	 cuiInstAux(T,L2).

% Extensão do predicado cuidadoPorCid: Cid, R -> {V,F}
cuidadoPorCid(Cid,R) :- findall((IDU),utente(IDU,_,_,Cid) , L),
					    cuiCidAux(L,R).

% Extensão do predicado cuiCidAux: L,R -> {V,F}
cuiCidAux([],[]).
cuiCidAux([IDU|T],R) :- findall((Data,IDU,IDP,D,C),cuidado(Data,IDU,IDP,D,C),L1),
						 concat(L1,L2,R),
					  	 cuiCidAux(T,L2).

% Extensão do predicado cuidadoPorData: Data, R -> {V,F}
cuidadoPorData(Data,R) :- findall((Data,IU,IP,D,C),(cuidado(Data,IU,IP,D,C)),R).


%----------------- Identificar Utentes de um prestador/especialidade/instituicão -----------------%


% Extensão do predicado utentePorPres: IDP, R -> {V,F}
utentePorPres(IDP,R) :- findall((IDU),cuidado(_,IDU,IDP,_,_),L),
						utePresAux(L,R).

% Extensão do predicado utePresAux: L, R -> {V,F}
utePresAux([],[]).
utePresAux([IDU|T],R) :- findall((IDU,Nome,I,C),utente(IDU,Nome,I,C),L1),
						 concat(L1,L2,R),
					  	 utePresAux(T,L2).

% Extensão do predicado utentePorEsp: Esp, R -> {V,F}
utentePorEsp(Esp,R) :- findall((IDP),prestador(IDP,_,Esp,_),L),
					   uteEspAux(L,X),
					   utePresAux(X,R).

% Extensão do predicado utentePorIns: Ins, R -> {V,F}
utentePorIns(Ins,R) :- findall((IDP),prestador(IDP,_,_,Ins),L),
					   uteEspAux(L,X),
					   utePresAux(X,R).

% Extensão do predicado uteEspAux: L, R -> {V,F}
uteEspAux([],[]).
uteEspAux([IDP|T],R) :- findall((IDU),cuidado(_,IDU,IDP,_,_),L1),
						concat(L1,L2,R),
					  	uteEspAux(T,L2).


%---------- Identificar Cuidados de Saúde realizador por utente/instituicao/prestador ------------%


% Extensão do predicado cuidadosPorUt: IDU, R -> {V,F}
cuidadosPorUt(IDU,R) :- findall((Data,IDU,IDP,X,Y),cuidado(Data,IDU,IDP,X,Y),R).

% Extensão do predicado cuidadosPorInst: Ins, R -> {V,F}
cuidadosPorInst(Inst,R) :- findall((IDP),prestador(IDP,_,_,Inst),L),
						   cuiInstAux(L,R).

% Extensão do predicado cuiInstAux: L, R -> {V,F}
cuiInstAux([],[]).
cuiInstAux([IDP|T],R) :- findall((Data,IDU,IDP,D,C),cuidado(Data,IDU,IDP,D,C),L1),
						 concat(L1,L2,R),
					  	 cuiInstAux(T,L2).

% Extensão do predicado cuidadosPorPres: IDU, R -> {V,F}
cuidadosPorPres(IDP,R) :- findall((Data,IDU,IDP,X,Y),cuidado(Data,IDU,IDP,X,Y),R).


%---------- Determinar todas as instituições/prestadores a quem um Utente já recorreu ------------%


% Extensão do predicado instituicoesPorUt: IDU, R -> {V,F}
instituicoesPorUt(IDU,R) :- findall((IDP),cuidado(_,IDU,IDP,_,_),L),
							instUtAux(L,X),
							removeDups(X,R).

% Extensão do predicado instUtAux: IDP, R -> {V,F}
instUtAux([],[]).
instUtAux([IDP|T],R) :- findall((Ins),prestador(IDP,_,_,Ins),L1),
						concat(L1,L2,R),
					  	instUtAux(T,L2).

% Extensão do predicado prestadoresPorUt: IDU, R -> {V,F}
prestadoresPorUt(IDU,R) :- findall((IDP),cuidado(_,IDU,IDP,_,_),L),
							presUtAux(L,X),
							removeDups(X,R).

% Extensão do predicado presUtAux: IDP, R -> {V,F}
presUtAux([],[]).
presUtAux([IDP|T],R) :- findall((IDP,N,E,Ins),prestador(IDP,N,E,Ins),L1),
						concat(L1,L2,R),
					  	presUtAux(T,L2).


%---- Calcular o custo total dos Cuidados de Saúde por Utente/Especialidade/Prestador/Datas ------%


% Extensão do predicado custoTotalUt: IDU, T -> {V,F}
custoTotalUt(IDU,T) :- findall((C),cuidado(_,IDU,_,_,C),L),
					   somaLista(L,T).

% Extensão do predicado custoTotalEsp: Esp, T -> {V,F}
custoTotalEsp(Esp,T) :- findall((IDP),prestador(IDP,_,Esp,_),L),
					   custoPrestador(L,X),
					   somaLista(X,T).

% Extensão do predicado presUtAux: IDP, R -> {V,F}
custoPrestador([],[]).
custoPrestador([IDP|T],R) :- findall((C),cuidado(_,_,IDP,_,C),L1),
						concat(L1,L2,R),
					  	custoPrestador(T,L2).

% Extensão do predicado custoTotalPres: IDP, T -> {V,F}
custoTotalPres(IDP,T) :- findall((C),cuidado(_,_,IDP,_,C),L),
						 somaLista(L,T). 


% Extensão do predicado custoTotalData: Data, T -> {V,F}
custoTotalData(Data,T) :- findall((C),cuidado(Data,_,_,_,C),L),
						 somaLista(L,T). 

%------------------------------------------------------------------------------------------------%



%------------------------------------------- Extras ----------------------------------------------%


%---------- Determinar todas as Moradas presentes na base de conhecimento sem repetições ---------%

% Extensão do predicado moradas: R -> {V,F} 
moradas(R) :- findall((Morada),utente(_,_,_,Morada),L),
			  removeDuplicados(L,R).


%-------------------- Determinar a lista de todos os custos totais dos Utentes -------------------%


% Extensão do predicado custoListaUt: L, R -> {V,F}
custoListaUt([],[]).
custoListaUt([IDU|T],R) :- findall(Custo, cuidado(_,IDU,_,_,Custo), L1),
							somaLista(L1,X),
							custoListaUt(T,L2),
							concat([X], L2, R).

% Extensão do predicado custoTodosUt: R -> {V,F}
custoTodosUt(R) :- findall((IDU), utente(IDU,_,_,_), L1),
					custoListaUt(L1,R).


%----------------------- Determinar o top 5 de Utentes que mais gastaram -------------------------%


% Extensão do predicado top5utentes: R -> {V,F}
top5utentes(R) :- findall(IDU, utente(IDU,_,_,_),L1),
					custoListaUt(L1,L2),
					concatPares(L2,L1,L3),
					sort(L3,L4),
					reversePares(L4,L5),
					top(L5,5,R).

%-------------------------------------------------------------------------------------------------%



%------------------------------------- Predicados Auxiliares -------------------------------------%

% Soma todos os elementos de uma lista.
% Extensão do predicado custoTotal: L, R -> {V,F}	
somaLista([],0).	
somaLista([H|T],R)	:- somaLista(T,X),
					   R is X+H.

% Concatena 2 listas.
% Extensao do predicado concat: L1, L2, L3 -> {V,F}  
concat( [],L,L ).
concat( [H|T],L2,[H|L] ) :- concat(T,L2,L).

% Concatena 2 listas em pares.
% Extensao do predicado concatPares: L1, L2, L3 -> {V,F} 
concatPares([],[],[]).
concatPares([X|L1],[Y|L2],[(X,Y)|R]) :- concatPares(L1,L2,R).


% Permite calcular o comprimento de uma lista.
% Extensão do predicado comprimento : L, N ->{V,F}
comprimento([],0).
comprimento([X|L],R) :- comprimento(L,N), R is 1+N.

% Remove os valores duplicados de uma lista.
% Extensão do predicado removeDuplicados : L, L1 ->{V,F}
removeDuplicados([],[]).
removeDuplicados([X|L],[H|R]) :- pertence(X,L), removeDuplicados(L,[H|R]).
removeDuplicados([X|L],[X|R]) :- n_pertence(X,L),removeDuplicados(L,R).

% Verifica se um dado Conhecimento pertence a uma lista.
% Extensão do predicado pertence: L, X -> {V,F}
pertence(X,[X|_]).
		     pertence(X,T).

n_pertence(X,L):- \+ pertence(X,L). % "\+" é o mesmo que "not"

% Inverte uma lista.
% Extensao do predicado reverse: L1, R -> {V,F} 
reverse([],[]).
reverse([H|T],L) :- reverse(T,P), concat(P,[H],L).

% Inverte uma lista de tuplos.
% Extensao do predicado reversePares: L1, R -> {V,F} 
reversePares([],[]).
reversePares([(X,Y)|T],L) :- reverse(T,P), concat(P,[(X,Y)],L).


% Delimita uma lista para um valor n.
% Extensao do predicado reverse: L1, N, R -> {V,F} 
top(X,0,[]).
top([X|T],N,[X|R]) :- N1 is N - 1, top(T,N1,R).


%------------------------------------------------------------------------------------------------%