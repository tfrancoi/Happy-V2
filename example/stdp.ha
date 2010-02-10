
	

(fun *s (of a b r) 
	(if (= 0 a) 
		(return r)
		(return (*s (- a 1) b (+ r b)))
	)
)
	

