%Subsets of a list with the property that difference between 2 cons numbers is a multiple of 3.
%They must have at least 2 elements.


%subset(l1, ..., ln) =	[] if n = 0;
%						 l1 u subset(l2, ..., ln) n >= 1
%						subset(l2, ..., ln) n >= 1
%subset(i, o).
subset([], []).
subset([H | T], [H | R]):-
    subset(T, R).
subset([_ | T], R):-
    subset(T, R).


%lengthS(l1, ..., ln) = 0 if n = 0;
%						1 + lenghtS(l2, ... ln) if n > 0
%flowmodel(i, o).
lengthS([], 0).
lengthS([_ | T], L):-
    lengthS(T, L1),
    L is L1 + 1.

%check(l1, ..., ln) = 1 if n = 1.
%					= 0 if |l1 - l2| % 3 != 0
%					= check(l2, ..., ln) otherwise.

check([_], 1):-!.
check([H1, H2 | T], Ok):-
    Dif is abs(H1 - H2),
    Dif mod 3 =:= 0,
    !,
    check([H2 | T], Ok).
check(_, 0).	%putem pune orice ca oricum nu ajunge aici

onesol(L, R):-
    subset(L, R),
    lengthS(R, Lg),
    Lg > 1,
    check(R, Ok),
    Ok =:= 1.

allsol(L, Res):-
    findall(R, onesol(L, R), Res).


