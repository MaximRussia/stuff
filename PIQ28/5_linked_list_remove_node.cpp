
/**
	Linked List Remove Nodes

	Given a linkedlist of integers and an integer value, 
	delete every node of the linkedlist containing
	that value.
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

struct Node {
	int val;
	Node *next;
};

void RemoveNodesWithValue(Node* head, int k) {
	Node* toDelete;
	while (head != NULL) {
		if (head->data == k) {
			toDelete = head;
			head = head->next;
			delete toDelete;
		}
		else {
			head = head->next;
		}
	}
}

int main() {

	return 0;
}
