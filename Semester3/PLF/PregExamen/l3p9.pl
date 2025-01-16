%9. Generate all permutation of N (N - given) respecting the property: for every 2<=i<=n exists an 1<=j<=i, 
%so |v(i)-v(j)|=1.

%insertEl(e l1, ..., ln) = e u l1 u l2 u ... u ln if n >= 0
%						= l1 u insertEl(e, l2, ... , ln) if n > 0
%

insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

%perm(l1, ..., ln) = [] if l is empty
%				= insertEl(l1, perm(l2, ..., ln))

perm([], []).
perm([H | T], R):-
    perm(T, L),
    insertEl(H, L, R).


%findElem(l1, ..., ln, E, CurrIndex, Index) = 0 if CurrIndex = Index
%											= 1 if l1 - E == 1 || E - l1 == 1
%											= findElem(l2, ..., ln, E, CurrIndex + 1, Index).

%flowmodel(i, i, i, i, o).
findElem(_, _, 1, 1, 1).
findElem(_, _, CurrIndex, CurrIndex, 0).
findElem([H | _], E, _, _, Ok):-
    H - E =:= 1,
    Ok is 1.
findElem([H | _], E, _, _, Ok):-
    E - H =:= 1,
    Ok is 1.
findElem([_ | T], E, CurrIndex, Index, Ok):-
    Curr is CurrIndex + 1,
    findElem(T, E, Curr, Index, Ok).

%check(l1, ..., ln, a1, ..., an, index) = 1 if l is empty
%					= 0 if not findElem(a1, ..., an, H, index).
%					= check(l2, ..., ln).

%flowmodel(i, i, i, o).
check([], _, _,1).
check([H | T], L, Index, Ok):-
    findElem(L, H, 1, Index, Ok1),
    Ok1 == 1,
    !,
    check(T, L, Index + 1, Ok).
check(_, _, _, 0).
    
onesol(L, R):-
    perm(L, R),
    check(R, R, 1, Ok),
    Ok == 1.

findsol(L, Result):-
    findall(R, onesol(L, R), Result).
    
