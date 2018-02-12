
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
// time. It only needs O(n) space. /// Binary Indexed Trees
//////////////////////////////////

struct fenwick_tree {
    int n;
    vector<int> data;

    fenwick_tree(int _n) : n(_n), data(vector<int>(n)) { }

    void update(int at, int by) {
        while (at < n) data[at] += by, at = child(at);
    }

    int parent(int at) {
    	return (at & (at + 1)) - 1;
    }

    int child(int at) {
    	return at | at + 1;
    }

    int _child(int at) {
    	return 2 * at;
    }

    int query(int at) {
        int res = 0;
        while (at >= 0) res += data[at], at = parent(at);
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

/////////////////////////////////////////////
// A suffix array is a sorted array of all suffixes of a given string.
// The definition is similar to Suffix Tree which is compressed trie of all
// suffixes of the given text. Any suffix tree based algorithm can be replaced
// with an algorithm that uses a suffix array enhanced with additional information and
// solves the same problem in the same time complexity (Source Wiki).
// A suffix array can be constructed from Suffix tree by doing a DFS traversal
// of the suffix tree. In fact Suffix array and suffix tree both can be constructed
// from each other in linear time.
// Advantages of suffix arrays over suffix trees include improved space requirements,
// simpler linear time construction algorithms (e.g., compared to Ukkonen’s algorithm) and improved cache locality (Source: Wiki)
/////////////////////////////////////////////

// Structure to store information of a suffix
struct suffix {
    int index;
    char *suff;
};

// A comparison function used by sort() to compare two suffixes
int cmp(struct suffix a, struct suffix b) {
    return strcmp(a.suff, b.suff) < 0? 1 : 0;
}

// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
int *buildSuffixArray(char *txt, int n) {
    // A structure to store suffixes and their indexes
    struct suffix suffixes[n];

    // Store suffixes and their indexes in an array of structures.
    // The structure is needed to sort the suffixes alphabatically
    // and maintain their old indexes while sorting
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suff = (txt+i);
    }

    // Sort the suffixes using the comparison function
    // defined above.
    sort(suffixes, suffixes+n, cmp);

    // Store indexes of all sorted suffixes in the suffix array
    int *suffixArr = new int[n];
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;

    // Return the suffix array
    return  suffixArr;
}

// A utility function to print an array of given size
void printArr(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// A suffix array based search function to search a given pattern
// 'pat' in given text 'txt' using suffix array suffArr[]
void search(char *pat, char *txt, int *suffArr, int n) {
    int m = strlen(pat);  // get length of pattern, needed for strncmp()

    // Do simple binary search for the pat in txt using the
    // built suffix array
    int l = 0, r = n-1;  // Initilize left and right indexes
    while (l <= r)
    {
        // See if 'pat' is prefix of middle suffix in suffix array
        int mid = l + (r - l)/2;
        int res = strncmp(pat, txt+suffArr[mid], m);

        // If match found at the middle, print it and return
        if (res == 0)
        {
            cout << "Pattern found at index " << suffArr[mid];
            return;
        }

        // Move to left half if pattern is alphabtically less than
        // the mid suffix
        if (res < 0) r = mid - 1;

        // Otherwise move to right half
        else l = mid + 1;
    }

    // We reach here if return statement in loop is not executed
    cout << "Pattern not found";
}

int main() {

    fenwick_tree f(12);
    f.update(0, 2);
    f.update(1, 1);
    f.update(2, 1);
    f.update(3, 3);
    f.update(4, 2);
    f.update(5, 3);
    f.update(6, 4);
    f.update(7, 5);
    f.update(8, 6);
    f.update(9, 7);
    f.update(10, 8);
    f.update(11, 9);

    for(int i = 0; i < f.data.size(); ++i) {
        cout << i << " " << f.data[i] << endl;
    }

    cout << "!!!!!!!" << endl << endl;
{
	char txt[] = "banana";
    int n = strlen(txt);
    int *suffixArr = buildSuffixArray(txt,  n);
    cout << "Following is suffix array for " << txt << endl;
    printArr(suffixArr, n);
}

{
	char txt[] = "banana";  // text
    char pat[] = "nan";   // pattern to be searched in text

    // Build suffix array
    int n = strlen(txt);
    int *suffArr = buildSuffixArray(txt, n);

    // search pat in txt using the built suffix array
    search(pat, txt, suffArr, n);
}
    cout << endl;
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
