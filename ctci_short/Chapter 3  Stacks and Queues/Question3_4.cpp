
/**
3.4 In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of
different sizes which can slide onto any tower. The puzzle starts with disks sorted
in ascending order of size from top to bottom (i.e., each disk sits on top of an
even larger one). You have the following constraints:
(1) Only one disk can be moved at a time.
(2) A disk is slid off the top of one tower onto the next tower.
(3) A disk can only be placed on top of a larger disk.
Write a program to move the disks from the first tower to the last using stacks.

**/

#include<iostream>
#include<stack>
using namespace std;

void towerOfHanoi(stack<int> &a, stack<int> &buff, stack<int> &dest, int n){
	if (n == 0){
		return;
	}
	towerOfHanoi(a, dest, buff, n - 1);
	dest.push(a.top());
	a.pop();
	towerOfHanoi(buff, a, dest, n - 1);
}

int main(){
	stack<int> primary, buffer, destination;
	int n = 10;
	for (int i = n; i > 0; i--)
		primary.push(i);
	towerOfHanoi(primary, buffer, destination, 10);
	while (!destination.empty()){
		cout << destination.top() << " ";
		destination.pop();
	}
}
