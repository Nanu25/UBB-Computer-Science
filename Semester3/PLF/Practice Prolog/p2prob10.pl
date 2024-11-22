%10. 
%a. For a list of integer numbers, define a predicate to write twice in list every prime number.
%b. For a heterogeneous list, formed from integer numbers and list of numbers, define a predicate to write in 
%every sublist twice every prime number.
%Eg.: [1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5] =>
%[1, [2, 2, 3, 3], 4, 5, [1, 4, 6], 3, [1, 3, 3, 7, 7, 9, 10], 5]

%is_prime(n, d) = {
%					false if n < 2.
%  					true if d * d > n
%					false if n % d == 0
%					is_prime(n, d + 1) otherwise.

is_prime(0, _, 0):-!.
is_prime(1, _, 0):-!.
is_prime(N, D, 1):-
    D * D > N,
    !.
is_prime(N, D, 0):-
    N mod D =:= 0,
    !.
is_prime(N, D, R):-
    D1 is D + 1,
    is_prime(N, D1, R).

mainPrime(N, R):-
    is_prime(N,2,R).

% dupPrime(l1, ... ln) = {
%				[] if n = 0 
%				l1 u l1 u dupPrime(l2, ... , ln) if mainPrime(l1).
%				l1 u dupPrime(l2 , ... , ln) otherwise.


dupPrime([], []).
dupPrime([H | T], R):-
    mainPrime(H, Ok),
    Ok == 1,
    !,
    dupPrime(T, R1),
    R2 = [H | R1],
    R = [H | R2].
dupPrime([H | T], [H | R]):-
    dupPrime(T, R).


changeList([], []).
changeList([H | T], R):-
    is_list(H),
    dupPrime(H, Nl),
    !,
    changeList(T, R1),
    R = [Nl | R1].
changeList([H | T], [H | R]):-
    changeList(T, R).




