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
		(one-object ?g - gripper)
		(two-objects ?g - gripper)
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
			(or (free ?g) (one-object ?g))
		)
		:effect (and
			(carry ?o ?g)
			(not (at-obj ?o ?l))
			(not (free ?g))
			(when
				(free ?g)
				(one-object ?g))
			(when
				(one-object ?g)
				(two-objects ?g))
		)
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
			(when
				(two-objects ?g)
				(one-object ?g))
			(when
				(one-object ?g)
				(free ?g))
			(not (carry ?o ?g)))
	)
)