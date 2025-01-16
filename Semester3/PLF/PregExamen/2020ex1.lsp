(defun F(L1 L2)
  (append (F (car L1) L2))
    (cond
      ((null l1) (cdr l2))
      (t (list (F (car l1) l2) (car l2)))
    )
)


;; Optimized version using lambda to store intermediate result
; (defun F1(L1 L2)
;   (cond
;     ((null L1) (cdr L2))
;     (t
;       ((lambda (temp)
;         (append temp (list (cons temp (car L2)))))
;       (F1 (car L1) L2))
;     )
;   )
; )
; (print (F '(1 2 3) '(a b)))



;3.
(defun G(l)
  
    (mapcon #' list l)
  
)

(trace G)  ;; Start tracing G function
(trace mapcon)  ;; Start tracing mapcon

(print (apply #'append (G '(1 2))))

(defun rem3(l)
  (cond
    ((and (numberp l) (= (mod l 3) 0)) nil)
    ((atom l) l)
    (t (mapcar #' rem3 l))
  )
)
(print (rem3 '(1 (2 A (3 A)) (6))))