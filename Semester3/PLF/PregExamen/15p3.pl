%15l3.

%insertEl(E, l1, ..., ln) = E u l1, ..., ln , n >= 0
%							= l1 u insertEl(E, l2, ..., ln) n > 0

insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
	insertEl(E, T, R).
 
%perm(l1, ..., ln) = [] if n = 0
%				=	insertEl(l1, perm(l2, ..., ln)).
         
perm([], []).
perm([H | T], R):-
    perm(T, P),
    insertEl(H, P, R).

%subset(l1, ... ,ln) = [] if n = 0
%						l1 u subset(l2, ..., ln), n > 0
%						subset(l2, ..., ln) n > 0.

subset([], []).
subset([_ | T], R):-
	subset(T, R).
subset([H | T], [H | R]):-
    subset(T, R).


%makelist(Index, N) = [N] if index = N,
%					=	index u makeList(index + 1, N), index < N.
makeList(N, N, [N]).
makeList(Index, N, [Index | R]):-
  	Index < N,
    !,
    Index1 is Index + 1,
    makeList(Index1, N, R).

%check(l1, ..., ln) = 1 if n = 0;
%					= 0 if l1 >= l2
%					= check(l2, ..., ln).

check([], 1).
check([_], 1).
check([H1, H2 | T], Ok):-
    H1 - H2 =:= -1,
    !,
    check([H2 | T], Ok).
check(_, 0).

checkSum([], 0).
checkSum([H | T], S):-
    checkSum(T, S1),
    S is S1 + H.


onesol(L, N, Res):-
    subset(L, S),
    perm(S, Res),
    check(Res, Ok),
	Ok =:= 1,
    checkSum(Res, S1),
	S1 == N.

allSol(N, Res):-
	makeList(1, N, L),
    findall(R, onesol(L, N, R), Res).





