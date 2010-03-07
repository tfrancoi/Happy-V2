[# include std.ha #]
(fun main (of arg) (
	(set a (array))
	(write ('(' (array) << 1 2 3 4 5) # 3))
	(write "-----")
	(' a << 1 2 3 4 5 "salut" "petit" "con")
	(write (len a))
	(write (' a # 0))
	('a print)
	('a # 0 "hello") 
	(print a)
))

(fun print (of arg) (
	(set i 0)
	(while (< i (len arg)) ( 
		(write ('a # i))
		(set i ('i + 1))
	))
))
