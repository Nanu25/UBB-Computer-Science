(defun inc(l)
  (cond
    ((and (numberp l) (evenp l)) (+ l 1))
    ((atom l) l)
    (t (mapcar #' inc l))
  )
)
(print (inc'(1 s 4 (2 f (7)))))

(defun inc1(l)
  (cond
    ((null l) nil)
    ((and (numberp (car l)) (evenp (car l))) (cons (+ (car l) 1) (inc1 (cdr l))))
    ((atom (car l)) (cons (car l) (inc1 (cdr l))))
    (t (cons (inc1 (car l)) (inc1 (cdr l))))
  )
)
(print (inc1'(1 s 4 (2 f (7)))))


(defun findMax(l)
  (cond
    ((numberp l) l)
    ((atom l) 0)
    (t (apply 'max (mapcar #' findMax l)))
  )
)

(defun countAll(l level)
  (cond
    ((atom l) 0)
    ((and (oddp level) (evenp (findMax l))) 1)
    (t (apply '+ (mapcar (lambda (l) (countAll l (+ 1 level)))l)))
  )
)

(defun mainCount(l)
  (countAll l 0)
)

(print (mainCount '(A (B 2) (1 C 4) (1 (6 F)) (((G) 4) 6))))
