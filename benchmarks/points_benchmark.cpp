// A divide and conquer program in C/C++ to find the smallest distance from a
// given set of points.

/**********
1) We sort all points according to x coordinates.

2) Divide all points in two halves.

3) Recursively find the smallest distances in both subarrays.

4) Take the minimum of two smallest distances. Let the minimum be d.

5) Create an array strip[] that stores all points which are at most d distance away from the middle line dividing the two sets.

6) Find the smallest distance in strip[].

7) Return the minimum of d and the smallest distance calculated in above step 6.

The great thing about the above approach is, if the array strip[] is sorted according to y coordinate, then we can find the smallest distance in strip[] in O(n) time. In the implementation discussed in previous post, strip[] was explicitly sorted in every recursive call that made the time complexity O(n (Logn)^2), assuming that the sorting step takes O(nLogn) time.
In this post, we discuss an implementation where the time complexity is O(nLogn). The idea is to presort all points according to y coordinates. Let the sorted array be Py[]. When we make recursive calls, we need to divide points of Py[] also according to the vertical line. We can do that by simply processing every point and comparing its x coordinate with x coordinate of middle line.

Following is C++ implementation of O(nLogn) approach.
***********/
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

struct Point {
	int x, y;
};

int compareX(const void* a, const void* b) {
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->x - p2->x);
}

int compareY(const void* a, const void* b) {
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->y - p2->y);
}

float dist(Point p1, Point p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y)
		);
}

float bruteForce(Point P[], int n) {
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
	for (int j = i + 1; j < n; ++j)
	if (dist(P[i], P[j]) < min)
		min = dist(P[i], P[j]);
	return min;
}

float min(float x, float y) {
	return (x < y) ? x : y;
}


float stripClosest(Point strip[], int size, float d) {
	float min = d;  // Initialize the minimum distance as d
	qsort(strip, size, sizeof(Point), compareY);

	// Pick all points one by one and try the next points till the difference
	// between y coordinates is smaller than d.
	// This is a proven fact that this loop runs at most 6 times
	for (int i = 0; i < size; ++i)
	for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
	if (dist(strip[i], strip[j]) < min)
		min = dist(strip[i], strip[j]);

	return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate
float closestUtil(Point P[], int n) {
	// If there are 2 or 3 points, then use brute force
	if (n <= 3)
		return bruteForce(P, n);

	// Find the middle point
	int mid = n / 2;
	Point midPoint = P[mid];

	// Consider the vertical line passing through the middle point
	// calculate the smallest distance dl on left of middle point and
	// dr on right side
	float dl = closestUtil(P, mid);
	float dr = closestUtil(P + mid, n - mid);

	// Find the smaller of two distances
	float d = min(dl, dr);

	// Build an array strip[] that contains points close (closer than d)
	// to the line passing through the middle point
	Point strip[n];
	int j = 0;
	for (int i = 0; i < n; i++)
	if (abs(P[i].x - midPoint.x) < d)
		strip[j] = P[i], j++;

	// Find the closest points in strip.  Return the minimum of d and closest
	// distance is strip[]
	return min(d, stripClosest(strip, j, d));
}

// The main functin that finds the smallest distance
// This method mainly uses closestUtil()
float closest(Point P[], int n) {
	qsort(P, n, sizeof(Point), compareX);

	// Use recursive function closestUtil() to find the smallest distance
	return closestUtil(P, n);
}

// Driver program to test above functions
int main() {
	const int inputsize = 15000;

	srand((unsigned)time(0));
	cout << "Init arrays ... size " << inputsize << endl;
	Point P[inputsize];

	for (int i = 0; i < inputsize; i++) {
		P[i].x = 1 + (rand() % 9999);
		P[i].y = 1 + (rand() % 9999);
	}

	{
		time_t t1 = clock();
		float res = closest(P, inputsize);
		time_t t2 = clock();
		printf("The smallest distance is %f (time = %f)\n", res, float(t2 - t1) / CLOCKS_PER_SEC);
	}

	for (int i = 0; i < inputsize; i++) {
		P[i].x = 1 + (rand() % 9999);
		P[i].y = 1 + (rand() % 9999);
	}

	{
		time_t t1 = clock();
		float res = bruteForce(P, inputsize);
		time_t t2 = clock();
		printf("The smallest distance is %f (time = %f)\n", res, float(t2 - t1) / CLOCKS_PER_SEC);	
	}
	return 0;
}
