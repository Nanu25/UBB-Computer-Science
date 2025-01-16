%f makes the max from a list.
f([], 0).
f([H | T], S):-
    f(T, S1),
    S1 < H,
    !,
    S is H.
f([_ | T], S):-
    f(T, S1),
    S is S1.

f1([], 0).
f1([H | T], S) :-  
    f1(T, S1),  
    aux(H, S1, S).

% aux(H: number, S1: number, S: number)
% (i, i, o) - deterministic
aux(H, S1, S) :-  
    S1 < H,  
    !,  
    S is H.
aux(_, S1, S1).


%3.
g([], []).
g([H | T], [H | S]):-
    g(T, S).
g([H | T], S):-
    H mod 2 =:= 0,
    g(T, S).

insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

perm([], []).
perm([H | T], R):-
    perm(T, P),
    insertEl(H, P, R).

check([], 1).
check([_], 1).
check([H1, H2 | _], Ok):-
    abs(H1 - H2) > 3,
    !,
    Ok is 0.
check([_, H2 | T], Ok):-
    check([H2 | T], Ok).

onesol(L, R):-
    perm(L, R),
    check(R, Ok),
    Ok =:= 1.

allsol(L, Res):-
    findall(R, onesol(L, R), Res).






