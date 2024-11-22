%Se da o lista L de numere si atomi.
%a) Sa se stearga toate elementele de valoare para din lista.
%b) Sa se dubleze elementele numerice ramase si sa se determine cel mai mic multiplu comun al
%elementelor numerice din aceasta lista.
%L = [ a, m, 10, 5, 6, 2, 3, 10, n, z ]
%a) Ln = [ a, m, 5, 5, 3, 3 n, z ]
%b) cmmmcL = 15

%elimpare(l1, ... , ln) = {
%							[] if n = 0;
%							l1 u elimPare(l2, ... ,ln) if l1 is odd or l1 is not number
%							elimPare(l2, ... , ln) otherwise
%elimPare(i, o).
elimPare([], []).
elimPare([H | T], [H | R]):-
    number(H),
    H mod 2 =:= 1,
    !,
    elimPare(T, R).
elimPare([H |T], [H | R]):-
    \+ number(H),
    !,
    elimPare(T, R).
elimPare([_| T], R):-
    elimPare(T, R).


%dubImp(l1, ... ,ln) = {
%						[] if n = 0
%						l1 u l1 u dubImp(l2, ... , ln) if l1 % 2 == 1
%						l1 u dubImp(l2, ... , ln) otherwise.
%

dubImp([], []).
dubImp([H | T], R):-
    number(H),
    H mod 2 =:= 1,
    !,
    dubImp(T, R1),
    R2 = [H | R1],
    R = [H | R2].
dubImp([H|T], [H | R]):-
    dubImp(T, R).

%Gcd(A, B) =
%				A if B = 0.
%				Gcd(B, A % B) othwerwise.
%

gcd(A, 0, A):-
	!.
gcd(A, B, R):-
    B > 0,
    !,
    C is A mod B,
    gcd(B, C, R).

lcmList([], C, C).
lcmList([H | T], C, R):-
    number(H),
    C1 is C * H,
    gcd(C, H, Gcd),
    Cmmmc is C1 // Gcd,
    !,
    lcmList(T, Cmmmc, R).
lcmList([ _ | T], C, R):-
    lcmList(T, C, R).


mainProblem(L, R):-
    elimPare(L, Ep),
    dubImp(Ep, Di),
    lcmList(Di, 1, R).




