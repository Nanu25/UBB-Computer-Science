;changeTree(l1, ..., ln, level, E) = E if level is odd and l atom
;                                   = l is l is atom
;                                   = i = [1, n] U(li) if l list
(defun changeTree(l level el)
  (cond
    ((and (atom l ) (oddp level)) el)
    ((atom l) l)
    (t (mapcar #' (lambda (l) (changeTree l (+ level 1) el)) l))
    
  )
)

(defun mainchangeTree(l el)
  (changeTree l 1 el)

)

(print (mainchangeTree '(a(b (g)) (c (d (e)  (f)))) 'h))