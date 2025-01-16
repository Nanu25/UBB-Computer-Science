%2.
f([], 0).
f([H | T], S):-
    f(T, S1),
    H < S1, 
    !,
    S is H + S1.
f([_ | T], S):-
    f(T, S1),
    S is S1 + 2.

f([], 0).
f([H | T], S):-
    f(T, S1),
    aux(H, S1, S).

aux(H, S1, S):-
    H < S1,
    !,
    S is H + S1.
aux(_, S1, S):-
    S is S1 + 2.

p(1).
p(2).
q(1).
q(2).
r(1).
r(2).

s:-
    p(X),!,q(Y),r(Z),
    write(X), write(Y), write(Z), nl.

subset([], []).
subset([H | T], [H | R]):-
    subset(T, R).
subset([_ | T], R):-
    subset(T, R).

check([], 0, 0).
check([H | T], N, S):-
    check(T, N1, S1),
    N is N1 + 1,
    S is S1 + H.


onesol(L, N, R):-
    subset(L, R),
    check(R, N1, S1),
    N1 >= N,
    S1 mod 3 =:= 0.

allsol(L, N, Res):-
    findall(R, onesol(L, N,  R), Res).








