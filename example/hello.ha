[! include std.ha !]
(fun main (of arg) (
	(write (set a 0))
	(while ('(set a (' a + 1)) <= 20) 
		(write a)
	)
	(set :-o "hooooo")
	(write :-o) 
))
