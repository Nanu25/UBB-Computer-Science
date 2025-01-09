create table ATM (
	Aid int primary key identity(1, 1),
	Adr varchar(50)
	)

create table Customer(
	Cid int primary key identity(1, 1),
	CName varchar(50),
	Bday date,
	)

create table BankAcc(
	Baid int primary key identity(1, 1),
	Cid int,
	IBAN varchar(50),
	Balance int,
	foreign key (Cid) references Customer(Cid)
)
drop table BankAcc

create table Cards(
	Cid int primary key identity(1, 1),
	Baid int,
	Cvv int,
	foreign key (Baid) references BankAcc(Baid)
)

create table Transactions(
	Tid int primary key identity (1, 1),
	Aid int,
	Cid int,
	Bani int,
	TTime time,
	foreign key (Aid) references ATM(Aid),
	foreign key (Cid) references Cards(Cid)
)

insert into Customer values ('Mihai', '2004.4.3'), ('Andrei', '2001.3.20')
select * from Customer

insert into BankAcc values (1, '12345', 123), (1, '5321', 1000), (8, '99999',  90)
select * from BankAcc

insert into Cards values (6, 123), (7, 100), (6, 999)
select * from Cards

insert into Atm values ('Mizil centru'), ('Cluj Fsega')

insert into Transactions values (1, 1, 100, '12:30'), (2, 2, 300, '12:00'), (2, 1, 3000, '12:32')
insert into Transactions values (1, 3, 1050, '12:30'), (2, 3, 1000, '12:00')


create or alter procedure deleteCardTrans
    @CardId int
as
begin
    declare @nr int
    select @nr = Count(*)
    from Transactions t
    where t.Cid = @CardId

    if @nr = 0
    begin
        raiserror('No transactions found for this card.', 16, 1) -- Severity 16, State 1
        return
    end

    delete Transactions
    where Cid = @CardId
end
go

select * from Transactions
exec deleteCardTrans 1


create or alter view showCards
as
	select c.Cvv
	from Cards c 
	inner join Transactions t on t.Cid = c.Cid
	group by c.Cvv
	having COUNT(distinct t.Aid) = (select COUNT (*) from ATM)

go

select * from showCards


create or alter function CardsOver()
	returns table
as
	return 
	select c.Cvv, c.Cid
	from Cards c
	inner join Transactions t on t.Cid = c.Cid
	group by c.Cvv, c.Cid
	having SUM(t.Bani) > 2000
go

select * from CardsOver()

