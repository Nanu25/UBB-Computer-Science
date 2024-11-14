%Seminar 1
% Multiply the elements  of a list wit a constant value.
% [1,2,3], k = 10 => [10, 20, 30]
% mulk(L - list, k - number, R - result list) = { 0 if n = 0, {l1 * k) u mulk(l2, ... ln, k),  n >= 1)
% flow model (i, i, o) -> info info output
mulk([], _, []).

mulk([H|T], K, R):-
    H1 is H*K,
    mulk(T, K, TR),
    R = [H1 | TR].


%Append an element at the end of a list.
% [1, 2, 3], e = 11 => [1, 2, 3, 11]
% app1(l1, l2, ... ,ln - list, k - element) = {{k} if n = 0, {l1}  u app1(l2, l3 ... ln, k), n >= 1);

app1([], K, [K]).
app1([H|T], K, [H|TR]):-
    app1(T, K, TR).
% R = [H | TR].


%Compute the sum of elements of a numerical list.
% sumlist(L1,L2, ..., Ln) = {0 if n = 0, l1 + sumlist(l2, ... , ln), if n > 0}
%sumlist(L - list, S - number)
%flow model (i, o), (i, i)

sumlist([], 0).
sumlist([H|T], S):-
    sumlist(T, TS),
    S is H + TS.

%compute the product of even elements in a numerical list.
%productlist(l1, l2, ... ln - list, P - product) = {1, if n = 0, prodlist(l2, ... ln) if l1 is odd, l1 * prodlist(l2, ... , ln) if l1 is even}
prodlist([], 1).
prodlist([H|T], P):-
    H mod 2 =\= 0,
    prodlist(T, P).
prodlist([H|T], P):-
    H mod 2 =:= 0,
    prodlist(T, TP),
    P is H * TP.


% Given a list of numbers, remove all increasing sequences.
% [1, 2, 4, 6, 5, 7, 8, 2, 1] => [2, 1].
%remIncr = { remincr(l3, l4, ... , ln) if l1 < l2 >= l3 and n >= 3, remincr(l2, l3, ... ln) if l1 < l2 < l3 and n >= 3, l1 u remincr(l2, l3, ... ln) if l1 > l2, [] if l1 < l2, l1 if n = 1.

increase([], _, _, []).
increase([H|T], K, I, R) :-
    I1 is I + 1,  
    I1 mod 2 =\= 0, 
    increase(T, K, I1, R).  
increase([H|T], K, I, R) :-
    I1 is I + 1,  
    I1 mod 2 =:= 0,  
    H1 is H + K,  
    increase(T, K, I1, TR),
	R = [ H1 | TR ].

    




