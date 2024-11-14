%Seminar 2

%suma(l1, ... ,ln) = 0 if n = 0
%					l1 + suma(l2, ... ln), n> 0

% suma(L - list, R - number) (i, o), (i, i)

suma([], 0).
suma([H|T], R):-
    suma(T, TR),
    R is H + TR.

%sumc(l1, ..., ln, C) =  C, if n = 0
%						sumc(l2, ... ln, C + l1) n > 0


% sumc(L-list, C-number, R-number)
% flow model (i, i, o)
sumc([], C, C).
sumc([H|T], C, S):-
    NewC is C + H,
    sumc(T, NewC, S).

mainSumC(L, S):-sumc(L, 0, S).

% Compute the no of ocurences of an element in a list.

% nOc(l1, ... , ln, E) =  0 if n = 0
% 							1 + nOc(l2, ... , ln) if l1 = E
% 							nOc(l2, ... , ln) if l1 != E.
%					


% nOc(L - list, E - element, R - result).
% flow model nOc(i, i, o)

nOc([], _, 0).
nOc([H|T], E, R):-
    H=:=E,
    !,
    nOc(T, E, R1),
    R is R1 + 1.
nOc([H|T], E, R):-
    E =\= H,
    nOc(T, E, R).

%with C

%nOcc(l1, ... ,ln, E, C) =  C is n = 0
%							nOcc(L2, ... , ln, E, C + 1) if l1 = E
%							nOcc(l2, ..., ln, E, C) if l1 != E.

nOcc([], _, C, C).
nOcc([E|T], E, C, R):- !,		%[E|T] il compara direct pe H si T.
    C1 is C + 1,
    nOcc(T, E, C1, R).
nOcc([_|T], E, C, R):-
    nOcc(T, E, C, R).

mainOcc(L, E, R):- nOcc(L, E, 0, R).


% remove from a list the elements appear only once.
% [1, 2, 1, 4, 3, 1, 4] => [1, 1, 1, 4, 1]
% remE(l1, l2, ... ln, c1, ... , cm) = [], n = 0;
%									   l1 u remE(l2, ... , ln, c1, ... , cm) if nrOcc(c1, c2... cm, l1) > 1
%										remE(l2, ..., ln, c1 ... cm) if nrOcc(c1, c2... cm, l1) = 1.

%remE(L list, C copy list, R result list)
%flow model (i, i,0)

remE([], _, []).
remE([H|T], C, R):-
    nOc(C, H, N),
    N > 1, 
    !,
    remE(T, C, R1),		%or remE(T, C, [H | R]).
    R = [H | R1].
remE([H|T], C, R):-
    nOc(C, H, N),
    N =:= 1, 
    remE(T, C, R).

mainRE(L, R):- remE(L, L, R).


%with collector
%remEC(l1, ..., ln, copy, C) = C if n = 0
%								remEC(l2, ... ,ln copy, l1 u C) if nrOc(copy, l1) > 1,
%								remEC(l2, ... ,ln copy, C) if nrOc(copy, l1) = 1,
%remEC(i, i, o).


%mainEC(l1, ... , ln) = remEC(l1, ... ln, l1, ... ln, [])


remEC([], _, C, C).
remEC([H|T], CP, C, R):-
    nOc(CP, H, N),
    N > 1,
    !,
    remEC(T, CP, [H | C], R).
remEC([H|T], CP, C, R):-
    nOc(CP, H, N),
    N =:= 1,
    remEC(T, CP, C, R).

mainEC(L, R):-remEC(L, L, [], R).



% [1, 1, 2, 3, 4, 3] remove the unique elements


countOcc([], _, 0).
countOcc([H|T], E, R):-
    H =:= E,
    !,
    countOcc(T, E, R1),
    R is R1 + 1.
countOcc([_|T], E, R):-
    countOcc(T, E, R).









