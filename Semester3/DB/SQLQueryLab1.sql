create table Team 
(
Team_name varchar(50) primary key,
Matches_played int not null, 
Wins int,
Losses int,
Draws int,
Goals_scored int, 
Goals_conceded int, 
Points int
);

create table Players
(
Pid int primary key,
First_name varchar(50) not null,
Last_name varchar(50)  not null,
Goals_scored int,
Assists_made int,
Team_name varchar (50) foreign key references Team(Team_name)
);

create table TopScorers
(
Player_name varchar(50),
Goals_scored int not null,
Match_played int not null,
Team_name varchar(50) foreign key references Team(Team_name)
)

create table HomeMatches 
(
Team_name varchar(50) primary key,
Matches_played int,
Wins int,
Losses int,
Draws int,
Goals_scored int,
Goals_conceded int, 
Points int,
FOREIGN KEY (Team_name) REFERENCES Team(Team_name)
)

create table Fans
(
Average_number int not null,
Maximum_nof int not null,
Minimum_nof int not null,
Stadium_capacity int not null,
Team_name varchar(50) foreign key references Team(Team_name)
)

drop table Fans

create table Fans
(
Team_name varchar(50) primary key,
Average_number int not null,
Maximum_nof int not null,
Minimum_nof int not null,
Stadium_capacity int not null,
foreign key (Team_name) references Team(Team_name)
)

create table Contracts
(
Cid integer primary key,
Pid int,
Team_name varchar(50),
Start_d date,
Last_d date,
Salary int,
foreign key(Team_name) references Team(Team_name),
foreign key (Team_name) references Team(Team_name)
)

drop table Contracts

create table Contracts
(
Cid integer primary key,
Pid int,
Team_name varchar(50),
Start_d date,
Last_d date,
Salary int,
foreign key(Pid) references Players(Pid),
)

create table StageMatches
(
Mid int primary key,
Home_team varchar(50),
Away_team varchar(50),
Stage varchar(50),
)

create table PlayerStatistics
(
Pid int foreign key references Players(Pid),
Mid int foreign key references  StageMatches(Mid),
Matches_played int
)

create table MostAggressivePlayers
(
Pid int foreign key references Players(Pid),
Number_matches int,
Yellow_cards int, 
Red_cards int
)

drop table PlayerStatistics

create table PlayerStatistics
(
Pid int,
Mid int,
Matches_played int,
primary key (Pid, Mid),
foreign key (Pid) references Players(Pid),
foreign key (Mid) references  StageMatches(Mid)
)


drop table MostAggressivePlayers

create table MostAggressivePlayers
(
Pid int primary key,
Number_matches int,
Yellow_cards int, 
Red_cards int,
foreign key (Pid) references Players(Pid)
)

create table Records
(
Team_name varchar(50) primary key,
Trophies int,
Finals_played int,
Most_goals_season int,
Longest_undefeated_streak int,
foreign key (Team_name) references Team(Team_name)
)

drop table TopScorers

create table TopScorers
(
Team_name varchar(50) primary key,
Player_name varchar(50),
Goals_scored int not null,
Match_played int not null,
foreign key (Team_name) references Team(Team_name)
)


alter table HomeMatches 
add Match_date date;

alter table StageMatches
add Match_date date;

alter table StageMatches
add Score varchar(50);

EXEC sp_rename 'PlayerStatistics.Matches_played', 'Goal_contribution', 'COLUMN';

alter table HomeMatches
drop column Match_date;