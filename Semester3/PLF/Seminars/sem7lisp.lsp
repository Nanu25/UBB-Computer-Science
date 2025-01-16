;Compute the depth of a tree repr as (node (subtree 1) ... (subtree n))

;depth(l1, ..., ln, level) = level is l is atom
;                         = MAX depth(li, level + 1) if l is list

(defun  depth(l level)
  (cond
    ((atom l) level)
    (t (apply #'MAX (mapcar #' (lambda (l) (depth l (+ level 1))) l)))
  )
)


(defun maindepth(l)
  (depth l 0)
)

(print (maindepth '(A (B (D) C))))


;or second variant.
;depth2(L) = 0 if l atom
;           1  + MAX(depth2(li)) if L is list

(defun depth2(l)
  (cond
    ((atom l) 0)
    (t (+ 1 (apply #'MAX (mapcar #' depth2 l))))
  )
)

(print (depth2 '(A (B (D) C))))




;Write a function to remove all elems multiples of k from a nonlinear list.

;avem nevoie de list pentru a pastra structura initiala.
;returnam doar primul element pentru ca avem un dublu set de paranteze
;remE(l1, ..., ln, k) = [] if l is numberp cand l % k == 0,
;                     =  l if l is not number or l is not multiple. 
;                     = [i e ( 1, n) U (remE li k)] if l list

;mainReme(l, k) = first element of remE(l, k)


(defun remE(l k)
  (cond
    ((and (numberp l) (eq (mod l k) 0)) nil)
    ((atom l) (list l))
    (t (list ( apply #'append (mapcar #' (lambda (l) (remE l k)) l))))    ;;putem pune mapcan in loc de append + mapcar.
  )
)

(defun mainReme (l k)
  (car (remE l k))
)

(print (mainReme '(1 2 (3 a 4) b) 2))



;Count the leafs of a tree using MAP function.
;(A (B (D (R) (F))) (C))
;count the sublist with one element.

;countLeafs(l1, ..., ln) = 0 if l atom;
;                       = 1 if l is list and length of l is 1;
;                       = i e [1, n] sigma(countLeafs (li)) if l is list;

(defun countLeafs(l)
  (cond
    ((atom l) 0)
    ((and (listp l) (= (length l) 1)) 1)
    (t (apply #'+ (mapcar #' countLeafs l)))
  )
)

(print (countLeafs '(A (B (D (R) (F))) (C))))





















