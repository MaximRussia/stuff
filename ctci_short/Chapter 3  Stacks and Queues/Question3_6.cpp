#include<iostream>
#include<stack>
using namespace std;

/**
3.6 Write a program to sort a stack in ascending order (with biggest items on top).
You may use at most one additional stack to hold items, but you may not copy
the elements into any other data structure (such as an array). The stack supports
the following operations: push, pop, peek, and isEmpty.
**/

void sortStack(stack<int> &st){
	stack<int> sorted; //top contains smallest element
	while (!st.empty()){
		int tmp = st.top();
		st.pop();
		while (!sorted.empty() && tmp > sorted.top()){
			st.push(sorted.top());
			sorted.pop();
		}
		sorted.push(tmp);
	}
	while (!sorted.empty()){
		st.push(sorted.top());
		sorted.pop();
	}
}

int main(){
	stack<int> my;
	int arr[] = { 6, 4, 8, 9, 10, 99, 7, 1, 0 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++){
		my.push(arr[i]);
	}
	sortStack(my);
	while (!my.empty()){
		cout << my.top() << '\n';
		my.pop();
	}
}
