-- Este Script serve para povoar a nossa Base de Dados de modo a inserir Entidades na nossa Base de Dados.

-- Selecionar a Base de Dados em questão.
USE EnunciadosExames;

-- Permissão para fazer operações de remoção de dados.
SET SQL_SAFE_UPDATES = 0;

SET FOREIGN_KEY_CHECKS = 0;

-- Povoamento da tabela "Curso".
INSERT INTO Curso
		VALUES 
		(1, 'Engenharia Informatica'),
        (2, 'Biologia Aplicada'),
        (3, 'Engenharia Mecanica'),
        (4, 'Psicologia'),
        (5, 'Letras'),
        (6, 'Marketing')
	;

-- Povoamento da tabela "Disciplina".
INSERT INTO Disciplina
	VALUES 
		(1, 'Programacao Funcional', 1),
        (2, 'Eletromagnetismo', 2),
        (3, 'Literatura', 3),
        (4, 'Portugues', 4),
        (5, 'Programacao Imperativa', 1),
        (6, 'Base de Dados', 1)
	;

-- Povoamento da tabela "Docente".
INSERT INTO Docente
	VALUES
		(1, 'Joaquim Nogueira', "Docente"),
        (2, 'Diogo Nogueira', "Diretor de Curso"),
        (3, 'Tiago Nogueira', "Docente"),
        (4, 'Cristina Silva', "Diretor de Curso"),
        (5, 'Teresa Catarina', "Docente")
	;

-- Povoamento da tabela "Exame".
INSERT INTO Exame
	VALUES
		(1, "2015/2016", 1, NULL, 1),
        (2, "2015/2016", 2, NULL, 1),
        (3, "2015/2016", 3, NULL, 1),
        (4, "2016/2017", 1, NULL, 1),
        (5, "2016/2017", 1, NULL, 1),
        (6, "2013/2014", 1, NULL, 6),
		(7, "2013/2014", 2, NULL, 6)
	;

-- Povoamento da tabela "Questao".
INSERT INTO Questao
	VALUES
		(12, "Escreva a seguinte formula em FN1.", 2, 2, 10, 6),
		(20, "Deduza a seguinte formula.", 4, 3, 15, 6),
        (9, "Diga o que entende por objetos.", 1, 12, 4, 6),
        (23, "Faca o esquema concetual relativo ao seguinte modelo fisico.", 5, 11, 20, 7)
	;
INSERT INTO Questao
	VALUES 
		(11, "Nova Questão.", 4, 1, 12, 6);
INSERT INTO Questao
	VALUES 
		(7, "Nova Questão.", 4, 1, 12, 6);
