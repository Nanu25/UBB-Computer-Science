;nrOc(l1, ..., ln, e) = 0 if l is null
;           = 1 + nrOc(l2, ..., ln) if e = l1
;           = nrOc(l2, ..., ln) otherwise


(defun nrOc(l E)
  (cond
    ((null l) 0)
    ((eq (car l) E) (+ 1 (nrOc (cdr l) E)))
    (t (nrOc (cdr l) E))
  )
)

;makeSet(l1, ..., ln) = nil if l is null;
;                     = makeSet(l2, ..., ln) if nrOc(l1, l) > 1,
;                     = l1 u makeSet(l2, ..., ln) if nrOc(l1, l) = 1.


(defun makeSet(l)
  (cond
    ((null l) nil)
    ((> (nrOc l (car l)) 1) (makeSet (cdr l)))
    (t (cons (car l) (makeSet (cdr l))))
  )
)


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

(defun mainMerge(a b)
  (makeSet (mergeList a b))
)


(print (mainMerge '(1 3 5 7) '(2 4 6 8)))
(print (mainMerge '(1 2 3 4 5) '(1 2 3 4 5)))
(print (mainMerge '(1 2 3 4 5) '(6 7 8 9)))
(print (mainMerge '(1 2 4 5 7) '(1 3 4 6 7)))


