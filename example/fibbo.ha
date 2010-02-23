[# include std.ha #]

(fun main (of arg) ( 
	(fibbo_while 40)
))

(fun fibbo_while (of max) (
	(set f1 0)
	(set f2 1)
	(set i 0)
	(while 
		(< 
			(set i (+ i 1))  
			max
		) 
		(
			(set f1 (+ f1 f2))
			(set temp f1)
			(set f1 f2)
			(set f2 temp)
			(write f2)
		)
	)
	(write f2)

))

