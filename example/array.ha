[# include std.ha #]
(fun main (of arg) (
	
	(set a (! 1 2 3 4))
	('a << 1 2)
	(print a)
	('a # 0 "salut")
	(print a)

))

(fun print (of arg) (
	(set i 0)
	(write (typeof arg))
	(while (< i (len arg)) ( 
		(write ('a # i))
		(set i ('i + 1))
	))
))
