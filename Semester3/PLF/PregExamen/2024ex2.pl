f([], []).
f([_ | T], S):-
    !,
    f(T, S).
 f([H | T], [H | S]):-
    H mod 2 =:= 0,
    f(T, S).


%g([], -1).
%g([H | T], S):-
 %   g(T, S1),
  %  S 1 > 0,
   % !,
   % S is S1 + H.
%g([_ | T], S).




insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

perm([], []).
perm([H | T], R):-
    perm(T, P),
    insertEl(H, P, R).


check([], 1).
check([_], 1).
check([H1, H2 | T], Ok):-
    abs(H2 - H1) =< 2,
    !,
    check([H2 | T], Ok).
check(_, 0).

generateList(N, Index, []):-
    X is N * 2,
    Index == X,
    !.
generateList(N, Index, [Index | R]):-
    Index1 is Index + 1,
    generateList(N, Index1, R).

onesol(L, R):-
    perm(L, R),
    check(R, 1).

allsol(N, Res):-
    generateList(N, N, L),
    findall(R, onesol(L, R), Res).
    
    
    
    







