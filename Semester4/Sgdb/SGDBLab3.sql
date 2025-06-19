CREATE TABLE Teams (
    TeamID int IDENTITY(1,1) PRIMARY KEY,
    TeamName varchar(100) UNIQUE,
    Sport varchar(50)
);

CREATE TABLE Players (
    PlayerID int IDENTITY(1,1) PRIMARY KEY,
    PlayerName varchar(100) UNIQUE,
    Position varchar(50)
);

CREATE TABLE TeamPlayers (
    TeamID int,
    PlayerID int,
    JerseyNumber int,
    PRIMARY KEY (TeamID, PlayerID),
    FOREIGN KEY (TeamID) REFERENCES Teams(TeamID),
    FOREIGN KEY (PlayerID) REFERENCES Players(PlayerID),
    CONSTRAINT UQ_Team_Jersey UNIQUE (TeamID, JerseyNumber)
);

CREATE TABLE LogTable (
    LogID int IDENTITY(1,1) PRIMARY KEY,
    Timestamp datetime,
    Action varchar(50),
    Message varchar(255)
);

CREATE FUNCTION dbo.ValidateSport (@Sport varchar(50))
RETURNS bit
AS
BEGIN
    IF @Sport IN ('Football', 'Basketball', 'Soccer')
        RETURN 1;
    RETURN 0;
END
GO

CREATE FUNCTION dbo.ValidateName (@Name varchar(100))
RETURNS bit
AS
BEGIN
    IF @Name IS NULL OR LEN(@Name) = 0 OR LEFT(@Name, 1) != UPPER(LEFT(@Name, 1))
        RETURN 0;
    RETURN 1;
END
GO


CREATE PROCEDURE InsertTeamPlayer
    @TeamName varchar(100),
    @Sport varchar(50),
    @PlayerName varchar(100),
    @Position varchar(50),
    @JerseyNumber int
AS
BEGIN
    SET NOCOUNT ON;

    INSERT INTO LogTable (Timestamp, Action, Message)
    VALUES (GETDATE(), 'Start InsertTeamPlayer', 
            'Starting insertion with parameters: TeamName=' + @TeamName + 
            ', Sport=' + @Sport + 
            ', PlayerName=' + @PlayerName + 
            ', Position=' + @Position + 
            ', JerseyNumber=' + CAST(@JerseyNumber AS varchar(10)));

    -- Validate parameters
    IF dbo.ValidateSport(@Sport) = 0
    BEGIN
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Validation Failed', 'Invalid sport: ' + @Sport);
        RAISERROR('Invalid sport', 16, 1);
        RETURN;
    END

    IF dbo.ValidateName(@TeamName) = 0
    BEGIN
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Validation Failed', 'Invalid team name: ' + @TeamName);
        RAISERROR('Invalid team name', 16, 1);
        RETURN;
    END

    IF dbo.ValidateName(@PlayerName) = 0
    BEGIN
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Validation Failed', 'Invalid player name: ' + @PlayerName);
        RAISERROR('Invalid player name', 16, 1);
        RETURN;
    END

    IF @Position IS NULL OR LEN(@Position) = 0
    BEGIN
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Validation Failed', 'Position cannot be null or empty');
        RAISERROR('Position cannot be null or empty', 16, 1);
        RETURN;
    END

    IF @JerseyNumber <= 0
    BEGIN
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Validation Failed', 'Invalid jersey number: ' + CAST(@JerseyNumber AS varchar(10)));
        RAISERROR('Jersey number must be positive', 16, 1);
        RETURN;
    END

    -- Begin transaction
    BEGIN TRANSACTION
    BEGIN TRY
        -- Insert into Teams
        INSERT INTO Teams (TeamName, Sport)
        VALUES (@TeamName, @Sport);
        DECLARE @TeamID int = SCOPE_IDENTITY();

        -- Log team insertion
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Insert Team', 
                'Inserted team: ' + @TeamName + ' with ID ' + CAST(@TeamID AS varchar(10)));

        -- Insert into Players
        INSERT INTO Players (PlayerName, Position)
        VALUES (@PlayerName, @Position);
        DECLARE @PlayerID int = SCOPE_IDENTITY();

        -- Log player insertion
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Insert Player', 
                'Inserted player: ' + @PlayerName + ' with ID ' + CAST(@PlayerID AS varchar(10)));

        -- Insert into TeamPlayers
        INSERT INTO TeamPlayers (TeamID, PlayerID, JerseyNumber)
        VALUES (@TeamID, @PlayerID, @JerseyNumber);

        -- Log junction table insertion
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Insert TeamPlayer', 
                'Linked team ' + CAST(@TeamID AS varchar(10)) + 
                ' with player ' + CAST(@PlayerID AS varchar(10)) + 
                ' and jersey number ' + CAST(@JerseyNumber AS varchar(10)));

        -- Commit transaction
        COMMIT TRANSACTION

        -- Log success
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Success InsertTeamPlayer', 
                'Successfully inserted team, player, and linked them.');
    END TRY
    BEGIN CATCH
        -- Roll back transaction on error
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;

        -- Log error
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Error InsertTeamPlayer', 
                'Error occurred: ' + ERROR_MESSAGE());

        -- Rethrow the error
        THROW;
    END CATCH
END
GO

EXEC InsertTeamPlayer 
    @TeamName = 'Aaa', 
    @Sport = 'Soccer', 
    @PlayerName = 'Yamal', 
    @Position = 'Forward', 
    @JerseyNumber = 10;

select * from TeamPlayers
select * from Teams
select * from Players
select * from LogTable

delete from TeamPlayers
delete from Teams
delete from Players
delete from LogTable


EXEC InsertTeamPlayer 
    @TeamName = 'lakers',  -- lowercase first letter
    @Sport = 'Basketball', 
    @PlayerName = 'LeBron James', 
    @Position = 'Forward', 
    @JerseyNumber = 23;

EXEC InsertTeamPlayer 
    @TeamName = 'Barcelona', 
    @Sport = 'Handball',		--invalid sport 
    @PlayerName = 'Messi', 
    @Position = 'Forward', 
    @JerseyNumber = 10;



-- 5 -- Procedure to add a team or retrieve existing team ID
CREATE OR ALTER PROCEDURE AddTeam
    @TeamName varchar(100),
    @Sport varchar(50),
    @TeamID int OUTPUT
AS
BEGIN
    IF (@TeamName IS NULL OR @Sport IS NULL)
    BEGIN
        RAISERROR('Team name and sport must not be null', 16, 1);
        RETURN;
    END
    IF dbo.ValidateName(@TeamName) = 0
    BEGIN
        RAISERROR('Invalid team name', 16, 1);
        RETURN;
    END
    IF dbo.ValidateSport(@Sport) = 0
    BEGIN
        RAISERROR('Invalid sport', 16, 1);
        RETURN;
    END
    BEGIN TRY
        INSERT INTO Teams (TeamName, Sport) VALUES (@TeamName, @Sport);
        SET @TeamID = SCOPE_IDENTITY();
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Added row to Teams', 'Team: ' + @TeamName);
    END TRY
    BEGIN CATCH
        IF ERROR_NUMBER() IN (2601, 2627)
        BEGIN
            SELECT @TeamID = TeamID FROM Teams WHERE TeamName = @TeamName;
            INSERT INTO LogTable (Timestamp, Action, Message)
            VALUES (GETDATE(), 'Team already exists', 'Team: ' + @TeamName);
        END
        ELSE
        BEGIN
            THROW;
        END
    END CATCH
END
GO

-- Procedure to add a player or retrieve existing player ID
CREATE OR ALTER PROCEDURE AddPlayer
    @PlayerName varchar(100),
    @Position varchar(50),
    @PlayerID int OUTPUT
AS
BEGIN
    IF (@PlayerName IS NULL OR @Position IS NULL)
    BEGIN
        RAISERROR('Player name and position must not be null', 16, 1);
        RETURN;
    END
    IF dbo.ValidateName(@PlayerName) = 0
    BEGIN
        RAISERROR('Invalid player name', 16, 1);
        RETURN;
    END
    BEGIN TRY
        INSERT INTO Players (PlayerName, Position) VALUES (@PlayerName, @Position);
        SET @PlayerID = SCOPE_IDENTITY();
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Added row to Players', 'Player: ' + @PlayerName);
    END TRY
    BEGIN CATCH
        IF ERROR_NUMBER() IN (2601, 2627)
        BEGIN
            SELECT @PlayerID = PlayerID FROM Players WHERE PlayerName = @PlayerName;
            INSERT INTO LogTable (Timestamp, Action, Message)
            VALUES (GETDATE(), 'Player already exists', 'Player: ' + @PlayerName);
        END
        ELSE
        BEGIN
            THROW;
        END
    END CATCH
END
GO

-- Procedure to link a player to a team with a jersey number
CREATE OR ALTER PROCEDURE AddTeamPlayer
    @TeamName varchar(100),
    @PlayerName varchar(100),
    @JerseyNumber int
AS
BEGIN
    DECLARE @TeamID int;
    DECLARE @PlayerID int;
    IF (@TeamName IS NULL OR @PlayerName IS NULL OR @JerseyNumber IS NULL)
    BEGIN
        RAISERROR('Team name, player name, and jersey number must not be null', 16, 1);
        RETURN;
    END
    SET @TeamID = (SELECT TeamID FROM Teams WHERE TeamName = @TeamName);
    SET @PlayerID = (SELECT PlayerID FROM Players WHERE PlayerName = @PlayerName);
    IF (@TeamID IS NULL)
    BEGIN
        RAISERROR('Team does not exist', 16, 1);
        RETURN;
    END
    IF (@PlayerID IS NULL)
    BEGIN
        RAISERROR('Player does not exist', 16, 1);
        RETURN;
    END
    BEGIN TRY
        INSERT INTO TeamPlayers (TeamID, PlayerID, JerseyNumber)
        VALUES (@TeamID, @PlayerID, @JerseyNumber);
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Linked player to team', @PlayerName + ' to ' + @TeamName + ' with jersey ' + CAST(@JerseyNumber AS varchar));
    END TRY
    BEGIN CATCH
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Error linking player to team', ERROR_MESSAGE());
        THROW;
    END CATCH
END
GO

-- Procedure to handle no-rollback scenario for many-to-many relationship
CREATE OR ALTER PROCEDURE NoRollbackScenarioManyToMany
    @TeamName varchar(100),
    @Sport varchar(50),
    @PlayerName varchar(100),
    @Position varchar(50),
    @JerseyNumber int
AS
BEGIN
    DECLARE @TeamID int;
    DECLARE @PlayerID int;
    -- Try to add or get team
    BEGIN TRY
        EXEC AddTeam @TeamName, @Sport, @TeamID OUTPUT;
    END TRY
    BEGIN CATCH
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Error adding team', ERROR_MESSAGE());
    END CATCH
    -- Try to add or get player
    BEGIN TRY
        EXEC AddPlayer @PlayerName, @Position, @PlayerID OUTPUT;
    END TRY
    BEGIN CATCH
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Error adding player', ERROR_MESSAGE());
    END CATCH
    -- Try to link them if both team and player are available
    IF @TeamID IS NOT NULL AND @PlayerID IS NOT NULL
    BEGIN
        BEGIN TRY
            EXEC AddTeamPlayer @TeamName, @PlayerName, @JerseyNumber;
        END TRY
        BEGIN CATCH
            INSERT INTO LogTable (Timestamp, Action, Message)
            VALUES (GETDATE(), 'Error linking', ERROR_MESSAGE());
        END CATCH
    END
    ELSE
    BEGIN
        INSERT INTO LogTable (Timestamp, Action, Message)
        VALUES (GETDATE(), 'Skipped linking', 'Team or player not available');
    END
END
GO

EXEC NoRollbackScenarioManyToMany 'Lyon', 'Soccer', 'Vini', 'Forward', 7;		--work ok
EXEC NoRollbackScenarioManyToMany 'Lyon', 'Soccer', 'Anthony', 'Center', 4;	--add only player
EXEC NoRollbackScenarioManyToMany 'FCSB', 'Handball', 'Alexis MEssi', 'Goalkeeper', 9;		--error for team, add player
EXEC NoRollbackScenarioManyToMany 'FCSB', 'Soccer', '', 'Forward', 10;		--don t add anything.

select * from TeamPlayers
select * from Teams
select * from Players
select * from LogTable

delete from TeamPlayers
delete from Teams
delete from Players
delete from LogTable

