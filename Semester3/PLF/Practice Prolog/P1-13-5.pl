%13.
%a. 
%nrOcc(l1, ..., ln, E) =
%							0 if n = 0
%							1 + nrOcc(l2, ..., ln) if l1 == E
%							nrOcc(l2, ..., ln) otherwise.
%

nrOcc([], _, 0).
nrOcc([H | T], E, R):-
    H =:= E,
    !,
    nrOcc(T, E, R1),
    R is R1 + 1.
nrOcc([_ | T], E, R):-
    nrOcc(T, E, R).

%set(l1, ..., ln) =
%					[] if n = 0;
%					l1 u set(l2, ..., ln) if n > 0 and nrOcc(R, l1) == 0
%					set(l2, ..., ln) otherwise
%
      
set([], C, C):-!.
set([H | T], C, R):-
    nrOcc(C, H, Ap),
    Ap == 0,
    !,
    C1 = [H  | C],
    set(T, C1, R).
set([_ | T], C, R):-
    set(T, C, R).


%Form a list that contains 2 lists
try(R, A, B):-
    R = [B | [A]].
    
    
%5.
%a. Write a predicate to compute the union of two sets.
%b. Write a predicate to determine the set of all the pairs of elements in a list. 
%Eg.: L = [a b c d] => [[a b] [a c] [a d] [b c] [b d] [c d]].
    
%union(l1, ..., ln, a1, ..., an) =
%									[] if n = 0;
%									l1 u union(l2, ..., ln, a1, ..., am) if l1 not in a1,..,an
%									union(l2, ..., ln, a1, ..., am)  otherwise.

union([], A, A):-!.
union([H | T], A, [H | R]):-
    nrOcc(A, H, Ap),
    Ap =:= 0,
    !,
    union(T, A, R).
union([_|T], A, R):-
    union(T, A, R).

mainUnion(A, B, R):-
    union(A, B, R).

%allPairs(l1, ..., ln, a1, ..., an) = 
%						pairs(l1, a1, ..., an) u allPairs(l2, ..., ln, a2, ..., an).

concatenate(R2, [], R2):-!.
concatenate(R2, [H | T], [H | R]):-
    !,
    concatenate(R2, T, R).

pairs([], _, []):-!.
pairs([H | T], E, [[E,H] | R]):-
    !,
    pairs(T, E, R).
    

allPairs([_], _, []):-!.
allPairs([H | T], [_ | T1],  R):-
    pairs(T1, H, R1),
    allPairs(T, T1, R2),
    concatenate(R2, R1, R).
        






