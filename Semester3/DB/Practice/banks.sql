-- Create a database to manage services offered by banks. The database will store data about the all the services
-- provided by banks. The entities of interest to the problem domain are: Clients, Banks, BankingServices and
-- InvestingServices. A client has a name and unique identification number, also each client can work with
-- multiple banks. A bank has a list of clients containing the name of the client and the identification number.
-- Also, one bank can offer multiple banking services or multiple investing opportunities. Banking services have a
-- list of clients which chose at least one service of this type, the list is composed only of identification numbers.
-- Investing services contains a list of clients as well, which chose at least one service of this type, but the list is
-- composed of client names.
-- 1. Write an SQL script that creates the corresponding relational data model.
-- 2. Implement a stored procedure that receives a bank and a client, if a client chose the banking services add
-- his identification number into the banking services list, do the same thing if the client chose investing services
-- but this time add his name into the investing services list, in case we have the same name multiple
-- times(investing services list) you may have to add the identification number as well. If a client chooses both
-- services add the necessary data of that client to both lists (based on what was described above).
	-- 3. Create a view that shows all the clients which chose both banking and investing services, for each client of
	-- that type show the identification number, name and which number the client is on both lists(each list has a
	-- specific number of clients, in ascending order).
-- 4. Implement a function that lists the names of the clients which are working with multiple banks and the
-- services used from each bank.

create table Client(
	Cid int primary key,
	Cname varchar(50) not null
)

create table Bank(
	Bid int primary key,
	Cname varchar(50) not null
)

create table BankService(
	Svid INT PRIMARY KEY IDENTITY(1,1),
	Cid int,
	Bid int,
	foreign key (Cid) references Client(Cid),
	foreign key (Bid)  references Bank(Bid)
);

drop table BankService

create table InvestService(
	Svid int primary key identity(1,1),
	Cid int,
	Bid int,
	Cname varchar(50) not null,
	foreign key (Cid) references Client(Cid),
	foreign key (Bid) references Bank(Bid)
)
drop table InvestService



create or alter procedure AddService
	@Cid int,
	@Bid int
as
	begin
		declare @Cname varchar(50)

		set @Cname = (select c.Cname from Client c where c.Cid = @Cid) 

		declare @nr int

		select @nr = Count(*)
		from BankService b
		where b.Cid = @Cid and b.Bid = @Bid

		if @nr = 0 
			begin
				insert into BankService values (@Cid, @Bid)
			end

		select @nr = Count(*)
		from InvestService i
		where i.Cid = @Cid and i.Bid = @Bid

		if @nr = 0
			begin
				insert into InvestService values (@Cid, @Bid, @Cname)
			end
	end
go


insert into Client values (1, 'Ion'), (2, 'Alex') 
insert into Client values (3, 'Mihai') 

insert into Bank values (1, 'BT'), (2, 'Rev') 

select * from BankService
select * from InvestService

exec AddService 3, 2

delete from BankService
where Svid = 3



-- 3. Create a view that shows all the clients which chose both banking and investing services, for each client of
	-- that type show the identification number, name and which number the client is on both lists(each list has a
	-- specific number of clients, in ascending order).
create or alter view ShowClients
as
	select c.Cid, 
		c.Cname,
		ROW_NUMBER() OVER (ORDER BY c.Cid) AS BankingRank,
		ROW_NUMBER() OVER (ORDER BY c.Cid) AS InvestingRank
	from Client c
	inner join BankService bs on bs.Cid = c.Cid 
	inner join InvestService i on i.Cid = c.Cid
	group by c.Cid, c.Cname
go

select * from ShowClients

--- 4. Implement a function that lists the names of the clients which are working with multiple banks and the
-- services used from each bank.
--nu afiseaza partea de investitii.
create or alter function ListClients()
	returns table
as
	return 
		select c.Cname
		from Client c
		inner join (
			select i.Cid, i.Bid
			from InvestService i
			union
			select bs.Cid, bs.Bid
			from BankService bs
		) as combined_bids on c.Cid = combined_bids.Cid
		group by c.Cname
		having COUNT(DISTINCT combined_bids.Bid) > 1
go

select * from  ListClients()