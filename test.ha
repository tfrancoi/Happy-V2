(	
	(fun main (of argv argc) 
		( 
			(set a (+ "salut l" "es amis"))
			(write (writes a " hin ! "))
			(write (+ 4 (+ 2 3)))
			(write a)
			(write 100 70 10 45 67)
			(write "hello \nworld")
		) 
	)	
	(fun writes (of arg arg2) 
		(
			(write (= "salut" "salut"))
			(write (+ arg arg2))
			(if (= "salut" "salut") (write "yes") (write "no"))
		
			(return (+ arg2 arg))			
		)
	)
)






