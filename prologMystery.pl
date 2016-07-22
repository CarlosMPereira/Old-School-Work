person(timmy, child).
person(jimmy, teen).
person(john, dad).
person(jane, mom).
person(ned, neighbor).
parents(timmy, john, jane).
parents(jimmy, ned, jane).
hates(jimmy, john).
hates(john, ned).
lies(jane, john).
killed(ned, knife).
has(kitchen, knife).
accidents(timmy).
alcholic(john).
depressed(jimmy).
has(ned, knife).
record(jimmy).
has(kitchen, chair).
likes(timmy, ned).
likes(jane, ned).

bastard_child(Person1, Person2) :- (person(Person1, neighbor),
	                           parents(X, Person1, Person2));
				   (person(Person2, neighbor),
				   parents(X, Person2, Person1)).

has_motive(Person1) :- hates(Person1, ned);
                       bastard_child(ned, Person1);
		       record(Person1).

murder_weapon(Person1, Object) :- has(Person1, Object).

drinking_problem(Person1) :- alcholic(Person1);
                             depressed(Person1).

accident_liable(Person1) :- accidents(Person1);
			    alcholic(Person1).

favorable_to(Person1, Person2) :- likes(Person1, Person2).

trust_issues(Person1, Person2) :- lies(Person1, Person2);
                                  lies(Person2, Person1).

is_weapon(Object) :- killed(ned, Object).


visits_daily(Person1) :- person(Person1, neighbor).


neglects(Person1, Person2) :- hates(Person2, Person1),
	                        not(parents(Person2, Person1, jane)).

reaches_for(Person1, Person2) :- likes(Person1, Person2),
			         person(Person1, child),
				 has(kitchen, chair).

babysits(Person1, Person2) :- person(Person2, child),
	                      visits_daily(Person1).


slashes_tires(Person1, Person2) :- hates(Person1, Person2).

jail_time(Person1) :- record(Person1).


sleeps_with(Person1, Person2) :- parents(jimmy, Person1, Person2);
				parents(timmy, Person1, Person2).

works(Person1) :- person(Person1, mom);
                  person(Person1, dad).

school(Person1) :- person(Person1, teen).


works_together(Person1, Person2) :- person(Person1, mom),
	                            person(Person2, dad).

drives_together(Person1, Person2) :- works_together(Person1,Person2).


situates(Person1, Person2) :- not(hates(Person1, Person2)),
	                      (parents(timmy, Person1, X);
			       parents(timmy, X, Person1)).








