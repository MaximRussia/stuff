
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

// A class for Min Heap
class MinHeap {
	int harr[256]; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:
	MinHeap();
	void MinHeapify(int);
	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }
	int extractMin();
	void decreaseKey(int i, int new_val);
	int getMin() { return harr[0]; }
	void deleteKey(int i);
	void insertKey(int k);
	void print();
};

MinHeap::MinHeap() {
	heap_size = 0;
}

void MinHeap::insertKey(int k) {
	if (heap_size == 256) {
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	while (i != 0 && harr[parent(i)] > harr[i]) {
		swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
}

void MinHeap::decreaseKey(int i, int new_val) {
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i]) {
		swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
}

int MinHeap::extractMin() {
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	int root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}

void MinHeap::deleteKey(int i) {
	decreaseKey(i, INT_MIN);
	extractMin();
}

void MinHeap::MinHeapify(int i) {
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i) {
		swap(harr[i], harr[smallest]);
		MinHeapify(smallest);
	}
}

void MinHeap::print() {
	for (int i = 0; i < heap_size; i++)
		cout << harr[i] << " ";
	cout << endl;

}

////////////////////////
// TRIE
////////////////////////
class Node {
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() { for (int i = 0; i < mChildren.size(); i++) { delete mChildren[i]; } mChildren.clear(); }
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
	for (int i = 0; i < mChildren.size(); i++) {
		Node* tmp = mChildren.at(i);
		if (tmp->content() == c) {
			return tmp;
		}
	}

	return NULL;
}

Trie::Trie() {
	root = new Node();
}

Trie::~Trie() {
	delete root; root = NULL;
}

void Trie::addWord(string s) {
	Node* current = root;

	if (s.length() == 0) {
		current->setWordMarker(); // an empty word
		return;
	}

	for (int i = 0; i < s.length(); i++) {
		Node* child = current->findChild(s[i]);
		if (child != NULL) {
			current = child;
		}
		else {
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
		if (i == s.length() - 1)
			current->setWordMarker();
	}
}


bool Trie::searchWord(string s) {
	Node* current = root;

	while (current != NULL) {
		for (int i = 0; i < s.length(); i++) {
			Node* tmp = current->findChild(s[i]);
			if (tmp == NULL)
				return false;
			current = tmp;
		}

		if (current->wordMarker())
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

	MinHeap h;
	h.insertKey(3);
	h.insertKey(2);
	h.insertKey(15);
	h.insertKey(5);
	h.insertKey(4);
	h.insertKey(45);
	cout << h.getMin() << endl;
	h.print();

	h.extractMin();
	cout << h.getMin() << endl;
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

	if (trie->searchWord("Hell"))
		cout << "Found Hell" << endl;

	if (trie->searchWord("Hello"))
		cout << "Found Hello" << endl;

	if (trie->searchWord("Helloo"))
		cout << "Found Helloo" << endl;

	if (trie->searchWord("Ball"))
		cout << "Found Ball" << endl;

	if (trie->searchWord("Balloon"))
		cout << "Found Balloon" << endl;

	delete trie;

	cout << endl;

	return 0;
}
