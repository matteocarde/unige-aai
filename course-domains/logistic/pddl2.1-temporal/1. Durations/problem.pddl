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
    (at apn1 apt1)
    (at tru1 pos1)
    (at obj11 pos1)
    (at obj12 pos1)
    (at obj13 pos1)
    (at tru2 pos2)
    (at obj21 pos2)
    (at obj22 pos2)
    (at obj23 pos2)
    (at tru3 pos3)
    (at obj31 pos3)
    (at obj32 pos3)
    (at obj33 pos3)
    (at tru4 pos4)
    (at obj41 pos4)
    (at obj42 pos4)
    (at obj43 pos4)
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

    (= (travel-time cit1 cit4) 15)
    (= (travel-time cit4 cit1) 15)
    (= (travel-time cit4 cit3) 10)
    (= (travel-time cit3 cit4) 10)
    (= (travel-time cit1 cit2) 20)
    (= (travel-time cit2 cit1) 20)

    (= (travel-time pos1 apt1) 5)
    (= (travel-time apt1 pos1) 5)
    (= (travel-time pos1 petrol1) 5)
    (= (travel-time petrol1 pos1) 5)
    (= (travel-time petrol1 apt1) 5)
    (= (travel-time apt1 petrol1) 5)
    (= (travel-time pos2 apt2) 7)
    (= (travel-time apt2 pos2) 7)
    (= (travel-time pos3 apt3) 4)
    (= (travel-time apt3 pos3) 4)
    (= (travel-time pos4 apt4) 6)
    (= (travel-time apt4 pos4) 6)

    (= (flight-time apt1 apt2) 60)
    (= (flight-time apt2 apt1) 60)

    (= (flight-time apt1 apt2) 80)
    (= (flight-time apt2 apt1) 80)

    (= (flight-time apt1 apt3) 90)
    (= (flight-time apt3 apt1) 90)

    (= (flight-time apt1 apt4) 70)
    (= (flight-time apt4 apt1) 70)

    (= (flight-time apt2 apt3) 75)
    (= (flight-time apt3 apt2) 75)

    (= (flight-time apt2 apt4) 85)
    (= (flight-time apt4 apt2) 85)

    (= (flight-time apt4 apt3) 65)
    (= (flight-time apt3 apt4) 65)

  )

  (:goal
    (and (at obj31 pos3) (at obj33 apt3) (at obj41 apt3) (at obj23 pos4)
      (at obj11 pos3) (at obj22 apt2) (at obj12 apt1) (at obj21 pos4)
      (at obj42 pos4) (at obj32 pos1))
  )
)