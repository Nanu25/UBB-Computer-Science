;10. Return the level of a node X in a tree of type (2). The level of the root element is 0.
;findLevel(l X level) = level if l is atom and l == x
;                     = nil if l is atom and l != X
;                     = i e [1, n] U (li) if l = [l1, ..., ln]

(defun findLevel(l X level)
  (cond
    ((and (atom l) (equal l X)) level)
    ((atom l) nil)
    (t (mapcan #' (lambda(l) (findLevel l X (+ level 1))) l))
  )
)


;A also can apply sum.

(defun mainFindLevel(l X)
  (findLevel l X -1)
)

(print (mainFindLevel '(A (B) (C (D) (E))) 'E))


;13. Define a function that returns the depth of a tree represented as (root list_of_nodes_subtree1 ... 
;list_of_nodes_subtreen) 
;Eg. the depth of the tree (a (b (c)) (d) (e (f))) is 

(defun findDepth(l level)
  (cond 
    ((atom l) level)
    (t (apply 'max (mapcar #' (lambda(l) (findDepth l (+ level 1))) l)))
  )
)

(defun mainFindDepth(l)
  (findDepth l 0)
)

(print (mainFindDepth '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K))))))



