#include <iostream>
#include "LinkedList.h"

/**
2.3 Implement an algorithm to delete a node in the middle of a singly linked list,
given only access to that node.
EXAMPLE
Input: the node c from the linked list a->b->c->d->e
Result: nothing is returned, but the new linked list looks like a- >b- >d->e
**/

int main() {
	LinkedList* myList = new LinkedList();
	myList->insert(5);
	myList->insert(7);
	myList->insert(12);
	myList->insert(7);
	myList->insert(16);
	myList->insert(18);
	myList->insert(25);
	myList->insert(11);
	myList->insert(5);

	/// just get a node in the list
	Node* temp = myList->head->next->next->next->next;

	std::cout << "The original list is: ";
	myList->display();

	std::cout << "Removing node with value: " << temp->data << std::endl;
	removeNode(temp);

	std::cout << "The new list is: ";
	myList->display();

	delete myList;

	return 0;
}
