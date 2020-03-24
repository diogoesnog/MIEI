-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema ficha4
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema ficha4
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `ficha4` DEFAULT CHARACTER SET utf8 ;
USE `ficha4` ;

-- -----------------------------------------------------
-- Table `ficha4`.`table1`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ficha4`.`table1` (
  `Sensor` INT NOT NULL,
  PRIMARY KEY (`Sensor`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ficha4`.`Paciente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ficha4`.`Paciente` (
  `idPaciente` INT NOT NULL,
  `nomePaciente` VARCHAR(45) NULL,
  `dataNascPaciente` DATE NULL,
  `idadePaciente` INT NULL,
  PRIMARY KEY (`idPaciente`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ficha4`.`Medicao`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ficha4`.`Medicao` (
  `idMedicao` INT NOT NULL,
  `tempCorporal` VARCHAR(45) NULL,
  `timeStamp` TIMESTAMP NULL,
  `systolic` INT NULL,
  `diastolic` INT NULL,
  `idSensor` INT NULL,
  `numSensor` INT NULL,
  `tipoSensor` VARCHAR(45) NULL,
  `Paciente_idPaciente` INT NOT NULL,
  PRIMARY KEY (`idMedicao`),
  INDEX `fk_Medicao_Paciente_idx` (`Paciente_idPaciente` ASC) VISIBLE,
  CONSTRAINT `fk_Medicao_Paciente`
    FOREIGN KEY (`Paciente_idPaciente`)
    REFERENCES `ficha4`.`Paciente` (`idPaciente`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
