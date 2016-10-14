
/**
3.7 An animal shelter holds only dogs and cats, and operates on a strictly "first in,
first out" basis. People must adopt either the "oldest" (based on arrival time) of
all animals at the shelter, or they can select whether they would prefer a dog or
a cat (and will receive the oldest animal of that type). They cannot select which
specificanimal they would like. Create the data structures to maintain this system
and implement operations such as enqueue, dequeueAny, dequeueDog and
dequeueCat.You may use the built-in LinkedList data structure.
**/

#include<iostream>
#include<queue>
#include<climits>
using namespace std;

class animal{
private:
	queue<int> dog, cat;
	int order;
public:
	animal(){
		order = 1;
	}
	void enque(string a){
		if (a == "dog"){
			dog.push(order);
			order++;
		}
		else if (a == "cat"){
			cat.push(order);
			order++;
		}
		return;
	}
	int dequeAny(){
		int tmp;
		if (dog.front() > cat.front()){
			tmp = cat.front();
			cat.pop();
		}
		else{
			tmp = dog.front();
			dog.pop();
		}
		return tmp;
	}
	int dequeDog(){
		if (dog.empty()){
			return INT_MIN;
		}
		int tmp = dog.front();
		dog.pop();
		return tmp;
	}
	int dequeCat(){
		if (cat.empty()){
			return INT_MIN;
		}
		int tmp = cat.front();
		cat.pop();
		return tmp;

	}
};

int main(){
	animal a;
	a.enque("dog");
	a.enque("cat");
	a.enque("dog");
	a.enque("dog");
	a.enque("cat");
	a.enque("dog");
	cout << a.dequeAny() << '\n';
	cout << a.dequeDog() << '\n';
}
