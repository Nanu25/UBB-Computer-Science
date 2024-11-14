%8. Generate all strings of n parentheses correctly closed.
% Eg: n=4 => (()) and () ()

%generate(N, OpenP, ClosedP) {
%				[] if n is odd.
%				( u generate(N, OpenP + 1, ClosedP) if OpenP <= N / 2;
%				) u generate(N, OpenP, ClosedP + 1) if OpenP <= ClosedP
% flow model = generate(i, i, i, o).

generate(N, _, _, []):-
    N mod 2 =:= 1,
    !.

%Solution.
generate(N, OpenP, ClosedP, []):-
    S is OpenP + ClosedP,
    N =:= S,
    !.

generate(N, OpenP, ClosedP, ['(' | R]):-
    Open1 is OpenP + 1,
    Nh is N // 2,
    Open1 =< Nh,
    generate(N, Open1, ClosedP, R).
                            
generate(N, OpenP, ClosedP, [')' | R]) :-
    Closed1 is ClosedP + 1,
    Closed1 =< OpenP,
    generate(N, OpenP, Closed1, R).

%flow model - mainGenerate(i, o).
mainGenerate(N, R):-
    generate(N, 0, 0, R).
