;; logistics domain Typed version.
;;

(define (domain logistics)
  (:requirements :strips :typing)
  (:types
    truck airplane - vehicle
    package vehicle - physobj
    airport location - place
    city place physobj - object
  )

  (:predicates
    (in-city ?loc - place ?city - city) ;If a place (airport or location) is in a city
    (at ?obj - physobj ?loc - place) ;true if a phisical object (package, truck, airplane) is in a place (airport or location)
    (in ?pkg - package ?veh - vehicle) ;true if a package is in a vehicle (truck or location)
    (link ?a - city ?b - city) ;true if two cities are connected
  )

  ; A truck can be loaded if both the truck and the packages is at the location
  ; the result is that the package is no longer in the location but inside the truck
  (:action load-truck
    :parameters (?pkg - package ?truck - truck ?loc - place)
    :precondition (and
      (at ?truck ?loc)
      (at ?pkg ?loc)
    )
    :effect (and
      (not (at ?pkg ?loc))
      (in ?pkg ?truck)
    )
  )

  ; A plance can be loaded if both the plance and the packages is at the location
  ; the result is that the package is no longer in the location but inside the plance
  (:action load-airplane
    :parameters (?pkg - package ?airplane - airplane ?loc - place)
    :precondition (and
      (at ?pkg ?loc)
      (at ?airplane ?loc)
    )
    :effect (and
      (not (at ?pkg ?loc))
      (in ?pkg ?airplane)
    )
  )

  ; Unloading the truck if the package is inside the truck
  ; The result is that the package is at the place of the truck and no longer in the truck
  (:action unload-truck
    :parameters (?pkg - package ?truck - truck ?loc - place)
    :precondition (and
      (at ?truck ?loc)
      (in ?pkg ?truck)
    )
    :effect (and
      (not (in ?pkg ?truck))
      (at ?pkg ?loc)
    )
  )

  ; Unloading the plane if the package is inside the plane
  ; The result is that the package is at the place of the plane and no longer in the plane
  (:action unload-airplane
    :parameters (?pkg - package ?airplane - airplane ?loc - place)
    :precondition (and
      (in ?pkg ?airplane)
      (at ?airplane ?loc)
    )
    :effect (and
      (not (in ?pkg ?airplane))
      (at ?pkg ?loc)
    )
  )

  ; A truck can always drive between locations inside cities
  (:action drive-truck
    :parameters (?truck - truck ?from - place ?to - place ?city - city)
    :precondition (and
      (at ?truck ?from)
      (in-city ?from ?city)
      (in-city ?to ?city)
    )
    :effect (and
      (not (at ?truck ?from))
      (at ?truck ?to)
    )
  )

  (:action drive-between-cities
    :parameters (?truck - truck ?fromPlace - place ?toPlace - place ?fromCity - city ?toCity - city)
    :precondition (and
      (at ?truck ?fromPlace)
      (in-city ?fromPlace ?fromCity)
      (in-city ?toPlace ?toCity)
      (link ?fromCity ?toCity)
    )
    :effect (and
      (not (at ?truck ?fromPlace))
      (at ?truck ?toPlace)
    )
  )

  ; A plane can only fly between cities which have an airport
  (:action fly-airplane
    :parameters (?airplane - airplane ?from - airport ?to - airport)
    :precondition (at ?airplane ?from)
    :effect (and
      (not (at ?airplane ?from))
      (at ?airplane ?to)
    )
  )
)