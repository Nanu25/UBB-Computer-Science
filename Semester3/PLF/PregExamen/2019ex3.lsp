(defun remE(l In N P)
  (cond
    ((null l) nil)
    ((= N P) (remE (cdr l) In (+ N In) (+ P 1)))
    (t (cons (car l) (remE (cdr l) In N (+ P 1))))
  )
)

(defun mainremE(l N) 
  (remE l N N 1)
)

(print (mainremE '(1 2 3 4 5) 2))


;countAtom(l1, ..., ln, C) = C if l is null
;                           = countAtom(l2, ..., ln, C + 1) if l1 is atom
;                           = countAtom(l2, ..., ln, C) if l1 is number.

(defun countAtom(l C)
  (cond
    ((null l) C)
    ((numberp (car l)) (countAtom (cdr l) C))
    (t (countAtom (cdr l) (+ 1 C)))
  )
)

;countSub(l level) = 0 if l is atom
;            = 1 +  i e (1, n), Sigma(l1) if l is list of len odd and level even
;             = i e (1, n), Sigma(l1) if l is list

(defun countSub(l level)
  (cond
    ((atom l) 0)
    ((and (oddp (countAtom l 0)) (= (mod level 2) 0)) (+ 1 (apply '+ (mapcar  (lambda (l) (countSub l (+ level 1))) l))))
    (t (apply '+ (mapcar  (lambda (l) (countSub l (+ level 1))) l)))
  )
)

(defun mainCount(l)
  (countSub l 0)
)

(print (mainCount '(A (B 2) (1 C 4) (1 (6 F)) (((G) 4) 6))))
