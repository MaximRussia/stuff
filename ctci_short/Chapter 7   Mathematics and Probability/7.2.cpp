
/**
	There are three ants on different vertices of a triangle. What is the probability of
	collision (between any two or all of them) if they start walking on the sides of the
	triangle? Assume that each ant randomly picks a direction, with either direction
	being equally likely to be chosen, and that they walk at the same speed.
	Similarly, find the probability of collision with n ants on an n-vertex polygon.
	**/

/**
	3 ants
	p(clocwise) = 0.5*0.5*0.5 = (0,5)^3
	p(counterclocwise) = 0.5*0.5*0.5 = (0,5)^3
	p(same direction) = 0.5*0.5*0.5 + 0.5*0.5*0.5 = (0,5)^3 + (0,5)^3 = 0.25
	p(collition) = 1 - 0.25 = 0.75

	LEVEL UP:
	To generalize this to an n-vertex polygon: there are still only two ways in which the ants
	can move to avoid a collision, but there are 2n ways they can move in total.Therefore, in
	general, probability of collision is:
	P (clockwise) = (1/2)^n
	P (counter) = (1/2)^n
	P (same direction) = 2*(1/2)^n = (1/2)^(n-1)
	P (collision) = 1 - P(same direction) = 1 - (1/2)^(n-1)
	**/
