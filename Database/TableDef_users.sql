-- ##############################################
-- table users:
--

CREATE TABLE users (
	  ID INT UNSIGNED NOT NULL AUTO_INCREMENT,
	  Username VARCHAR(20) NOT NULL,
	  PasswordHash Varchar(111),
	  PRIMARY KEY(ID)
) ENGINE=XtraDB;
