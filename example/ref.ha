(fun main (of arg) (
	(set a (new 6))
	(set b (new 9))
	(write a)
	(write b)
	(swap a b)
	(write a)
	(write b)
	(write (' a + b))
	
))

(fun swap (of a b) (
	(set temp ('a @))
	(' a :=  ('b @))
	(' b := temp)

))
