%3
%a. Merge two sorted lists with removing the double values.
%b. For a heterogeneous list, formed from integer numbers and list of numbers, merge all sublists with removing 
%the double values.
%[1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5, [1, 1, 11], 8] =>
%[1, 2, 3, 4, 6, 7, 9, 10, 11].


%mergeList(a1, ... , an, b1, ... ,bm) ={
%					[] if n = 0 and m = 0
%					a if m = 0 and n != 0
%					b if m != 0 and n = 0.
%					a1 u mergeList(a2, ... , an, b1, ... , bn) if a1 < b1.
%					b1 u mergeList(a1, ... , an, b2, ..., bn) otherwise.

mergeList([], [], []).
mergeList([], B, B).
mergeList(A, [], A).
mergeList([HA | TA], [HB | TB], [HA | R]):-
    HA < HB,
    !,
    mergeList(TA, [HB | TB], R).
mergeList([HA | TA], [HB | TB], [HB | R]):-
    mergeList([HA | TA], TB, R).
    
removeDup([], _, []).
removeDup([H | T], L, [H | R]):-
    nrOcc(L, H, Ap),
    Ap == 0,
    !,
    L1 = [H | L],
    removeDup(T, L1, R).
removeDup([_ | T], L, R):-
    removeDup(T, L, R).


nrOcc([], _, 0).
nrOcc([H | T], E, R):-
    H == E,
	!,
    nrOcc(T, E, R1),
    R is R1 + 1.
nrOcc([_ | T], E, R):-
    nrOcc(T, E, R).

mainMergeList(L1, L2, R):-
    mergeList(L1, L2, Aux),
    removeDup(Aux, [], R).


mergeAll([], []).
mergeAll([H | T], R):-
    is_list(H),
    !,
    mergeAll(T, R1),
    mainMergeList(H, R1, R).
mergeAll([_|T], R):-
    mergeAll(T, R).



%7
%a. Determine the position of the maximal element of a linear list. 
%Eg.: maxpos([10,14,12,13,14], L) produces L = [2,5].
%b. For a heterogeneous list, formed from integer numbers and list of numbers, replace every sublist with the 
%position of the maximum element from that sublist.
%[1, [2, 3], [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
%[1, [2], [1, 3], 3, 6, [2], 5, [1, 2, 3], 7]

%findMax(l1, ... ln, R) = {
%							R if n = 0;
%							findMax(l2, ..., ln, l1) if l1 > R;
%							findMax(l2, ..., ln, R) if l1 <= R.
findMax([], C, C).
findMax([H | T], C, R):-
    H > C,
	!,
    findMax(T, H, R).
findMax([_ | T], C, R):-
    findMax(T, C, R).

mainfindMax(L, R):-
    findMax(L, 0, R).

%maxPos(l1, ... , ln, index) =
%						[] if n = 0;
%						index u maxPos(l2, ... , ln, index + 1) if l1 == Maxim;
%						maxPos(l2, ... , ln, index + 1) otherwise.

maxPos([], _, [], _).
maxPos([H | T], M, [Index | R], Index):-
    H =:= M,
    !,
    Index1 is Index + 1,
    maxPos(T, M, R, Index1).
maxPos([_ | T], M, R, Index):-
    Index1 is Index + 1,
    maxPos(T, M, R, Index1).

mainMaxPos(L, R):-
    mainfindMax(L, M),
    maxPos(L, M, R, 1).


%subMax(l1, ... , ln) = {
%						[] if n = 0
%						mainMaxPos(H) u subMax(l2, ... , ln) if l1 is list
%						subMax(l2, ... , ln) if l1 not a list.
subMax([], []).
subMax([H | T], [R1 | R]):-
       is_list(H),
       !,
       mainMaxPos(H, R1),
       subMax(T, R).
subMax([H | T], [H | R]):-
       subMax(T, R).



%8. 
%a. Determine the successor of a number represented as digits in a list. 
%Eg.: [1 9 3 5 9 9] --> [1 9 3 6 0 0]
%b. For a heterogeneous list, formed from integer numbers and list of numbers, determine the successor of a 
%sublist considered as a number.
%[1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => 
%[1, [2, 4], 4, 5, [6, 8, 0], 10, 11, [1, 2, 1], 6]

% addOne(l1, ..., ln, Carry) = {
%									addOne([], 0) if n = 0 and Carry = 0
%									1 u addOne([], 0) if n = 0 and Carry = 1.
%									(l1 + Carry) u addOne(l2, ... ln, Carry) if n > 0.

%flow model addOne(i,i,o).
addOne([], 0, []).
addOne([], 1, R):-
  	addOne([], 0, R1),
    R = [1 | R1].
   
addOne([H | T], Carry, R):-
    H1 is H + Carry,
    Carry1 is H1 // 10,
    H2 is H1 mod 10,
    !,
    addOne(T, Carry1, R1),
    R = [H2 | R1].
    

%reverse(l1, ..., ln) = {
%							[] if n = 0
%							reverse(l2,...,ln) u l1 if n > 0
% flow model reverse(i,i, o).

reverse([], C, C).
reverse([H|T], C, R):-
    C1 = [H | C],
    reverse(T, C1, R).

mainaddOne(L, R2):-
    reverse(L, [], R),
    addOne(R, 1, R1),
    reverse(R1, [], R2).
   

%findSucc(l1, ... ,ln) {
%						[] if n = 0;
%						findSucc(mainaddOne(l1), l2, ... , ln) if n > 0 and l1 is list
% 						findSucc(l2, ... , ln) if n > 0 and l1 is not a list.

findSucc([], []).
findSucc([H | T], R):-
    is_list(H),
    !,
    mainaddOne(H, H1),
    findSucc(T, R1),
    R = [H1 | R1].
findSucc([H | T], R):-
    findSucc(T, R1),
    R = [H | R1].
    

%P2 - p4.

%transform a heter list to a normal list.
try([], []).
try([H|T], R) :-
    is_list(H),           % Check if H is a sublist
    try(H, RH),           % Recursively flatten the sublist H
    try(T, RT),           % Recursively flatten the tail of the list
    append(RH, RT, R).    % Append the flattened head and tail
try([H|T], [H|R]) :-
    \+ is_list(H),        % If H is not a sublist, just add it to the result
    try(T, R).














    