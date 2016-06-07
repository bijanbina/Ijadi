-- -----------------------------------------------------
-- Table `Parsed File`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Parsed File` (
  `Filename` VARCHAR(50) NOT NULL ,
  `linecount` INT NULL ,
  `path` VARCHAR(80) NULL ,
  `checksum` VARCHAR(50) NULL ,
  `modifydate` BIGINT UNSIGNED NULL ,
  PRIMARY KEY (`Filename`) );

CREATE UNIQUE INDEX `Filename_UNIQUE` ON `Parsed File` (`Filename` ASC) ;


-- -----------------------------------------------------
-- Table `Defines`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Defines` (
  `Definename` VARCHAR(50) NOT NULL ,
  `defineto` VARCHAR(80) NULL ,
  `filename` VARCHAR(50) NULL ,
  `linenumber` INT NULL ,
  PRIMARY KEY (`Definename`) );

CREATE UNIQUE INDEX `Definename_UNIQUE` ON `Defines` (`Definename` ASC) ;


-- -----------------------------------------------------
-- Table `Functions`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Functions` (
  `Functionname` VARCHAR(50) NOT NULL ,
  `filename` VARCHAR(30) NULL ,
  `linenumber` INT NULL ,
  PRIMARY KEY (`Functionname`) );

CREATE UNIQUE INDEX `Functionname_UNIQUE` ON `Functions` (`Functionname` ASC) ;


-- -----------------------------------------------------
-- Table `Datatypes`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Datatypes` (
  `Dataname` VARCHAR(50) NOT NULL ,
  `type` TINYINT NULL ,
  `filename` VARCHAR(50) NULL ,
  `linenumber` INT NULL ,
  PRIMARY KEY (`Dataname`) );

CREATE UNIQUE INDEX `Dataname_UNIQUE` ON `Datatypes` (`Dataname` ASC) ;
