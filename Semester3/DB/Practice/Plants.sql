create table Category(
	Cid int primary key identity(1, 1),
	Cname varchar(50) unique,
	Descrip varchar(50)
	)

create table Locations(
	Lid int primary key identity(1, 1),
	Lname varchar(50) unique,
	Descrip varchar(50)
	)

create table Plants(
	Pid int primary key identity(1, 1),
	Lid int,
	Pname varchar(50) unique,
	Adate date,
	Lastwater date,
	foreign key (Lid) references Locations(Lid)
	)


create table Imagine(
	Iid int primary key identity(1, 1),
	Pid int,
	Cid int,
	Ipath varchar(50) unique,
	Caption varchar(50),
	Upload date,
	foreign key (Pid) references Plants(Pid),
	foreign key (Cid) references Category(Cid)
	)
drop table Imagine

create table CareHistory(
	Chid int primary key identity(1, 1),
	Pid int,
	Chdate date,
	Chtime time,
	foreign key (Pid) references Plants(Pid)
)

insert into Locations values ('Mizil' , 'The best City'), ('Cluj', 'Forta Steaua')
insert into Category values ('Aaa', 'd'), ('Bbb', 'g')
insert into Imagine values (1, 2, 'aaa', 'a', '2023-02-03'), (1, 1, 'b', 'bbb', '2024-03-03'), (2, 1, 'b4', 'bbb', '2024-03-03') 
select * from Imagine

insert into CareHistory values (1, '2020-3-3', '1:3:2')
insert into CareHistory values (1, '2024-3-4', '1:34:2'), (2, '2023-4-1', '12:3:2')


create or alter procedure addPlant(@Lid int, @Name varchar(50), @Acdate date, @Lastw date)
as
	begin
		declare @nr int
		select @nr = Count(*)
		from Plants p
		where p.Pname = @Name

		if @nr = 0
		begin
			insert into Plants values (@Lid, @Name, @Acdate, @Lastw)
			return
		end

		update Plants
		set Adate = @Acdate
		where Pname = @Name

	end
go


exec addPlant 1, 'Trandafir', '2023-02-03', '2024-01-03'
select * from Plants
exec addPlant 1, 'Trandafir', '2024-02-03', '2024-04-03'
exec addPlant 2, 'Mac', '2024-02-03', '2024-03-03'
exec addPlant 1, 'Crin', '2022-02-03', '2023-12-03'

create or alter view displayPlants
as
	select L.Lname, Count(p.Pid) as Pcount, Min(p.Adate) as Adate
	from Locations L
	inner join Plants p on L.Lid = p.Lid
	group by Lname
go

select * from displayPlants

--plant with at least X imagines and minimum cared date
create or alter function PlantX(@X int)
	returns varchar(50)
as
begin
	declare @plant varchar(50)

	select  top 1 @plant = p.Pname
	from Plants p
	inner join Imagine i on i.Pid = p.Pid
	inner join CareHistory ch on ch.Pid = p.Pid
	group by p.Pname
	having count(i.Iid) >= @X and min(ch.Chdate) = (select min(Chdate) from CareHistory)

	return @plant
end
go

SELECT dbo.PlantX(2);
