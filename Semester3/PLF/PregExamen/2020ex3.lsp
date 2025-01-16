
(defun F(x &REST y)
  (cond
    ((null y) x)
    (t (append x (mapcar #' CAR y)))
  )
)

(print (append (F '(1 2)) (F '(3 4) '(5 6) '(7 8))))


(defun replacek(l level k)
  (cond
    ((and (atom l) (= level k)) 0)
    ((atom l) l)
    (t (mapcar #' (lambda (l) (replacek l (+ level 1) k)) l))
  )
)


(defun mainrep(l k)
  (replacek l 0 k)
)

(print (mainrep '(a (1 (2 b)) (c (d))) 2))

