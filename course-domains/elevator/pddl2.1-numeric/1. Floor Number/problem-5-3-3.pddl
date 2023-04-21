(define (problem pb1)
  (:domain elevator)
  (:objects
    personA personB personC personD personE - person
    elevator1 elevator2 elevator3 - elevator

  )
  (:init
    (= (floors) 3)
    (= (at-person personA) 1)
    (= (target personA) 2)
    (= (at-person personB) 1)
    (= (target personB) 3)
    (= (at-person personC) 2)
    (= (target personC) 3)
    (= (at-person personD) 1)
    (= (target personD) 2)
    (= (at-person personE) 3)
    (= (target personE) 1)

    (= (at-elevator elevator1) 3)
    (= (at-elevator elevator2) 2)
    (= (at-elevator elevator3) 1)
  )
  (:goal
    (and
      (reached personA)
      (reached personB)
      (reached personC)
      (reached personD)
      (reached personE)
    )
  )
)