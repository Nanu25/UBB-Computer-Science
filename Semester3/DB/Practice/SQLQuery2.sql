create table ShoeModel(
	Smid int primary key identity(1, 1),
	Smname varchar(50),
	Season varchar(50)
)

create table Shoes(
	Shid int primary key identity(1, 1),
	Smid int,
	Price decimal (5, 2),
	foreign key (Smid) references ShoeModel(Smid)
)

create table Woman(
	Wid int primary key identity(1, 1),
	Wname varchar(50),
	Amount decimal (5, 2)
)

create table PresentationShop(
	Psid int primary key identity(1, 1),
	Psname varchar(50),
	Pscity varchar(50),
)
drop table PresentationShop

create table PresentationShoeShop(
	Pssid int primary key identity (1, 1),
	Psid int, 
	Shid int,
	Nrs int,
	foreign key (Psid) references PresentationShop(Psid),
	foreign key (Shid) references Shoes(Shid)
)


create table Buy (
	Bid int primary key identity(1, 1),
	Wid int,
	Shid int,
	Amount decimal (5,2),
	foreign key (Wid) references Woman(Wid),
	foreign key (Shid) references Shoes(Shid)
)
insert into Buy values (1, 1, 10), (2, 1, 15), (1, 1, 20)

insert into Woman values ('Ana', 154.50), ('Alexandra', 198.32) 
select * from Woman

insert into ShoeModel values ('Jordan', 'Summer'), ('Puma', 'Winter') 

insert into Shoes values (1, 100.43), (1, 150.32), (2, 90)
insert into PresentationShop values ('Gucci', 'Mizil'), ('Tommy', 'Vadu')

create or alter procedure AddPresentationShop(
	@Psid int,
	@Shid int, 
	@cnt int
	)
as
	begin
		declare @ok int
		declare @ok1 int

		select @ok = Count(*) 
		from PresentationShop p
		where p.Psid = @Psid
		select @ok1 = Count(*) from Shoes s where s.Shid = @Shid
		if @ok = 0 or @ok1 = 0 
		begin
			raiserror('Invalid data', 10, 1)
			return
		end

		declare @nr int
		
		select @nr = Count(*)
		from PresentationShoeShop p
		where p.Psid = @Psid and p.Shid = @Shid
		
		if @nr = 0
		begin
			insert into PresentationShoeShop values (@Psid, @Shid, @cnt) 
			return
		end

		update PresentationShoeShop 
		set Nrs = Nrs + @cnt
		where Psid = @Psid and Shid = @Shid

	end
go

select * from PresentationShoeShop

exec AddPresentationShop 1, 1, 10
exec AddPresentationShop 2, 2, 1
exec AddPresentationShop 1, 2, 1
exec AddPresentationShop 1, 1, 10
exec AddPresentationShop 1, 6, 10
exec AddPresentationShop -1, 1, 10


create or alter function ShowWoman(@Shid int)
returns table
as
return (
    select w.Wname
    from Woman w
    inner join Buy b on b.Wid = w.Wid
    where b.Shid = @Shid
    group by w.Wname
    having count(b.Shid) > 1
)

select * from ShowWoman(1)


create or alter function ShowShoe (@t int)
returns table
as
	return 
		select s.Shid
		from Shoes s
		inner join PresentationShoeShop ps on ps.Shid = s.Shid
		group by s.Shid
		having count(distinct ps.Psid) >= @t

go

select * from ShowShoe(2)