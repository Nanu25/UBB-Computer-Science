(defun F(L)
  (cond
    ((null l) nil)
    ((listp (car l)) (append (F (CAR L)) (F (CDR L)) (CAR (F (CAR L)))))
    (T (LIST(CAR L)))
  )
)


(defun f(l)
  (cond
    ((null l) nil)
    (t ((lambda (fl)
        (cond
          ((listp (car l)) (append (fl) (f (cdr l)) (car fl)))
          (t (LIST(car l)))
        )
      ) (f (car l))
      )
    )
  )
)



(defun F(x &OPTIONAL y)
  (cond
    ((null y) (cdr x))
    (t (cons (CAR x) y))
  )
)

(print (append (F '(1 2)) (F '(3 4) '(5 6))))




(defun subE(l level e e1)
  (cond
    ((and (atom l) (and (oddp level) (equal e l))) e1)
    ((atom l) l)
    (t (mapcar #' (lambda (l) (subE l (+ level 1) e e1)) l))
  )

)

(print (subE '(1 d (2 d (d))) 0 'd 'f))




