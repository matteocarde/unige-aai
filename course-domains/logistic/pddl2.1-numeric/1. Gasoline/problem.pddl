(define (problem logistics-10-0)
  (:domain logistics)
  (:objects
    apn1 - airplane
    apt1 apt4 apt3 apt2 - airport
    pos4 pos3 pos2 pos1 petrol1 - location
    cit4 cit3 cit2 cit1 - city
    tru4 tru3 tru2 tru1 - truck
    obj43 obj42 obj41 obj33 obj32 obj31 obj23 obj22 obj21 obj13 obj12 obj11 - package
  )

  (:init
    (at-place apn1 apt1)
    (at-place tru1 pos1)
    (at-place obj11 pos1)
    (at-place obj12 pos1)
    (at-place obj13 pos1)
    (at-place tru2 pos2)
    (at-place obj21 pos2)
    (at-place obj22 pos2)
    (at-place obj23 pos2)
    (at-place tru3 pos3)
    (at-place obj31 pos3)
    (at-place obj32 pos3)
    (at-place obj33 pos3)
    (at-place tru4 pos4)
    (at-place obj41 pos4)
    (at-place obj42 pos4)
    (at-place obj43 pos4)
    (in-city pos1 cit1)
    (in-city apt1 cit1)
    (in-city pos2 cit2)
    (in-city apt2 cit2)
    (in-city pos3 cit3)
    (in-city apt3 cit3)
    (in-city pos4 cit4)
    (in-city apt4 cit4)

    (in-city petrol1 cit1)
    (is-petrol-station petrol1)

    (link cit1 cit4)
    (link cit4 cit1)
    (link cit4 cit3)
    (link cit3 cit4)
    (link cit1 cit2)
    (link cit2 cit1)

    (= (distance cit1 cit4) 15)
    (= (distance cit4 cit1) 15)
    (= (distance cit4 cit3) 10)
    (= (distance cit3 cit4) 10)
    (= (distance cit1 cit2) 20)
    (= (distance cit2 cit1) 20)

    (= (distance-run tru1) 0)
    (= (distance-run tru2) 0)
    (= (distance-run tru3) 0)
    (= (distance-run tru4) 0)

    (= (max-distance tru1) 40)
    (= (max-distance tru2) 40)
    (= (max-distance tru3) 40)
    (= (max-distance tru4) 40)

  )

  (:goal
    (and (at-place obj31 pos3) (at-place obj33 apt3) (at-place obj41 apt3) (at-place obj23 pos4)
      (at-place obj11 pos3) (at-place obj22 apt2) (at-place obj12 apt1) (at-place obj21 pos4)
      (at-place obj42 pos4) (at-place obj32 pos1))
  )
)