f(1,1):-!.
f(K, X):-
    K1 is K - 1,
    f(K1, Y),
    Y > 1, 
    !,
    K2 is K1 - 1,
    X is K2.
f(K, X):-
    K1 is K - 1,
    f(K1, Y),
    Y > 0.5, 
    !,
    X is Y.
f(K, X):-
    K1 is K - 1,
    f(K1, Y),
    X is Y - 1.


f(1, 1):-!.
f(K, X):-
    K1 is K - 1,
    f(K1, Y),
    aux(K1, Y, X).

aux(K1, Y, X):-
    Y > 1,
    !,
    K2 is K1 - 1,
    X is K2.

aux(_, Y, X):-
    Y > 0.5,
    !,
    X is Y.
aux(_, Y, X):-

    X is Y - 1.



insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).


arr([H | _], 1, [H]).
arr([_ | T], K, R):-
    K >= 1,
    arr(T, K, R).
arr([H | T], K, R):-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).


check([], 1).
check([H | T], P):-
    check(T, P1),
    P is P1 * H.

onesol(L, K, P, R):-
    arr(L, K, R),
    check(R, P1),
    P > P1.

allsol(L, K, P, Res):-
    findall(R, onesol(L, K, P, R), Res).

    
    
    
    
    
    




