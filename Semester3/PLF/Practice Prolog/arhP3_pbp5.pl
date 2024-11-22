%Se da o lista L de numere intregi, pozitive si negative.
%a) Sa se creeze 2 liste N si P astfel: P va contine doar numerele pozitive, iar N va contine
%numerele negative.
%b) Determinati elementele minime din cele doua liste create.

%buildList(l1, ... , ln, poz, neg) =
%									[] if n = 0
%									buildList(l2, ... , ln, l1 u poz, neg) if l1 > 0
%									buildList(l2, ..., ln, poz, l1 u neg) if l1 < 0
%									buildList(l2, ..., ln,pos, neg) if l = 0 
%

buildList([], [], []).
buildList([H | T], [H | P], N):-
    H > 0,
    !,
    buildList(T, P, N).
buildList([H | T], P, [H | N]):-
    H < 0,
    !,
    buildList(T, P, N).
buildList([_|T], P, N):-
    buildList(T, P, N).

findMin([], C, C).
findMin([H | T], C, R):-
    H < C,
    C1 is H,
    !,
    findMin(T, C1, R).
findMin([ _ | T], C, R):-
    findMin(T, C, R).

mainProb(L, P, N, M1, M2):-
    buildList(L, P, N),
    findMin(P, 100000, M1),
    findMin(N, 100000, M2).
        

%5. 
%a. Substitute all occurrences of an element of a list with all the elements of another list. 
%Eg. subst([1,2,1,3,1,4],1,[10,11],X) produces X=[10,11,2,10,11,3,10,11,4].
%b. For a heterogeneous list, formed from integer numbers and list of numbers, replace in every sublist all 
%occurrences of the first element from sublist it a new given list.
%Eg.: [1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] =>
%[1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]
%

%subst(l1, ..., ln) = {
%			[] if n = 0
%			l1 u subst(l2, ... ln) if l1 != E
%			L u subst(l2, ..., ln) if l1 == E.
%			
%

subst([], _, _, []).
subst([H | T], E, L, [H | R]):-
    H =\= E,
    !,
    subst(T, E, L, R).
subst([_ | T], E, L, R):-
    subst(T, E, L, R1),
    concat(L, R1, R).

concat([], L, L).
concat([H | T], L, [H | R]):-
        concat(T, L, R).


firstElem([], _).
firstElem([H | T],  R):-
    firstElem(T, _),
    R is H.

substAll([], _, []).
substAll([H | T], L, R):-
    is_list(H),
    !,
    substAll(T, L, R1),
    firstElem(H, Fd),
    subst(H, Fd, L, R2),
    R = [R2 | R1].
substAll([H|T], L, [H | R]):-
    substAll(T, L, R). 
    

        
