;; Enrico Scala (enricos83@gmail.com) and Miquel Ramirez (miquel.ramirez@gmail.com)
;;Setting seed to 1229
(define (problem instance_4_500_1229_scale)
	(:domain farmland)
	(:objects
		farm0 farm1 farm2 farm3  - farm
	)
  (:init
		(= (x farm0) 1)
		(= (x farm1) 500)
		(= (x farm2) 0)
		(= (x farm3) 0)
		
		(adj farm0 farm1)
		(adj farm0 farm2)
		(adj farm1 farm0)
		(adj farm1 farm3)
		(adj farm2 farm0)
		(adj farm2 farm3)
		(adj farm3 farm1)
		(adj farm3 farm2)
		
		(= (cost) 0)
	)
	(:goal
		(and
			(> (x farm0) 0)
			(> (x farm1) 0)
			(> (x farm2) 0)
			(> (x farm3) 0)
			
			(> (+ (* 1.5 (x farm0))(+ (* 1.0 (x farm1))(+ (* 1.3 (x farm2))(+ (* 1.2 (x farm3)) 0)))) 700.0)
		)
	)
)


