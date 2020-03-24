ave(pitigui).
ave(canario).
ave(periquito).
ave(avestruz).
ave(pinguim).

e_um(silvestre,mamifero).
e_um(cao,mamifero).
e_um(gato,mamifero).
e_um(morcego,mamifero).

e_um(piupiu,canario).
e_um(boby,cao).
e_um(trux,avestruz).
e_um(pingu,pinguim).
e_um(batemene,morcego).


ave(X):-
	voa(X).

mamifero(X):-
	-voa(X).

e_um(X,Z) :-
	e_um(Y,Z).
	