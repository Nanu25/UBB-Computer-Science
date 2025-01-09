create table R(
	FK1 int,
	FK2 int,
	C1 varchar(50),
	C2 varchar(50),
	C3 int,
	C4 decimal (5, 2),
	C5 varchar(50),
	CONSTRAINT pk_R PRIMARY KEY(FK1, FK2)
	)
drop table R


insert into R(FK1, FK2, C1, C2, C3, C4, C5) values  
(1, 3, 'Chicken Breast', 'Caesar Salad', 10, 150.5, 'R123'), 
(2, 5, 'Tomato', 'Caprese Salad', 12, 175.25, 'R454'), 
(3, 3, 'Salmon', 'Honey Mustard Salmon', 29, 200.75, 'R183'), 
(4, 1, 'Avocado', 'Shrimp Warps', 18, 150.25, 'R194'), 
(7, 2, 'Spinach', 'Spinach Risotto', 32, 125.75, 'R104'), 
(16, 12, 'Quinoa', 'Burrito Bowl', 15, 250.25, 'R193'), 
(5, 13, 'Avocado', 'Guacamole', 19, 175.25, 'R185'), 
(2, 2, 'Tomato', 'Bruschetta', 13, 100.5, 'R182'), 
(6, 1, 'Chicken Breast', 'Alfredo Pasta', 25, 250, 'R190'), 
(9, 6, 'Salmon', 'Teriyaki Salmon', 16, 220.25, 'R100'), 
(8, 4, 'Quinoa', 'Quinoa Salad', 30, 170.75, 'R97'), 
(5, 8, 'Spinach', 'Spinach and Feta', 14, 100.25, 'R341')

SELECT C1, avg(C3) AvgC3, SUM(C4) SUMC4
FROM R 
WHERE C4 > 145 AND C5 LIKE 'R1%' 
GROUP BY C1
HAVING avg(C3) > 15 and sum(C4) < 490

SELECT * 
FROM  
(SELECT FK1, FK2, C3+C4 C3C4 FROM R 
WHERE FK1 >= FK2) r1  
full JOIN (SELECT FK1, FK2, C4
FROM R  
WHERE C4 >= 180) r2 ON r1.FK1 = r2.FK1 AND r1.FK2 = r2.FK2 


CREATE OR ALTER TRIGGER TrOnUpdate  
ON R  
FOR UPDATE AS  
DECLARE @total INT = 0 
SELECT @total = i.C3 + 5 + d.C3 + 5
FROM deleted d INNER JOIN inserted i ON d.FK1 = i.FK1 AND d.FK2 = i.FK2
WHERE d.C3 <= i.C3 
PRINT @total 

UPDATE R 
SET C3 = 28 
WHERE FK1 <= FK2  
