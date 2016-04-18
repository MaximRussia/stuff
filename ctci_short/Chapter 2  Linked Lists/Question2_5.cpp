#include <iostream>
#include <cmath>
#include "LinkedList.h"

/**
2.5 You have two numbers represented by a linked list, where each node contains a
single digit. The digits are stored in reverse order, such that the Ts digit is at the
head of the list. Write a function that adds the two numbers and returns the sum
as a linked list.
EXAMPLE
Input: (7-> 1 -> 6) + (5 -> 9 -> 2).That is, 617 + 295.
Output: 2 -> 1 -> 9.That is, 912.
FOLLOW UP
Suppose the digits are stored in forward order. Repeat the above problem.
EXAMPLE
Input: (6 -> 1 -> 7) + (2 -> 9 -> 5).That is, 617 + 295.
Output: 9 -> 1 -> 2.That is, 912.
**/

/*implementation runs in O(n) time with O(1) space by overwriting one of the
 original lists. It is an iterative implementation that handles numbers of
 different lengths.
 for part B (if the lists are in forward order) simply reversing the list
 in O(n) time and running the same algorithm does the trick
*/
int lenList(Node* head);
void padList(Node* head, int pad);

void sumLinks(Node* list1, Node* list2) {
    if (list1 == NULL && list2 == NULL) return;

    int carry = 0;
    int val = 0;
    Node* l1 = list1;
    Node* l2 = list2;

    /// determine if a list is longer and if so, pad that list
    int l1Len = lenList(l1);
    int l2Len = lenList(l2);

    if (l1Len > l2Len) {
        padList(l2, l1Len - l2Len);
    }

    if (l2Len > l1Len) {
        padList(l1, l2Len - l1Len);
    }


    while (l1 || l2) {
        l1->data += carry;

        val = l1->data + l2->data;

        if (val > 9) {
            carry = 1;
            val = val - 10;
        }
        else {
            carry = 0;
        }

        l1->data = val;

        l1 = l1->next;
        l2 = l2->next;
    }

    /// if the final digit had a carry we need to add one to the end
    if (carry) {
        /// reset the head and find the last element
        l1 = list1;
        while (l1->next) {
            l1 = l1->next;
        }

        l1->next = new Node();
        l1->next->data = 1;
        l1->next->next = nullptr;
    }
}

/// helper function to display to list value normally
int listValue(Node* head) {
    int value = 0;
    double digit = 0;
    Node* temp = head;

    /// I did this implementation because I wanted to avoid O(n) space
    while (temp) {
        value += pow(10.0,digit) * temp->data;
        digit++;
        temp = temp->next;
    }

    return value;
}

/// helper function to determine the length of a list
int lenList(Node* head) {
    Node* temp = head;
    int len = 0;

    while (temp) {
        temp = temp->next;
        len++;
    }

    return len;
}

/// helper function to pad the list with a different length with 0 zeros
void padList(Node* list, int pad) {
    int count = 0;
    Node* temp = list;

    /// get to the end of the list
    while (temp->next) {
        temp = temp->next;
    }

    while (count != pad) {
        temp->next = new Node();
        temp = temp->next;
        temp->data = 0;
        temp->next = nullptr;
        count++;
    }
}

/// this is used for partB
Node* reverse(Node* head) {
    if (head == NULL) {
        return nullptr;
    }

    Node* previous = nullptr;

    while (head) {
        Node* temp = head->next;
        head->next = previous;
        previous = head;
        head = temp;
    }

    head = previous;

    return head;
}

int main() {
    LinkedList* list1 = new LinkedList();
    list1->insert(5);
    list1->insert(3);
    list1->insert(6);

    LinkedList* list2 = new LinkedList();
    list2->insert(2);
    list2->insert(1);
    list2->insert(6);

    std::cout << listValue(list1->head) << " + " << listValue(list2->head) << " = ";
    sumLinks(list1->head,list2->head);
    std::cout << listValue(list1->head) << std::endl;
    delete list1;
    delete list2;
    std::cout << std::endl;

    LinkedList* list3 = new LinkedList();
    list3->insert(7);
    list3->insert(4);
    list3->insert(2);
    list3->insert(8);
    list3->insert(9);

    LinkedList* list4 = new LinkedList();
    list4->insert(2);
    list4->insert(6);

    std::cout << listValue(list3->head) << " + " << listValue(list4->head) << " = ";
    sumLinks(list3->head,list4->head);
    std::cout << listValue(list3->head) << std::endl;
    delete list3;
    delete list4;

    LinkedList* list5 = new LinkedList();
    list5->insert(7);
    list5->insert(4);
    list5->insert(2);
    list5->insert(8);
    list5->insert(9);

    LinkedList* list6 = new LinkedList();
    list6->insert(2);
    list6->insert(6);

    std::cout << std::endl << "-- Now with lists that are originally in forward order --" << std::endl;
    list5->head = reverse(list5->head);
    list6->head = reverse(list6->head);
    std::cout << listValue(list5->head) << " + " << listValue(list6->head) << " = ";
    sumLinks(list5->head,list6->head);
    std::cout << listValue(list5->head) << std::endl;
    delete list5;
    delete list6;

    return 0;
}
