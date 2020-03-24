-- Saber a receita total do filme Beauty and the Beast
SELECT SUM(Preco) FROM bilhete
   JOIN filme ON bilhete.Filme_IDfilme = filme.IDfilme
    WHERE filme.Nome = "Beauty and the Beast";

-- Saber o top 3 de clientes que mais gastaram no cinema

SELECT Nome, SUM(Preco) AS GastoTotal FROM cliente
  JOIN bilhete ON cliente.NIF = bilhete.Cliente_NIF
    GROUP BY NIF
    ORDER BY GastoTotal DESC;

-- Criação de os utilizadores e as suas respetivas permissões
CREATE USER 'CinemaAdmin'@'localhost' IDENTIFIED BY 'admin';
CREATE USER 'Caixeiro'@'localhost' IDENTIFIED BY 'caixeiro';

GRANT ALL PRIVILEGES ON cinema TO 'CinemaAdmin'@'localhost';
GRANT INSERT, UPDATE, DELETE ON cliente to 'Caixeiro'@'localhost';
GRANT INSERT, UPDATE, DELETE ON bilhete to 'Caixeiro'@'localhost';
GRANT INSERT, UPDATE, DELETE ON infobilhete to 'Caixeiro'@'localhost';
FLUSH PRIVILEGES;

-- Eliminar os utilizadores criados
DROP USER 'CinemaAdmin'@'localhost', 'Caixeiro'@'localhost';

-- Em modo VIEW
CREATE VIEW GastoTotal AS
  SELECT Nome, SUM(Preco) AS GastoTotal FROM cliente
    JOIN bilhete ON cliente.NIF = bilhete.Cliente_NIF
      GROUP BY NIF
      ORDER BY GastoTotal DESC;
SELECT * FROM GastoTotal;