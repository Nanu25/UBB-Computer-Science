%. Define a predicate to remove from a list all repetitive elements. 
%Eg.: l=[1,2,1,4,1,3,4] => l=[2,3])
%b. Remove all occurrence of a maximum value from a list on integer numbers.

%nrOcc(l1, ... , ln, E) = {
%							0 if n = 0.
%							1 + nrOcc(l2, ... , ln, E) if l1 == E.
%							nrOcc(l2, ... , ln, E) if l1 != E.

nrOcc([], _, 0).
nrOcc([H1 | T], E, R):-
    H1 == E, 
    !,
    nrOcc(T, E, R1),
	R is R1 + 1.
nrOcc([_ | T], E, R):-
    nrOcc(T, E, R).

%remEl(l1, ... , ln) = {
%							[] if n = 0
%							l1 u remEl(l2, ... , ln) if nrOcc(l1) == 1
%							remEl(l2, ... , ln) if nrOcc(l1) > 1.

remEl([], _, []).
remEl([H | T], List, [H | R]):-
    nrOcc(List, H, Ap),
    Ap == 1,
    !,
    remEl(T, List, R).
remEl([_|T], List, R):-
    remEl(T, List, R).


mainRemEl(L, R):-
    remEl(L, L, R).
    
findMax([], C, C).
findMax([H | T], C, M):-
    H > C,
    !,
    findMax(T, H, M).
findMax([_|T], C, M):-
    findMax(T, C, M).

mainMax(L, R):-
	findMax(L, 0, R).

remMax([], _, []).
remMax([H | T], M, [H | R]):-
    H =\= M,
    !,
    remMax(T, M, R).
remMax([_ | T], M, R):-
    remMax(T, M, R).

mainRemMax(L, R):-
    mainMax(L, Max),
    remMax(L, Max, R).


%b. Calculate the alternate sum of list’s elements (l1 - l2 + l3 ...)

% altSum(l1, ..., ln, poz) = {
%								0 if n = 0
%								l1 + altSum(l2, ..., ln, poz + 1) if poz is odd.
%								l1 - altSum(l2, ..., ln, poz + 1) if poz is even
%flowmodel(i, i, o).

altSum([], _, 0).
altSum([H | T], Poz, S):-
    Poz mod 2 =:= 0,
    Poz1 is Poz + 1,
    !,
    altSum(T, Poz1, S1),
    S is S1 - H.
altSum([H | T], Poz, S):-
    Poz1 is Poz + 1,
    !,
    altSum(T, Poz1, S1),
    S is S1 + H.

mainAltSum(L, R):-
    altSum(L, 1, R).
       


% Define a predicate to produce a list of pairs (atom n) from an initial list of atoms. In this initial list atom has 
% n occurrences.
% Eg.: numberatom([1, 2, 1, 2, 1, 3, 1], X) => X = [[1, 4], [2, 2], [3, 1]].

countAp([], _, [], 0).
countAp([H|T], A, NewList, R):-
    H =:= A, 
    countAp(T, A, NewList, R1),
  	R is R1 + 1.
countAp([H|T], A, NewList, R):-
    H =\= A,
    countAp(T, A, TNewList, R),
	NewList = [H | TNewList].

numberatom([], []).
numberatom([H|T], R):-
   	countAp([H|T], H, NewList, Cnt),
    numberatom(NewList, TR),
    R = [ [H, Cnt] | TR ].
    



%Write a predicate to delete first occurrence of the minimum number from a list

% findmin(l1, ... , ln) = { 
%							l1 if n = 1
%							findmin(l1, min(l2, ... ,ln)) if n > 1
%findmin(i, 0)


findmin([], X, X).
findmin([H|T], C, R):-
    H < C,
    !,
    C1 is H,
    findmin(T, C1, R).
findmin([_|T], C, R):-
    findmin(T, C, R).

% deletFmin(l1, ... ,ln) = [] if n = 0
% 						l1 u deleteFmin(l2, ... , ln) if l1 != Min
% 						deleteFmin(l2, ... , ln) if l1 = min and l1 is the first occurance of min

deleteFmin([], _, _, []).
deleteFmin([H|T], Ok, Min, R):-
    H =:= Min,
    Ok =:= 0,
    Ok1 is Ok + 1,
    !,
    deleteFmin(T, Ok1, Min, R).
deleteFmin([H|T], Ok, Min, R):-
    deleteFmin(T, Ok, Min, R1),
	R = [H | R1].

mainDelete(L, R):- 
    findmin(L, 100, Min),
    deleteFmin(L, 0, Min, R).








    
    
    
    
    