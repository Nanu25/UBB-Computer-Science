; 14.
; a) Write a function to return the union of two sets.
; b) Write a function to return the product of all numerical atoms in a list, at any level.
; c) Write a function to sort a linear list with keeping the double values.
; d) Build a list which contains positions of a minimum numeric element from a given linear list.

;a. union(l1, .., ln, a1, ..., am) = a if l is nil;
;                                   l1 u union(l2, ..., ln, a1,. ..., am) if l1 not in a
;                                   union(l2, ..., ln, a1, ..., am) if l1 in a.


(defun countAp(l E)
  (cond
    ((null l) 0)
    ((equal E (car l)) (+ 1 (countAp (cdr l) E)))
    (t (countAp (cdr l) E))
  )

)

(defun uni(l1 l2)
  (cond
    ((null l1) l2)
    ((equal (countAp l2 (car l1) ) 0) (cons (car l1) (uni (cdr l1) l2)))
    (t (uni (cdr l1) l2))
  )
)

(print (uni '(1 2 a 4) '(a b 3 4 10))) 

; b. prod(l1, ..., ln) = 1 if l is nil
;                       l1 * prod(l2, ..., ln) if l1 is number
;                       prod(l2, ..., ln otherwise);

; (defun prod(l)
;   (cond
;     ((null l) 1)
;     ((numberp (car l)) (* (car l) (prod (cdr l))))
;     (t (prod (cdr l))))
; )


; (print (prod '(1 2 a 4)))

;d findMin(l1, ..., ln) = 1000 if l is nil
;                             min(findMin(l2, ..., ln), l1) otherwise.
; (defun findMin(l)
;   (cond 
;     ((null l) 1000)
;     ((< (car l) (findMin (cdr l))) (car l))
;     (t (findMin (cdr l)))
;   )
; )


; (defun findPos(l e index)
;   (cond
;     ((null l) nil)
;     ((= (car l) e) (cons index (findPos (cdr l) e (+ index 1))))
;     (t (findPos (cdr l) e (+ index 1)))
;   )
; )

; (print (findPos '(1 2 4 5 3 1 3 1) (findMin  '(1 2 4 5 3 1 3 1)) 1))

