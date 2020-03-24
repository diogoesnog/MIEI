-- Permissão para fazer operações de remoção de dados.
SET SQL_SAFE_UPDATES = 0;

-- Escolher a base de dados necessária. Ter em conta que a linguagem MySQL não é case-sensitive.
USE Caderneta;

-- Exercício 1 --

-- Sem INNER JOIN --
SELECT c.PagCaderneta FROM Cromo c, Jogador j, Equipa e, Posicao p
		WHERE 
        c.Jogador = j.Nr AND 
        j.equipa = e.Id AND
        j.Posicao = p.Id AND
        (e.Designacao = 'Sporting Clube de Braga' OR e.Designacao = 'Rio Ave Futebol Clube') AND
        p.Designacao = 'Defesa';
        
-- Com INNER JOIN --
SELECT c.PagCaderneta FROM Cromo AS c
		INNER JOIN Jogador AS j ON j.Nr = c.jogador
        INNER JOIN Equipa AS e ON e.Id = j.Equipa
        INNER JOIN Posicao AS p ON p.Id = j.Posicao
        WHERE (e.Designacao = 'Sporting Clube de Braga' OR e.Designacao = 'Rio Ave Futebol Clube')
        AND p.Designacao = 'Defesa';
        
-- Exercício 2 --

-- Sem INNER JOIN --
SELECT c.Nr FROM Cromo c, Jogador j, Posicao p, Equipa e
		WHERE c.Jogador = j.Nr
        AND j.Equipa = e.Id
        AND j.Posicao = p.Id
        AND (e.Treinador = 'Jorge Jesus' OR e.Treinador = 'Nuno Espírito Santo')
        AND NOT(p.Designacao = 'Médio' OR p.Designacao = 'Defesa')
        ORDER BY c.Nr ASC;
        
-- Com INNER JOIN --
SELECT c.Nr From Cromo AS c
		INNER JOIN Jogador AS j ON j.Nr = c.Jogador
        INNER JOIN Posicao AS p ON p.Id = j.Posicao
        INNER JOIN Equipa AS e ON e.Id = j.Equipa
        WHERE (e.Treinador = 'Jorge Jesus' OR e.Treinador = 'Nuno Espírito Santo')
        AND NOT(p.Designacao = 'Médio' OR p.Designacao = 'Defesa')
        ORDER BY c.Nr ASC;

-- Exercício 3 --

-- Sem INNER JOIN --
CREATE VIEW CromosEmFalta AS
		SELECT c.Nr, j.Nome, e.Designacao FROM Cromo c, Jogador j, Equipa e
		WHERE 
        c.Adquirido = 'N' AND
        c.Jogador = j.Nr AND
        j.Equipa = e.Id;

SELECT * FROM CromosEmFalta;

-- Com INNER JOIN --
CREATE VIEW ListaCromosEmFalta AS
	SELECT c.Nr, j.Nome, e.Designacao FROM Cromo AS c
    INNER JOIN Jogador AS j ON j.Nr = c.Jogador
    INNER JOIN Equipa AS e ON e.Id = j.Equipa
    WHERE c.Adquirido = 'N';
    
SELECT * FROM ListaCromosEmFalta;

-- Exercício 4 --
DELIMITER $$
CREATE PROCEDURE EquipaCromos (nome VARCHAR(45))
BEGIN
    SELECT * FROM Cromo AS c
    INNER JOIN Jogador AS j ON j.Nr = c.Jogador
    INNER JOIN Equipa AS e ON e.Id = j.Equipa
    WHERE e.Designacao = nome
    ORDER BY c.PagCaderneta,c.Nr ASC;
END $$

CALL EquipaCromos('Sporting Clube de Braga');

-- Exercício 5 --
DELIMITER $$
CREATE PROCEDURE CadernetaCompleta()
BEGIN
    SELECT c.Nr,t.Descricao,j.Nome,e.Designacao,c.Adquirido FROM Cromo AS c
    INNER JOIN Jogador AS j ON j.Nr = c.Jogador
    INNER JOIN Equipa AS e ON e.Id = j.Equipa
    INNER JOIN TipoCromo AS t ON t.Nr = c.Tipo;
END $$

CALL CadernetaCompleta;

-- Exercício 6 --
DELIMITER $$
CREATE FUNCTION CromoRepetido(idCromo INT)
	RETURNS CHAR(1)
BEGIN
	DECLARE repetido CHAR(1);
    SET repetido = (SELECT Adquirido FROM Cromo WHERE Nr = idCromo);
    RETURN repetido;
END $$

SELECT CromoRepetido(1);

-- Exercício 7 --
DELIMITER $$
CREATE FUNCTION DevolveCromo(IdCromo INT)
    RETURNS VARCHAR(250)
    BEGIN
      DECLARE tipo VARCHAR(20);
      DECLARE nome VARCHAR(75);
      DECLARE equipa VARCHAR(75);

      SET tipo = (SELECT t.Descricao FROM TipoCromo AS t
                      INNER JOIN Cromo AS c ON t.Nr = c.Tipo
                      WHERE c.Nr = IdCromo);

      SET nome = (SELECT j.Nome FROM Jogador AS j
                      JOIN Cromo AS c ON j.Nr = c.Jogador
                      WHERE c.Nr = IdCromo);

      SET equipa = (SELECT e.Designacao FROM Equipa AS e
                      JOIN Jogador AS j ON e.Id = j.Equipa
                      JOIN Cromo AS c ON j.Nr = c.Jogador
                      WHERE c.Nr = IdCromo);

      RETURN CONCAT_WS(",",tipo,nome,equipa);
END $$

SELECT DevolveCromo(86);


-- Informação extra para estudar os JOIN's. --
SELECT * FROM Cromo c RIGHT JOIN Jogador j ON c.Jogador = j.Nr;