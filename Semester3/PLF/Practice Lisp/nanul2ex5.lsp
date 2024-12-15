;5. Return the level (depth) of a node in a tree of type (1). The level of the root element is 0.

; find_left(l1l2...ln, nrNoduri, nrMuchii) = 
; = nil, if n = 0
; = nil, if nrNoduri = 1 + nrMuchii
; = {l1} U {l2} U find_left(l3...ln, nrNoduri + 1, l2 + nrMuchii), otherwise

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



;findLevel(l1, ..., ln X level) = 0 if l is null
;                                 level if l1 = X
;                                 findLevel(l3, ..., ln X level + 1) or findLevel(l5, ..., ln X level + 1) otherwise.

(defun findLevel(l X level)
  (cond
    ((null l) 0)
    ((equal X (car l)) level)
    (t (+ (findLevel (left  l) X (+ level 1)) (findLevel (right  l) X (+ level 1))))
  )
)

(defun mainLevel (l X)
  (findLevel l X 0)
)

;(A 2 B 0 C 2 D 0 E 0)
(print (mainLevel '(A 2 B 0 C 2 D 0 E 1 T 0) 'T))




