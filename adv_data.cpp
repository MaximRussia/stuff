
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
	if (heap_size == 1) {
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
	if (l < heap_size && harr[l] < harr[smallest])
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

//////////////////////////////////
// Fenwick Tree. A Fenwick Tree is a data structure that represents
// an array of n numbers. It supports adjusting the i-th element in O(log n)
// time, and computing the sum of numbers in the range i..j in O(log n)
// time. It only needs O(n) space.
//////////////////////////////////

struct fenwick_tree {
    int n;
    vector<int> data;

    fenwick_tree(int _n) : n(_n), data(vector<int>(n)) { }

    void update(int at, int by) {
        while (at < n) data[at] += by, at |= at + 1; /// 2*at + 1
    }

    int query(int at) {
        int res = 0;
        while (at >= 0) res += data[at], at = (at & (at + 1)) - 1; /// tricky around power of 2 (-1 when get pow of 2)
        return res;
    }

    int rsq(int a, int b) { return query(b) - query(a - 1); }
};

struct fenwick_tree_sq {
    int n;
    fenwick_tree x1, x0;

    fenwick_tree_sq(int _n) :
        n(_n), x1(fenwick_tree(n)), x0(fenwick_tree(n)) { }

    void update(int x, int m, int c) {
        x1.update(x, m);
        x0.update(x, c);
    }

    int query(int x) { return x*x1.query(x) + x0.query(x); }
};

void range_update(fenwick_tree_sq &s, int a, int b, int k) {
    s.update(a, k, k * (1 - a));
    s.update(b+1, -k, k * b);
}

int range_query(fenwick_tree_sq &s, int a, int b) {
    return s.query(b) - s.query(a - 1);
}

//////////////////////////////
//  Union-Find. An implementation of the Union-Find disjoint sets
//  data structure.
//////////////////////////////
struct union_find {
    vector<int> parent;
    union_find(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }

    bool connect(int x, int y) {
        return find(x) == find(y);
    }
};


int main() {

    {
        int a = 10;
        while(a >= 0) {
            int b = (a & (a + 1)) - 1;
            cout << a << " " << b << endl;
            a = b;
        }
    }
    {
        int a = 50;
        while(a >= 0) {
            int b = (a & (a + 1)) - 1;
            cout << a << " " << b << endl;
            a = b;
        }
    }
    {
        int a = 100;
        while(a >= 0) {
            int b = (a & (a + 1)) - 1;
            cout << a << " " << b << endl;
            a = b;
        }
    }
    {
        int a = 1000;
        while(a >= 0) {
            int b = (a & (a + 1)) - 1;
            cout << a << " " << b << endl;
            a = b;
        }
    }

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

	return 0;
}
