(define (problem pb1)
	(:domain robot)
	(:objects
		roomA - room
		roomB - room
		roomC - room
		ball1 - obj
		ball2 - obj
		ball3 - obj
		ball4 - obj
		eve - robot
		wally - robot
		eve_left - gripper
		eve_right - gripper
		wally_left - gripper
		wally_right - gripper
	)
	(:init
		(at-robot wally roomA)
		(at-robot eve roomB)
		(free wally_left)
		(free wally_right)
		(free eve_left)
		(free eve_right)
		(of-robot wally wally_left)
		(of-robot wally wally_right)
		(of-robot eve eve_left)
		(of-robot eve eve_right)
		(at-obj ball1 roomA)
		(at-obj ball2 roomA)
		(at-obj ball3 roomA)
		(at-obj ball4 roomA)
		(allowed wally roomA)
		(allowed wally roomB)
		(allowed eve roomB)
		(allowed eve roomC)
	)
	(:goal
		(and (at-obj ball1 roomC)
			(at-obj ball2 roomC)
			(at-obj ball3 roomC)
			(at-obj ball4 roomC))
	)
)