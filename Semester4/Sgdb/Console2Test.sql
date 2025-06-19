use SgdbT

BEGIN TRANSACTION
INSERT INTO BookType VALUES ('a', 'aa')
COMMIT TRANSACTION

select * from BookType

