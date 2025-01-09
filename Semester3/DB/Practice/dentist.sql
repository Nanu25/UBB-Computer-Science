create table Dentist(
	Did int primary key identity (1, 1),
	Dname varchar(50),
	Phone varchar(50),
	Email varchar(50)
	)

create table Patient(
	Pid int primary key identity (1, 1),
	Pname varchar(50),
	Phone varchar(50),
	Email varchar(50),
	Paddress varchar(50)
	)
drop table Patient

create table Servicee(
	Seid int primary key identity (1, 1),
	Sname varchar(50) unique,
	Fee int
)

create table TratamentPlan(
	Tpid int primary key identity (1, 1),
	Seid int,
	Tpname varchar(50) unique,
	Duration int,
	Fee int,
	foreign key (Seid) references Servicee(Seid)
	)

create table Appoiments(
	Aid int primary key identity(1, 1),
	Tpid int,
	Did int,
	Pid int,
	Adate date,
	Atime int,
	foreign key (Tpid) references TratamentPlan(Tpid),
	foreign key (Did) references Dentist(Did),
	foreign key (Pid) references Patient(Pid)
)


-- Implement a stored procedure that receives the details of a patient and
--  adds the patient in the database. If there is already a patient with the 
--  same name, the procedure should return an error message and it
--  should not add the patient in the database.
create or alter procedure addPatient(
	@Pname varchar(50),
	@Phone varchar(50),
	@Email varchar(50),
	@Address varchar(50)
)
as
	begin
		declare @nr int
		select @nr = Count(*)
		from Patient p
		where p.Pname = @Pname

		if @nr = 0
		begin
			insert into Patient values(@Pname, @Phone, @Email, @Address)
			return
		end

		raiserror('This patient already exists', 10, 1)

	end
go

exec addPatient 'Alex', '076', 'alex@gmail', 'Cluj' 
exec addPatient 'Andrei', '075', 'and@gmail', 'Oradea' 
exec addPatient 'Alex', '026', 'al@gmail', 'Mizil' 

insert into Servicee values ('Control', 100), ('Ekg', 50)
insert into Dentist values ('Ion', '333', 'ion@'), ('Popa', '32', 'popa@')
insert into TratamentPlan values (1, 'Mentinere', 3, 500), (2, 'zzz', 30, 100)
insert into Appoiments values (1, 1, 1, '2024-02-03', 1), (1, 2, 2, '2024-03-03', 100)
insert into Appoiments values (2, 1, 1, '2024-02-05', 1), (2, 2, 2, '2025-03-03', 100)


-- create a view that displays the name of the patients that have appointments
-- scheduled for february 2024
create or alter view showPatients
as
	select p.Pname
	from Patient p
	inner join Appoiments a on a.Pid = p.Pid
	where a.Adate >= '2024-02-01' and a.Adate <= '2024-02-28'
go

select * from showPatients

-- implement a function that returns the dentist with the highest number of treatment plans
-- prescribed during appointments within a time period. The period of time is represented by a
-- start time and end time, which are function parameters. 

CREATE OR ALTER FUNCTION findDentist(@Sdate DATE, @Edate DATE)
RETURNS VARCHAR(50)
AS
BEGIN
    DECLARE @denname VARCHAR(50);
    
    SELECT TOP 1 @denname = d.Dname
    FROM Dentist d
    INNER JOIN Appoiments a ON a.Did = d.Did
    WHERE a.Adate BETWEEN @Sdate AND @Edate
    GROUP BY d.Dname
    ORDER BY COUNT(*) DESC;
    
    RETURN @denname;
END;
GO

SELECT dbo.findDentist('2024-02-01', '2024-03-28');

