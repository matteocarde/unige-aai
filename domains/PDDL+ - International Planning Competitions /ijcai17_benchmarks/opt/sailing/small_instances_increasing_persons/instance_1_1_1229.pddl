;;Setting seed to 1229
;; Enrico Scala (enricos83@gmail.com) and Miquel Ramirez (miquel.ramirez@gmail.com)
(define (problem instance_1_1_1229)

	(:domain sailing)

	(:objects
		b0  - boat
		p0  - person
	)

  (:init
		(= (x b0) 3)
(= (y b0) 0)


		(= (d p0) 32)


	)

	(:goal
		(and
			(saved p0)

		)
	)
)


