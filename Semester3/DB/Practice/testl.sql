create table Student(
	Stid int primary key identity(1, 1),
	Sname varchar(50),
	Byear int,
	Mail varchar(50),
	Major varchar(50)
)

create table Teacher(
	Tid int primary key identity(1, 1),
	Tname varchar(50),
	Byear int,
	Mail varchar(50),
	Phone varchar(50),
	Area varchar(50)
)

create table Course(
	Cid int primary key identity(1, 1),
	Tid int,
	Cname varchar(50),
	Domain varchar(50),
	foreign key (Tid) references Teacher(Tid)
	)

create table Catalogs(
	Cid int primary key identity(1, 1),
	Stid int,
	Tid int,
	Grade int,
	Gdate date,
	foreign key (Stid) references Student(Stid),
	foreign key (Tid) references Teacher(Tid)

)

create table CourseGrade(
	Gcid int primary key identity(1, 1),
	Stid int,
	Cid int,
	Grade int,
	foreign key (Stid) references Student(Stid),
	foreign key (Cid) references Course(Cid)
)
drop table CourseGrade

insert into Student values ('Andrei', 2003, 'an@gmail', 'bbc'), ('Ioana', 2030, 'i@gmail', '1b')
insert into Teacher values ('Alex', 1980, 'alex@gmail', '078', 'Math'), ('Mihai', 1959, 'm@gmail', '094', 'Info')
insert into Teacher values ('Dan', 1980, 'dan@gmail', '073', 'En'), ('Rusu', 1954, 'r@gmail', '094', 'OS')

insert into Course values (1, 'DB', 'Info'), (2, 'PS', 'Math')
insert into Course values (4, 'Os', 'Info')



create or alter procedure AddGrade(@Sid int, @Tid int, @Grade int, @Date date) as
begin
	declare @nr int
	select @nr = Count(*)
	from Student
	where Stid = @Sid

	declare @nr1 int
	select @nr1 = Count(*)
	from Teacher
	where Tid = @Tid

	if @nr = 1 and @nr1 = 1
	begin
		insert into Catalogs values (@Sid, @Tid, @Grade, @Date)
		return
	end

	raiserror('Invalid input', 10, 1)

end
go


Exec AddGrade 1, 1, 10, '2024-02-03'
select * from Catalogs
Exec AddGrade 1, 2, 10, '2024-03-03'
Exec AddGrade 2, 2, 10, '2024-03-03'
Exec AddGrade 1, 4, 10, '2024-03-03'
Exec AddGrade 3, 4, 10, '2024-03-03'

Exec AddGrade 1, 6, 10, '2024-02-03'


insert into CourseGrade values (1, 1, 10), (1, 2, 10), (2, 2, 10)
insert into CourseGrade values (1, 3, 10)

create or alter view ShowStud
as
	select s.Sname
	from Student s
	inner join CourseGrade cg on cg.Stid = s.Stid
	group by s.Sname
	having count(*) = (select Count(*) from Course)
go

select * from ShowStud


create or alter function ShowTeachers(@N int)
	returns table
as
	return 
		select t.Tname
		from Teacher t
		inner join Catalogs c on c.Tid = t.Tid
		group by t.Tname
		having Count(distinct c.Stid) >= @N
go

select * from ShowTeachers(3)