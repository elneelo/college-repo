CREATE TABLE GameMaps(
	MapName VARCHAR(30) NOT NULL,
	MapSize DECIMAL(10,2) NOT NULL,
	MapLocation VARCHAR(30) NOT NULL,
	MaximumMapPlayers INTEGER NOT NULL,
	MapWeather VARCHAR(30) NOT NULL,
	PRIMARY KEY (MapName)
);

INSERT INTO GameMaps VALUES('Jungle',472.64,'South America',12,'Extremely Warm');
INSERT INTO GameMaps VALUES('City',389.25,'New York',12,'Warm');
INSERT INTO GameMaps VALUES('Farm',507.67,'Ireland',18,'Lashing Rain');
INSERT INTO GameMaps VALUES('Mountain',602.88,'Sweden',18,'Snow');
INSERT INTO GameMaps VALUES('Favela',448.54,'South America',12,'Extremely Warm');
INSERT INTO GameMaps VALUES('Beach',697.35,'Portugal',18,'Warm');

CREATE TABLE Player(
	Username VARCHAR(30) NOT NULL,
	FirstName VARCHAR(30) NOT NULL,
	LastName VARCHAR(30) NOT NULL,
	Age INTEGER NOT NULL,
	Email VARCHAR(30) NOT NULL,
	TotalGames INTEGER,
	TotalFriendsOnline INTEGER,
	PRIMARY KEY (Username)
);

INSERT INTO Player VALUES('eagle','Tom','Jones',19,'tomjones@mail.com',12,3);
INSERT INTO Player VALUES('parrot','Conor','Dell',19,'conordell@mail.com',12,3);
INSERT INTO Player VALUES('falcon','Bryan','Jerries',19,'bryanjerries@mail.com',12,3);
INSERT INTO Player VALUES('ostrich','Basil','Fawlty',19,'basilfawlty@mail.com',12,3);
INSERT INTO Player VALUES('owl','Jonny','Jones',19,'jonnyjones@mail.com',12,3);
INSERT INTO Player VALUES('crow','The','Crow',19,'thecrow@mail.com',12,3);

CREATE TABLE GameModeStats(
	CurrentGameModeUser VARCHAR(30) NOT NULL,
	ModeStatId INTEGER NOT NULL,
	GameMode VARCHAR(30),
	ModeKillDeathRatio DECIMAL(10,2) NOT NULL,
	ModeWinLossRatio DECIMAL(10,2) NOT NULL,
	ModeScorePerMinute INTEGER NOT NULL,
	PRIMARY KEY (ModeStatId),
	FOREIGN KEY (CurrentGameModeUser) REFERENCES Player(Username),
	CONSTRAINT CheckMSPM CHECK (ModeScorePerMinute < 1000),
	CONSTRAINT CheckModeId CHECK (ModeStatId < 10000000000)
);

INSERT INTO GameModeStats VALUES('eagle',1328313,'Team Deathmatch',1.54,0.67,211);
INSERT INTO GameModeStats VALUES('parrot',11924,'Search and Destroy',2.09,2.80,323);
INSERT INTO GameModeStats VALUES('falcon',101,'Team Deathmatch',0.46,1.58,408);
INSERT INTO GameModeStats VALUES('ostrich',2139,'Hardpoint',3.87,0.96,627);
INSERT INTO GameModeStats VALUES('owl',12241,'Domination',1.32,0.88,304);
INSERT INTO GameModeStats VALUES('crow',10912,'Search and Destroy',0.58,0.76,188);

CREATE TABLE GameTypeStats(
	CurrentGameTypeUsername VARCHAR(30) NOT NULL,
	TypeStatId INTEGER NOT NULL,
	GameType VARCHAR(30),
	TypeKillDeathRatio DECIMAL(10,2) NOT NULL,
	TypeWinLossRatio DECIMAL(10,2) NOT NULL,
	TypeScorePerMinute INTEGER NOT NULL,
	PRIMARY KEY (TypeStatId),
	FOREIGN KEY (CurrentGameTypeUsername) REFERENCES Player(Username),
	CONSTRAINT CheckTSPM CHECK (TypeScorePerMinute < 1000),
	CONSTRAINT CheckTypeId CHECK (TypeStatId < 10000000000)
);

INSERT INTO GameTypeStats VALUES('eagle',1742214,'Core',0.58,0.76,188);
INSERT INTO GameTypeStats VALUES('parrot',12478,'HardCore',1.32,0.88,304);
INSERT INTO GameTypeStats VALUES('falcon',2983722,'Core',0.46,1.58,408);
INSERT INTO GameTypeStats VALUES('ostrich',110944,'HardCore',0.59,2.15,396);
INSERT INTO GameTypeStats VALUES('owl',23875025,'HardCore',1.07,0.92,367);
INSERT INTO GameTypeStats VALUES('crow',23588,'Nuked Out',0.76,0.56,201);
	
CREATE TABLE PlayerStats(
	UserStats VARCHAR(30) NOT NULL,
	SpecialistToken VARCHAR(30),
	KillDeathRatio DECIMAL(10,2) NOT NULL,
	WinLossRatio DECIMAL(10,2) NOT NULL,
	ScorePerMinute INTEGER NOT NULL,
	FavouriteGameMode VARCHAR(30),
	FavouriteGameType VARCHAR(30),
	FavouriteKillstreak VARCHAR(30),
	BestKillstreak INTEGER,
	PRIMARY KEY (SpecialistToken),
	FOREIGN KEY (UserStats) REFERENCES Player(Username),
	CONSTRAINT CheckSPM CHECK (ScorePerMinute < 1000)
);

INSERT INTO PlayerStats VALUES('eagle','ruin',0.97,0.60,289,'Core','Team Deathmatch','Spy Plane',8);
INSERT INTO PlayerStats VALUES('parrot','vet',0.86,0.71,255,'HardCore','Search and Destroy','Spy Plane',9);
INSERT INTO PlayerStats VALUES('falcon','robot',1.46,1.60,402,'Core','Team Deathmatch','Airstrike',16);
INSERT INTO PlayerStats VALUES('ostrich','runner',2.67,3.10,546,'HardCore','Hardpoint','Helicopter',27);
INSERT INTO PlayerStats VALUES('owl','knife',0.56,0.42,188,'HardCore','Domination','Airstrike',11);
INSERT INTO PlayerStats VALUES('crow','noob',1.06,0.88,304,'Core','Search and Destroy','Spy Plane',14);

CREATE TABLE WeaponLoadout(
	UserClass VARCHAR(30) NOT NULL,
	LoadoutId INTEGER NOT NULL,
	Wallpaper VARCHAR(30),
	UserClassNumber INTEGER NOT NULL,
	PrimaryWeapon VARCHAR(30) NOT NULL,
	AttachmentOne VARCHAR(30) NOT NULL,
	AttachmentTwo VARCHAR(30) NOT NULL,
	SecondaryWeapon VARCHAR(30) NOT NULL,
	SecondaryAttachment VARCHAR(30) NOT NULL,
	LethalGrenade VARCHAR(30) NOT NULL,
	TacticalGrenade VARCHAR(30) NOT NULL,
	PerkOne VARCHAR(30) NOT NULL,
	PerkTwo VARCHAR(30) NOT NULL,
	PerkThree VARCHAR(30) NOT NULL,
	PRIMARY KEY (LoadoutId),
	FOREIGN KEY (UserClass) REFERENCES Player(Username),
	FOREIGN KEY (Wallpaper) REFERENCES PlayerStats(SpecialistToken),
	CONSTRAINT CheckTLoadoutId CHECK (LoadoutId < 10000000000)
);

INSERT INTO WeaponLoadout VALUES('eagle',34363,'ruin',1,'kn-44','sight','scope','beretta','laser','frag','emp','Flak Jacket','Hardened','Marathon');
INSERT INTO WeaponLoadout VALUES('parrot',354366,'vet',1,'an-94','sight','scope','b23r','laser','frag','emp','Lightweight','Sleight Of Hand','Tactical Mask');
INSERT INTO WeaponLoadout VALUES('falcon',1012021,'robot',1,'spas-12','sight','scope','spectre','laser','frag','emp','Flak Jacket','Sleight Of Hand','Awareness');
INSERT INTO WeaponLoadout VALUES('ostrich',4721,'runner',1,'vmp','sight','scope','beretta','laser','frag','emp','Ghost','Hardened','Engineer');
INSERT INTO WeaponLoadout VALUES('owl',104990,'knife',1,'kuda','sight','scope','b23r','laser','frag','emp','Ghost','Steady Aim','Tactical Mask');
INSERT INTO WeaponLoadout VALUES('crow',112314,'noob',1,'ak-47','sight','scope','tmp','laser','frag','emp','Flak Jacket','Scout','Tactical Mask');

CREATE TABLE Killstreaks(
	StreakForUser VARCHAR(30) NOT NULL,
	UsedKillstreakId INTEGER NOT NULL,
	StreakOne VARCHAR(30) NOT NULL,
	StreakTwo VARCHAR(30) NOT NULL,
	StreakThree VARCHAR(30) NOT NULL,
	MostUsedStreak VARCHAR(30),
	HighestStreak INTEGER,
	ShowcaseToken VARCHAR(30),
	PRIMARY KEY (UsedKillstreakId),
	FOREIGN KEY (StreakForUser) REFERENCES Player(Username),
	FOREIGN KEY (ShowcaseToken) REFERENCES PlayerStats(SpecialistToken),
	CONSTRAINT CheckUKSID CHECK (UsedKillstreakId < 10000000000)
);

INSERT INTO Killstreaks VALUES('eagle',101,'Spy Plane','Airstrike','Helicopter','Airstrike',12,'ruin');
INSERT INTO Killstreaks VALUES('parrot',207,'Spy Plane','Airstrike','Helicopter','Helicopter',9,'vet');
INSERT INTO Killstreaks VALUES('falcon',3171,'Spy Plane','Airstrike','Helicopter','Helicopter',16,'robot');
INSERT INTO Killstreaks VALUES('ostrich',19411,'Spy Plane','Airstrike','Helicopter','Airstrike',27,'runner');
INSERT INTO Killstreaks VALUES('owl',10190,'Spy Plane','Airstrike','Helicopter','Spy Plane',6,'knife');
INSERT INTO Killstreaks VALUES('crow',222908,'Spy Plane','Airstrike','Helicopter','Airstrike',14,'noob');


