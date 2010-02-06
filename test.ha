[# include std.ha #]

(	
	(fun main (of argv argc) 
		( 
			(write (- 10 3))
			(write (<= 5 4) (< 4 4))
			(write (>= 5 4) (> 4 4))
			(write (* 3 400000))
			(write (fibbo 24))
		) 
	)		
	
	(fun fibbo (of a) 
		(if (= a 0) 
			(return 0)
			(if (= a 1)
				(return 1)
				(return (+ (fibbo (- a 1)) (fibbo (- a 2))))
			)
		)
	)
)






