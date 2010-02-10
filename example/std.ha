(
	[# include stdp.ha #] 
	
	
	
	(fun > (of a b) (return (< b a)))
	(fun >= (of a b) 
		(if (= a b) 
			(return 1)
			(return (< b a))
		)
	)
	
	(fun <= (of a b)  
		(if (= a b) 
			(return 1)
			(return (< a b))
		)
	)
	
	(fun * (of a b) (return (*s a b 0)))
	
	
)
