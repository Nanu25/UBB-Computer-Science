%2
f([], -1).
f([H | T], S):-
    H > 0,
    f(T, S1),
    S1 < H, 
    !,
    S is H.
f([_| T], S):-
    f(T, S1),
    S is S1.

f1([], -1).
f1([H | T], S):-
    f1(T, S1),
    aux(H, S1, S).

aux(H, S1, S):-
    H > 0,
    H > S1,
    !,
    S is H.
aux(_, S1, S1).

%insertEl(E, l1, ..., ln) = E u l1 ..., ln if n >= 0 
%							l1 u insert(E, l2, ..., ln).

insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

%arr(l1, ..., ln, k) = L1 if k = 1 
%					= arr(l2, ..., ln, k) if k >= 1 n > 0
%					=insertEl(l1, arr(l2, ..., ln, k - 1))if k > 1 n > 0

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
    P1 == P.

allsol(L, K, P, Res):-
    findall(R, onesol(L, K, P, R), Res).






