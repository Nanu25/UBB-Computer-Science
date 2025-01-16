remN([], _, _, _, _, []).
remN([_ | T], N, P, F, Np, R):-
    P =:= Np,
    Np1 is Np + N * F, 
    F1 is F * 2,
    P1 is P + 1,
    !,
    remN(T, N, P1, F1, Np1, R).
remN([H | T], N, P, F, Np, [H | R]):-
    P1 is P + 1,
    remN(T, N, P1, F, Np, R).

mainRem(L, N, R):-
    remN(L, N, 1, 1, N, R).


subset([], []).
subset([H | T], [H | R]):-
    subset(T, R).
subset([_ | T], R):-
    subset(T, R).

check([], 0).
check([_ | T], Lg):-
    check(T, Lg1),
    Lg is Lg1 + 1.

onesol(R, R1):-
    subset(R, R1),
    check(R1, Lg),
    Lg mod 2 =:= 0.

allsol(L, Result):-
    findall(R, onesol(L, R), Result).

