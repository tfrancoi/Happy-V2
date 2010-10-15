(
	
	(fun main (of args) (
		[! (write "test") !]
		[! (set a sum) !]
		[! (write (a 4 5)) !]
		(write (test -))
	))

	(fun sum (of a b) (return ('a - b) ))

	(fun test (of ++) (
		(set i 0)
		(while ('(set i ('i + 1)) < 10)  
			(write (++ 1 i))
		)
		(return (++ 10 20))
	))
)
