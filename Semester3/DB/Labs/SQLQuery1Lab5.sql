use aa


create table Ta (
	aid int primary key,
	a2 int unique,
	Number int
	)
drop table Ta

create table Tb (
	bid int primary key,
	b2 int,
	Nr int
	)
drop table Tb

create table Tc (
	cid int primary key,
	aid int,
	bid int,
	foreign key (aid) references Ta(aid),
	foreign key (bid) references Tb(bid)
	)
drop table Tc


CREATE PROCEDURE populateTableTa(@rows INT) AS
	while @rows > 0 BEGIN
		INSERT INTO Ta VALUES(@rows, @rows - 20000, @rows + 1234)
		SET @rows = @rows - 1
	END;
GO
drop procedure populateTableTa

CREATE OR ALTER PROCEDURE populateTableTb(@rows INT) AS
	while @rows > 0 BEGIN
		INSERT INTO Tb VALUES(@rows, @rows - 60000 / @rows + @rows / 2, @rows * 2 - @rows / 3)
		SET @rows = @rows - 1
	END;
GO



CREATE OR ALTER PROCEDURE populateTableTc(@rows INT) AS
	IF @rows > (SELECT COUNT(*) FROM Ta) * (SELECT COUNT(*) FROM Tb) BEGIN
		RAISERROR ('Too many entities requested', 10, 1)
	END
	DECLARE valuesCursor CURSOR LOCAL FOR (
		SELECT a.aid, b.bid
		FROM Ta a CROSS JOIN Tb b
	)
	DECLARE @aid INT
	DECLARE @bid INT
	OPEN valuesCursor
	FETCH valuesCursor INTO @aid, @bid
	while @@FETCH_STATUS = 0 AND @rows > 0 BEGIN
		INSERT INTO Tc VALUES(@rows, @aid, @bid)
		FETCH valuesCursor INTO @aid, @bid	
		SET @rows = @rows - 1
	END
	CLOSE valuesCursor 
	DEALLOCATE valuesCursor;
GO



exec populateTableTa 1000;
exec populateTableTb 10000;
exec populateTableTc 12000;

--cluster index scan
select * from Ta	--0.0046
select * from Tb
select * from Tc

--Clustered Index Seek
SELECT * FROM Ta WHERE aid = 5;	--0.0031

SELECT a2 FROM Ta;	--0.005		--Non clustered index scan

SELECT a2 FROM Ta WHERE a2 <= -19315;	--0.0038 Nonclustered index seek

SELECT * FROM Ta WHERE a2 = 25;	--0.0032 Nonclustered Index Seek + Key Lookup

--b---

SELECT *  
FROM Tb 
WHERE b2 = 543;	--0.0034

IF EXISTS (SELECT NAME FROM sys.indexes WHERE name = 'N_idx_Tb_b2') 
    DROP INDEX N_idx_Tb_b2 ON Tb;

-- Create a nonclustered index on the column b2
CREATE NONCLUSTERED INDEX N_idx_Tb_b2 ON Tb(b2);

SELECT *  
FROM Tb 
WHERE b2 = 543;		--0.0031


SELECT b2  
FROM Tb 
WHERE b2 = 543;		--0.0032

SELECT b2, Nr  
FROM Tb 
WHERE b2 = 543;	--0.0032

SELECT *  
FROM Tb 
WHERE b2 = 8;	--0.0032

--C----


CREATE OR ALTER VIEW v1 AS
SELECT Ta.aid, Ta.a2, Tc.cid, Tc.bid
FROM Ta 
INNER JOIN Tc ON Ta.aid = Tc.aid;
GO

SELECT * FROM v1 --0.004

IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'idx_Tc_aid')
    DROP INDEX idx_Tc_aid ON Tc;



CREATE NONCLUSTERED INDEX idx_Tc_aid ON Tc(aid);

SELECT * FROM v1;	--0.0038