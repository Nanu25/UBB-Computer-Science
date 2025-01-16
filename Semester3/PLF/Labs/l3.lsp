;Write a function that returns the maximum of numeric atoms in a list, at any leve
;findMax(l1, ..., ln) = l if l1 is atom
;                     = 99999999 if l is nil
;                     = max(U(findMax(li))) otherwise.

(defun findmax(l)
  (cond
    ((numberp l) l)
    ((atom l) -99999999)
    (t (apply 'max (mapcar #' findmax  l)))
  )
)

(print (findmax '(3 (B (10 (-3) (4)) (103 (23))) (-4 (F (J (3213)) (23))))))