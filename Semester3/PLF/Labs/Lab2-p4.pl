%a. Write a predicate to determine the sum of two numbers written in list representation
% [1, 9, 5] [8, 7, 4] => [1, 0, 6, 9]

% sumtwolists(a1, ... , an, b1, b2, ..., bm, Carry) = {
%														0 if n = 0 and m = 0 and Carry = 0
%														1 u sumtwollists( , , 0) if Carry = 1 and n = 0 and m = 0
%														(a1 + Carry) u sumtwolists(a2, ... an , ,Carry) if n > 0 and m = 0.
%														(b1 + Carry) u sumtwolists( , b2 ... bn, Carry) if n = 0 and m > 0.
%														(a1 + b1 + Carry) u sumtwolists(a2, ... an, b2 ... bn, Carry) if n > 0 and m > 0
% sumtwolists(L1, L2, Carry, R) : L1, L2,, R - lists, Carry - int
% sumtwolists(L1, L2, Carry, R) - (i, i, i, o).

sumtwolists([], [], 0, []).
sumtwolists([], [], 1, R):-
    sumtwolists([], [], 0, R1),
    R = [1 | R1].
sumtwolists([H1 | T], [], Carry, R):-
    D is H1 + Carry,
    Carry1 is D // 10,
    D1 is D mod 10,
    sumtwolists(T, [], Carry1, R1),
    R = [D1 | R1].
sumtwolists([], [H1 | T], Carry, R):-
    D is H1 + Carry,
    Carry1 is D // 10,
    D1 is D mod 10,
    sumtwolists(T, [], Carry1, R1),
    R = [D1 | R1].
sumtwolists([H1|T1], [H2|T2], Carry, R):-
    D is H1 + H2 + Carry,
    Carry1 is D // 10,
    D1 is D mod 10,
    sumtwolists(T1, T2, Carry1, R1),
    R = [D1 | R1].

%reverse(l1, ... ln) = [] if n = 0
%					reverse(l2, ... ln) u l1 if n > 0
%reverse(L1, C, R) L1, R, c lists
%reverse(i, i, o).

reverse([], C, C).
reverse([H | T], C, R):-
    C1 = [H | C],
    reverse(T, C1, R).

mainsumtwolists(L1, L2, R):-
    reverse(L1, [], R1),
    reverse(L2, [], R2),
    sumtwolists(R1, R2, 0, Rrev),
	reverse(Rrev, [], R).


%For a heterogeneous list, formed from integer numbers and list of digits, write a predicate to compute the 
%sum of all numbers represented as sublists.
%Eg.: [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => [8, 2, 2].


%sum_of_all_lists(l1, ... ,ln) = { 0 if n = 0,
%									mainsumtwolists(l1, sum_of_all_lists(l2, ... ,ln)) if l1 is a list.
%									sum_of_all_lists(l2, ... ,ln) if l1 si not a list.
%flow model: sum_of_all_lists(i, o).

sum_of_all_lists([], [0]).
sum_of_all_lists([H|T], R):-
    is_list(H),
    !,
	sum_of_all_lists(T, R1),
    mainsumtwolists(H, R1, R).
sum_of_all_lists([_|T], R):-
    !,
    sum_of_all_lists(T, R).

 






















