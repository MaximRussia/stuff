
/**
3.3 Imagine a (literal) stack of plates. If the stack gets too high, it might topple.
Therefore, in real life, we would likely start a new stack when the previous stack
exceeds some threshold. Implement a data structure SetOf Stacks that mimics
this. SetOf Stacks should be composed of several stacks and should create a
new stack once the previous one exceeds capacity. SetOf Stacks. push() and
SetOf Stacks. pop() should behave identically to a single stack (that is, popO
should return the same values as it would if there were just a single stack).
FOLLOW UP
Implement a function popAt(int index) which performs a pop operation on
a specific sub-stack.
**/

#include<iostream>
#include<stack>
#include<climits>
using namespace std;
#define STACK_NUM 100

class newStack{
private:
	stack<int> *myStack;
	int threshold;
	int curStack;
public:
	newStack(){
		threshold = 10;
		myStack = new stack<int>[STACK_NUM];
		curStack = 0;
	}
	void push(int data){
		if (myStack[curStack].size() >= threshold){
			curStack++;
		}
		myStack[curStack].push(data);
	}
	void pop(){
		if (myStack[curStack].empty()){
			if (curStack == 0){
				cout << "Stack is empty\n";
				return;
			}
			curStack--;
		}
		myStack[curStack].pop();
	}
	int top(){
		if (myStack[curStack].empty()){
			if (curStack == 0){
				return INT_MIN;
			}
			curStack--;
		}
		return myStack[curStack].top();
	}
	bool empty(){
		if (curStack == 0){
			return myStack[curStack].empty();
		}
		else
			return false;
	}
	void popAt(int index){
		if (myStack[index].empty()){
			cout << "sub-stack " << index << " is empty" << '\n';
			return;
		}
		myStack[index].pop();
	}
};

int main(){
	newStack sta;
	for (int i = 0; i < 100; i++)
		sta.push(i);
	sta.popAt(4);
	for (int i = 0; i < 101; i++){
		cout << sta.top() << '\n';
		sta.pop();
	}
	return 0;
}
