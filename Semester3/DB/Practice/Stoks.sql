-- Create a database to manage services offered by a stock exchange. The database will store data about all the intermediaries involved in trading. 
-- The entities of interest to the problem domain are: Clients, Brokers, StockExchange, Stocks and Bonds. 
-- A client has a name and a unique identification number. 
-- Clients can work with multiple brokers. 
-- A broker has a name and a list of clients. Brokers can work with multiple stock exchanges. 
-- A stock exchange has a list of brokerage companies containing all the brokers the exchange 
-- is working with Multiple stocks or bonds can be listed on the same exchange.
--  Both stocks and bonds have a name and the identification number of the client which bought it through a broker.
-- 2. Implement a stored procedure that receives a client and returns all the stocks and bonds names bought
-- by the client and also the name of the brokerage company through which the client made the purchases.
-- 3. Create a view that shows all the stocks bought by the clients from identification numbers of those clients.
-- 4. Implement a function that lists the identification numbers of the clients which are investing in multiple stock exchanges.

create table Clients (
	Cid int primary key identity(1, 1),
	Cname varchar(50)
)

create table Brokers(
	Bid int primary key identity(1, 1),
	Bname varchar(50)
)

create table Stocks (
	Stid int primary key identity(1, 1),
	Cid int,
	Bid int, 
	Seid int,
	Sname varchar(50),
	foreign key (Cid) references Clients(Cid),
	foreign key (Bid) references Brokers(Bid),
	foreign key (Seid) references StockExchange(Seid)
	)
drop table Stocks

create table Bonds (
	Boid int primary key identity(1, 1),
	Cid int,
	Bid int, 
	Seid int,
	Sname varchar(50),
	foreign key (Cid) references Clients(Cid),
	foreign key (Bid) references Brokers(Bid),
	foreign key (Seid) references StockExchange(Seid)
	)
drop table Bonds


create table StockExchange(
	Seid int primary key identity(1, 1),
	Sename varchar(50)
)




insert into Clients values ('Alex'), ('Ion')
insert into Brokers values ('Andrei'), ('Ana')

insert into StockExchange values ('Binance'), ('Etoro')

insert into Stocks values (1, 1, 1, 'SP'), (1, 2, 1, 'BTC')
insert into Stocks values (1, 1, 2, 'SP50')

insert into Bonds values (2, 2, 1, 'EUR'), (1, 2, 2, 'USD')

-- 2. Implement a stored procedure that receives a client and returns all the stocks and bonds names bought
-- by the client and also the name of the brokerage company through which the client made the purchases.

create or alter procedure FindClient(
    @cid int
)
as
begin
    select 
		C.Cname,
        s.Sname as StockName, 
        b.Sname as BondName, 
        br.Bname as BrokerName
    from 
        Clients c
    left join Stocks s on s.Cid = c.Cid
    left join Brokers br on br.Bid = s.Bid
    left join Bonds b on b.Cid = c.Cid and b.Bid = br.Bid
    where c.Cid = @cid
end
go


Exec FindClient 1

-- 4. Implement a function that lists the identification numbers of the clients which are investing in multiple stock exchanges.

create or alter function ShowClients()
	returns table
as
	return 
		select c.Cid
		from Clients c
		inner join Stocks as s on s.Cid = c.Cid 
		group by c.Cid
		having Count(distinct s.Seid) > 1
go

select * from ShowClients()