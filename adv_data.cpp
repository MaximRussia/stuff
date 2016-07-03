
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <climits>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

using namespace std;

/////////////////////////////////
// HEAP
/////////////////////////////////

class PriorityQueue {
    vector<int> pq_keys;
    void shiftRight(int low, int high);
    void shiftLeft(int low, int high);
    void buildHeap();
public:
    PriorityQueue(){}
    PriorityQueue(vector<int>& items) {
        pq_keys = items;
        buildHeap();
    }
    /*Insert a new item into the priority queue*/
    void enqueue(int item);
    /*Get the maximum element from the priority queue*/
    int dequeue();
    /*Just for testing*/
    void print();
    int get_max();
};

void PriorityQueue::enqueue(int item) {
    pq_keys.push_back(item);
    shiftLeft(0, pq_keys.size() - 1);
    return;
}

int PriorityQueue::dequeue() {
    assert(pq_keys.size() != 0);
    int last = pq_keys.size() - 1;
    int tmp = pq_keys[0];
    pq_keys[0] = pq_keys[last];
    pq_keys[last] = tmp;
    pq_keys.pop_back();
    shiftRight(0, last-1);
    return tmp;
}

int PriorityQueue::get_max() {
    assert(pq_keys.size() != 0);
    return pq_keys[0];
}

void PriorityQueue::print() {
    int size = pq_keys.size();
    for (int i = 0; i < size; ++i) {
        cout << pq_keys[i] << " ";
    }
    cout << endl;
}

void PriorityQueue::shiftLeft(int low, int high) {

    while (high > low) {
        int parentIdx = (high-1)/2;
        /*if child is bigger than parent we need to swap*/
        if (pq_keys[high] > pq_keys[parentIdx]) {
            swap(pq_keys[high], pq_keys[parentIdx]);
            /*Make parent index the child and shift towards left*/
            high = parentIdx;
        }
        else {
            break;
        }
    }
    return;
}

void PriorityQueue::shiftRight(int low, int high) {

    while ((low*2)+1 <= high) {
        int leftChild = (low*2)+1;
        int rightChild = leftChild + 1;
        int swapIdx = low;
        /*Check if low is less than left child*/
        if (pq_keys[swapIdx] < pq_keys[leftChild]) {
            swapIdx = leftChild;
        }
        /*If right child exists check if it is less than current low*/
        if ((rightChild <= high) && (pq_keys[swapIdx] < pq_keys[rightChild])) {
            swapIdx = rightChild;
        }
        /*Make the biggest element of low, left and right child the low*/
        if (swapIdx != low) {
            swap(pq_keys[low], pq_keys[swapIdx]);
            /*
            Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself
            */
            low = swapIdx;
        }
        else {
            break;
        }
    }
    return;
}

void PriorityQueue::buildHeap() {
    /*
    Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child
    */
    int size = pq_keys.size();
    int midIdx = (size-2)/2;
    while (midIdx >= 0) {
        shiftRight(midIdx, size-1);
        --midIdx;
    }
    return;
}

////////////////////////
// TRIE
////////////////////////
class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() { for(int i = 0; i < mChildren.size(); i++) { delete mChildren[i]; } mChildren.clear(); }
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

Node* Node::findChild(char c) {
    for ( int i = 0; i < mChildren.size(); i++ ) {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c ) {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie() {
    root = new Node();
}

Trie::~Trie() {
    // Free memory
    delete root; root = NULL;
}

void Trie::addWord(string s) {
    Node* current = root;

    if ( s.length() == 0 ) {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ ) {
        Node* child = current->findChild(s[i]);
        if ( child != NULL ) {
            current = child;
        }
        else {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


bool Trie::searchWord(string s) {
    Node* current = root;

    while ( current != NULL ) {
        for ( int i = 0; i < s.length(); i++ ) {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}
////////////////////////

int main() {
	
    cout << "/////////////////////////////////" << endl;
    cout << "// HEAP" << endl;
    cout << "/////////////////////////////////" << endl;

    PriorityQueue h;
    h.enqueue(3);
    h.enqueue(2);
    h.enqueue(15);
    h.enqueue(5);
    h.enqueue(4);
    h.enqueue(45);
    cout << h.get_max() << endl;
    h.print();

    h.dequeue();
    cout << h.get_max() << endl;
    h.print();

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// TRIE" << endl;
    cout << "/////////////////////////////////" << endl;

   /**
            *
        H       B
        E       A
        L       L
        L       L^
        O^      O
                O
                N^
    **/

    Trie* trie = new Trie();
    trie->addWord("Hello");
    trie->addWord("Balloon");
    trie->addWord("Ball");

    if ( trie->searchWord("Hell") )
        cout << "Found Hell" << endl;

    if ( trie->searchWord("Hello") )
        cout << "Found Hello" << endl;

    if ( trie->searchWord("Helloo") )
        cout << "Found Helloo" << endl;

    if ( trie->searchWord("Ball") )
        cout << "Found Ball" << endl;

    if ( trie->searchWord("Balloon") )
        cout << "Found Balloon" << endl;

    delete trie;

    cout << endl;
	
	return 0;
}