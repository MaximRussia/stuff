
/**
	Binary Search Tree Check
	Given a binary tree, check whether it’s a binary search tree or not.
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

struct Node {
	int val;
	Node* right;
	Node* left;
};

int isBST(struct Node* node) {
	if (node == NULL)
		return 1;

	if (node->left != NULL && node->left->data > node->data)
		return 0;

	if (node->right != NULL && node->right->data < node->data)
		return 0;

	if (!isBST(node->left) || !isBST(node->right))
		return 0;

	return 1;
}

int main() {

	return 0;
}
