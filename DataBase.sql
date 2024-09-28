DROP DATABASE IF EXISTS Game;

CREATE DATABASE Game;

USE Game;

CREATE TABLE Player (
Id INTEGER AUTO_INCREMENT PRIMARY KEY,
Password TEXT NOT NULL,
Name TEXT NOT NULL,
Points INTEGER DEFAULT 0 
)ENGINE =InnoDB;

	CREATE TABLE Games (
		Id INTEGER AUTO_INCREMENT PRIMARY KEY,
Date DATETIME DEFAULT NOW()
)ENGINE =InnoDB;

CREATE TABLE PlayerGame (
	Player INTEGER NOT NULL, 
	Games INTEGER NOT NULL,
	PointsGame INTEGER DEFAULT 0,
	FOREIGN KEY (Player) REFERENCES Player (Id),
	FOREIGN KEY (Games) REFERENCES Games(Id)
	)ENGINE=InnoDB;

INSERT INTO Player (Id, Name, Password) VALUES (1, 'Marta', 'eetac1');
INSERT INTO Player (Id,Name,Password) VALUES (2,'Niina', 'eetac2');
INSERT INTO Player (Id,Name,Password) VALUES (3,'Nojus', 'eetac3');

UPDATE Player SET Points=FLOOR(RAND() * (1000 - 50+ 1)) + 50 WHERE Name= 'Marta' OR Name= 'Niina' OR Name= 'Nojus';

UPDATE Games 
SET DATE = DATE_ADD('2019-01-01 00:00:00', INTERVAL FLOOR(RAND() * 157680000) SECOND);

INSERT INTO Games(Id) VALUES (1);
INSERT INTO Games(Id) VALUES (2);
INSERT INTO Games(Id) VALUES (3);
INSERT INTO Games(Id) VALUES (4);
INSERT INTO Games(Id) VALUES (5);

INSERT INTO PlayerGame(Player, Games) VALUES (1, 1);
INSERT INTO PlayerGame(Player, Games) VALUES (2, 1);
INSERT INTO PlayerGame(Player, Games) VALUES (3, 5);
INSERT INTO PlayerGame(Player, Games) VALUES (1, 2);
INSERT INTO PlayerGame(Player, Games) VALUES (3, 2);
INSERT INTO PlayerGame(Player, Games) VALUES (2, 4);

INSERT INTO PlayerGame(Player, Games) VALUES (3, 1);
INSERT INTO PlayerGame(Player, Games) VALUES (2, 3);
INSERT INTO PlayerGame(Player, Games) VALUES (1, 4);
INSERT INTO PlayerGame(Player, Games) VALUES (1, 5);
