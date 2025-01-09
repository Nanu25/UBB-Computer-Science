create table R(
	FK1 int,
	FK2 int,
	C1 varchar(50),
	C2 varchar(50),
	C3 int,
	C4 decimal (5, 2),
	C5 varchar(50),
	CONSTRAINT pk_R PRIMARY KEY(FK1, FK2)
	)
drop table R


insert into R(FK1, FK2, C1, C2, C3, C4, C5) values  
(10, 5, 'Everything She Wants', 'George Michael', 550, 250.5, 'YT20'), 
(13, 7, 'Love of My Life', 'Freddie Mercury', 800, 175.25, 'YT105'), 
(11, 16, 'Chain of Fools', 'Aretha Franklin', 925, 150.75, 'YT221'), 
(12, 15, 'I Have Nothing', 'Whitney Houston', 450, 125.5, 'YT100'), 
(5, 2, 'Human Nature', 'Michael Jackson', 275, 150.25, 'YT125'), 
(2, 2, 'All I Do', 'Stevie Wonder', 425, 125.75, 'YT250'), 
(16, 8, 'My Cherie Amour', 'Stevie Wonder', 375, 250.25, 'YT21'), 
(14, 8, 'R-e-s-p-e-c-t', 'Aretha Franklin', 175, 180.5, 'YT26'), 
(16, 18, 'Bohemian Rhapsody', 'Freddie Mercury', 275, 195.5, 'YT80'), 
(18, 16, 'Father Figure', 'George Michael', 190, 210.75, 'YT91'), 
(11, 1, 'Man in the Mirror', 'Michael Jackson', 200, 195.5, 'YT120'), 
(18, 12, 'Billie Jean', 'Michael Jackson', 190, 200, 'YT129')

--c
SELECT C2, avg(C3) AvgC3, Min(C4) MinC4
FROM R 
WHERE C1 like '%of%' or C4 < 200 
GROUP BY C2
HAVING avg(C3) >= 400

--c
SELECT * 
FROM  
(SELECT FK1, FK2, C3-C4 C3difC4 FROM R 
WHERE FK1 >= FK2) r1  
inner JOIN (SELECT FK1, FK2, C5
FROM R  
WHERE C5 like 'YT2%' and C4 > 170) r2 ON r1.FK1 = r2.FK1 AND r1.FK2 = r2.FK2 


--e
CREATE OR ALTER TRIGGER TrOnUpdate  
ON R  
FOR UPDATE AS  
DECLARE @total INT = 0 
SELECT @total = SUM(i.C4 + d.C4)
FROM deleted d INNER JOIN inserted i ON d.FK1 = i.FK1 AND d.FK2 = i.FK2
WHERE d.C4 <= i.C4 
PRINT @total 

UPDATE R 
SET C3 = 525
WHERE FK1 <= FK2  


-- Create a database for a health tracking system. The entities of interest to the problem domain are:
-- Users, Activities, Meals, Health Metrics and User Activities Journal. 
-- A user has a name, an age and a gender. Names are unique. 
-- An activity has a name and a number of calories burned per hour. Names are unique. 
-- A meal has a name and a number of calories per serving. Names are unique. 
-- The system stores data about health metrics: user, date of recording, weight, blood pressure and heart rate. 
-- Users can perform multiple activities. The system will store the date when the activity was performed and the duration (in minutes).
-- 2. Implement a stored procedure that receives the details of a health metric and adds the metric
-- in the database. If the date of recording is in the future (e.g. today is 05-01-2024 and the date of
-- recording for the health metric is 06-01-2024), the system will display an error message and it
-- will not save the health metric in the database.
-- 3. Create a view that displays the average weight and the maximum blood pressure for each user
-- based on the data recorded during the last year (2023).
-- 4. Implement a function that returns the average duration of a specific activity A for a given user
-- U, where A and U are function parameters.


create table Users (
	Usid int primary key identity(1, 1),
	Uname varchar(50) unique,
	Age int,
	Gender varchar(50)
	)

create table Meal (
	Mid int primary key identity(1, 1),
	Mname varchar(50) unique,
	Calories int
)

create table HealthMetrics (
	Hmid int primary key identity(1, 1),
	Usid int,
	Hmdate date,
	UWeight int,
	Bloodrate int,
	Hearthrate int,
	foreign key (Usid) references Users(Usid)
)

create table Activity (
	Aid int primary key identity(1, 1),
	Aname varchar(50) unique, 
	Calories int
)

create table UserActivity (
	Usid int,
	Aid int,
	ADate date,
	Duration int,
	foreign key (Usid) references Users(Usid),
	foreign key (Aid) references Activity(Aid)
)


-- 2. Implement a stored procedure that receives the details of a health metric and adds the metric
-- in the database. If the date of recording is in the future (e.g. today is 05-01-2024 and the date of
-- recording for the health metric is 06-01-2024), the system will display an error message and it
-- will not save the health metric in the database.

create or alter procedure AddHealthMetric
	@Usid int,
	@Hmdate date,
	@UWeight int,
	@Bloodrate int,
	@Hearthrate int
as
	begin
		if @Hmdate > GETDATE()
			begin
				raiserror('Invalid date', 10, 1)
				return
			end

		insert into HealthMetrics values (@Usid, @Hmdate, @UWeight, @Bloodrate, @Hearthrate)

	end
go

insert into Users values ('Ion',20, 'Male'), ('Ana', 25, 'Female'), ('Andrei', 30, 'Male')

insert into Activity values ('Eat', 500), ('Run', -300)

insert into UserActivity values (1, 1, '2024-04-02', 34), (1, 2, '2024-01-02', 54), (2, 1, '2024-04-02', 4)
insert into UserActivity values (1, 1, '2024-01-02', 100), (1, 2, '2004-01-02', 2)

exec AddHealthMetric 1, '2025-01-02', 76, 50, 70
exec AddHealthMetric 2, '2025-01-05', 67, 55, 73

exec AddHealthMetric 1, '2024-06-02', 80, 59, 90
exec AddHealthMetric 1, '2024-05-09', 90, 60, 76
exec AddHealthMetric 2, '2024-02-10', 67, 75, 73

exec AddHealthMetric 1, '2026-01-02', 76, 50, 70
select * from HealthMetrics


--3. Create a view that displays the average weight and the maximum blood pressure for each user
-- based on the data recorded during the last year (2024).

create or alter view ShowAvgMax
as
	select u.Usid, Avg(h.UWeight) as AvgWeight, Max(h.Bloodrate) as MaxBlood
	from Users u
	inner join HealthMetrics h on h.Usid = u.Usid
	where h.Hmdate >= '2024-01-01' AND h.Hmdate <= '2024-12-31'
	group by u.Usid
go

select * from ShowAvgMax

-- 4. Implement a function that returns the average duration of a specific activity A for a given user
-- U, where A and U are function parameters.


create or alter function FindAvg(@A int, @U int)
	returns int
as
	begin
	declare @ans int

	set @ans = (select AVG(ua.Duration) as avgDuration
				from UserActivity ua
				where ua.Usid = @U and ua.Aid = @A
				)
	return @ans

	end
go

declare @ans int
select @ans = dbo.FindAvg(2, 1);
select @ans;

