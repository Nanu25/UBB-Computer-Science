;Return the list of nodes on the k-th level of a tree of type (1).



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


;findNodes(l1, ..., ln k index) = null if l is nil
;                                 l1 if index == k  
;                                 findNodes(left l k index + 1) u findNodes(right l k index + 1) otherwise.

;i don t use cons because it will put null in my result.
(defun findNodes(l k index)
  (cond
    ((null l) nil)
    ((= index k) (list (car l)))
    (t (append (findNodes (left l) k (+ index 1)) (findNodes (right l) k (+ index 1))))
  )
)

(print (findNodes '(A 2 B 0 C 2 D 0 E 0) 1 0))
(print (findNodes '(A 2 B 0 C 2 D 0 E 1 X 0) 2 0))








