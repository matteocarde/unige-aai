;; The trucks now have a limited amount of distance they can run

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
    (at-place ?obj - physobj ?loc - place) ;true if a phisical object (package, truck, airplane) is in a place (airport or location)
    (in ?pkg - package ?veh - vehicle) ;true if a package is in a vehicle (truck or location)
    (link ?a - city ?b - city) ;true if two cities are connected
    (is-petrol-station ?l - location) ;true if the location l is a petrol station
  )

  (:functions
    (distance ?a - city ?b - city)
    (distance-run ?t - truck)
    (max-distance ?t - truck)
  )

  ; A truck can be loaded if both the truck and the packages is at the location
  ; the result is that the package is no longer in the location but inside the truck
  (:action load-truck
    :parameters (?pkg - package ?truck - truck ?loc - place)
    :precondition (and
      (at-place ?truck ?loc)
      (at-place ?pkg ?loc)
    )
    :effect (and
      (not (at-place ?pkg ?loc))
      (in ?pkg ?truck)
    )
  )

  ; A plance can be loaded if both the plance and the packages is at the location
  ; the result is that the package is no longer in the location but inside the plance
  (:action load-airplane
    :parameters (?pkg - package ?airplane - airplane ?loc - place)
    :precondition (and
      (at-place ?pkg ?loc)
      (at-place ?airplane ?loc)
    )
    :effect (and
      (not (at-place ?pkg ?loc))
      (in ?pkg ?airplane)
    )
  )

  ; Unloading the truck if the package is inside the truck
  ; The result is that the package is at the place of the truck and no longer in the truck
  (:action unload-truck
    :parameters (?pkg - package ?truck - truck ?loc - place)
    :precondition (and
      (at-place ?truck ?loc)
      (in ?pkg ?truck)
    )
    :effect (and
      (not (in ?pkg ?truck))
      (at-place ?pkg ?loc)
    )
  )

  ; Unloading the plane if the package is inside the plane
  ; The result is that the package is at the place of the plane and no longer in the plane
  (:action unload-airplane
    :parameters (?pkg - package ?airplane - airplane ?loc - place)
    :precondition (and
      (in ?pkg ?airplane)
      (at-place ?airplane ?loc)
    )
    :effect (and
      (not (in ?pkg ?airplane))
      (at-place ?pkg ?loc)
    )
  )

  ; A truck can always drive between locations inside cities
  (:action drive-truck
    :parameters (?truck - truck ?from - place ?to - place ?city - city)
    :precondition (and
      (at-place ?truck ?from)
      (in-city ?from ?city)
      (in-city ?to ?city)
    )
    :effect (and
      (not (at-place ?truck ?from))
      (at-place ?truck ?to)
    )
  )

  (:action drive-between-cities
    :parameters (?truck - truck ?fromPlace - place ?toPlace - place ?fromCity - city ?toCity - city)
    :precondition (and
      (at-place ?truck ?fromPlace)
      (in-city ?fromPlace ?fromCity)
      (in-city ?toPlace ?toCity)
      (link ?fromCity ?toCity)
      (<= (+ (distance-run ?truck) (distance ?fromCity ?toCity)) (max-distance ?truck))
    )
    :effect (and
      (not (at-place ?truck ?fromPlace))
      (at-place ?truck ?toPlace)
      (increase
        (distance-run ?truck)
        (distance ?fromCity ?toCity))
    )
  )

  ; This action allows refueling at petrol station
  (:action refueling
    :parameters (?truck - truck ?station - location)
    :precondition (and
      (at-place ?truck ?station)
      (is-petrol-station ?station)
    )
    :effect (and
      (assign (distance-run ?truck) 0)
    )
  )

  ; A plane can only fly between cities which have an airport
  (:action fly-airplane
    :parameters (?airplane - airplane ?from - airport ?to - airport)
    :precondition (at-place ?airplane ?from)
    :effect (and
      (not (at-place ?airplane ?from))
      (at-place ?airplane ?to)
    )
  )
)