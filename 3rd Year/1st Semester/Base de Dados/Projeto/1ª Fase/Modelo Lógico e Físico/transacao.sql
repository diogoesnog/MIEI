DELIMITER //
CREATE PROCEDURE updateContactoNovoBilhete(IN nif INT, IN contactonovo INT, IN idfilme mediumint(7),IN sala tinyint(2),
IN sessao time, IN lugar varchar(4), IN caixa tinyint(1),IN preco double(5,2))

BEGIN
  DECLARE erro BOOLEAN DEFAULT 0;
  DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET Erro =1;
    START TRANSACTION;
    -- Verificar o estado inicial do registo
    SELECT Contacto FROM cliente
            WHERE NIF = nif;
    -- Alterar o contacto do cliente com aquele nif
    UPDATE cliente
          SET Contacto = contactonovo
          WHERE NIF = nif;
    -- Inserção de um nova entrada na tabela infobilhete caso não exista esta entrada
    IF ( (SELECT COUNT(*) FROM infobilhete WHERE Sala = sala AND Sessao=sessao AND Lugar=lugar) = 0) THEN
    INSERT INTO infobilhete VALUES(sala,sessao,lugar);
    END IF;
    -- Inserção de uma nova entrada na tabela bilhete
    INSERT INTO bilhete VALUES("2017-09-10 17:15:30",nif,idfilme,sala,sessao,lugar,preco);

    IF Erro THEN ROLLBACK;
    END IF;
    COMMIT;
END //