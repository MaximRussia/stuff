
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
using namespace std;

struct tnode {
	int v;
	tnode* right;
	tnode* left;
	tnode* n;
	tnode() : v(0), right(NULL), left(NULL), n(NULL) {}
	tnode(int v) : v(v), right(NULL), left(NULL), n(NULL) {}
};

void insertarray(tnode* &root, const vector<int> &v, int start, int end) {
	if (start > end) return;
	// same as (start+end)/2, avoids overflow.
	int mid = start + (end - start) / 2;
	root = new tnode(v[mid]);
	insertarray(root->left, v, start, mid - 1);
	insertarray(root->right, v, mid + 1, end);
};

void connectNeibours(tnode* root) {
	if (!root) return;

	queue<tnode*> q1;
	queue<tnode*> q2;
	vector<tnode*> v;
	q1.push(root);

	while (!q1.empty() || !q2.empty()) {
		if (!q1.empty()) {
			while (!q1.empty()) {
				tnode* node = q1.front(); q1.pop();

				if (node->left) {
					v.push_back(node->left);
					q2.push(node->left);
				}

				if (node->right) {
					v.push_back(node->right);
					q2.push(node->right);
				}
			}
		} else if (!q2.empty()) {
			while (!q2.empty()) {
				tnode* node = q2.front(); q2.pop();

				if (node->left) {
					v.push_back(node->left);
					q1.push(node->left);
				}

				if (node->right) {
					v.push_back(node->right);
					q1.push(node->right);
				}
			}
		}

		if (v.size() > 1) {
			for (int i = 0; i < v.size() - 1; i++) {
				v[i]->n = v[i + 1];
			}
		}

		v.clear();
	}
}

void printLevelByLevelNeibours(tnode* &root) {
	if (!root) { cout << "empty" << endl; return; }

	queue<tnode*> q1;
	queue<tnode*> q2;
	q1.push(root);

	while (!q1.empty() || !q2.empty()) {
		if (!q1.empty()) {
			while (!q1.empty()) {
				tnode* node = q1.front(); q1.pop();
				if (node->n != NULL)
					cout << "[" << node->v << "->" << node->n->v << "]";
				else
					cout << "[" << node->v << "->" << "null" << "]";
				if (node->left) q2.push(node->left);
				if (node->right) q2.push(node->right);
			}
		} else if (!q2.empty()) {
			while (!q2.empty()) {
				tnode* node = q2.front(); q2.pop();
				if (node->n != NULL)
					cout << "[" << node->v << "->" << node->n->v << "]";
				else
					cout << "[" << node->v << "->" << "null" << "]";

				if (node->left) q1.push(node->left);
				if (node->right) q1.push(node->right);
			}
		}

		cout << endl;
	}
}

void printLevelByLevel(tnode* &root) {
	if (!root) { cout << "empty" << endl; return; }

	queue<tnode*> q1;
	queue<tnode*> q2;
	q1.push(root);

	while (!q1.empty() || !q2.empty()) {
		if (!q1.empty()) {
			while (!q1.empty()) {
				tnode* node = q1.front(); q1.pop();
				cout << node->v << " ";
				if (node->left) q2.push(node->left);
				if (node->right) q2.push(node->right);
			}
		} else if (!q2.empty()) {
			while (!q2.empty()) {
				tnode* node = q2.front(); q2.pop();
				cout << node->v << " ";
				if (node->left) q1.push(node->left);
				if (node->right) q1.push(node->right);
			}
		}

		cout << endl;
	}
}


int main() {

	tnode* root = NULL;

	insertarray(root, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 0, 8);

	connectNeibours(root);

	printLevelByLevel(root);
	printLevelByLevelNeibours(root);

	return 0;
}
