%Se dau doua liste A si B.
%a) Sa se determine valorile elementelor maxime din cele doua liste.
%b) Sa se creeze o lista noua N care va contine valorile maxime obtinute dublate
%A = [4, 7, 2, 6]
%B= [11, 10, 9]
%a) Max_a = 7
%Max_b = 11
%b) NL = [ 14, 22 ]

%findMax(l1, ... , ln, R) =
%							R if n = 0.
%							findMax(l2, ... , ln, l1) if l1 > R
%							findMax(l2, ... , ln, R) otherwise.

findMax([], C, C).
findMax([H | T], C, R):-
    H > C,
    C1 is H,
    !,
    findMax(T, C1, R).
findMax([_ | T], C, R):-
    findMax(T, C, R).


%flowmodel(i, i, o, o, o).
mainFindTwoMax(L1, L2, R1, R2, Dr):-
    findMax(L1, 0, R1),
    findMax(L2, 0, R2),
    X is R1 * 2,
    Y is R2 * 2,
    Dr1 = [Y | []],
    Dr = [X | Dr1].

%12.
%a. Define a predicate to add after every element from a list, the divisors of that number.
%b. For a heterogeneous list, formed from integer numbers and list of numbers, define a predicate to add in 
%every sublist the divisors of every element.
%Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] =>
%[1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2]

%	divizor(N, D) = {
%						[] if D >= N
%						D u divizor(N, D + 1) if N % D == 0
%						divizor(N, D + 1) otherwise.
%

divizor(N, D, []):-
    D >= N,
    !.
divizor(N, D, [D | R]) :-
    N mod D =:= 0,
    D1 is D + 1,
    !,
    divizor(N, D1, R).
divizor(N, D, R):-
    D1 is D + 1,
    !,
    divizor(N, D1, R).

mainDivizor(N, R):-
    divizor(N, 2, R).


%IMPORTANT%
concatenate([], L, L).
concatenate([H | T], L, [H | R]):-
	concatenate(T, L, R).


addDivs([], []).
addDivs([H | T], [H | R] ):-
    mainDivizor(H, Divs),
    concatenate(Divs, TempRes, R),
    addDivs(T, TempRes).

addEveryList([], []).
addEveryList([H | T], [R1 | R]):-
    is_list(H),
    !,
    addDivs(H, R1),
    addEveryList(T, R).
addEveryList([H | T], [H | R]):-
    addEveryList(T, R).










