%9. 
%a. For a list of integer number, write a predicate to add in list after 1-st, 3-rd, 7-th, 15-th element a given value e.
%b. For a heterogeneous list, formed from integer numbers and list of numbers; add in every sublist after 1-st, 
%3-rd, 7-th, 15-th element the value found before the sublist in the heterogenous list. The list has the particularity 
%that starts with a number and there aren’t two consecutive elements lists.
%Eg.: [1, [2, 3], 7, [4, 1, 4], 3, 6, [7, 5, 1, 3, 9, 8, 2, 7], 5] =>
%[1, [2, 1, 3], 7, [4, 7, 1, 4, 7], 3, 6, [7, 6, 5, 1, 6, 3, 9, 8, 2, 6, 7], 5].
%

%addElement(l1, ..., ln) ={
%							[] if n = 0;
%							 e u l1 u addElement(l2, ..., ln, poz + 1, next + poz + 1) if poz == next		
%							l1 u addElement(l2, ..., ln, poz + 1, next) if poz == next	
%

addElement([], _, _, _, []).
addElement([H | T], Poz, Next, E, [H | R]):-
	Poz =\= Next,
    Poz1 is Poz + 1,
    !,
    addElement(T, Poz1, Next, E, R).
addElement([H | T], Poz, Next, E, R):-
    Next1 is Next + 1 + Poz,
    Poz1 is Poz + 1,
    addElement(T, Poz1, Next1, E, R1),
    R2 = [E | R1],
    R = [H | R2].
    
mainAddElement(L, E, R):-
    addElement(L, 1, 1, E, R).

% modifyList(l1, ... , ln) = {
% 								[] if n = 0;
% 								modifyList(mainAddElement(l1, PrevElem) u  l2, ... , ln) if l1 is list.
%								modifyList(l2, ..., ln) otherwise.
modifyList([], _, []).
modifyList([H | T], Prev, [R1 | R]):-
    is_list(H),
    !,
    modifyList(T, Prev, R),
    mainAddElement(H, Prev, R1).

modifyList([H | T], _, [H | R]):-
   	Prev1 is H,
    modifyList(T, Prev1, R).

mainModifyList(L, R):-
    modifyList(L, 0, R).
    
    
    
    
