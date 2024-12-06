USE LAB1
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRuns]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tests]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Views]

GO



CREATE TABLE [Tables] (

	[TableID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunTables] (

	[TestRunID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunViews] (

	[TestRunID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRuns] (

	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,

	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,

	[StartAt] [datetime] NULL ,

	[EndAt] [datetime] NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestTables] (

	[TestID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[NoOfRows] [int] NOT NULL ,

	[Position] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestViews] (

	[TestID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Tests] (

	[TestID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Views] (

	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



ALTER TABLE [Tables] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 

	(

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRuns] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Tests] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 

	(

		[TestID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Views] WITH NOCHECK ADD 

	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 

	(

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] ADD 

	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestRunViews] ADD 

	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestTables] ADD 

	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestViews] ADD 

	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	),

	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	)

GO

-------------- Lab 4 ---------------------------

create or alter procedure addToTables (@tableName varchar(50)) as
    if @tableName in (select Name from Tables) begin
        print 'Table already present in Tables'
        return
    end
    if @tableName not in (select TABLE_NAME from INFORMATION_SCHEMA.TABLES) begin
        print 'Table not present in the database'
        return
    end
    insert into Tables (Name) values (@tableName)
GO

create or alter procedure addToViews (@viewName varchar(50)) as
    if @viewName in (select Name from Views) begin
        print 'View already present in Views'
        return
    end
    if @viewName not in (select TABLE_NAME from INFORMATION_SCHEMA.VIEWS) begin
        print 'View not present in the database'
        return
    end
    insert into Views (Name) values (@viewName)
GO

create or alter procedure addToTests (@testName varchar(50)) as
    if @testName in (select Name from Tests) begin
        print 'Test already present in Tests'
        return
    end
    insert into Tests (Name) values (@testName)
GO

create or alter procedure connectTableToTest (@tableName varchar(50), @testName varchar(50), @rows int, @pos int) as
    if @tableName not in (select Name from Tables) begin
        print 'Table not present in Tables'
        return
    end
    if @testName not in (select Name from Tests) begin
        print 'Tests not present in Tests'
        return
    end
    if exists(
        select *
        from TestTables T1 join Tests T2 on T1.TestID = T2.TestID
        where T2.Name=@testName and Position=@pos
        ) begin
        print 'Position provided conflicts with previous positions'
        return
    end
    insert into TestTables (TestID, TableID, NoOfRows, Position) values (
        (select Tests.TestID from Tests where Name=@testName),
        (select Tables.TableID from Tables where Name=@tableName),
        @rows,
        @pos
    )
GO

create or alter procedure connectViewToTest (@viewName varchar(50), @testName varchar(50)) as
    if @viewName not in (select Name from Views) begin
        print 'View not present in Views'
        return
    end
    if @testName not in (select Name from Tests) begin
        print 'Tests not present in Tests'
        return
    end
    insert into TestViews (TestID, ViewID) values (
        (select Tests.TestID from Tests where Name=@testName),
        (select Views.ViewID from Views where Name=@viewName)
    )
GO


create or alter procedure runTest (@testName varchar(50)) as
    if @testName not in (select Name from Tests) begin
        print 'test not in Tests'
        return
    end
    declare @command varchar(100)
    declare @testStartTime datetime2
    declare @startTime datetime2
    declare @endTime datetime2
    declare @table varchar(50)
    declare @rows int
    declare @pos int
    declare @view varchar(50)
    declare @testId int
    select @testId=TestID from Tests where Name=@testName
    declare @testRunId int
    set @testRunId = (select max(TestRunID)+1 from TestRuns)
    if @testRunId is null
        set @testRunId = 0
    declare tableCursor cursor scroll for
        select T1.Name, T2.NoOfRows, T2.Position
        from Tables T1 join TestTables T2 on T1.TableID = T2.TableID
        where T2.TestID = @testId
        order by T2.Position
    declare viewCursor cursor for
        select V.Name
        from Views V join TestViews TV on V.ViewID = TV.ViewID
        where TV.TestID = @testId

    set @testStartTime = sysdatetime()
    open tableCursor
    fetch last from tableCursor into @table, @rows, @pos
    while @@FETCH_STATUS = 0 begin
        exec ('delete from '+ @table)
        fetch prior from tableCursor into @table, @rows, @pos
    end
    close tableCursor

    open tableCursor
    SET IDENTITY_INSERT TestRuns ON
    insert into TestRuns (TestRunID, Description, StartAt)values (@testRunId, 'Tests results for: ' + @testName, @testStartTime)
    SET IDENTITY_INSERT TestRuns OFF
    fetch tableCursor into @table, @rows, @pos
    while @@FETCH_STATUS = 0 begin
        set @command = 'populateTable' + @table
        if @command not in (select ROUTINE_NAME from INFORMATION_SCHEMA.ROUTINES) begin
            print @command + 'does not exist'
            return
        end
        set @startTime = sysdatetime()
        exec @command @rows
        set @endTime = sysdatetime()
        insert into TestRunTables (TestRunID, TableId, StartAt, EndAt) values (@testRunId, (select TableID from Tables where Name=@table), @startTime, @endTime)
        fetch tableCursor into @table, @rows, @pos
    end
    close tableCursor
    deallocate tableCursor

    open viewCursor
    fetch viewCursor into @view
    while @@FETCH_STATUS = 0 begin
        set @command = 'select * from ' + @view
        set @startTime = sysdatetime()
        exec (@command)
        set @endTime = sysdatetime()
        insert into TestRunViews (TestRunID, ViewID, StartAt, EndAt) values (@testRunId, (select ViewID from Views where Name=@view), @startTime, @endTime)
        fetch viewCursor into @view
    end
    close viewCursor
    deallocate viewCursor

    update TestRuns
    set EndAt=sysdatetime()
    where TestRunID = @testRunId
GO


CREATE PROCEDURE populateTableTeam (@rows INT)
AS
BEGIN
    DECLARE @i INT = 1;
    WHILE @i <= @rows
    BEGIN
        INSERT INTO Team (Team_name, Matches_played, Wins, Losses, Draws, Goals_scored, Goals_conceded, Points)
        VALUES (
            CONCAT('Team_', @i),                 -- Team_name
            ABS(CHECKSUM(NEWID()) % 38),         
            ABS(CHECKSUM(NEWID()) % 20),         -- Wins (random between 0-19)
            ABS(CHECKSUM(NEWID()) % 20),         -- Losses (random between 0-19)
            ABS(CHECKSUM(NEWID()) % 5),          -- Draws (random between 0-4)
            ABS(CHECKSUM(NEWID()) % 100),        -- Goals_scored (random between 0-99)
            ABS(CHECKSUM(NEWID()) % 100),        -- Goals_conceded (random between 0-99)
            ABS(CHECKSUM(NEWID()) % 100)         -- Points (random between 0-99)
        );
        SET @i = @i + 1;
    END
END;

--Test pk

--EXEC populateTableTeam 10;



EXEC addToTables 'Team'
EXEC addToViews 'TeamPerformance'
EXEC addToTests 'TeamTest1'

select * from Team

delete from Team
where Team_name like 'Team%'


EXEC connectTableToTest 'Team', 'TeamTest', 10, 4
EXEC connectTableToTest 'Team', 'TeamTest1', 1000, 4
EXEC connectViewToTest 'TeamPerformance', 'TeamTest'
EXEC runTest 'TeamTest1'
select * from TestRuns


--INSERT INTO Tables (Name) VALUES ('Team')
--INSERT INTO Tests (Name) VALUES ('TeamTest');

--INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES (1, 1, 10, 1)  -- Populate 10 rows in Team table

--SELECT * FROM Tests;

--select * from Tables;
--SELECT * FROM TestTables;
--EXEC runTest 'TeamTest';


--Test pk fk

CREATE OR ALTER PROCEDURE populateTableContracts (@rows INT)
AS
BEGIN
    DECLARE @i INT = 1;
    DECLARE @teamName NVARCHAR(50);
    DECLARE @startDate DATE;
    DECLARE @endDate DATE;
    DECLARE @salary INT;
    DECLARE @pid INT;
	DECLARE @cid INT = 50;

    WHILE @i <= @rows
    BEGIN
        
        SET @teamName = CONCAT('Team_', (@i % 10) + 1); 
        SET @startDate = DATEADD(DAY,  10, GETDATE());
        SET @endDate = DATEADD(YEAR, 1, @startDate);
        SET @salary = 3000 + (@i * 50); 
        SET @pid = (@i % 10) + 1; 

        -- Insert into Contracts table
        INSERT INTO Contracts (Cid, Pid, Team_name, Start_d, Last_d, Salary)
        VALUES (@cid, @pid, @teamName, @startDate, @endDate, @salary);

        SET @i = @i + 1;
		set @cid = @cid + 1;
    END;
END;
GO


EXEC addToTables 'Contracts'
EXEC addToViews 'TeamPlayers'
EXEC addToTests 'ContractTest'

EXEC connectTableToTest 'Contracts', 'ContractTest', 10, 2
EXEC connectViewToTest 'TeamPlayers', 'ContractTest'
EXEC runTest 'ContractTest'

--INSERT INTO Tables (Name) VALUES ('Contracts')
--INSERT INTO Tests (Name) VALUES ('ContractsTest');
--INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES
--(2, 3, 10, 1)  -- Populate 10 rows in Contracts table

select * from Contracts

delete from Contracts
where Cid between 50 and  60

EXEC runTest 'ContractsTest';

select * from TestViews

--Test 3

CREATE TABLE Flights (
    FlightNumber INT,
    DepartureDate DATE,
    ArrivalDate DATE,
    DepartureAirport VARCHAR(3),
    ArrivalAirport VARCHAR(3),
    PRIMARY KEY (FlightNumber, DepartureDate)
);

CREATE OR ALTER PROCEDURE populateTableFlights
    @NumberOfFlights INT
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @i INT = 1;
    DECLARE @FlightNumber INT;
    DECLARE @DepartureDate DATE;
    DECLARE @ArrivalDate DATE;
    DECLARE @DepartureAirport VARCHAR(3);
    DECLARE @ArrivalAirport VARCHAR(3);

    WHILE @i <= @NumberOfFlights
    BEGIN
        -- Generate random flight data
        SET @FlightNumber = ABS(CHECKSUM(NEWID())) % 1000 + 1; 
        SET @DepartureDate = DATEADD(DAY, ABS(CHECKSUM(NEWID())) % 30, GETDATE());
        SET @ArrivalDate = @DepartureDate; 
        SET @DepartureAirport = CHAR(65 + ABS(CHECKSUM(NEWID())) % 26) + 
                                CHAR(65 + ABS(CHECKSUM(NEWID())) % 26) +
                                CHAR(65 + ABS(CHECKSUM(NEWID())) % 26); 
        SET @ArrivalAirport = CHAR(65 + ABS(CHECKSUM(NEWID())) % 26) + 
                              CHAR(65 + ABS(CHECKSUM(NEWID())) % 26) +
                              CHAR(65 + ABS(CHECKSUM(NEWID())) % 26); 

        -- Ensure departure and arrival airports are different
        WHILE @DepartureAirport = @ArrivalAirport
        BEGIN
            SET @ArrivalAirport = CHAR(65 + ABS(CHECKSUM(NEWID())) % 26) + 
                                  CHAR(65 + ABS(CHECKSUM(NEWID())) % 26) +
                                  CHAR(65 + ABS(CHECKSUM(NEWID())) % 26);
        END

        -- Insert into the Flights table
        INSERT INTO Flights (FlightNumber, DepartureDate, ArrivalDate, DepartureAirport, ArrivalAirport)
        VALUES (@FlightNumber, @DepartureDate, @ArrivalDate, @DepartureAirport, @ArrivalAirport);

        SET @i = @i + 1;
    END

    PRINT CONCAT('Successfully added ', @NumberOfFlights, ' flights.');
END;


EXEC addToTables 'Flights'
EXEC addToViews 'TeamAverageSalary'		--nu chiar aici
EXEC addToTests 'FlightTest'

EXEC connectTableToTest 'Flights', 'FlightTest', 1000, 1
EXEC connectViewToTest 'TeamAverageSalary', 'FlightTest'
EXEC runTest 'FlightTest'

select * from TestTables
delete from TestTables

--INSERT INTO Tables (Name) VALUES ('Flights')
--INSERT INTO Tests (Name) 
--VALUES ('FlightTest');
--INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES
--(2, 2, 10, 1) 

select * from Flights
select * from Tables
delete from Flights
EXEC runTest 'FlightTest';


--View one
CREATE VIEW TeamPerformance AS
SELECT 
    Team_name,
    Matches_played,
    Goals_scored
FROM 
    Team;

SELECT * FROM TeamPerformance;


CREATE VIEW TeamPlayers AS
SELECT
    t.Team_name,
    p.First_name,
	p.Last_name
FROM 
    Team t
INNER JOIN 
    Players p
ON 
    t.Team_name = p.Team_name;

SELECT * FROM TeamPlayers;


CREATE VIEW TeamAverageSalary AS
SELECT
    p.Team_name,
    AVG(c.Salary) AS AverageSalary
FROM
    Players p
INNER JOIN
    Contracts c
ON
    p.Pid = c.Pid
GROUP BY
    p.Team_name;


select * from TeamAverageSalary