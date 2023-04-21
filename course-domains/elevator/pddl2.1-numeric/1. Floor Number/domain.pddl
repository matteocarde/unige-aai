; Infinite capacity but now floors are treated as integer numbers

(define (domain elevator)
  (:requirements :strips :typing)
  (:types
    person elevator
  )
  (:predicates
    (reached ?p - person)
    (in ?e - elevator ?p - person)
  )
  (:functions
    (at-elevator ?e - elevator)
    (at-person ?p - person)
    (target ?p - person)
    (floors)
  )

  (:action move-up
    :parameters (?e - elevator)
    :precondition (and
      (< (at-elevator ?e) (floors))
    )
    :effect (and
      (increase (at-elevator ?e) 1)
    )
  )

  (:action move-down
    :parameters (?e - elevator)
    :precondition (and
      (> (at-elevator ?e) 0)
    )
    :effect (and
      (decrease (at-elevator ?e) 1)
    )
  )

  (:action load
    :parameters (?p - person ?e - elevator)
    :precondition (and
      (= (at-person ?p) (at-elevator ?e))
    )
    :effect (and
      (in ?e ?p)
      (assign (at-person ?p) -1)
    )
  )

  (:action unload
    :parameters (?p - person ?e - elevator)
    :precondition (and
      (in ?e ?p)
    )
    :effect (and
      (not (in ?e ?p))
      (assign (at-person ?p) (at-elevator ?e))
    )
  )

  (:action reached
    :parameters (?p - person)
    :precondition (and
      (= (at-person ?p) (target ?p))
      (not (reached ?p))
    )
    :effect (and
      (reached ?p)
    )
  )

)