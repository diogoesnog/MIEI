-- Permissão para fazer operações de remoção de dados.
SET SQL_SAFE_UPDATES = 0;

-- Escolher a base de dados necessária. Ter em conta que a linguagem MySQL não é case-sensitive.
USE Caderneta;

-- Exercício 5 ---

-- QUERY 1 --
SELECT Equipa, Posicao, Nome FROM Jogador ORDER BY Equipa, Posicao, Nome ASC;

-- QUERY 2 --
SELECT j.Nome
	FROM Jogador j, Cromo c 
    WHERE j.Nr = c.Jogador AND Adquirido = "N";

-- QUERY 3 --
SELECT Count(Jogador) FROM Cromo WHERE Adquirido = "N";

-- QUERY 4 -- 
SELECT c.Nr 
	FROM Cromo c, Jogador j, Equipa e
    WHERE   
    c.Jogador = j.Nr AND
	j.Equipa = e.Id AND 
    (e.Designacao = "Clube de Futebol os Belenenses" OR
    e.Designacao = "Vitória Sport Clube");
