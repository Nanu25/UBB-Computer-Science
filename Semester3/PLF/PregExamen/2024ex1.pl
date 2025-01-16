f(0, 0):-!.
f(I, Y):-
    J is I - 1,
    f(J, V),
    V =< 1,
    !,
    Y is V + 1.
f(I,Y):-
    Y is I - 2.


p(100).
p(N):-
    write(N),
    N1 is N - 1,
    p(N1).

chairs(0, []):-!.
chairs(N, ['R' | Rl]):-
	N1 is N - 1,
    chairs(N1, Rl).
chairs(N, ['Y' | Rl]):-
	N1 is N - 1,
    chairs(N1, Rl).

check([], 0).
check([H | T], Nr):-
    H == 'Y',
    !,
    check(T, Nr1),
    Nr is Nr1 + 1.
check([_ | T], Nr):-
    check(T, Nr).


onesol(R):-
    chairs(5, R),
    check(R, Nr),
    Nr =< 3.

allsol(Res):-
    findall(R, chairs1(5, 0, R), Res).


chairs1(0,_,[]):-!.
chairs1(N, Nry, ['R' | Rl]):-
    N1 is N - 1,
    chairs1(N1, Nry, Rl).
chairs1(N, Nry, Rl):-
	Nry < 3,
    N1 is N - 1,
    Nry1 is Nry + 1,
    chairs1(N1, Nry1, Rl1),
    Rl = ['Y' | Rl1].





