;Compute the number of nodes from the even levels of an n-ary tree, represented as (root (subtree_1) 
;(subtree_2) ... (subtree_n)). The level of the root is 1. For example, for the tree (A (B (D (G) (H)) (E 
;(I))) (C (F (J (L)) (K)))) the result is 7. 


;nrElemEvenLevels(l1, ..., ln, level) = 0 if l is null
;                                       1 is l1 is atom and level is even
;                                       Sigma(nrElemEvenLevels(l2, ..., ln, level + 1)) otherwise

(defun nrElemEvenLevels(tree level)
  (cond
    ((and (atom tree) (= (mod level 2) 0)) 1)
    ((atom tree) 0)
    (t (apply '+ (mapcar #' (lambda (tree) (nrElemEvenLevels tree (+ level 1))) tree)))
  )
)

(defun mainnr(tree)
  (nrElemEvenLevels tree 0)
)


(print (mainnr '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K))))))

;to do model
;findNodesLevelK(l1, ..., ln, level, k) = list l1 if level == k and l1 is atom
;                                       = nil if l1 is atom
;                                       = U (findNodesLevelK (l2, ..., ln), level + 1, k)

(defun findNodesLevelK (tree level k)
  (cond
    ((and (atom tree) (= level k)) (list tree))
    ((atom tree) nil)
    (t (apply 'append (mapcar #' (lambda (tree) (findNodesLevelK tree (+ level 1) k)) tree)))
  )
)


(defun findNodesLevelK1 (tree level k)
  (cond
    ;; If the current node is an atom and at the desired level, return it in a list
    ((and (atom tree) (= level k)) (list tree))
    ;; If it's an atom but not at the desired level, return nil
    ((atom tree) nil)
    ;; Otherwise, recursively process the subtrees and concatenate the results
    (t (mapcan (lambda (subtree) (findNodesLevelK subtree (+ level 1) k)) tree))))


(print (findNodesLevelK1 '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))) 0 2) )

