%subset(l1, ..., ln) = 
%						[] if n = 0
%						l1 u subset(l2, ... , ln), n > 0
%						subset(l2, ..., ln), n > 0.
%

%findall(R ,subset([1,2,3],R), All)
%flowmodel(i, o).
subset([], []).
subset([H | T], [H|R]):-
    subset(T, R).
subset([_|T], R):-
    subset(T, R).
    

%comb(l1, ..., ln) =
%					 l1, if k = 1
%					comb(l2, ..., ln, k) if  k>= 1, n > 0
%					l1 u comb(l2, ... ,ln, k - 1) k > 1;	daca punem elementul scadem k.
%

%comb(i, i, o).
comb([H | _], 1, [H]).
comb([_ | T], K, R):-
    K >= 1, 
    comb(T, K, R).
comb([H | T], K, [H | R]):-
	K > 1,
	K1 is K - 1,
	comb(T, K1, R).

%insertEl(e, l1, ..., ln) = e U l1, ..., ln n >= 0,
%							l1 u insertEl(e, l2, ..., ln) n > 0
%
insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).


%permutation = {
%				[] if n = 0
%				insertEL(l1, perm(l2, ..., ln)), n > 0.
%

perm([], []).
perm([H | T], R):-
    perm(T, P),
    insertEl(H, P, R).

%arr(l1, ..., ln, k) = 
%						l1 if k == 1
%						arr(l2,...,ln, k) if k >= 1, n > 0
%						insertEl(l1, arr(l2, ..., ln, k - 1)) k > 1, n > 0.
%

arr([H | _], 1, [H]).
arr([_ | T], K, R):-
    K >= 1,
    arr(T, K, R).
arr([H | T], K, R):-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).


%Given a list. Generate all list of arrangements of K elements from the list that has the product P
%and the sum S. eg: L[1,2,3,10], K = 2, P = 30, S = 13, we have R=[[3, 10], [10,3]].

suma([], 0).
suma([H | T], S):-
    suma(T, S1),
    S is S1 + H.

prod([], 1).
prod([H | T], P):-
    prod(T, P1),
    P is P1 * H.


%onesol(L, K, S, P) = a1a2..ak if a1a2...ak=(arr(L, K), sum(a1a2...ak) == S, prod(a1a2,...,ak) = P
%					

%mainOneSol(L, K, S, P) = findall(onesol(L, K, S, P)).

%onesol(L - list, K - number, S - number, P - number, A - list) (i,i,i,i,o).

oneSol(L, K, S, P, A):-
    arr(L, K, A),
    suma(A, S),
    prod(A, P).

mainAllSol(L, K, S, P, R):-
    findall(A, oneSol(L, K, S, P, A), R).

%Given a sequence a1a2...an composed of distinct integers, display all subsequences with a valley aspect
% [5,3,4,2,7,11,1,8,6] => some sols [5,4,3,11], [11,6, 1, 3, 4, 5].


% 0 dec, 1 inc
%valley(L1 - list, F - Numeric).
%valley(l1, ..., ln, F)=
%						True, n = 1, F = 1
%						valley(l2, ..., ln, 0) l1  > l2, F = 0
%						valley(l2, .., ln, 1) if l1 < l2 and F = 0 or 1.
%						False 

valley([_], 1):-!.
valley([H1, H2 | T], 0):-
    H1 > H2,
    !,
    valley([H2 | T], 0).
valley([H1, H2 | T], _):-
    H1 < H2,
    !,
    valley([H2 | T], 1).


main_Valley([H1, H2 | T]):-
    H1 > H2,
    valley([H2 | T], 0).

%oneSol(l1, ..., ln) =
%						p1, ..., pk if p = perm(subset(l1, ..., ln)) and valley(p1, ..., pk).
%allSol(l1, ..., ln) = {
%							U oneSol(l1, ..., ln).
%

oneSol(L, R):-
    subset(L, Sub),
    perm(Sub, R),
    main_Valley(R).


allSol(L, S):-
    findall(R, oneSol(L, R), S).







