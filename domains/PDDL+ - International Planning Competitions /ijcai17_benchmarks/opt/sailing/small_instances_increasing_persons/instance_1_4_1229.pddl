;;Setting seed to 1229
;; Enrico Scala (enricos83@gmail.com) and Miquel Ramirez (miquel.ramirez@gmail.com)
(define (problem instance_1_4_1229)

	(:domain sailing)

	(:objects
		b0  - boat
		p0 p1 p2 p3  - person
	)

  (:init
		(= (x b0) -2)
(= (y b0) 0)


		(= (d p0) 32)
(= (d p1) 110)
(= (d p2) 140)
(= (d p3) 26)


	)

	(:goal
		(and
			(saved p0)
(saved p1)
(saved p2)
(saved p3)

		)
	)
)


