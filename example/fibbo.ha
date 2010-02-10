[# include std.ha #]

(fun main (of arg) ( 
	(fibbo_while 28)
))

(fun fibbo_while (of max) (
	(set f1 0)
	(set f2 1)
	(set i 0)
	(while (< i max) 
		(
			(set f1 (+ f1 f2))
			(set temp f1)
			(set f1 f2)
			(set f2 temp)
			(set i (+ i 1))
		)
	)
	(write f2)

))
