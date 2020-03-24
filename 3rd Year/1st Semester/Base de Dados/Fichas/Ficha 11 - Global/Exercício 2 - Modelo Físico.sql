CREATE SCHEMA IF NOT EXISTS enunciadoexames;
USE enunciadoexames;

-- Tabela Docente.
CREATE TABLE IF NOT EXISTS Docente (
  Codigo INT NOT NULL,
  Nome VARCHAR(45) NOT NULL,
  Categoria VARCHAR(45) NULL,
  PRIMARY KEY (Codigo));

-- Tabela Disciplina. 
CREATE TABLE IF NOT EXISTS Disciplina (
  Codigo INT NOT NULL,
  Designacao VARCHAR(45) NOT NULL,
  Docente_Codigo INT NOT NULL,
  PRIMARY KEY (Codigo, Docente_Codigo),
  FOREIGN KEY (Docente_Codigo) REFERENCES Docente(Codigo));

-- Tabela Curso.
CREATE TABLE IF NOT EXISTS Curso (
  idCurso INT NOT NULL,
  Designacao VARCHAR(45) NOT NULL,
  PRIMARY KEY (idCurso));

-- Tabela DisciplinaAndCurso.
CREATE TABLE IF NOT EXISTS DisciplinaAndCurso (
  Disciplina_Codigo INT NOT NULL,
  Curso_idCurso INT NOT NULL,
  PRIMARY KEY (Disciplina_Codigo, Curso_idCurso),
  FOREIGN KEY (Disciplina_Codigo) REFERENCES Disciplina(Codigo),
  FOREIGN KEY (Curso_idCurso) REFERENCES Curso(idCurso));

-- Tabela Exame.
CREATE TABLE IF NOT EXISTS Exame (
  idExame INT NOT NULL,
  AnoLetivo VARCHAR(9) NOT NULL,
  OrdemExame TINYINT(2) NOT NULL,
  DificuldadeExame TINYINT NULL,
  Disciplina_Codigo INT NOT NULL,
  PRIMARY KEY (idExame, Disciplina_Codigo),
  FOREIGN KEY (Disciplina_Codigo) REFERENCES Disciplina(Codigo));

-- Tabela Questão.
CREATE TABLE IF NOT EXISTS Questao (
  Numero INT NOT NULL,
  Enunciado TEXT NOT NULL,
  DificuldadeQuestao TINYINT(1) NOT NULL,
  OrdemQuestao TINYINT(2) NOT NULL,
  Pontuacao TINYINT(3) NOT NULL,
  Exame_idExame INT NOT NULL,
  PRIMARY KEY (Numero, Exame_idExame),
  FOREIGN KEY (Exame_idExame) REFERENCES Exame(idExame));