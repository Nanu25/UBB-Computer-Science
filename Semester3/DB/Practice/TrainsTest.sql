use aa

create table TrainTypes(
	Typeid int primary key,
	TypeName varchar(50),
	TypeDesc varchar(50)
);

create table Trains(
	Tid int primary key,
	TrainName varchar(50),
	TrainType int foreign key references TrainTypes(Typeid)
)

create table Station(
	Stid int primary key,
	StName varchar(50) unique
);


create table Routes(
	Rid int primary key, 
	RouteName varchar(50) unique,
	Tid int foreign key references Trains(Tid)
)


create table Stops(
	Routeid int foreign key references Routes(Rid),
	StationId int foreign key references Station(Stid),
	Arr time,
	Dep time
	)
drop table Stops

--2. Implement a stored procedure that receives a route, a station, arrival and departure times, and adds the station 
--to the route. If the station is already on the route, the departure and arrival times are updated. 

create or alter procedure addRoute
	@routeId int,
	@stationId int,
	@arrival time,
	@departure time
as
begin
	declare @nr int
	set @nr = 0

	select @nr = Count(*)
	from Stops s
	where  s.StationId = @stationId and s.RouteId = @routeId

	if @nr = 0
		begin
			insert into Stops values (@routeId, @stationId, @arrival, @departure)
		end
	else
		begin
			update Stops
			set Arr = @arrival, Dep = @departure
			where  StationId = @stationId and RouteId = @routeId
		end
		
end
go

INSERT INTO TrainTypes VALUES(1, 'description 1', '1'), (2, 'descrition 2', '2') 
INSERT INTO Trains values (1, 'InterRegio', 1), (2, 'Intercity', 1), (3, 'Regio', 2) 
INSERT INTO Station values (1, 'Cluj-Napoca'), (2, 'Brasov'), (3, 'Bucuresti') 
Insert into Routes values (1, 'Sighisoara', 1), (2, 'Medias', 2) 
INSERT Stops VALUES(1,1,'12:00:00', '18:00:00'), (1,2,'15:30:00', '22:42:00'), 
(2,2,'08:05:00', '21:48:00')  

select * from Stops  
EXEC addRoute 2,1, '5:00:00', '9:00:00' 
select * from Stops 
EXEC addRoute 2,1, '5:00:00', '12:00:00' 
exec addRoute 1,3, '1:20:00', '3:23:00'

--3. Create a view that shows the names of the routes that pass through all the stations.  

create view Names as
	select r.RouteName
	from Routes r inner join Stops s on r.Rid = s.RouteId
	group by r.RouteName
	having count(*) = (select COUNT(*) from Station)

go


select * from Names

--4. Implement a function that lists the names of the stations with more than R routes, where R is a function parameter.

create or alter function ListNames (@R int)
	returns table
as
	return select s.StName
	from Station s inner join Stops st on s.Stid = st.StationId
	group by s.Stname
	having count(*) >= @R
go

Select * from ListNames(1)
