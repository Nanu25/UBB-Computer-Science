%1.
f([], -1).
f([H | T], S):-
    f(T, S1),
    S1 > 0,
    !,
    S is S1 + H.
f([_|T], S):-
    f(T, S1),
    S is S1.

f1([], -1).
f1([H | T], S):-
    f1(T, S1),
    aux(H, S1, S).

aux(H, S1, S):-
    S1 > 0,
    !,
    S is S1 + H.
aux(_, S1, S1).

countOc([], _, 0).
countOc([H | T], E, C):-
    H =:= E,
    !,
    countOc(T, E, C1),
	C is C1 + 1.
countOc([_ | T], E, C):-
    countOc(T, E, C).

makeSet([], []).
makeSet([H | T], R):-
    makeSet(T, R1),
    countOc(R1, H, C),
    C =:= 0,!,
    R = [H | R1].
makeSet([_ | T], R):-
    makeSet(T, R).

makeSet1([], R, R).
makeSet1([H | T], R, C):-
    countOc(R, H, X),
    X =:= 0,
    !,
    R1 = [H | R],
    makeSet1(T, R1, C).
makeSet1([_|T], R, C):-
    makeSet1(T, R, C).


%insertEl(E, l1, ..., ln) = E u l1 l2, ... ln 
%						  = l1 u insertEl(E, l2, ..., ln)
insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

%arr(l1, ..., ln, K) = l1 if k = 1.
%						arr(l2, ..., ln, k) if k >= 1 and n > 0
%						insertEl(l1, arr(l2, ..., ln, k - 1)), if k > 1

arr([H | _], 1, [H]).
arr([_ | T], K, R):-
    K >= 1,
    arr(T, K, R).
arr([H | T], K, R):-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).

findP([], 1).
findP([H | T], P):-
    findP(T, P1),
    P is P1 * H.

onesol(L, K, P, R):-
    arr(L, K, R),
    findP(R, P1),
    P1 =:= P.

all(L, K, P, Res):-
    findall(R, onesol(L, K, P, R), Res).
    






