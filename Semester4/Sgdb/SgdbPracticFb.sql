 --Create a database for a MiniFacebook system. The entities of interest to the problem domain are: Users, 
--Pages, Likes, Categories, Posts, and Comments. Each user has a name, current city and date of birth. A user can 
--like multiple pages. The system stores the date of each like. A page has a name and a category, e.g., sports, 
--movies, music, etc. A category also has a category description. Users write posts and comment on existing posts. -
--A user’s post has a date, text, and number of shares. A comment is anonymous, has a text, a date, and a flag 
--indicating whether it’s a top comment for the corresponding post. 
--1. Write an SQL script that creates the corresponding relational data model.  

create table Users (
	[Uid] int primary key identity,
	[Name] varchar(50),
	City varchar(50),
	Bday date
)



create table Categories (
	Cid int primary key identity,
	[Name] varchar(50),
	[Description] varchar(50)
	)


create table Pages(
	Pid int primary key identity,
	Cid int foreign key references Categories (Cid)
)

create table PageLike(
	Lid int primary key identity,
	[Uid] int foreign key references Users ([Uid]),
	Pid int foreign key references Pages (Pid),
	[Date] datetime
	)
CREATE TABLE Posts (
	Pid INT PRIMARY KEY IDENTITY,
	[Uid] INT FOREIGN KEY REFERENCES Users ([Uid]),
	[Date] DATE,  -- changed from DATETIME to DATE
	[Text] VARCHAR(50),
	Shares INT
);
drop table Posts
delete from Posts
ALTER TABLE Posts
ALTER COLUMN [Date] DATE;

create table Comments (
	Cid int primary key identity, 
	[Text] varchar(50),
	[Date] date,
	[Top] int
	)

create table PostComments(
	Pid int foreign key references Posts(Pid),
	Cid int foreign key references Comments(Cid)
	)

INSERT INTO Users ([Name], City, Bday)
VALUES 
('Alice Johnson', 'New York', '1990-05-12'),
('Bob Smith', 'Los Angeles', '1988-09-23'),
('Charlie Brown', 'Chicago', '1995-11-03');


INSERT INTO Posts ([Uid], [Date], [Text], Shares)
VALUES 
(1, GETDATE(), 'Excited to join!', 10),
(2, GETDATE(), 'Ready to post updates.', 5);