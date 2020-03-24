-- Permissão para fazer operações de remoção de dados.
SET SQL_SAFE_UPDATES = 0;

-- Escolher a base de dados necessária. Ter em conta que a linguagem MySQL não é case-sensitive.
USE Mercearia;

-- Alínea (c) ---

-- QUERY 1 --
SELECT Nome FROM Cliente;

-- QUERY 2 --
SELECT Nome FROM Cliente WHERE Localidade = "Aguada do Queixo";

-- QUERY 3 --
SELECT distinct(Profissao) FROM Cliente;

-- QUERY 4 --
SELECT Designacao, Preco FROM Produto ORDER BY Designacao ASC, Preco ASC;

-- QUERY 5 --
SELECT Numero, Total, Data FROM Venda WHERE DATA = "2017/10/05";

SELECT vp.venda, p.designacao
	FROM vendaproduto vp, produto p 
    WHERE p.numero = vp.produto AND venda = 1;
    
-- Alínea (d) --

-- QUERY 1 --
INSERT INTO Cliente
    VALUES (10, "Tiago Nogueira", "1997/12/13", "Estudante", "Rua do desespero", "Fafe", "4820-367", 00000000, "diogo@gmail.com", "Muitas", NULL)
    ;

-- QUERY 2 --
UPDATE Cliente SET Rua = "Nova Rua" WHERE Numero = 9;

-- QUERY 3 --
UPDATE Produto SET Preco = Preco * 1.1 WHERE Tipo = "Peixe";

-- QUERY 4 --

INSERT INTO Venda
	(Numero, Data, Estado, Total, Cliente_Numero)
	VALUES 
		(6,  '2017/10/30', 'S',  0, 8);
        
INSERT INTO VendaProduto
	(Venda, Produto, Quantidade, Preco, Valor)
	VALUES 
		(6, 1, 2, (SELECT Preco FROM Produto WHERE Numero = 1), 2*(SELECT Preco FROM Produto WHERE Numero = 1)),
		(6, 2, 1, (SELECT Preco FROM Produto WHERE Numero = 2),  (SELECT Preco FROM Produto WHERE Numero = 2)),
		(6, 3, 3, (SELECT Preco FROM Produto WHERE Numero = 3), 3*(SELECT Preco FROM Produto WHERE Numero = 3)),
		(6, 4, 1, (SELECT Preco FROM Produto WHERE Numero = 4),  (SELECT Preco FROM Produto WHERE Numero = 4));

	
UPDATE Venda SET Total = (SELECT SUM(Valor) FROM VendaProduto WHERE Venda = 6) WHERE Numero = 6;

-- QUERY 5 --
DELETE FROM VendaProduto WHERE Venda = 6;
DELETE FROM Venda WHERE Numero = 6;