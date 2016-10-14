
/**
	Given two lines on a Cartesian plane, determine whether the two lines would inter-
	sect.
	**/

/**
In problems like these, be aware of the following:
• Ask questions. This question has a lot of unknowns—ask questions to clarify them.
Many interviewers intentionally ask vague questions to see if you'll clarify your
assumptions.
• When possible, design and use data structures. It shows that you understand and
care about object-oriented design.
• Think through which data structures you design to represent a line.There are a lot of
options, with lots of trade-offs. Pick one, and explain your choice.
• Don't assume that the slope and y-intercept are integers.
• Understand limitations of floating point representations. Never check for equality
with ==. Instead, check if the difference is less than an epsilon value.
**/

///If two different lines are not parallel, then they intersect. Thus, to check if two lines inter-
///sect, we just need to check if the slopes are different (or if the lines are identical)

class Line {
	static double epsilon = 0.000001;
public:
	double slope;
	double yintercept;

	Line(double s, double y) {
		slope = s;
		yintercept = y;
	}

	bool intersect(Line lne2) {
		return Math.abs(slope - line2.slope) > epsilon ||
			Math.abs(yintercept - line2.yintercept) < epsilon;
	}
}
