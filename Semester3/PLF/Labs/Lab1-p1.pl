%Lab1
% check2(x, R) = { 
% true is x is 1
% false if x mod 2 != 0
% check2(x / 2, R) if x mod 2 == 0
% check2(x, R), X - number, R - restul
% check2(i, o)

check2(1, 1).	

check2(X, 1):-
    X > 1,
    X mod 2 =:= 0,        
    X1 is X // 2,          
    check2(X1, 1).         

check2(X, 0):-
    X > 1,
    X mod 2 =\= 0.         


%insert_at_powers_of_2(l1, l2, ... , ln, V, P, R). = { 
% [] is n = 0
% l1 u V u insert_at_powers_of_2(T, V, P + 1, R) if P is power of two
% l1 u insert_at_powers_of_2(T, V, P + 1, R) if P is not a power of 2.
% insert_at_powers_of_2(L, V, P, R) L - list, V - value, P - position, R - result list.
% insert_at_powers_of_2(i, i, i, o) - flowmodel

insert_at_powers_of_2([], _, _, []).

insert_at_powers_of_2([H|T], V, P, R):-
    check2(P, 1),
    P1 is P + 1,
    !,
    insert_at_powers_of_2(T, V, P1, TR),
	R1 = [V | TR],		% nu pot folosi aceeasi variabila de mai multe ori!
    R = [H | R1].
insert_at_powers_of_2([H|T], V, P, R):-
    check2(P, 0),
    P1 is P + 1,
    insert_at_powers_of_2(T, V, P1, TR),
    R = [ H | TR].



% gcd(a, b) = {
% a if b = 0
% gcd(b, a % b) if b != 0.
% }
% gcd(a, b) : 1 - first number, b = first number
% gcd(i, i, o).

gcd(A, 0, A).

gcd(A, B, R):-
    B > 0,
    B1 is A mod B,
    gcd(B, B1, R).

% lcmList(l1,l2,...,ln, R) = {
% l1 if n = 1.
% lcmList(l2,...,ln), l1 * R /  gcd(l1, R)) n > 1. 
% }
% lcmList(L, R) = L - list, R - result
% lcmList(i, o).

lcmList([X], X).
lcmList([H|T], R):-
    lcmList(T, R1),
    gcd(H, R1, Gcdnew),
    R is R1 * H // Gcdnew.

%Extra lab.
% insert2(l1, l2, ... ,ln, Index, Actual_power, V) 
% [] if n = 0;
% l1 u insert2(l2, ... ,ln, Index + 1, Actual_power, V) if index != actual_power
% l1 u V u insert2(l2, ..., ln, Index + 1, Actual_power*2, V) if index == actual_power.






