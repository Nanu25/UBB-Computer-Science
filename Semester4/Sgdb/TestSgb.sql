use SgdbT

create table BookStore(
	Bsid int primary key identity,
	[Name] varchar(50),
	City varchar(50),
	Street varchar(50),
	Number int
	)

insert into BookStore values
('Anc', 'Cluj', 'Bulevardul Rep', 12)

create table Employers(
	Eid int primary key identity,
	Bsid int foreign key references BookStore(Bsid),
	[Name] varchar(50),
	Surname varchar(50),
	Gender varchar(50),
	Experience int
	)

create table BookType(
	Btid int primary key identity,
	[Name] varchar(50),
	[Description] varchar(50)
	)

insert into BookType
values ('Luceafarul', 'Poezie')

create table Books(
	Bid int primary key identity,
	Btid int foreign key references BookType(Btid),
	Title varchar(50),
	Publisher varchar(50),
	No_page int
	)

create table AvailableBooks (
	Id int primary key identity,
	Bsid int foreign key references BookStore(Bsid),
	Bid int foreign key references Books(Bid),
	Price int,
	Copies int
	)

SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
BEGIN TRANSACTION
SELECT * FROM BookType
WAITFOR DELAY '00:00:10'
SELECT * FROM BookType
COMMIT TRANSACTION
