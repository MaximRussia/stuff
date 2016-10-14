
#include <iostream>
#include <unordered_map>
#include "LinkedList.h"

/**
2.1 Write code to remove duplicates from an unsorted linked list.
FOLLOW UP
How would you solve this problem if a temporary buffer is not allowed?
**/
/// First implementation uses undordered_map run time is O(n) with O(n) space
void removeDuplicates_1(Node* head) {
	if (head == NULL) return;

	std::unordered_map<int, bool> map;
	Node* current = head;
	map[current->data] = 1;

	while (current->next) {
		if (map[current->next->data] == 0) {
			map[current->next->data] = 1;
			current = current->next;
		}
		else {
			std::cout << "Duplicate Found: " << current->next->data << " removed" << std::endl;
			removeNextNode(current);
		}
	}
}

/// This implementation uses no additional data structure run time is O(n^2) with O(1) space
void removeDuplicates_2(Node* head) {
	if (head == NULL) return;

	Node* current = head;
	Node* runner;

	while (current) {
		runner = current;

		while (runner->next) {
			if (current->data == runner->next->data) {
				std::cout << "Duplicate Found: " << runner->next->data << " removed" << std::endl;
				removeNextNode(runner);
			}
			else {
				runner = runner->next;
			}
		}

		current = current->next;
	}
}


int main() {
	LinkedList* myList = new LinkedList();
	myList->insert(5);
	myList->insert(7);
	myList->insert(12);
	myList->insert(7);
	myList->insert(16);
	myList->insert(16);
	myList->insert(25);
	myList->insert(11);
	myList->insert(5);

	std::cout << "The original list is: ";
	myList->display();

	/// change to removeDuplicates_2 to run that implementation
	removeDuplicates_2(myList->head);

	std::cout << "The list with duplicated removed is: ";
	myList->display();
	delete myList;

	return 0;
}
