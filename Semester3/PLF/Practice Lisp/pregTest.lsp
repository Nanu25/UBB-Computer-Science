;a) Write a function to test whether a list is linear.
;b) Write a function to replace the first occurence of an element E in a given list with an other element O.
;c) Write a function to replace each sublist of a list with its last element.
; A sublist is an element from the first level, which is a list.
; Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f)
; (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)
;d) Write a function to merge two sorted lists without keeping double values


;a
;isflaten(l1, ... ,ln) = true if l is null
;                           = false if (car l) is list
;                           = isflaten(cdr l) otherwise.

(defun isflaten(l)
  (cond
    ((null l) 1)
    ((listp (car l)) 0)
    (t (isflaten (cdr l)))
  )
)

(print (isflaten '(1 2 3 4)))

;b
; replaceE(l1, ..., ln, E, O) = O if l1 = E
;                             = l1 u replaceE(l2, ..., ln, E, O) otherwise

(defun replaceE(l E O)
  (cond
    ((null l) nil)
    ((eq (car l) E) (cons O (cdr l)))
    (t (cons (car l) (replaceE (cdr l) E O)))
  )
)

(print (replaceE '(1 2 3 a b a) 'a 'E))

;c) Write a function to replace each sublist of a list with its last element.
; A sublist is an element from the first level, which is a list.
; Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f)
; (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)

;rep(l1, ..., ln) = nil if l is null
;                       = l1 u rep(l2, ..., ln, l1) if l1 is atom
;                       = findLast(car l) u rep(l2, ..., ln) if car l is list.
                        

(defun findLast(l)
  (cond 
    ((null l) nil)
    ((null (cdr l)) 
     (cond
       ((listp (car l)) (findLast (car l)))
       (t (car l))))
    (t (findLast (cdr l)))
  )
)

(defun rep(l)
  (cond
    ((null l) nil)
    ((atom (car l)) (cons (car l) (rep (cdr l))))
    (t (cons (findLast (car l)) (rep (cdr l))))
  )
)

(print (rep '(a (b c) (d (e (f))))))



;d) Write a function to merge two sorted lists without keeping double values
;mergeList(a1, ..., an, b1, b2, ..., bm) = a if b nill
;                                        = b if a nill
;                                        = a1 u mergeList(a2, ... an, b1, ..., bm) if a1 < b1 
;                                        = b1 u mergeList(a1, ... an, b2, ..., bm) if b1 < a1
;                                        = a1 u mergeList(a2, ... an, b2, ..., bm) if a1 = b1 

(defun mergeList(a b)
  (cond
    ((null a) b)
    ((null b) a)
    ((< (car a) (car b)) (cons (car a) (mergeList (cdr a) b)))
    ((< (car b) (car a)) (cons (car b) (mergeList a (cdr b))))
    (t (cons (car a) (mergeList (cdr a) (cdr b))))
  )
)

(print (mergeList '(1 2 3 4 5 10) '(1 3 5 7 9 )))


;b) Write a function to get from a given list the list of all atoms, on any 
; level, but on the same order. Example:
; (((A B) C) (D E)) ==> (A B C D E)

;b getList(l1, l2, ..., ln) = nil if l is null
;                           = l1 u getList(l2, ..., ln) if l1 is atom;
;                           = getList(l1) u getList(l2, ..., ln) if l1 is list

(defun getList(l)
  (cond
    ((null l) nil)
    ((atom (car l)) (append (list (car l)) (getList (cdr l))))
    (t (append (getList (car l)) (getList (cdr l))))
  )
)

(print (getList '(((A B) C) (D E))))

;c) Write a function to return the set of all the atoms of a list.
; Exemplu: (1 (2 (1 3 (2 4) 3) 1) (1 4)) ==> (1 2 3 4)

;flatten(l1, ..., ln) = null if l is nil
;                     = l1 u flatten(l2, ..., ln) if l1 is atom;
;                     = flatten(l1) U flatten(l2, ..., ln) otherwise.

(defun flatten(l)
  (cond
    ((null l) nil)
    ((atom (car l)) (append (list (car l)) (flatten (cdr l))))
    (t (append (flatten (car l)) (flatten (cdr l))))
  )
)

(print (flatten '((1 (2 (1 3 (2 4) 3) 1) (1 4)))))


(defun nrOc(l E)
  (cond
    ((null l) 0)
    ((eq (car l) E) (+ 1 (nrOc (cdr l) E)))
    (t (nrOc (cdr l) E))
  )
)

;makeSet(l1, ..., ln) = nil if l is null;
;                     = nil if nrOc(l1, l) > 1,
;                     = l1 u makeSet(l2, ..., ln)


(defun makeSet(l)
  (cond
    ((null l) nil)
    ((> (nrOc l (car l)) 1) (makeSet (cdr l)))
    (t (cons (car l) (makeSet (cdr l))))
  )
)

(defun mainSet(l)
  (makeSet (flatten l))
)

(print (mainSet '((1 (2 (1 3 (2 4) 3) 1) (1 4)))))

















