; (print (+ 1 2))
; (print (list 1 2 3 4 5))
; (print (null '(6)))
; (print (atom 9))
; (print (list '(1 2 3) '(4 5 6)))    ;a list with two lists
; (print (append '(1 2 3) '(4 5 6)))  ;concatenate two lists.




;factorial(n) = 1 if n = 0
;               n * factorial(n - 1) if n > 0

(defun factorial(n)
  (cond     ;like switch
    ;condition 1 => ret value 1;
    ;condition 2 => ret value 2;
    ;...
    ;(t  otherwise ret)

    ( (= n 0) 1)
    (t (> n 0) (* n (factorial (- n 1))))
  )
)

(print (factorial 3 ))




;suma(l1, ..., ln) = 0 if n = 0
;                     l1 + suma(l2, ..., ln) if the list is not empty

(defun suma(l)
  (cond
    ( (null l) 0)
    (t (+ (car l) (suma (cdr l))))
  )
)
(print (suma '(1 2 3 4 5)))


;sumac(l1, ..., ln, c) = c if n = 0
;                         sumac(l2, ..., ln, c + l1) if n > 0

; (defun sumc(l c)
;   (cond
;     ( (null l) c)
;     (t (sumc (cdr l) (+ c (car l))))
;   )
; )


; (defun mainsc (l)
;   (sumc l 0)
; )
; (print (mainsc '(1 2 3 4 5)))


;Merge two sorted linear lists without keeping double values.
;mrg(l1, ..., ln, a1, ..., am) =
;                                 l1, ..., ln if n = 0
;                                 a1,...am if m = 0
;                                 l1 u merge(l2, ..., ln, a1, ... , am) if l1 < a1
;                                 a1 u merge(l1, ..., ln, a2, ..., am) if l1 > a1
;                                 l1 u merge(l2, ..., lm, a2, ..., am) if l1 = a1

(defun mrg(a b)
  (cond
    ( (null a) b)
    ( (null b) a)
    ( (< (car a) (car b)) (cons (car a) (mrg (cdr a) b)))
    ( (> (car a) (car b)) (cons (car b) (mrg a (cdr b))))
    (t (= (car a) ( car b)) (cons (car a) (mrg (cdr a) (cdr b))))
  )
)

; (print (mrg '(1 2 3 4) '(3 4 10 21)))



;Remove all occ of an element from a list
; ex (2 1 (a (7 1) 3) 1 1 c (1)), e = 1 = > (2 (a (7) 3) c ())
;

;remE(l1 l2 ... ln, e) =  [] if n = 0;
;                       remE(l2, ..., ln, e) , l1 - atom and l1 = e
;                       remE(l1, e) u remE(l2, ..., ln, e) , l1 - list

(defun remE(l e)
  (cond 
    ((null l) ())
    ((and (atom (car l)) (equal (car l) e)) (remE (cdr l) e))
    ( (atom (car l)) (cons (car l) (remE (cdr l) e)))
    (t (cons (remE (car l) e) (remE (cdr l) e)) )
  )
)
; (print ( remE '(2 1 (a (7 1) 3) 1 1 c (1)) 1))



;Build a list with the pos of the min element from a liner list.
;  (1 2 a 7 0 1 b 0) => (5 8)

;findMin(l1 l2 ... ln,  c) = c if n = 0
;                           findMin(l2, ..., ln, l1) if number(l1) and c > l1
;                           findMin(l2, ..., ln, c) otherwise.

(defun findMin(l c)
  (cond
    ((null l) c)
    ((and (numberp (car l)) (> c (car l))) (findMin (cdr l) (car l)))
    (t (findMin (cdr l) c))
  )
)

(print (findMin ' (1 2 a 7 0 1 b 0) 100))

;posElem(l1, ... ln e index) = [] if n = 0;
;                     index u posElem(l2, ..., ln, e, index + 1) if l1 number and l1 = e
;                     posElem(l2, ..., ln, e, index + 1) otherwise.

(defun posElem(l e index)
  (cond
    ( (null l) ())
    ( (and (numberp (car l)) (= (car l) e)) (cons index (posElem (cdr l) e (+ index 1))))
    (t (posElem (cdr l) e (+ index 1)))
  )
)

(defun mainMin(l)
  (posElem l (findMin l 1000) 1)
)


(print (mainMin '(1 2 a 7 0 1 b 0) ))


























