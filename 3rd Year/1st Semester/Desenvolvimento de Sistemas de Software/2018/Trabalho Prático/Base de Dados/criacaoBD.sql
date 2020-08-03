-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema ConfiguraFacil
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `ConfiguraFacil` ;

-- -----------------------------------------------------
-- Schema ConfiguraFacil
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `ConfiguraFacil` DEFAULT CHARACTER SET utf8 ;
USE `ConfiguraFacil` ;

-- -----------------------------------------------------
-- Table `ConfiguraFacil`.`Cliente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ConfiguraFacil`.`Cliente` (
  `nif` INT(9) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `morada` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`nif`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ConfiguraFacil`.`Exterior`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ConfiguraFacil`.`Exterior` (
  `idComponente` INT NOT NULL AUTO_INCREMENT,
  `designacao` VARCHAR(45) NOT NULL,
  `preco` DECIMAL(7,2) NOT NULL,
  `stock` INT NOT NULL,
  PRIMARY KEY (`idComponente`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ConfiguraFacil`.`Interior`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ConfiguraFacil`.`Interior` (
  `idComponente` INT NOT NULL AUTO_INCREMENT,
  `designacao` VARCHAR(45) NOT NULL,
  `preco` DECIMAL(7,2) NOT NULL,
  `stock` INT NOT NULL,
  PRIMARY KEY (`idComponente`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ConfiguraFacil`.`Base`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ConfiguraFacil`.`Base` (
  `idComponente` INT NOT NULL AUTO_INCREMENT,
  `designacao` VARCHAR(45) NOT NULL,
  `preco` DECIMAL(7,2) NOT NULL,
  `stock` INT NOT NULL,
  PRIMARY KEY (`idComponente`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ConfiguraFacil`.`Modelo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ConfiguraFacil`.`Modelo` (
  `idModelo` INT NOT NULL AUTO_INCREMENT,
  `Cliente_nif` INT(9) NOT NULL,
  `tipo` VARCHAR(45) NOT NULL,
  `precoModelo` DECIMAL(7,2) NOT NULL,
  `precofinal` DECIMAL(8,2) NOT NULL,
  `pacote` VARCHAR(7) NOT NULL,
  `pintura` INT NOT NULL,
  `motorizacao` INT NOT NULL,
  `jantes` INT NOT NULL,
  `pneus` INT NOT NULL,
  `vidros` INT NOT NULL,
  `parachoques` INT NOT NULL,
  `tetos` INT NOT NULL,
  `luzes` INT NOT NULL,
  `frisos` INT NOT NULL,
  `estofos` INT NOT NULL,
  PRIMARY KEY (`idModelo`),
  INDEX `fk_Modelo_Cliente1_idx` (`Cliente_nif` ASC) INVISIBLE,
  INDEX `pintura_idx` (`pintura` ASC) INVISIBLE,
  INDEX `motorizacao_idx` (`motorizacao` ASC) INVISIBLE,
  INDEX `luzes_idx` (`luzes` ASC) INVISIBLE,
  INDEX `frisos_idx` (`frisos` ASC) INVISIBLE,
  INDEX `estofos_idx` (`estofos` ASC) INVISIBLE,
  INDEX `jantes_idx` (`jantes` ASC) INVISIBLE,
  INDEX `pneus_idx` (`pneus` ASC) INVISIBLE,
  INDEX `vidros_idx` (`vidros` ASC) INVISIBLE,
  INDEX `parachoques_idx` (`parachoques` ASC) INVISIBLE,
  INDEX `tetos_idx` (`tetos` ASC) VISIBLE,
  CONSTRAINT `fk_Modelo_Cliente1`
    FOREIGN KEY (`Cliente_nif`)
    REFERENCES `ConfiguraFacil`.`Cliente` (`nif`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `pintura`
    FOREIGN KEY (`pintura`)
    REFERENCES `ConfiguraFacil`.`Base` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `motorizacao`
    FOREIGN KEY (`motorizacao`)
    REFERENCES `ConfiguraFacil`.`Base` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `luzes`
    FOREIGN KEY (`luzes`)
    REFERENCES `ConfiguraFacil`.`Interior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `frisos`
    FOREIGN KEY (`frisos`)
    REFERENCES `ConfiguraFacil`.`Interior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `estofos`
    FOREIGN KEY (`estofos`)
    REFERENCES `ConfiguraFacil`.`Interior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `jantes`
    FOREIGN KEY (`jantes`)
    REFERENCES `ConfiguraFacil`.`Exterior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `pneus`
    FOREIGN KEY (`pneus`)
    REFERENCES `ConfiguraFacil`.`Exterior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `vidros`
    FOREIGN KEY (`vidros`)
    REFERENCES `ConfiguraFacil`.`Exterior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `parachoques`
    FOREIGN KEY (`parachoques`)
    REFERENCES `ConfiguraFacil`.`Exterior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `tetos`
    FOREIGN KEY (`tetos`)
    REFERENCES `ConfiguraFacil`.`Exterior` (`idComponente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
