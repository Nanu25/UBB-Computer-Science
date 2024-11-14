% Length predicate
lungime([], 0).
lungime([_ | T], R) :- 
    lungime(T, R1),
    R is R1 + 1.

% Merge two sorted lists
merge([], L, L).
merge(L, [], L).
merge([H1|T1], [H2|T2], [H1|R]) :-
    H1 =< H2,
    merge(T1, [H2|T2], R).
merge([H1|T1], [H2|T2], [H2|R]) :-
    H1 > H2,
    merge([H1|T1], T2, R).

% Split a list into two halves
split(List, Left, Right) :-
    lungime(List, Len),
    HalfLen is Len // 2,
    split_at(List, HalfLen, Left, Right).

% Helper predicate to split list at N elements
split_at(L, 0, [], L).
split_at([H|T], N, [H|L1], L2) :-
    N > 0,
    N1 is N - 1,
    split_at(T, N1, L1, L2).

% mergeSort predicate
mergeSort([], []).
mergeSort([X], [X]):-!.
mergeSort(List, Sorted) :-
    split(List, LeftHalf, RightHalf),
    mergeSort(LeftHalf, SortedLeft),
    mergeSort(RightHalf, SortedRight),
    merge(SortedLeft, SortedRight, Sorted).

% Main entry point for mergeSort
mainMerge(L, R) :-
    mergeSort(L, R).
