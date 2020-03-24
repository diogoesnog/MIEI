-- Criação em SQL da Base de Dados
-- Diogo Araújo, Diogo Nogueira, Mariana Lino e Tifany Silva

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Libertar um SCHEMA com o nome CINEMA já existente
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `Cinema` ;

-- -----------------------------------------------------
-- Criar Schema Cinema
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `Cinema` DEFAULT CHARACTER SET utf8 ;
USE `Cinema` ;

-- -----------------------------------------------------
-- Tabela `Cinema`.`Filme`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Cinema`.`Filme` (
  `IDfilme` MEDIUMINT(7) UNSIGNED NOT NULL COMMENT 'Id IMDB ',
  `Nome` VARCHAR(45) NOT NULL,
  `Duracao` TIME NOT NULL,
  `Ano` YEAR NOT NULL,
  `Pais` VARCHAR(2) NULL COMMENT 'ISO_ALPHA2',
  `Realizador` VARCHAR(45) NULL,
  `Elenco` TEXT NULL,
  `Sinopse` TEXT NULL,
  PRIMARY KEY (`IDfilme`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Tabela `Cinema`.`Cliente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Cinema`.`Cliente` (
  `NIF` INT(9) UNSIGNED NOT NULL,
  `Nome` VARCHAR(45) NOT NULL,
  `Contacto` INT(9) UNSIGNED NOT NULL,
  `DataNascimento` DATE NULL,
  PRIMARY KEY (`NIF`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Tabela `Cinema`.`InfoBilhete`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Cinema`.`InfoBilhete` (
  `Sala` TINYINT(2) UNSIGNED NOT NULL,
  `Sessao` TIME NOT NULL,
  `Lugar` VARCHAR(4) NOT NULL,
  PRIMARY KEY (`Sala`, `Sessao`, `Lugar`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Tabela `Cinema`.`Bilhete`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Cinema`.`Bilhete` (
  `DataCompra` DATETIME NOT NULL,
  `Filme_IDfilme` MEDIUMINT(7) UNSIGNED NOT NULL,
  `Cliente_NIF` INT(9) UNSIGNED NOT NULL,
  `InfoBilhete_Sala` TINYINT(2) UNSIGNED NOT NULL,
  `InfoBilhete_Sessao` TIME NOT NULL,
  `InfoBilhete_Lugar` VARCHAR(4) NOT NULL,
  `Preco` DECIMAL(5,2) NOT NULL,
  `NumCaixa` TINYINT(1) UNSIGNED NULL,
  PRIMARY KEY (`DataCompra`, `Filme_IDfilme`, `Cliente_NIF`, `InfoBilhete_Sala`, `InfoBilhete_Sessao`, `InfoBilhete_Lugar`),
  INDEX `fk_Bilhete_Filme1_idx` (`Filme_IDfilme` ASC),
  INDEX `fk_Bilhete_Cliente1_idx` (`Cliente_NIF` ASC),
  INDEX `fk_Bilhete_InfoBilhete1_idx` (`InfoBilhete_Sala` ASC, `InfoBilhete_Sessao` ASC, `InfoBilhete_Lugar` ASC),
  CONSTRAINT `fk_Bilhete_Filme1`
    FOREIGN KEY (`Filme_IDfilme`)
    REFERENCES `Cinema`.`Filme` (`IDfilme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Bilhete_Cliente1`
    FOREIGN KEY (`Cliente_NIF`)
    REFERENCES `Cinema`.`Cliente` (`NIF`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Bilhete_InfoBilhete1`
    FOREIGN KEY (`InfoBilhete_Sala` , `InfoBilhete_Sessao` , `InfoBilhete_Lugar`)
    REFERENCES `Cinema`.`InfoBilhete` (`Sala` , `Sessao` , `Lugar`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Tabela `Cinema`.`Genero`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Cinema`.`Genero` (
  `IDGenero` TINYINT(2) UNSIGNED NOT NULL,
  `Nome` VARCHAR(45) NOT NULL,
  `Filme_IDfilme` MEDIUMINT(7) UNSIGNED NOT NULL,
  PRIMARY KEY (`IDGenero`, `Filme_IDfilme`),
  INDEX `fk_Genero_Filme_idx` (`Filme_IDfilme` ASC),
  CONSTRAINT `fk_Genero_Filme`
    FOREIGN KEY (`Filme_IDfilme`)
    REFERENCES `Cinema`.`Filme` (`IDfilme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;