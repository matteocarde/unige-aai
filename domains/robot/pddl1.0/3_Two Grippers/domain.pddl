(define (domain robot)
	(:requirements :strips :typing)
	(:types
		room obj robot gripper
	)
	(:predicates
		(of-robot ?r - robot ?g - gripper)
		(at-robot ?r - robot ?l - room)
		(at-obj ?b - obj ?r - room)
		(carry ?o - obj ?g - gripper)
		(free ?g - gripper)
		(allowed ?r - robot ?l - room)
	)

	(:action move
		:parameters (?r - robot ?a - room ?b - room)
		:precondition (and
			(at-robot ?r ?a)
			(allowed ?r ?b)
		)
		:effect (and
			(at-robot ?r ?b)
			(not (at-robot ?r ?a))
		)
	)

	(:action pick
		:parameters (?o - obj ?l - room ?g - gripper ?r - robot)
		:precondition (and
			(at-obj ?o ?l)
			(of-robot ?r ?g)
			(at-robot ?r ?l)
			(free ?g)
		)
		:effect (and
			(carry ?o ?g)
			(not (at-obj ?o ?l))
			(not (free ?g)))
	)

	(:action drop
		:parameters (?o - obj ?l - room ?g - gripper ?r - robot)
		:precondition (and
			(carry ?o ?g)
			(of-robot ?r ?g)
			(at-robot ?r ?l)
		)
		:effect (and
			(at-obj ?o ?l)
			(free ?g)
			(not (carry ?o ?g)))
	)
)