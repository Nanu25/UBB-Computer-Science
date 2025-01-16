; (defun G (L)
;   (list (car L) (car L)))  ;; Create a list with two copies of the first element

; (setq Q 'G)               ;; Set Q to the function object G
; (setq P Q)                 ;; P is also set to the function object G

; (print (funcall P '(A B C))) ;; Call P with the list '(A B C) and print the result


(defun modif(l level)
  (cond
    ((numberp l) (* level l))
    ((atom l) l)
    (t (mapcar #' (lambda (l) (modif l (+ level 1))) l))
  )
)

(defun mainmodif(l)
  (modif l 0)
)

(print (mainmodif '(1(2(A(B)))(3(4(C(5)))))))

