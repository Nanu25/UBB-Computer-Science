;Ex2. Consider the definition of the function that generates the list 
;of subsets of a set represented as a list.
(defun insFirst (e l)
  (cond
    ((null l) nil)
    (t (cons (cons e (car l)) (insFirst e (cdr l))))
  )
)

(defun subSet(l)
  (cond
    ((null l) (list nil))
    (t (append (subSet (cdr l)) (insFirst (car l) (subSet (cdr l)))))
  )
)

;As you can see, the call (subSet (cdr l)) is repeated. To avoid the 
;repeated call, we will use a LAMBDA expression.

;A possible solution is the following:
(defun subSet (l)
  (cond
    ((null l) (list nil))
    (t ((lambda (s)
    (append s (insPrimaPoz (car l) s))
     )
     (subSet (cdr l))
     )
    )
  )
)


(defun G(F l)
  (funcall F l)
)

(print (G #' (lambda (l) (G #' cdr l)) '(1 2 3)))




(defun inEven(l)
  (cond
    ((and (numberp l) (evenp l)) (+ l 1))
    ((atom l) l)
    (t (mapcar #' inEven l))
  )
)

(print (inEven '(1 s 4(2 f(7)))))





