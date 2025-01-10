create table Movies(
	Movieid int,
	Title varchar(50),
	Genre varchar(50),
	Director varchar(50),
	BoxOffice int
	CONSTRAINT pk_R PRIMARY KEY(Movieid)
	)


insert into Movies values  
(1001, 'The Sham', 'Drama', 'Frank', 28), 
(1002, 'The Godfather', 'Crime, Drama', 'Francis', 250), 
(1003, 'The Dark Knight', 'Action Crime', 'Cristopher', 1005), 
(1004, 'Schindler', 'Drama, History', 'Steven', 321), 
(1005, 'Pulp', 'Crime, Drama', 'Quentin', 213), 
(1006, 'The lord', 'Adventure Drama Fantasy', 'Peter',  1130), 
(1007, 'Forrest Gump', 'Drama Romance', 'Robert', 678), 
(1008, 'Inception', 'Action Sc-fi', 'Cristopher', 836), 
(1009, 'Interstellar', 'Adventure Drama Sci fi', 'Cristopher', 677), 
(1010, 'Fight', 'Drama', 'David' , 101)


SELECT Title,
(Select MAX(BoxOffice) from Movies where Genre = M.Genre) as MaxBox
from Movies M
where Genre = 'Drama' 


SELECT M.title, M.BoxOffice, M.Director
from Movies m
join (select director from Movies where Genre = 'Drama') D
on m.Director = D.Director
where M.BoxOffice > 500


select Genre, Count(*) as Mc
from Movies
group by Genre
having Count(*) > (select COUNT(*) from Movies)
