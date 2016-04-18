#include <string>
#include <map>
#include <cmath>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

template<typename T>
class SingleLinkedList {

    struct ListNode {
        T v;
        ListNode* next;
        ListNode() : v(0), next(nullptr) {}
        ListNode(T v) : v(v), next(nullptr) {}
    };

    ListNode *head;

public:
    SingleLinkedList() : head(nullptr) {}
    SingleLinkedList(const SingleLinkedList &list) : head(nullptr) {
        this->Clone(list.GetHead());
    }

    SingleLinkedList(SingleLinkedList &&list) : head(nullptr) {
        this->Clone(list.GetHead());
    }

    virtual ~SingleLinkedList() {
        this->Clean();
    }

    void PushBack(T v) {
        if(!head) {
            head = new ListNode(v);
            return;
        }

        ListNode* first = head;

        while(first->next) {
            first = first->next;
        }

        first->next = new ListNode(v);
    }

    void Reverse() {
        if(Empty()) return;

        ListNode* prev = nullptr;
        ListNode* first = head;

        while(first) {
            ListNode* next = first->next;
            first->next = prev;
            prev = first;
            first = next;
        }
        head = prev;
    }

    void SelectionSort() {
        if(Empty()) return;

        ListNode* first = head;
        while(first) {
            ListNode* second = first;
            ListNode* remove = first;
            while(second) {
                if(second->v < first->v) {
                    remove = second;
                }
                second = second->next;
            }

            if(remove != first) {
                swap(remove->v, first->v);
            }

            first = first->next;
        }
    }

    string ToString() {
        if(Empty()) return "Empty!";

        ostringstream res;
        res << "[ ";

        ListNode* first = head;
        while(first) {
            res << first->v;
            first = first->next;
            if(first) {
            res << ", ";
            }
        }

        res << " ]";
        return res.str();
    }

    void Clean() {
        if(Empty()) return;

        ListNode* tmp = head;

        while(tmp) {
            head = head->next;
            delete tmp;
            tmp = nullptr;
            tmp = head;
        }
    }

    ListNode* GetHead() {
        if(Empty()) return nullptr;

        return head;
    }

    size_t GetSize() {
        if(Empty()) return 0;

        size_t i = 0;
        ListNode* first = head;

        while(first) {
            i++;
            first = first->next;
        }

        return i;
    }

    bool Empty() const {
        return nullptr == head;
    }

    void Clone(SingleLinkedList<T> &list) {
        if(list.Empty()) return;

        if(head) {
            Clean();
        }

        ListNode* first = list.GetHead();

        while(first) {
            PushBack(first->v);
            first = first->next;
        }
    }

    ListNode* Get_K_FromLast(size_t k) {
        if(Empty()) return nullptr;

        ListNode* first = head;

        while(k && first) {
            k--;
            first = first->next;
        }

        if(!first) return nullptr;

        ListNode* res = head;

        while(first) {
            res = res->next;
            first = first->next;
        }

        return res;
    }
};

int main() {


    SingleLinkedList<int> l1;
    SingleLinkedList<int> l2;

    for(int i = 0; i < 10; i++) l1.PushBack(i);
    for(int i = 10; i > 0; i--) l2.PushBack(i);

    cout << l1.ToString() << endl;

    l1.Clone(l2);

    cout << l1.ToString() << endl;

    l1.SelectionSort();

    cout << l1.ToString() << endl;

    l1.Reverse();

    cout << l1.ToString() << endl;

    cout << l1.GetSize() << endl;

    cout << l1.Get_K_FromLast(5)->v << endl;

    cout << endl << endl;

    return 0;
}
