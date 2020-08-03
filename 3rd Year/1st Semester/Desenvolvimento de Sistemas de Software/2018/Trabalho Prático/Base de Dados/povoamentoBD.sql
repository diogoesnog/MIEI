-- Universidade do Minho
-- Mestrado Integrado em Engenharia Informática
-- Unidade Curricular de Desenvolvimento de Sistemas de Software
-- 2018/2019
--
-- Caso de Estudo: "ConfiguraFácil"
-- Povoamento parcial da base de dados.


USE configurafacil;


-- INSERIR PINTURAS
INSERT INTO base (idComponente, designacao, preco, stock)
	VALUE (100, "Pintura Azul", 3500, 10);
INSERT into base (designacao, preco, stock)
  VALUES
  ("Pintura Branca", 2500, 10), ("Pintura Preta", 2500, 10), ("Pintura Vermelha", 3500, 10);


-- INSERIR MOTORIZAÇÕES
INSERT INTO base (idComponente, designacao, preco, stock)
	VALUES (200, "Motor Diesel", 2000, 10), (NULL, "Motor Gasolina", 1000, 10), (null,"Motor Elétrico", 0, 10), (NULL, "Motor Híbrido", 1500, 10);

-- INSERIR ESTOFOS
INSERT INTO interior (idComponente, designacao, preco, stock)
  VALUE (300, "Estofo Pele Preto", 1255, 10);
INSERT INTO interior (designacao, preco, stock)
  VALUES ("Estofo Tecido Preto", 0, 10), ("Estofo Sport Cinzento", 1765, 10), ("Estofo Pele Camel",1855,10 );

-- INSERIR FRISOS
INSERT INTO interior (idComponente, designacao, preco, stock)
  VALUE (400,"Frisos em Prata", 0, 10);
INSERT INTO interior (designacao, preco, stock)
  VALUES ("Frisos Preto Brilhante", 170, 10),("Frisos Preto Brilhante", 170, 10), ("Frisos Pérola Cromado",180,10), ("Frisos Liga de Carbono",200,10);

-- INSERIR LUZES
INSERT INTO interior (idComponente, designacao, preco, stock)
  VALUE (500,"Luzes Normais Brancas", 0, 10);
INSERT INTO interior (designacao, preco, stock)
  VALUES ("Luzes Vermelhas", 115, 10), ("Luzes Azuis",115,10), ("Luzes Personalizáveis",155,10);

-- INSERIR TETOS
INSERT INTO exterior (idComponente, designacao, preco, stock)
  VALUE (600, "Teto de Abrir Automático", 1950, 10);
INSERT INTO exterior (designacao, preco, stock)
  VALUES ("Teto Panorâmico", 1755, 10), ("Teto Normal",0,10), ("Teto de Abrir em Tecido",1630,10);

-- INSERIR JANTES
INSERT INTO exterior (idComponente, designacao, preco, stock)
  VALUE (700, "Jantes Liga-Leve Ferric",856, 10);
INSERT INTO exterior (designacao, preco, stock)
  VALUES ("Jantes Normais", 0, 10), ("Jantes Bicolores em Preto",945,10), ("Jantes em Preto",745,10);

-- INSERIR PNEUS
INSERT INTO exterior (idComponente, designacao, preco, stock)
  VALUES (800, "Pneu Michelin", 1555, 10), (NULL, "Pneu Continental", 0, 10);

-- INSERIR VIDROS
INSERT INTO exterior (idComponente, designacao, preco, stock)
  VALUES (900, "Vidro Escurecido", 2069, 10), (NULL,"Vidro Normal", 0, 10);

-- INSERIR PARACHOQUES
INSERT INTO exterior (idComponente, designacao, preco, stock)
  VALUE (1000, "Pára-Choque Linha Sport",1869,10);
INSERT INTO exterior (designacao, preco, stock)
  VALUES ("Pára-Choque Linha Confort",1559,10), ("Pára-Choque Básico",0,10);