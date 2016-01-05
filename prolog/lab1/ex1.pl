numeral(0).
numeral(s(X)) :- numeral(X).
numeral(X+Y) :- numeral(X),numeral(Y).
numeral(p(X)) :- numeral(X).
numeral(-X) :- numeral(X).
numeral(X-Y) :- numeral(X),numeral(Y).

isZero(0,0).
isZero(s(X),s(Y)) :-
	isZero(X,Y),
	Y \=p(_).
isZero(s(X),Y) :- isZero(X,p(Y)).
isZero(p(X),p(Y)) :-
	isZero(X,Y),
	Y \=s(_).
isZero(p(X),Y) :- isZero(X,s(Y)).

add2(0,X,Y) :- isZero(X,Y).
add2(s(X),Y,s(Z)) :-
	add2(X,Y,Z),
	Z \=p(_).
add2(s(X),Y,Z) :- add2(X,Y,p(Z)).
add2(p(X),Y,p(Z)) :-
	add2(X,Y,Z),
	Z \=s(_).	
add2(p(X),Y,Z) :- add2(X,Y,s(Z)).

add2(X+Y,Z,R1) :-
	add2(X,Y,R2),
	add2(R2,Z,R1),
	numeral(R1).
	
add2(X,Y+Z,R1) :-
	add2(Y,Z,R2),
	add2(X,R2,R1),
	numeral(R1).
	
add2(A+B,X+Y,R1) :-
	add2(X,Y,R2),
	add2(A,B,R3),
	add2(R2,R3,R1),
	numeral(R1).

add2(-X,Y,Z) :-
	minus(X,R1),
	add2(R1,Y,Z),
	numeral(Z).
	
add2(X,-Y,Z) :-
	minus(Y,R1),
	add2(R1,X,Z),
	numeral(Z).
	
add2(X-Y,Z,R) :-
	subtract(X,Y,R1),
	add2(R1,Z,R),
	numeral(R).
	
add2(X,Y-Z,R) :-
	subtract(Y,Z,R1),
	add2(X,R1,R),
	numeral(R).

add2(X-Y,A-B,Z) :-
	subtract(X,Y,R1),
	subtract(A,B,R2),
	add2(R1,R2,Z),
	numeral(Z).
	
add2(-(X-Y),Z,R) :-
	subtract(X,Y,R1),
	minus(R1,R2),
	add2(R2,Z,R),
	numeral(R).
	
add2(X,-(Y-Z),R) :-
	subtract(Y,Z,R1),
	minus(R1,R2),
	add2(X,R2,R),
	numeral(R).
	
add2(-(X-Y),-(A-B),Z) :-
	subtract(X,Y,R1),
	subtract(A,B,R2),
	minus(R1,R1M),
	minus(R2,R2M),
	add2(R1M,R2M,Z),
	numeral(Z).

minus(0,0).

minus(s(X),p(Z)) :-
	minus(X,Z),
	Z \=s(_).
	
minus(p(X),s(Z)) :-
	minus(X,Z),
	Z \=p(_).
	
minus(p(X),Z) :-
	minus(X,p(Z)).
	
minus(s(X),Z) :-
	minus(X,s(Z)).
	
subtract(X,Y,Z) :-
	minus(Y,R1),
	add2(X,R1,Z).	
subtract(X,-Y,Z) :- add2(X,Y,Z).
subtract(-X,Y,Z) :- add2(X,Y,Z).

subtract(X,Y-Z,R) :-
	subtract(Y,Z,R1),
	subtract(X,R1,R),
	numeral(R).
	
subtract(X-Y,Z,R) :-
	subtract(X,Y,R1),
	subtract(R1,Z,R),
	numeral(R).
	
subtract(X-Y,A-B,R) :-
	subtract(X,Y,R1),
	subtract(A,B,R2),
	subtract(R1,R2,R),
	numeral(R).
	
subtract(X,-(Y-Z),R) :-
	subtract(Y,Z,R1),
	minus(R1,MR1),
	subtract(X,MR1,R),
	numeral(R).
	
subtract(-(X-Y),Z,R) :-
	subtract(X,Y,R1),
	minus(R1,MR1),
	subtract(MR1,Z,R),
	numeral(R).
	
subtract(-(X-Y),-(A-B),R) :-
	subtract(X,Y,R1),
	subtract(A,B,R2),
	minus(R1,MR1),
	minus(R2,MR2),
	subtract(MR1,MR2,R),
	numeral(R).

