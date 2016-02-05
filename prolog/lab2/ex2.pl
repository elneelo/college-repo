
/*****QUESTION 1*****/


s --> z(Count), [2], one(Count).

z(0) --> [].
z(succ(Count)) --> [0], z(Count).
z(Count) --> [1], z(Count).

one(0) --> [].
one(succ(Count)) --> [1], one(Count).
one(Count) --> [0], one(Count).


/*****QUESTION 2*****/


s --> col(X1),
			nat(Y1),
			pet(Z1),
			col(X2),
			nat(Y2),
			pet(Z2), {X2 \= X1}, {Y2 \= Y1}, {Z2 \= Z1},
			col(X3),
			nat(Y3),
			pet(Z3), {X3 \= X2}, {X3 \= X1}, {Y3 \= Y2}, {Y3 \= Y1}, {Z3 \= Z2}, {Z3 \= Z1}.

col(red) --> [red].
col(blue) --> [blue].
col(green) --> [green].

nat(english) --> [english].
nat(japanese) --> [japanese].
nat(spanish) --> [spanish].

pet(snail) --> [snail].
pet(jaguar) --> [jaguar].
pet(zebra) --> [zebra].


/*****QUESTION 3*****/


reverse([]) --> [].
reverse([L|Ls]) --> reverse(Ls), [L].

mkList(N,L) :-
	numlist(1,N,X),
	reverse(X,L).

sumAll(Sum) --> {Sum > 0},
					 {mkList(Sum,List)},
					 findVal(List,0,Sum,Ret),
					 {Ret =:= Sum}.

findVal(L,A,Sum,Ret) --> {member(Val,L)},
											 [Val],
											 {Anew is A + Val},
											 {Anew =< Sum},
											 findVal(L,Anew,Sum,Ret).

findVal(_,A,_,A) --> [].



/*s(Sum) --> check(mkList(Sum,List)).

check([H|T]) --> check(T).
check([1]).*/
