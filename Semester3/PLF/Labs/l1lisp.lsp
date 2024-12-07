; 15.
; a) Write a function to insert an element E on the n-th position of a linear list.
; b) Write a function to return the sum of all numerical atoms of a list, at any level.
; c) Write a function to return the set of all sublists of a given linear list. Ex. For list ((1 2 3) ((4 5) 6)) => 
; ((1 2 3) (4 5) ((4 5) 6)) 
; d) Write a function to test the equality of two sets, without using the difference of two sets

; addElement(l1, ..., ln E index) = [] if l is NIL
;                                 e if index is N
;                                 l1 u addElement(l2, ..., ln e index + 1)
(defun addElement(l e n index)
  (cond
    ((= n index) (cons e l))
    ((NULL l) NIL)
    (t (cons(car l) (addElement (cdr l) e n (+ index 1) )))
  )
)
; (print (addElement '(1 2 3 4) 'x 10 0))

;B

; sum(l1, ..., ln) = 0 if l is nil
;                   l1 + sum(l2, ..., ln) if l1 is numberp
;                   sum(l1) +  sum(l2, .., ln) otherwise

(defun sum(l)
  (cond
    ((numberp l) l)
    ((atom l) 0)
    (t (+ (sum(car l)) (sum(cdr l)) ))
  )
)
; (print (sum '(1 2 (b 5))))


;c
;collect-sublists(l1, ..., ln) = [] if l is nil
;                               l1 u collect-sublists(car l1) u collect-sublists(l2, ..., ln) is l1 is list
;                               collect-sublists(l2, ... ,ln ) otherwise;

(defun collect-sublists (l)
  (cond
    ((null l) nil)  
    ((listp (car l))  
     (append
      (list (car l))  
      (collect-sublists (car l))  
      (collect-sublists (cdr l))))  
    (t (collect-sublists (cdr l))))
)  


; (print (collect-sublists '((1 2 3) ((4 5) 6))))  ; Output: ((1 2 3) ((4 5) 6))
; (print (collect-sublists '(1 2 3)))  ; Output: nil 



;d
; nrOcc(l1, ..., ln, e) =
;                           0 if l1 is nil
;                           1 + nrOcc(l2, ..., ln, e) if l1 = e
;                           nrOcc(l2, ..., ln, e) if l1 != e

(defun nrOcc(e l)
  (cond 
    ((atom l) 0)
    ((= (car l) e) (+ 1 (nrOcc e (cdr l))))
    (t (nrOcc e (cdr l)))
  )
)


; eqset(l1, ..., ln a1, ..., am) = 1 if l1 is nil or a is nil
;               0 if nrOcc(l1, l2 ... ln) != nrOcc(l1, a) or nrOcc(car l2 l1) != nrOcc(car l2 l2)
;               eqset(l2,..., a2...) otherwise.

(defun eqset(l1 l2 c1 c2)
  (cond
    ((and (null l1) (numberp (car l2))) 0)
     ((and (null l2) (numberp (car l1))) 0)
    ((atom l2) 1)
    ((atom l1) 1)   ;if i find all the elements;
    ((/= (nrOcc (car l1) c1) (nrOcc (car l1) c2)) 0)
    ((/= (nrOcc (car l2) c1) (nrOcc (car l2) c2)) 0)
    (t (eqset (cdr l1) (cdr l2) c1 c2))
  )
)

(print (eqset '(1 2 3) '(3 2 1) '(1 2 3) '(3 2 1)))

