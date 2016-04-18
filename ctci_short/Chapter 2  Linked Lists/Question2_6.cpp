#include <iostream>
#include "LinkedList.h"

/**
2.6 Given a circular linked list, implement an algorithm which returns the node at
the beginning of the loop.
DEFINITION
Circular linked list: A (corrupt) linked list in which a node's next pointer points
to an earlier node, so as to make a loop in the linked list.
EXAMPLE
Input: A ->B->C->D->E-> C [the same C as earlier]
Output: C
**/

/// runs in O(n) time with O(1) space
Node* findCycleBegin(Node* head) {
    if (head == NULL) return nullptr;

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) /// a collision
            return slow;
    }

    /// once they meet, they are at the start of the loop
    return NULL;
}

int main()
{
    LinkedList* list1 = new LinkedList();
    list1->insert(5);
    list1->insert(3);
    list1->insert(6);
    list1->insert(8);
    list1->insert(1);
    list1->insert(2);

    std::cout << "For the list: ";
    list1->display();
    std::cout << "A cycle begins at value: ";

    /// create a cycle in the list
    list1->createCycle();

    Node* beginCycle = findCycleBegin(list1->head);
    std::cout << beginCycle->data << std::endl;

    return 0;
}
