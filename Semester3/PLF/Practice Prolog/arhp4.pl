%Se da o lista L de numere si de atomi.
%a) Sa se stearga toti atomi si toate elementele de valoare impara din lista si sa se determine
%cmmdc al acestei liste.
%b) Sa se dubleze elementele ramase in lista.
%L = [ a, m, 10, 5, 6, 2, 3, 12, 2, n, z ]
%a) NL = [10, 6, 2, 12, 2]
%b) NL = [10, 10, 6, 6, 2, 2, 12, 12, 2, 2]

%elimIA(l1, ... , ln) ={
%						[] if n = 0
%						l1 u elimIA(l2, ... , ln) if l1 is even
%						elimIA(l2, ..., ln).
%
% elimIA(i, o).

elimIA([], []).
elimIA([H | T], [H | R]):-
    number(H),
    H mod 2 =:= 0,
    !,
    elimIA(T, R).
elimIA([_ | T], R):-
    elimIA(T, R).

gcd(A, 0, A).
gcd(A, B, R):-
    B > 0,
    C is A mod B,
    gcd(B, C, R).

%gcdList(l1, ..., ln) = 
%						R if n = 0,
%						gcdList(l2, ..., ln, gcd(l1, R). otherwise
%

gcdList([], 0).
gcdList([H | T], R):-
    gcdList(T, R1),
    !,
    gcd(H, R1, R).

dubList([], []).
dubList([H | T], [H | [H | R]]):-
    	!,
        dubList(T, R).

maingcdList(L, R, L2):-
    elimIA(L, L1),
    gcdList(L1, R),
    dubList(L1, L2).




