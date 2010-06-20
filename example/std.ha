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
	
	(fun add (of array liste) ( 
		(set i 0)
		(while (' i < (len liste)) (
			(' array << ('liste # i))
			(set i ('i + 1))
		))
		
	))
	
	
	
)
