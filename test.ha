(
	[# include std.ha #]
	(fun main (of args) (
		[! (write "test") !]
		[! (set a sum) !]
		[! (write (a 4 5)) !]
		(write (test sum))
	))

	(fun sum (of a b) (return ('a + b) ))

	(fun test (of f) (
		(set i 0)
		(while ('(set i ('i + 1)) <= 10)  
			(write (f 1 i))
		)
		(return (f 10 20))
	))
)
