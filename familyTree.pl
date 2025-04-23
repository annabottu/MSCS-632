% Basic Relationships
parent(john, mary).
parent(john, justin).
parent(amy, mary).
parent(amy, justin).
parent(mary, sydney).
parent(mary, vince).
parent(henry, sydney).
parent(henry, vince).
parent(justin, jennifer).
parent(justin, joey).
parent(junie, jennifer).
parent(junie, joey).
male(john).
male(justin). 
male(vince).
male(joey).
male(henry).
female(mary).
female(amy).
female(sydney).
female(jennifer).
female(junie).

% Derived Relationships

% Grandparent: X is a grandparent Y if Z is a child of X and 
grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

% Siblings: X and Y are siblings if they have a parent incommon but can not be the same person
sibling(X, Y) :-
    parent(P, X),
    parent(P, Y),
    X \= Y.

% Cousin: X and Y are cousins if their parents are siblings (if they have atleast one similar parent)
cousin(X, Y) :- 
    parent(P1, X),
    parent(P2, Y),
    sibling(P1, P2),
    X \= Y.

% Child: Y is the child of X
child(X, Y) :- 
    parent(Y, X).

% Indirect Relationships - identifing all descendants of a person
% X is a descendant of Y if Y is the parent of X
% X is a descendant of Y if Z is a parent of X, and Z is also a descendant of Y
descendant(X, Y) :-
    parent(Y, X).
descendant(X, Y) :-
    parent(Z, X),
    descendant(Z, Y).

