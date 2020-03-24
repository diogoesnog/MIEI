-- Escolher a base de dados necessária. Ter em conta que a linguagem MySQL não é case-sensitive.
USE EnunciadosExames;

-- Exercício 5 --

-- Alínea (a) --
SELECT DISTINCT(p.Nome) FROM Docente AS p
	INNER JOIN Disciplina AS d ON d.Docente_Codigo = p.Codigo
    ORDER BY p.Nome ASC;

-- Alínea (b) --
SELECT p.Nome, COUNT(d.Docente_Codigo) AS TotalDisciplinas
	FROM Docente p, Disciplina d
	WHERE d.Docente_Codigo = p.Codigo
 GROUP BY p.Codigo
 ORDER BY TotalDisciplinas DESC
 LIMIT 3;
 
-- Alínea (c) --
SELECT e.idExame FROM Exame AS e 
	WHERE (e.AnoLetivo = "2015/2016" OR e.AnoLetivo = "2016/2017");

-- Alínea (d) --
SELECT q.Numero FROM Questao AS q
	INNER JOIN Exame AS e ON q.Exame_idExame = e.idExame
    INNER JOIN Disciplina AS d ON e.Disciplina_Codigo = d.Codigo
    WHERE e.OrdemExame = 1 AND e.AnoLetivo = "2013/2014" AND d.Designacao = "Base de Dados";

-- Alínea (e) --
CREATE TRIGGER AtualizaDificuldade AFTER INSERT ON Questao
	FOR EACH ROW 
	UPDATE Exame AS e SET e.DificuldadeExame = 
		(SELECT AVG(q.DificuldadeQuestao) FROM Questao AS q WHERE q.Exame_idExame = NEW.Exame_idExame)
	WHERE e.idExame = NEW.Exame_idExame;
