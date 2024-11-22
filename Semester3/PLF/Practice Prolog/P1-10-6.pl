%10.
%a. Define a predicate to test if a list of an integer elements has a "valley" aspect (a set has a "valley" aspect if 
%elements decreases up to a certain point, and then increases. 
%eg: 10 8 6 9 11 13 – has a “valley” aspect
%remove from a list of lists, from all sublist, the even elements from valley aspect lists:
% [1, 7, [10 8 6 9 11 13], 4, 0, [6,4,5], 42, [11,5,10,4]] => [1,7,[9, 11, 13], 4, 0, [5], 42, [11,5,10,4]]

%valley(l1, ..., ln, F) =
%						true if n = 1 and F = 1
%						valley(l2, ..., ln, 0) if l1 > l2 and F = 0
%						valley(l2, ..., ln, 1) if l2 > l1.
%						false otherwise.

valley([_], 1):-!.
valley([H1, H2 | T], F):-
    F == 0,
    H1 > H2,
    !,
    valley([H2 | T], F).
valley([H1, H2 | T], _):-
    H1 < H2,
    !,
    valley([H2 | T], 1).

mainValley([H1, H2 | L]):-
    H1 > H2,
    valley([H2 | L], 0). 
    

%remEven(l1, ..., ln) = [] if n = 0
%						l1 u remEven(l2, ..., ln) if l1 is odd
%						remEven(l2, ..., ln) otherwise
%

remEven([], []).
remEven([H | T], [H | R]):-
    H mod 2 =\= 0,
    !,
    remEven(T, R).
remEven([_ | T], R):-
    remEven(T, R).


%modifyList(l1, ..., ln) = [] if n = 0
%							remEven(l1) u modifyList(l2, ..., ln) if l1 is list and valley
%							modifyList(l2, ..., ln) othwerwise
%							
%
modifyList([], []).
modifyList([H | T], [R1 | R]):-
    is_list(H),
    mainValley(H),
    remEven(H, R1),
    !,
    modifyList(T, R).
modifyList([H | T], [H | R]):-
    modifyList(T, R).


%6
%Determine the product of a number represented as digits in a list to a given digit. 
%Eg.: [1 9 3 5 9 9] * 2 => [3 8 7 1 9 8]

%prod(l1, ..., ln, Carry) = 
%								[] if n = 0 and Carry = 0
%								Carry u prod(l2, ..., ln, 0) if Carry > 0 and n = 0.
%								(l1 * D + Carry) % 10 u prod(l2, ..., ln, (l1 * D + Carry)//10) otherwise.
%

prod([], 0, _, []):-!.
prod([], Carry, _, [Carry | R]):-
    !,
    prod([], 0, _, R).
prod([H | T], Carry, D, [D1 | R]):-
    X is H * D + Carry,
    D1 is X mod 10,
	Carry1 is X // 10,
    prod(T, Carry1, D, R).

reverse([], C, C).
reverse([H | T], C,  R):-
    C1 = [H | C],
	reverse(T, C1, R).

mainProd(L, X, R):-
    reverse(L, [], L1),
    prod(L1, 0, X, R1),
    reverse(R1, [], R).

%subtitute each list with the prod between minim digit of the sublist and the number for each sublist
%[3, 2, [1, 9, 3, 5, 9, 9], 4, 3, [9, 9, 5], [7, 2, 3]] => [3, 2, [1, 9, 3, 5, 9, 9], 4, 3, [4,9,7,5], [1,4,4,6]]

findMin([], C, C):-!.
findMin([H | T], C, R):-
    H < C,
    C1 is H,
    !,
    findMin(T, C1, R).
findMin([_|T], C, R):-
    findMin(T, C, R).

mainMin(L, R):-
    findMin(L, 10, R).

%mainProdList(l1, ..., ln) = [] if n = 0
%							mainProd(l1, mainMin(l1)) u mainProdList(l2, ..., ln) if l1 is list
%							l1 u mainProdList(l2, ..., ln).
%

mainProdList([], []).
mainProdList([H | T], [R1 | R]):-
    is_list(H),
    mainMin(H, Min),
    mainProd(H, Min, R1),
    !,
    mainProdList(T, R).
mainProdList([H | T], [H | R]):-
    mainProdList(T, R).

%Write a predicate to substitute in a list a value with all the elements of another list.
%[1,2,3,1], [4, 5, 6] => [4,5,6,2,3,4,5,6].

%concatenate(l1, ..., ln, a1, ..., am) = {
%											a1,...am if n = 0
%											l1 u concatenate(l2, ..., ln, a1, ... , am) otherwise
%

concat([], A, A):-!.
concat([H | T], A, [H | R]):-
    concat(T, A, R).

%sub(l1, ..., ln)= [] if n = 0
%					a1a2,...,an u sub(l2, ..., ln) if l1 == E,
%					l1 u sub(l2, ..., ln) otherwise.
%

sub([], _, _, []).
sub([H | T], E, L, R):-
    H == E,
    !,
    sub(T, E, L, R1),
    concat(L, R1, R).
sub([H | T], E, L, [H | R]):-
    sub(T, E, L, R).







