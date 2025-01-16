;Determine the length of a list. (1 (2 (a) c d) (3)) = 6

;LG(l1, ..., ln) = 0 if l is nil
;   = 1  if l1 is an atom
;   =  LG(l1) + LG(l2, ..., ln) if l1 is a list


(defun LG(l)
  (cond
    ((null l) 0)
    ((atom l) 1)
    (t (+ (LG (car l)) (LG (cdr l))))
  )
)

(print (LG '(1 (2 (a) c d) (3))))


;With MAP function
;Apply the function on every element of the list.

(DEFUN LG1(L)
  (COND
    ((null L) 0)
    ((ATOM L) 1)
    (T (APPLY #'+ (MAPCAR 'LG1 L)))
  )
)
(print (LG1 '(1 (2 (a) c d) (3))))

;Define a function that, given a nonlinear list, returns the list of 
;atoms (from any level) in the list.
;(ATOMI '(1 (2 (3 (4 5) 6)) (7 (8 9)))) = (1 2 3 4 5 6 7 8 9)


;concat(l1, ..., ln)  = null if l si null
;                     = l1 if l1 is atom
;                     = append(concat(l1), concat(l2, ..., ln)) if l1 is list 

(defun concat(l)
  (cond
    ((null l)  nil)
    ((atom l)  (list l))
    (t (append (concat (car l)) (concat (cdr l))))
  )
)
(print (concat '(1 (2 (3 (4 5) 6)) (7 (8 9)))))


;With MAP function
;Apply the function on every element of the list.

(defun concat1(l)
  (cond
    ((null l) nil)
    ((atom l) (list l))
    (t (apply #' append (MAPCAR 'concat1 l)))
  )
)
(print (concat1 '(1 (2 (3 (4 5) 6)) (7 (8 9)))))



(DEFUN ATOMI (L)
  (COND
    ((ATOM L) (LIST L))
    (T (MAPCAN #'ATOMI L))
  )
)
(print (ATOMI '(1 (2 (3 (4 5) 6)) (7 (8 9)))))



;Define a function which, given a nonlinear list, returns T if all 
;sublists (including the list) have even length (at the surface level), or NIL otherwise. 
;(VERIF '(1 (2 (3 (4 5))))) = T
;(VERIF '(1 (2 (3 (4 5 6))))) = NIL

;verif(l1, l2, ..., ln) = true if l is nill
;           false if l1 is list and length(l1) is odd;
;           verif(l2, l3, ..., ln) if l1 is atom
;           and verif(l1) verif(l2, ..., ln)

(defun isOdd(l)
  (cond
    ((oddp l) t)
    (t nil)
  )
)

(defun verif(l)
  (cond 
    ((null l) t)
    ((atom (car l)) (verif (cdr l)))
    ((isOdd (length (car l))) nil)
    (t (and (verif (car l)) (verif (cdr l))))
  )
)

(print (verif '(1 (2 (3 (4 5))))))
(print (verif '(1 (2 (3 (4 5 6))))))


;With map functions

(defun verif1(l)
  (cond
    ((null l) t)
    ((atom l) t)
    ((isOdd (length  l)) nil)
    (t (mapcan #'verif1 l))
  )
)


(trace verif1 isOdd)
(print (verif1 '(1 (2 (3 (4 5))))))
(print (verif1 '(1 (2 (3 (4 5 6))))))


;Course cersion
DEFUN MYAND (L)
(COND
((NULL L) T)
((NOT (CAR L)) NIL)
(T (MYAND (CDR L)))
)
)
(DEFUN VERIF (L)
(COND
((ATOM L) T)
((NOT (EVEN L)) NIL)
(T (FUNCALL #’MYAND
(MAPCAR #‘VERIF L)))
)
)








