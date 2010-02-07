[# include std.ha #]

(	
	(fun main (of argv argc) 
		( 
			
			(set a 0)
			(while (< (set a (+ a 1)) 10) (
				(write a)				
			))
			(write (set b "18 - - - - - - - "))
			(write (set b 23))
			(write (- 10 3))
			(write (typeof 4))
			(set a (+ 5 6))
			(write (<= 5 4) (< 4 4))
			(write (>= 5 4) (> 4 4))
			(write (* 7 a))
			[! (write (fibbo 24)) !]
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






