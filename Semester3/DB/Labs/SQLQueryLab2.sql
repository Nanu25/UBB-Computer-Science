USE Lab1;
GO

insert into Team(Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points) values ('FCSB', 10, 9, 0, 1, 17, 5, 28);
SELECT * from Team;
INSERT INTO Team (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points) 
VALUES 
('Manchester City', 10, 8, 1, 1, 20, 8, 25),
('Real Madrid', 10, 5, 4, 1, 12, 6, 16),
('Bayern Munich', 10, 8, 1, 1, 24, 7, 25),
('Barcelona', 10, 7, 2, 1, 18, 10, 22);

SELECT * FROM Team;

insert into Players(Pid, First_name, Last_name, Goals_scored, Assists_made, Team_name) values
(1, 'Leo', 'Messi', 10, 5, 'FCSB'),
(2, 'Darius', 'Olaru', 5, 10, 'FCSB'),
(3, 'Zlatan', 'Ibrahimovic', 7, 2, 'Barcelona')
--integrity error.
insert into Players(Pid, First_name, Last_name, Goals_scored, Assists_made, Team_name) values
(4, 'De', 'Bruyne', 2, 10, 'Juventus')

SELECT * FROM Players;

INSERT INTO StageMatches (Mid, Home_team, Away_team, Stage, Match_date, Score)
VALUES
(1, 'FCSB', 'Barcelona', 'UCL', '2024-02-24', '3-1'),  -- February doesn't have 30 days, so adjust the date
(2, 'Bayern Munich', 'Manchester City', 'UEL', '2024-01-24', '2-2'),
(3, 'Real Madrid', 'FCSB', 'UCL', '2023-12-14', '0-2'),
(4, 'Real Madrid', 'Barcelona', 'UCL', '2023-11-10', '0-1');

SELECT * FROM StageMatches;

insert into PlayerStatistics(Pid, Mid, Goal_contribution)
values
(2, 1, 2);

insert into PlayerStatistics(Pid, Mid, Goal_contribution)
values
(1, 2, 3),   
(3, 1, 1),  
(2, 3, 1),   
(3, 4, 2);   

Select * from PlayerStatistics;

INSERT INTO Players (Pid, First_name, Last_name, Goals_scored, Assists_made, Team_name) 
VALUES
(5, 'Cristiano', 'Ronaldo', 15, 7, 'Manchester City'),
(6, 'Karim', 'Benzema', 12, 5, 'Real Madrid'),
(7, 'Robert', 'Lewandowski', 20, 3, 'Bayern Munich'),
(8, 'Sergio', 'Ramos', 3, 1, 'Real Madrid'),
(9, 'Neymar', 'Jr', 10, 8, 'Barcelona');

INSERT INTO MostAggressivePlayers (Pid, Number_matches, Yellow_cards, Red_cards)
VALUES
(8, 250, 120, 25),
(5, 500, 85, 5),   
(7, 400, 55, 1),   
(9, 300, 70, 6),   
(6, 350, 60, 3);    

INSERT INTO Records (Team_name, Trophies, Finals_played, Most_goals_season, Longest_undefeated_streak)
VALUES
('Manchester City', 25, 15, 100, 25),
('Real Madrid', 35, 20, 120, 30),
('Barcelona', 30, 22, 110, 27),
('FCSB', 67, 30, 125, 60);

INSERT INTO TopScorers (Team_name, Player_name, Goals_scored, Match_played)
VALUES
('Manchester City', 'Cristiano Ronaldo', 15, 10),
('Real Madrid', 'Karim Benzema', 12, 10),
('Bayern Munich', 'Robert Lewandowski', 20, 10);


INSERT INTO Contracts (Cid, Pid, Team_name, Start_d, Last_d, Salary)
VALUES
(1, 1, 'FCSB', '2023-01-01', '2026-01-01', 2000000),  
(2, 5, 'Manchester City', '2022-07-01', '2025-07-01', 1500000),
(3, 6, 'Real Madrid', '2021-06-01', '2024-06-01', 1800000),
(4, 7, 'Bayern Munich', '2023-02-01', '2026-02-01', 1700000),
(5, 9, 'Barcelona', '2022-08-01', '2025-08-01', 1600000);

INSERT INTO Fans (Team_name, Average_number, Maximum_nof, Minimum_nof, Stadium_capacity)
VALUES
('FCSB', 50000, 55000, 45000, 60000),   
('Manchester City', 45000, 50000, 40000, 55000),
('Real Madrid', 48000, 52000, 45000, 60000),
('Bayern Munich', 47000, 51000, 43000, 58000),
('Barcelona', 46000, 50000, 42000, 55000);

INSERT INTO HomeMatches (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
VALUES
('FCSB', 10, 9, 0, 1, 30, 5, 28),  
('Manchester City', 10, 7, 1, 2, 25, 10, 23),
('Real Madrid', 10, 6, 2, 2, 20, 15, 20),
('Bayern Munich', 10, 8, 1, 1, 28, 8, 25),
('Barcelona', 10, 7, 2, 1, 26, 12, 22);

select * from HomeMatches

INSERT INTO Team (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
VALUES
('Atalanta', 10, 6, 3, 1, 21, 12, 19),
('Valencia', 10, 5, 4, 1, 15, 10, 16);

select * from Team

INSERT INTO Players (Pid, First_name, Last_name, Goals_scored, Assists_made, Team_name)
VALUES
(10, 'Duván', 'Zapata', 10, 3, 'Atalanta'),
(11, 'Carlos', 'Soler', 7, 5, 'Valencia');

INSERT INTO StageMatches (Mid, Home_team, Away_team, Stage, Match_date, Score)
VALUES
(5, 'Valencia', 'Atalanta', 'UEL', '2024-02-15', '1-2');

INSERT INTO HomeMatches (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
VALUES
('Atalanta', 10, 6, 3, 1, 21, 12, 19),
('Valencia', 10, 5, 4, 1, 15, 10, 16);

INSERT INTO Fans (Team_name, Average_number, Maximum_nof, Minimum_nof, Stadium_capacity)
VALUES
('Atalanta', 35000, 40000, 30000, 45000),
('Valencia', 45000, 50000, 40000, 55000);

INSERT INTO Contracts (Cid, Pid, Team_name, Start_d, Last_d, Salary)
VALUES
(6, 10, 'Atalanta', '2023-01-01', '2025-01-01', 1200000), 
(7, 11, 'Valencia', '2022-06-01', '2025-06-01', 1100000); 

select * from Fans;

update Fans
set Average_number = 30000
where Team_name LIKE '%a' and Stadium_capacity >= 47000

update Fans
set Stadium_capacity = Stadium_capacity + 2000
where Minimum_nof < 10000

select * from Fans;
select * from Contracts

update Contracts
set Salary = Salary + 5
where  Team_name LIKE 'FCSB'

update Contracts
set Salary = Salary * 1.1
where Last_d < '2025-01-01';

select * from Contracts

select * from TopScorers

update TopScorers
set Goals_scored = Goals_scored + 2
where Goals_scored between 16 and 20 OR Team_name LIKE '%d'

update TopScorers
set Match_played = Match_played + 2
where Goals_scored > 20;

update Team
set Points = Points + 3
where Wins > 8;

update Team
set Goals_conceded = Goals_conceded - 1
where Draws < 5;

update StageMatches
set Score = '1-1'
where Home_team = 'Real Madrid' AND Score LIKE '0-%';

update StageMatches
set Match_date = '2024-06-15'
where Stage = 'UEL';

update HomeMatches
set Goals_conceded = Goals_conceded - 2
where Wins > 5;

update HomeMatches
set Matches_played = Matches_played + 1
where draws < 3;

update Playerstatistics
set Goal_contribution = Goal_contribution + 4
where mid > 2;

update Playerstatistics
set goal_contribution = 0
where goal_contribution < 5;

update Records
set Trophies = Trophies + 1
where finals_played > 3;

update Records
set Most_goals_season = Most_goals_season - 5
where Longest_undefeated_streak > 15;

update MostAggressivePlayers
set Yellow_cards = Yellow_cards + 1
where Number_matches > 10;

update MostAggressivePlayers
set Red_cards = Red_cards + 1
where Yellow_cards > 5;

update Players
set Goals_scored = Goals_scored + 2
where assists_made > 10;

update Players
set Assists_made = 0
where team_name = 'bayern munich' and goals_scored < 5;



select * from TopScorers


--delete section

INSERT INTO Team (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
VALUES
('Braila', 1, 0, 0, 0, 1, 1, 1),
('Alba', 1, 1, 0, 0, 0, 0, 0);

delete Team
where Team_name  LIKE '%a' and Matches_played = 1

select * from Team

insert into Players(Pid, First_name, Last_name, Goals_scored, Assists_made, Team_name) values
(12, 'Hugo', 'Lloris', 0, 0, 'FCSB'),
(13, 'Sergio', 'Fernandez', 1, 0, 'FCSB');


insert into Team (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
values ('team_x', 0, 0, 0, 0, 0, 0, 0),
	 ('team_y', 0, 0, 0, 0, 0, 0, 0)

insert into HomeMatches (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
values ('team_x', 5, 1, 3, 1, 5, 10, 4),
('team_y', 1, 3, 4, 1, 5, 11, 3);

delete from HomeMatches
where team_name = 'team_x';

delete from HomeMatches
where team_name = 'team_y';

delete from Team
where Team_name = 'team_x';

delete from Team
where Points = 0

insert into PlayerStatistics (Pid, Mid, Goal_contribution)
values 
(99, 10, 2),
(88, 11, 1),
(77, 12, 4);

delete from PlayerStatistics
where pid == 77;

delete from PlayerStatistics
where pid >= 77;

insert into Records(Team_name, Trophies, Finals_played, Most_goals_season, Longest_undefeated_streak)
values 
('test_team_1', 1, 1, 10, 5)

delete from Records
where Team_name = 'test_team_1' and Trophies = 1

insert into Players (Pid, First_name, Last_name, Goals_scored, Assists_made, Team_name)
values 
(55, 'john', 'doe', 1, 2, 'Real Madrid'),
(102, 'jane', 'doe', 3, 1, 'Real Madrid'),
(103, 'jack', 'smith', 4, 0, 'Real Madrid');

delete from Players
where pid = 101;

insert into MostAggressivePlayers (Pid, Number_matches, Yellow_cards, Red_cards)
values 
(55, 15, 5, 1),
(102, 18, 7, 2),
(103, 20, 10, 3);

delete from MostAggressivePlayers
where Pid = 55;

delete from MostAggressivePlayers
where Pid >= 100 and Pid <= 105;

delete Players 
where Goals_scored in (0,1)

insert into players (pid, first_name, last_name, goals_scored, assists_made, team_name)
values (777, 'contract', 'player', 3, 5, 'contract_team');

insert into team (team_name, matches_played, wins, losses, draws, goals_scored, goals_conceded, points)
values ('contract_team', 0, 0, 0, 0, 0, 0, 0);

insert into contracts (cid, pid, team_name, start_d, last_d, salary)
values (100, 777, 'contract_team', '2024-01-01', '2025-12-31', 1),
(101, 777, 'contract_team', '2024-01-01', '2025-2-31', 1);

delete from contracts
where cid = 100;

delete from Contracts
where Salary = 1;

delete from players
where pid = 777;

delete from team
where team_name = 'contract_team';

insert into team (team_name, matches_played, wins, losses, draws, goals_scored, goals_conceded, points)
values ('fan_team', 0, 0, 0, 0, 0, 0, 0);

insert into fans (team_name, average_number, maximum_nof, minimum_nof, stadium_capacity)
values ('fan_team', 25000, 50000, 10000, 60000);

delete from fans
where team_name = 'fan_team';

delete from fans
where Team like 'X%'

delete from team
where team_name = 'fan_team';

insert into team (team_name, matches_played, wins, losses, draws, goals_scored, goals_conceded, points)
values ('record_team', 0, 0, 0, 0, 0, 0, 0);

insert into records (team_name, trophies, finals_played, most_goals_season, longest_undefeated_streak)
values ('record_team', 3, 1, 22, 10);

delete from records
where team_name = 'record_team';

delete from Records
where Team_name like '%z'

delete from team
where team_name = 'record_team';


insert into team (team_name, matches_played, wins, losses, draws, goals_scored, goals_conceded, points)
values ('top_team', 0, 0, 0, 0, 0, 0, 0);

insert into TopScorers (team_name, player_name, goals_scored, match_played)
values ('top_team', 'top_player', 20, 15);

delete from TopScorers
where team_name = 'top_team';

delete from TopScorers
where Team_name like '%x_'

delete from team
where team_name = 'top_team';

select * from Players

select *
from Players
where Goals_scored >= 10
union
select *
from Players
where Team_name like 'F%'

select Team_name
from TopScorers
where Goals_scored >= 20 or Team_name like 'M%'
union
select Team_name
from Team
where Wins >= 8

select * 
from Contracts
where Salary >= 1500000
intersect
select *
from Contracts
where Team_name like '_____%'
order by Team_name


select Team_name
from Fans
where Stadium_capacity in (45000, 55000, 60000)
intersect
select Team_name
from Team
where Points >= 20
order by Team_name



select * 
from HomeMatches
where Wins > 3
except
select *
from HomeMatches
where Wins not in (6, 7)

select *
from MostAggressivePlayers
where Red_cards > 3
except
select *
from MostAggressivePlayers
where Pid = 5

INSERT INTO Team (Team_name, Matches_played)
VALUES ('Dinamo', 1);

delete Team
where Team_name like 'Dinamo'

select *
from Contracts c inner join Players p
on c.Pid = p.Pid

insert into Players(Pid, First_name, Last_name, Team_name)
values
(15, 'Mike', 'Owens', 'Real Madrid'),
(16, 'Leroy', 'Sane', 'Bayern Munich')

insert into Contracts(Cid, Pid, Team_name)
values
(15, 15, 'Real Madrid'),
(16, 16, 'Bayern Munich')

SELECT *
FROM Contracts c
LEFT JOIN Players p ON c.Pid = p.Pid
LEFT JOIN Team t ON p.Team_name = t.Team_name;

select *
from PlayerStatistics ps
right join Players p on p.Pid = ps.Pid
right join StageMatches sg on sg.Mid = ps.Mid

select *
from Contracts c full outer join Players p 
on c.Pid = p.Pid

select Team_name
from Team t
where t.Team_name in 
	(select Team_name 
	from TopScorers ts
	where ts.Player_name LIKE '%i')


select First_name, Last_name
from Players p
where p.Team_name in
	(select Team_name
	from Team t
	where t.Team_name in
		(select Team_name
		from Fans
		where fans.Average_number >= 45000)
	)

Select top 3 *
from Records r
where exists 
	(Select Team_name
	from HomeMatches hm
	where hm.Goals_scored between 15 and 23 and hm.Draws <= 5)

Select top 3 *
from MostAggressivePlayers map
where exists 
	(
		select Team_name
		from Players p
		where p.Team_name like 'R%' or p.Team_name like 'F%'
	)

select distinct Home_team
from (
	select Home_team
	from StageMatches sm
	where sm.Stage LIKE 'UCL'
	) A 


select distinct Pid
from (
	select Pid
	from PlayerStatistics ps
	where ps.Pid  = 3 or ps.Goal_contribution > 2
	) A

select p.Team_name, COUNT(p.Pid) as np
from Players p
group by p.Team_name;


insert TopScorers Values
('FCSB', 'Leo Messi', 50, 30)

insert TopScorers Values
('Barcelona', 'Leo Messi', 40, 25)

insert TopScorers Values
('Atalanta', 'Cristiano Ronaldo', 17, 30)

insert TopScorers values
('Valencia', 'Leo Messi', 2, 10)



select Player_name, AVG(Goals_scored) as gs
from TopScorers ts
group by ts.Player_name
having AVG(Goals_scored) > 17

select *
from  PlayerStatistics

select Pid, SUM(Goal_contribution) as gc
from PlayerStatistics ps
group by ps.Pid
having SUM(Goal_contribution) >= (
	select max(Goal_contribution) from PlayerStatistics
	)

select distinct Home_team, count(Mid) as mi
from StageMatches
group by Home_team
having count(Mid) * 3 > (select min(Goals_conceded) from Team)


select Team_name
from Team t
where t.Points > all(
	select MAX(Matches_played)
	from HomeMatches hm
	where hm.Team_name like '%a'
	)
order by -t.Points

select Team_name
from Team t
where t.Points > (
	select MAX(Matches_played)
	from HomeMatches hm
	where hm.Team_name like '%a'
	)
order by -t.Points

select Last_name
from Players p
where p.Assists_made < any(
	select Goal_contribution
	from PlayerStatistics ps
	where ps.Pid >= 1 and ps.Pid <= 5
	)

select Last_name
from Players p
where p.Assists_made < (
	select Max(Goal_contribution)
	from PlayerStatistics ps
	where ps.Pid >= 1 and ps.Pid <= 5
	)

select *
from Contracts c
where c.Team_name <>all(
	select top 3 Team_name
	from Team t
	where t.Wins >= 7
	)

select *
from Contracts c
where c.Team_name not in (
    select top 3 Team_name
    from Team t
    where t.Wins >= 7  
)

	

INSERT INTO Contracts (Cid, Pid, Team_name, Start_d, Last_d, Salary)
VALUES (11, 1, 'Real Madrid', '2023-01-01', '2024-12-31', 30000);


select *
from Fans f
where f.Minimum_nof = any (
		select Salary
		from Contracts c
		where c.Salary > (
			select min(Salary)
			from Contracts
		)
	)

select *
from Fans f
where f.Minimum_nof in (
		select Salary
		from Contracts c
		where c.Salary > (
			select min(Salary)
			from Contracts
		)
	)