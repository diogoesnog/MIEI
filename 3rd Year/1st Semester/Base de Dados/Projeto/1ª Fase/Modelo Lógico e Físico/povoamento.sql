
-- Inserir no InfoBilhete
INSERT INTO cinema.infobilhete (Sala, Sessao, Lugar)
  VALUES (7, "00:40", "F15"),
         (1, "21:40", "G14"),
         (1, "21:40", "G15"),
         (3, "18:20", "F15"),
         (1, "21:40", "F14"),
         (3, "19:20", "C15");

-- Inserir no Cliente
INSERT INTO cinema.cliente (NIF, Nome, Contacto, DataNascimento)
  VALUES (253356369, "Diogo Nogueira", 913392656, "1997-12-13"),
         (249929589, "Diogo Araújo", 914215212, "1997-10-08"),
         (123456789, "Tifany Silva", 910040099, "1994-01-25"),
         (321654987, "Mariana Lino", 916024677, "1997-05-08"),
         (462589750, "António Silva", 934567789, "1960-03-25");

-- Inserir no Filme
INSERT INTO cinema.filme (IDfilme, Nome, Duracao, Ano, Pais, Realizador, Elenco, Sinopse)
  VALUES (0848228, "The Avengers", "02:23:00", 2012, "US", "Joss Whedon", "Robert Downey Jr., Chris Evans, Scarlett Johansson", "Superheróis a lutar aliens"),
         (2771200, "Beauty and the Beast", "02:09:00", 2017, "US", "Bill Condon", "Emmy Watson, Dan Stevens, Luke Evans", "Uma adaptação do livro e filme Bela e o Monstro"),
         (1528071, "Horns", "02:00:00", 2013, "US", NULL, NULL, NULL),
         (1375666, "Inception", "02:28:00", 2010, "US", "Christopher Nolan", "Leonardo DiCaprio, Joseph Gordon-Levitt, Ellen Page", "Um filme com uma trama tão intensa e misteriosa"),
         (0120737, "The Lord of the Rings", "02:58:00", 2001, "US", "Peter Jackson", "Elijah Wood, Ian McKellen, Orlando Bloom", NULL);

-- Inserir no Género
INSERT INTO cinema.genero (IDGenero, Nome, Filme_IDfilme)
  VALUES (1, "Ação", 0848228),
         (2, "Mistério", 1375666),
         (3, "Musical", 2771200),
         (4, "Terror", 1528071),
         (5, "Medieval", 0120737);

-- Inserir no bilhete
INSERT INTO cinema.bilhete (DataCompra, Filme_IDfilme, Cliente_NIF, InfoBilhete_Sala, InfoBilhete_Sessao, InfoBilhete_Lugar, Preco, NumCaixa)
  VALUES ("2017-11-23 17:15:00", 0848228, 123456789, 7, "00:40", "F15", 6.60, 3),
         ("2017-11-24 17:15:00", 2771200, 321654987, 1, "21:40", "G14", 10.60, NULL),
         ("2017-11-24 17:15:30", 2771200, 321654987, 1, "21:40", "G15", 10.60, NULL),
         ("2017-11-24 18:15:00", 1375666, 249929589, 3, "18:20", "F15", 5.75, 2),
         ("2017-11-24 18:15:30", 0120737, 249929589, 1, "21:40", "F14", 10, 2),
         ("2017-11-20 18:15:30", 1528071, 123456789, 3, "19:20", "C15", 5, NULL);

