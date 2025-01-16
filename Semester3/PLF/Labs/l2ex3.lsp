;3. Return the number of levels of a tree of type

;(A 2 B 0 C 2 D 0 E 0)

; find_left(l1l2...ln, nrNoduri, nrMuchii) = 
; = nil, if n = 0
; = nil, if nrNoduri = 1 + nrMuchii
; = l1 U l2 U find_left(l3...ln, nrNoduri + 1, l2 + nrMuchii), otherwise

(defun find_left (tree nodes edges)
  (cond
   	((null tree) nil)
    ((= nodes (+ 1 edges)) nil)
    (t (cons (car tree) 
             (cons (cadr tree) 
                   (find_left (cddr tree) (+ 1 nodes) (+ (cadr tree) edges))
             )
       )
    )
  )
)

(defun left (tree)
  (find_left (cddr tree) 0 0)
)

; find_right(l1l2...ln, nrNoduri, nrMuchii) =
; = nil, if n = 0
; = nil, if nrNoduri = 1 + nrMuchii
; = l1 U l2 U find_right(l3...ln, nrNoduri + 1, l2 + nrMuchii), otherwise

(defun find_right (tree nodes edges)
  (cond
   	((null tree) nil)
    ((= nodes (+ 1 edges)) tree)
    (t (find_right (cddr tree) (+ 1 nodes) (+ (cadr tree) edges)))
  )
)

(defun right (tree)
  (find_right (cddr tree) 0 0)
)


(defun maxim(a b)
  (cond
    ((> a b) a)
    (t b)
  )
)

;nrLevels(l1, ..., ln) = 0 if tree is null 
;                       1 if l2 is 0
;                       1 + max(nrLevels(l3,..., ln), nrLevels(l4,...,ln)) if l2 is 2
;
(defun nrLevels (tree)
  (cond
    ((null tree) 0)           ; No levels in an empty tree
    ((= (cadr tree) 0) 1)    ; A leaf node contributes 1 level
    ((= (cadr tree) 1)      ; A node with one child
     (+ 1 (nrLevels (cdr (cdr tree)))))
    (t                        ; A node with two children
     (+ 1 (maxim (nrLevels (left tree)) ; Levels in left subtree
                 (nrLevels (right tree)))))))
(print (nrLevels '(A 2 B 0 C 2 D 0 E 0)))
(print (nrLevels '(A 2 B 0 C 2 D 0 E 1 X 0)))








