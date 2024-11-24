USE Lab1;
GO

create procedure afisare
@name varchar(50)
as
	select *
	from Team as t
	where t.Team_name = @name
go

exec afisare 'Readrid'

create procedure changecolumn
@tablename varchar(50),
@col varchar(50),
@type varchar(50),
@originaltype varchar(50)
as
	declare @sql nvarchar(max);
	declare @undo nvarchar(max);

	set @sql = 'alter table' + quotename(@tablename) + 'alter column' + quotename(@col) + @type;
	set @undo = 'alter table' + quotename(@tablename) + 'alter column' + QUOTENAME(@col) + @originaltype;
	exec sp_executesql @sql;

	insert into Version (StoredProcedureName, ChangeSQL, InitialOperation)
    values ('changecolumn', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

go
drop procedure changecolumn

select * from Aaa
exec changecolumn 'Aaa', 'id', 'BIGINT', 'int'


drop procedure changecolumn

create table Aaa (
	 id INT CONSTRAINT PK_Aaa_id PRIMARY KEY,
	 City varchar(50) not null
	 )

drop table Aaa

exec changecolumn 'Aaa', 'City', 'int','varchar'
exec undoLastChange

create table Version (
    versionNo int identity(1,1) primary key,
    StoredProcedureName varchar(50),
    ChangeSQL nvarchar(max),
	InitialOperation nvarchar(max)
);
drop table Version


create procedure getCurrentVersion
as
begin
    select top 1 versionNo, StoredProcedureName
    from Version
    order by versionNo desc;
end
go

create procedure undoLastChange
as
begin
    declare @last_sql nvarchar(max);

    select top 1 @last_sql = ChangeSQL
    from Version
    order by versionNo desc;

    if @last_sql is not null
    begin
        exec sp_executesql @last_sql;

        delete from Version
        where versionNo = (select max(versionNo) from Version);
    end
    else
    begin
        print 'No changes to undo';
    end
end
go


CREATE PROCEDURE goToVersion
    @version INT
AS
BEGIN
    DECLARE @currentVersion INT;
    DECLARE @sql NVARCHAR(MAX);

    IF @version < 0
    BEGIN
        PRINT 'Error: Version number must be a positive integer.';
        RETURN;
    END;

    SELECT @currentVersion = versionNo
    FROM CurrentVersion;

    IF @currentVersion = @version
    BEGIN
        PRINT 'The database is already at the specified version.';
        RETURN;
    END;

    IF NOT EXISTS (SELECT 1 FROM Version WHERE versionNo = @version)
    BEGIN
        PRINT 'Error: The specified version does not exist in the Version table.';
        RETURN;
    END;

    IF @currentVersion < @version
    BEGIN
        PRINT 'Upgrading database...';
        WHILE @currentVersion < @version
        BEGIN
            SET @sql = (SELECT InitialOperation
                        FROM Version 
                        WHERE versionNo = @currentVersion + 1);
            EXEC sp_executesql @sql;

            SET @currentVersion = @currentVersion + 1;

            PRINT 'Upgraded to version ' + CAST(@currentVersion AS VARCHAR);
        END;
    END
    ELSE
    BEGIN
        PRINT 'Downgrading database...';
        WHILE @currentVersion > @version
        BEGIN
            SET @sql = (SELECT ChangeSQL
                        FROM Version 
                        WHERE versionNo = @currentVersion);
            EXEC sp_executesql @sql;

            SET @currentVersion = @currentVersion - 1;

            PRINT 'Downgraded to version ' + CAST(@currentVersion AS VARCHAR);
        END;
    END;

    UPDATE CurrentVersion
    SET versionNo = @currentVersion;

    PRINT 'Database version updated successfully.';
END;
GO

drop procedure goToVersion

create procedure addColumn
@tableName varchar(50),
@colName varchar(50),
@colType varchar(50)
as
	begin
		declare @sql nvarchar(max);
		declare @undo nvarchar(max);

		set @sql = 'alter table' + quotename(@tableName) + 'add' + quotename(@colName) + QUOTENAME(@colType);
		set @undo = 'alter table' + QUOTENAME(@tableName) + 'drop column' + QUOTENAME(@colName);
		exec sp_executesql @sql
		
		insert into Version (StoredProcedureName, ChangeSQL, InitialOperation)
		values ('addColumn', @undo, @sql);

		DECLARE @newVersion nvarchar(max);
		SELECT @newVersion = MAX(versionNo) FROM Version;

		UPDATE CurrentVersion
		SET versionNo = @newVersion;
	end
go
drop procedure addColumn

select * from Aaa
exec addColumn 'Aaa', 'B', 'int'

create procedure removeColumn
@tableName varchar(50),
@colName varchar(50),
@initialType varchar(50)
as
	begin
		declare @sql nvarchar(max);
		declare @undo nvarchar(max);
		 
		set @sql = 'alter table' + quotename(@tableName) + 'drop column' + QUOTENAME(@colName);
		set @undo = 'alter table' + quotename(@tableName) + 'add' + QUOTENAME(@colName) + QUOTENAME(@initialType);

		exec sp_executesql @sql

		insert into Version (StoredProcedureName, ChangeSQL, InitialOperation) 
		values ('removeColumn', @undo, @sql);

		DECLARE @newVersion nvarchar(max);
		SELECT @newVersion = MAX(versionNo) FROM Version;

		UPDATE CurrentVersion
		SET versionNo = @newVersion;
		end
go
drop procedure removeColumn

exec removeColumn 'Aaa', 'C', 'int'
exec undoLastChange

drop procedure removeColumn


create procedure addDefaultConstraint
    @tableName varchar(50),
    @colName varchar(50),
    @defaultValue varchar(50)
as
begin
    declare @sql nvarchar(max);
    declare @undo nvarchar(max);
    declare @constraintName varchar(100);

    set @constraintName = 'DF_' + @tableName + '_' + @colName;
     SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
               ' ADD CONSTRAINT ' + QUOTENAME(@constraintName) + 
               ' DEFAULT (' + @defaultValue + ') FOR ' + QUOTENAME(@colName);
    set @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + ' DROP CONSTRAINT ' + QUOTENAME(@constraintName);
    exec sp_executesql @sql;

    insert into Version (StoredProcedureName, ChangeSQL, InitialOperation)
    values ('addDefaultConstraint', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

end
go

drop procedure addDefaultConstraint
exec addDefaultConstraint 'Aaa', 'B', '7'

select * from Aaa


CREATE PROCEDURE removeDefaultConstraint
    @tableName VARCHAR(50),
    @colName VARCHAR(50),
    @initialConstraint VARCHAR(50)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @undo NVARCHAR(MAX);
    DECLARE @constraintName VARCHAR(100);

    SET @constraintName = 'DF_' + @tableName + '_' + @colName;

    SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
               ' DROP CONSTRAINT ' + QUOTENAME(@constraintName);

    -- Ensure @initialConstraint is treated as a constant
    SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
                ' ADD CONSTRAINT ' + QUOTENAME(@constraintName) + 
                ' DEFAULT (' + @initialConstraint + ') FOR ' + QUOTENAME(@colName);

    EXEC sp_executesql @sql;

    INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
    VALUES ('removeDefaultConstraint', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

END;
GO

drop procedure removeDefaultConstraint
exec removeDefaultConstraint 'Aaa', 'C', '7'


CREATE PROCEDURE addPk
    @tableName VARCHAR(50),
    @colName VARCHAR(50)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @undo NVARCHAR(MAX);

    SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + ' ADD CONSTRAINT PK_' + @tableName + '_' + @colName + ' PRIMARY KEY (' + QUOTENAME(@colName) + ')';
    SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + ' DROP CONSTRAINT PK_' + @tableName + '_' + @colName;

    EXEC sp_executesql @sql;

    INSERT INTO Version (StoredProcedureName, ChangeSQl, InitialOperation)
    VALUES ('addPk', @undo, @sql);
END;
GO

drop procedure addPk
exec addDefaultConstraint 'Aaa', 'C', '7'
exec addPk 'Aaa', 'City';

CREATE PROCEDURE removePk
@tableName varchar(50),
@colName varchar(50)
as
	begin
	    DECLARE @sql NVARCHAR(MAX);
		DECLARE @undo NVARCHAR(MAX);

		SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + ' DROP CONSTRAINT PK_' + @tableName + '_' + @colName;
		SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + ' ADD CONSTRAINT PK_' + @tableName + '_' + @colName + ' PRIMARY KEY (' + QUOTENAME(@colName) + ')';

		EXEC sp_executesql @sql;

		INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
		VALUES ('removePk', @undo, @sql);

		DECLARE @newVersion nvarchar(max);
		SELECT @newVersion = MAX(versionNo) FROM Version;

		UPDATE CurrentVersion
		SET versionNo = @newVersion;

	end
go  
drop procedure removePk

exec removePk 'Aaa', 'id';
select * from MostAggressivePlayers
exec addColumn 'MostAggressivePlayers', 'aux', 'int'
exec addDefaultConstraint 'MostAggressivePlayers', 'aux', '7'

insert MostAggressivePlayers (Pid, Number_matches, Yellow_cards, Red_cards) 
values (16, 3, 4, 5)



CREATE PROCEDURE addCandidateKey
    @tableName VARCHAR(50),
    @colName VARCHAR(50)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @undo NVARCHAR(MAX);
    DECLARE @constraintName NVARCHAR(128);

    SET @constraintName = 'UK_' + @tableName + '_' + @colName;

    SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
               ' ADD CONSTRAINT ' + QUOTENAME(@constraintName) + 
               ' UNIQUE (' + QUOTENAME(@colName) + ')';

    SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
                ' DROP CONSTRAINT ' + QUOTENAME(@constraintName);

    EXEC sp_executesql @sql;

    INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
    VALUES ('addCandidateKey', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

END;
GO


drop procedure addCandidateKey
exec addCandidateKey 'MostAggressivePlayers', 'Number_matches'
exec undoLastChange
insert MostAggressivePlayers (Pid, Number_matches, Yellow_cards, Red_cards, aux) 
values (15, 500, 4, 5, 7)
select * from MostAggressivePlayers
DELETE FROM MostAggressivePlayers WHERE Pid = 15;

create procedure removeCandidateKey
@tableName varchar(50),
@colName varchar(50)
as
	begin
		declare @sql  nvarchar(max);
		declare @undo nvarchar(max);
		DECLARE @constraintName NVARCHAR(128);

		SET @constraintName = 'UK_' + @tableName + '_' + @colName;

		
		SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
					' DROP CONSTRAINT ' + QUOTENAME(@constraintName);
		
		SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
					' ADD CONSTRAINT ' + QUOTENAME(@constraintName) + 
					' UNIQUE (' + QUOTENAME(@colName) + ')';

		EXEC sp_executesql @sql;

		INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
		VALUES ('removeCanditateKey', @undo, @sql);

		DECLARE @newVersion nvarchar(max);
		SELECT @newVersion = MAX(versionNo) FROM Version;

		UPDATE CurrentVersion
		SET versionNo = @newVersion;

	end
go
drop procedure removeCandidateKey

exec addCandidateKey 'TopScorers', 'Goals_scored'
select * from TopScorers
insert TopScorers (Team_name, Player_name, Goals_scored, Match_played) 
values ('Valencia', 'Messi', 50, 12) 
exec removeCandidateKey 'TopScorers', 'Goals_scored'
DELETE FROM TopScorers WHERE Team_name = 'Valencia';


CREATE PROCEDURE addForeignKey
    @tableName VARCHAR(50),          
    @colName VARCHAR(50),            
    @referencedTable VARCHAR(50),    
    @referencedCol VARCHAR(50)       
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @undo NVARCHAR(MAX);
    DECLARE @constraintName NVARCHAR(128);

    SET @constraintName = 'FK_' + @tableName + '_' + @colName + '_' + @referencedTable + '_' + @referencedCol;

    SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
               ' ADD CONSTRAINT ' + QUOTENAME(@constraintName) + 
               ' FOREIGN KEY (' + QUOTENAME(@colName) + ') REFERENCES ' + 
               QUOTENAME(@referencedTable) + ' (' + QUOTENAME(@referencedCol) + ')';

    SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
                ' DROP CONSTRAINT ' + QUOTENAME(@constraintName);

    EXEC sp_executesql @sql;

    INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
    VALUES ('addForeignKey', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

END;
GO
drop procedure addForeignKey

exec addForeignKey 'Aaa', 'B', 'MostAggressivePlayers', 'Pid'
exec undoLastChange

CREATE PROCEDURE removeForeignKey
    @tableName VARCHAR(50),          
    @colName VARCHAR(50),            
    @referencedTable VARCHAR(50),    
    @referencedCol VARCHAR(50)       
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
    DECLARE @undo NVARCHAR(MAX);
    DECLARE @constraintName NVARCHAR(128);

    SET @constraintName = 'FK_' + @tableName + '_' + @colName + '_' + @referencedTable + '_' + @referencedCol;

	 SET @sql = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
                ' DROP CONSTRAINT ' + QUOTENAME(@constraintName);

    SET @undo = 'ALTER TABLE ' + QUOTENAME(@tableName) + 
               ' ADD CONSTRAINT ' + QUOTENAME(@constraintName) + 
               ' FOREIGN KEY (' + QUOTENAME(@colName) + ') REFERENCES ' + 
               QUOTENAME(@referencedTable) + ' (' + QUOTENAME(@referencedCol) + ')';

    EXEC sp_executesql @sql;

    INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
    VALUES ('removeForeignKey', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

END;
GO
drop procedure removeForeignKey

exec removeForeignKey 'Aaa', 'B', 'MostAggressivePlayers', 'Pid'

CREATE PROCEDURE createTable
    @tableName VARCHAR(50),        
    @columns NVARCHAR(MAX),         
    @primaryKey VARCHAR(50) = NULL  
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
	DECLARE @undo NVARCHAR(MAX);

    SET @sql = 'CREATE TABLE ' + QUOTENAME(@tableName) + ' (' + @columns;

    IF @primaryKey IS NOT NULL
        SET @sql = @sql + ', PRIMARY KEY (' + QUOTENAME(@primaryKey) + ')';

    SET @sql = @sql + ')';
	SET @undo = 'DROP TABLE' + QUOTENAME(@tableName);

    EXEC sp_executesql @sql;


    PRINT 'Table ' + @tableName + ' has been created successfully.';
	INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
    VALUES ('createTable', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

END;
GO

drop procedure createTable

EXEC createTable
    @tableName = 'Orders',
    @columns = 'OrderID INT, CustomerID INT, OrderDate DATE, TotalAmount DECIMAL(10, 2)',
    @primaryKey = 'OrderID';

CREATE PROCEDURE dropTable
    @tableName VARCHAR(50),        
    @columns NVARCHAR(MAX),         
    @primaryKey VARCHAR(50) = NULL  
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);
	DECLARE @undo NVARCHAR(MAX);

	SET @sql = 'DROP TABLE' + QUOTENAME(@tableName);
    SET @undo = 'CREATE TABLE ' + QUOTENAME(@tableName) + ' (' + @columns;

    IF @primaryKey IS NOT NULL
        SET @undo = @undo + ', PRIMARY KEY (' + QUOTENAME(@primaryKey) + ')';

    SET @undo = @undo + ')';

    EXEC sp_executesql @sql;


    PRINT 'Table ' + @tableName + ' has been deleted.';
	INSERT INTO Version (StoredProcedureName, ChangeSQL, InitialOperation)
    VALUES ('dropTable', @undo, @sql);

	DECLARE @newVersion nvarchar(max);
	SELECT @newVersion = MAX(versionNo) FROM Version;

    UPDATE CurrentVersion
    SET versionNo = @newVersion;

END;
GO

drop procedure dropTable

EXEC dropTable
    @tableName = 'Orders',
    @columns = 'OrderID INT, CustomerID INT, OrderDate DATE, TotalAmount DECIMAL(10, 2)',
    @primaryKey = 'OrderID';


drop procedure goToVersion
exec removeColumn 'MostAggressivePlayers', 'Height', 'float'

exec addColumn 'MostAggressivePlayers', 'Height', 'float'

exec dropTable
 @tableName = 'Orders',
 @columns = 'OrderID INT, CustomerID INT, OrderDate DATE, TotalAmount DECIMAL(10, 2)',
 @primaryKey = 'OrderID'; 

EXEC createTable
    @tableName = 'Orders',
    @columns = 'OrderID INT, CustomerID INT, OrderDate DATE, TotalAmount DECIMAL(10, 2)',
    @primaryKey = 'OrderID'; 

exec addForeignKey 'Orders', 'CustomerID', 'Players', 'Pid' 
exec goToVersion 1
exec goToVersion 3
exec removeForeignKey 'Orders', 'CustomerID', 'Players', 'Pid'

exec addCandidateKey 'Records', 'Trophies'


insert MostAggressivePlayers (Pid, Number_matches, Yellow_cards, Red_cards) 
values (16, 3, 4, 5)


select * from Version
select * from CurrentVersion
UPDATE CurrentVersion
SET versionNo = 1;