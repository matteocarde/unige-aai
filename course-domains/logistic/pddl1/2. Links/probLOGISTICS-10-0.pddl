(define (problem logistics-10-0)
  (:domain logistics)
  (:objects
    apn1 - airplane
    apt1 apt4 apt3 apt2 - airport
    pos4 pos3 pos2 pos1 - location
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
    (link cit1 cit4)
    (link cit4 cit1)
    (link cit4 cit3)
    (link cit3 cit4)
    (link cit1 cit2)
    (link cit2 cit1)
  )

  (:goal
    (and (at obj31 pos3) (at obj33 apt3) (at obj41 apt3) (at obj23 pos4)
      (at obj11 pos3) (at obj22 apt2) (at obj12 apt1) (at obj21 pos4)
      (at obj42 pos4) (at obj32 pos1))
  )
)