#ifndef __LINKEDLIST_h__
#define __LINKEDLIST_h__

struct Node
{
    int data;
    Node* next;
};

class LinkedList
{
    public:
        Node* head;
        LinkedList();
        ~LinkedList();
        void display();
        void insert(int value);
        void createCycle();
    private:
    // added this so insertion is O(1) time
        Node* tail;
};

/// runs in O(1) time with O(1) space (note: this is only true if you are not iterating through the list)
bool removeNode(Node* &node) {
    if (node == NULL || node->next == NULL) return false;

    /// copy the next nodes information to the current
    /// node and then delete the next node updating the pointers
    Node* temp = node->next;
    node->data = temp->data;
    node->next = temp->next;
    delete temp;

    return true;
}

bool removeNextNode(Node* &node) {
    if(!node && !node->next) return false;
    Node* temp = node->next;
    node->next = node->next->next;
    delete temp;
}


////////////////////////////////////////////////////



LinkedList::LinkedList()
{
    this->head = nullptr;
}

LinkedList::~LinkedList()
{
    Node* current = head;

    while (current != 0)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;

    std::cout << "List successfully deleted from memory" << std::endl;
}

void LinkedList::insert(int value)
{
    if (head == NULL)
    {
        head = new Node();
        tail = head;
        head->next = nullptr;
        head->data = value;
    }
    else
    {
        tail->next = new Node();
        tail = tail->next;
        tail->data = value;
        tail->next = nullptr;
    }
}

void LinkedList::createCycle()
{
    tail->next = head->next->next;
}

void LinkedList::display()
{
    Node* temp;

    if (head == NULL)
    {
        return;
    }

    temp = head;

    while (temp != NULL)
    {
        std::cout << temp->data << ' ';
        temp = temp->next;
    }

    std::cout << std::endl;
}

#endif // __LINKEDLIST_h__
