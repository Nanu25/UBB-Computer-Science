%[[1,2], 5, [7, 2, 1], s, a, b].
% H | T
% H = [1, 2]
% T = [5, [7, 2, 1], s, a, b].
% is_list(H)
% atomic(H)
% number(H).

%Given a heterogeneous list composed of numbers, symbols abd lists of numbers, remove the sublists.

%[[1,2], 5, [7, 2, 1], s, a, b] => [5, s, a, b]

% process(l1, l2, ... , ln) = {
%								[] if n = 0
%								process(l2, ..., ln) if l1 - list, l1 = l11, l12, ..., l1m.
%								l1 u process(l2, ... ,ln) otherwise.

process([], []).
process([H | T], R):-
    is_list(H),
    !,
    process(T, R).
process([H|T], [H|R]):-
    % atomic(H), sau \+ is_list(   H) sau not(is_list(H)).
    process(T, R).

% Given a list of numbers and sublists of numbers, subtitue each sublists
%  for which the sum of the elems is odd with the first element of that list.
% we assume that sublists have at least one element.

% ex. [1, 2, [2, 4], 7, 3, [4, 6, 7], [1], 8, 10, [3, 2]].
% => [1, 2,[2, 4], 7, 3, 4, 1, 8, 10, 3].
suma([], 0).
suma([H|T], S):-
    suma(T, TS),
    S is TS + H.

%process1(l1, ... ,ln) = {
%							[] if n = 0
%							l11 u process1(l2, ..., ln) if l1 is list and suma(l1) % 2 == 1
%							l1 u process1(l2, ..., ln) otherwise
%process1(L-list, R-list).
%flow model(i, o).

process1([], []).
process1([H | T], [H1 | R]):-
    is_list(H),
    suma(H, S),
    S mod 2 =:= 1,
    !,
    H = [H1 | _ ],
    process1(T, R).
process1([H|T], [H|R]):-
    process1(T, R).

%Remove the the odd elements from the sublists that are mountain

%removeOdd(l1, ..., ln) = {
%							[] if n = 0
%							l1 u removeOdd(l2, ... , ln) if l1 % 2 == 0
%							removeOdd(l2, ... , ln) if l1 % 2 == 1

removeOdd([], []).
removeOdd([H|T], [H|R]):-
    H mod 2 =:= 0,
	!,
    removeOdd(T, R).
removeOdd([_|T], R):-
    removeOdd(T, R).

% mountain(l1, ... ,ln) {
%							true if n = 1 and f = 1
%							mountain(l2, ... ln, 0) l1 < l2, F = 0
%							mountain(l2, ..., ln, 1) l1 > l2, F = 0;
%							mountain(l2, ..., ln, 1), l1 > l2 F = 1
%							False otherwise

mountain([_], 1).
mountain([H1, H2| T], 0) :-
    H1 < H2,
    mountain([H2 | T], 0).
mountain([H1, H2 | T], _):-
    H1 > H2,
    mountain([H2|T], 1).

%mainMountain(l1, ..., ln) = {
%								mountain(l2, ..., ln, 0) if l1 < l2
%								false otherwise.

mainMountain([H1, H2 | T]):-
    H1 < H2,
    mountain([H2 | T], 0).


%process2(l1, ..., ln) = {
%							[] if n = 0;
%							removeOdd(l1) u process2(l2, ..., ln), is_list(l1) and mountain(l1)
%							l1 u process2(l2, ... ,ln), otherwise.


process2([], []).
process2([H | T], [H1 | R]):-
    is_list(H),
    mainMountain(H),
    !,
    removeOdd(H, H1),
    process2(T, R).
process2([H|T], [H|R]):-
    process2(T, R).





%%%%%					%%%%%
%			EXTRA			%
%							%
%%%%%					%%%%%

%rem_inc(l1, ... , ln) = {
%							[], n = 0.
%							[l1], n = 1.
%							[], if n = 2 and l1 < l2
%							l1 u rem_inc(l2, ..., ln) if l1 >= l2
%							rem_inc

rem_inc([], []).
rem_inc([H], [H]).
rem_inc([H1, H2], []):-
    H1 < H2.
rem_inc([H1, H2 | T], [H1 | R]):-
    H1 >= H2,
    rem_inc([H2 | T], R).
rem_inc([H1, H2, H3 | T], R):-
    H1 < H2,
    H2 < H3,
    rem_inc([H2, H3|T], R).
rem_inc([H1, H2, H3 | T], R):-
    H1 < H2,
    H2 >= H3,
    rem_inc([H3|T], R).

















