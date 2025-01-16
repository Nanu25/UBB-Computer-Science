;mapcar #'function '()
;aplica functia function on every element of the list  si face lista din raspunsuri
;mapcan #'function '() => nconc (f(1) f(2) ... f(n))
;nconc e aproximativ la fel cu mapcar.
;cu mapcan nu trebuie sa folosim append(for flatten a list).

;(1 2 a (3 (0 b))) => (3 6 a (9 (0 b)))
;newtriple(x) = 3 * x if x is number
;             = x if not number
;             = i e (1, n) U newtriple(xi) if x = x1, ..., xn
;base case sunt la atom level.
(defun newtriple(x)
  (cond
    ((numberp x) (* 3 x))
    ((atom x) x)
    (t (mapcar #'newtriple x))
  )
)

(print (newtriple '(1 2 3 (a 3))))

;product of num elem in a nonlinear list.
;(1 (2 a (b 3)) 4)
;every non numeric will be 1.
;product(l) = l if l is number
;           = 1 if l is atom
;           = i e (1, n) pi(li) if l = (l1, ..., ln)

(defun product (l)
  (cond
    ((numberp l) l)
    ((atom l) 1)
    (t (apply '* (mapcar #' product l)))
  )
)

(print (product '(1 (2 a (b 3)) 4)))


;find the number of nodes of even levels of a tree
;countEven(l level) = 1 if level is even and l is atom
;                   = 0 if level is odd and l is atom
;                   = i e (1, n) sigma(l1) if l = (l1, ..., ln);

(defun countEven(tree level)
  (cond
    ((and (atom tree) (= (mod level 2) 0)) 1)
    ((atom tree) 0)
    (t (apply '+ (mapcar #' (lambda (tree) (countEven tree (+ level 1))) tree )))
  )
)

(defun countEvenMain(tree)
  (countEven tree 0)  ;pana sa ajunga in primul element, creste
)

(print (countEvenMain '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K))))))










