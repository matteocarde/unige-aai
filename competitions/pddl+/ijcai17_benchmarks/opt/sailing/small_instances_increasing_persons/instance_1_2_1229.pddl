;;Setting seed to 1229
;; Enrico Scala (enricos83@gmail.com) and Miquel Ramirez (miquel.ramirez@gmail.com)
(define (problem instance_1_2_1229)

	(:domain sailing)

	(:objects
		b0  - boat
		p0 p1  - person
	)

  (:init
		(= (x b0) 7)
(= (y b0) 0)


		(= (d p0) 32)
(= (d p1) 110)


	)

	(:goal
		(and
			(saved p0)
(saved p1)

		)
	)
)


