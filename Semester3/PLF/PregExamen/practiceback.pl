%Write a program to generate the list of all subsets of sum S with the elements of a list (S - given).
%Eg: [1,2,3,4,5,6,10] si S=10 => [[1,2,3,4], [1,4,5], [2,3,5], [4,6], [10]] (not necessary in this order)

%subset(l1, ..., ln) = null if l is null
%					= l1 u subset(l2, ..., ln), n > 0
%					= subset(l2, ..., ln), n > 0

subset([], []).
subset([H | T], [H | R]):-
    subset(T, R).
subset([_ | T], R):-
    subset(T, R).

%findSum(l1, ..., ln, S) = 0 if l = 0
%						findSum(l2, ..., ln, S + l1).

findSum([], 0).
findSum([H | T], S):-
    findSum(T, S1),
    S is H + S1.

onesol(L, R, S):-
    subset(L, R),
    findSum(R, S).	%Compara direct rezultatul din FindSum(R, 0) adica il compara pe 0 cu S.

%ambele merg.
onesol1(L, R, S):-
    subset(L, R),
    findSum(R, S1),
    S =:= S1.

findAllSub(L, S, AllSubsets) :-
    findall(R, onesol(L, R, S), AllSubsets).


%A player wants to choose the predictions for 4 games. The predictions can be 1, X, 2. Write a predicate 
%to generate all possible variants considering that: last prediction can’t be 2 and no more than two
%possible predictions X.

%getpredict(l1, ..., ln, index, R) = R if index is 4.
%								= getpredict(l2, ..., ln, index + 1, 1 u R)
%								= getpredict(l2, ..., ln, index + 1, 2 u R)
%								= getpredict(l2, ..., ln, index + 1, X u R)
getpredict(Ind, R, R):-
    Ind == 4.
getpredict(Ind, [1 | R], CR):-
    Ind < 4,
    Index1 is Ind + 1,
    getpredict(Index1, R, CR).
getpredict(Index, [2 | R], CR):-
    Index < 4,
    Index1 is Index + 1,
    getpredict(Index1, R, CR).
getpredict(Index, ['x' | R], CR):-
    Index < 4,
    Index1 is Index + 1,
    getpredict(Index1, R, CR).

% Check if a prediction list is valid
check([], 1).
check([H], Ok):-     % Changed to handle single element list
    H \== 2,         % Changed =\= to \== for atom comparison
    Ok is 1,
    !.
check([_, H2], Ok):- % For two elements, last can't be 2
    H2 \== 2,       
    Ok is 1,
    !.
check([H1, H2, H3 | _], Ok):-
    H1 == x,         % Changed =:= to == for atom comparison
    H2 == x,
    H3 == x,
    Ok is 0,
    !.
check([_ | T], Ok):- % Simplified recursive case
    check(T, Ok).

% Find one solution
onesol1(R):-
    getpredict(0, [], R),   % Removed extra period
    check(R, Ok),
    Ok == 1.

% Find all solutions
fndall(Result):-
    findall(R, onesol1(R), Result).


% Generate all valid predictions for 4 games where:
% - Each prediction can be 1, x, or 2
% - Last prediction cannot be 2
% - No more than two x predictions allowed

% Generate a list of 4 predictions
generate_predictions(Predictions) :-
    length(Predictions, 4),
    fill_predictions(Predictions),
    last(Predictions, Last),
    Last \== 2,
    count_x(Predictions, Count),
    Count =< 2.

% Fill the list with valid predictions
fill_predictions([]).
fill_predictions([H|T]) :-
    member(H, [1, 2, x]),
    fill_predictions(T).

% Count occurrences of x in the list
count_x([], 0).
count_x([x|T], Count) :-
    count_x(T, RestCount),
    Count is RestCount + 1.
count_x([H|T], Count) :-
    H \== x,
    count_x(T, Count).

% Find all valid solutions
find_all_predictions(Result) :-
    findall(P, generate_predictions(P), Result).



