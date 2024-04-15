male(mayur).
male(tushar).
male(satish).
female(bhagyshri). 

parent(satish, mayur).
parent(bhagyshri, mayur).
parent(bhagyshri, tushar).
parent(satish, tushar).

sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
brother(X, Y) :- sibling(X, Y), male(X).