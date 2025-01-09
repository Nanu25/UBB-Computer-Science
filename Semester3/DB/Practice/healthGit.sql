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