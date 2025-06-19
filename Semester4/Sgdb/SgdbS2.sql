create table Category (
	Cid int primary key identity,
	[Description] varchar(50)
	)

insert into Category 
values ('aaa'), ('bbb')

create table Projects(
	Pid int primary key identity,
	Cid int foreign key references Category (Cid),
	[Name] varchar(50),
	TeamLead varchar(50)
	)

insert into Projects
values (1, 'ana', 'alex'), (2, 'ion', 'boris')

create table Developer (
	Did int primary key identity,
	Pid int foreign key references Projects (Pid),
	[Name] varchar(50),
	Age int,
	Experience int,
	[Date] date
	)

insert into Developer
values (1,  'Andrei', 20, 2, '2025-01-04')

drop table Developer


create table Tasks(
	Tid int primary key identity, 
	Did int foreign key references Developer (Did),
	[Description] varchar(50),
	[Date] date
	)

insert into Tasks values (1, 'aaa', '2025-02-03')

create table Features(
	Fid int primary key identity,
	[Name] varchar(50),
	[Hour] int
	)

create table TaskFeatures (
	Tfid int primary key identity,
	Tid int foreign key references Tasks(Tid),
	Fid int foreign key references Features(Fid)
	)