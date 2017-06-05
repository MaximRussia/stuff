/**
	Trim Binary Search Tree
	Given the root of a binary search tree and 2 numbers min and max, trim the tree such that all the
	numbers in the new tree are between min and max (inclusive). The resulting tree should still be a
	valid binary search tree.
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cstring>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	TreeNode() : val(0), left(NULL), right(NULL) {}
};

TreeNode* Insert(TreeNode *root, char data) {
	if (root == NULL) {
		root = new TreeNode(data);
		return root;
	} else if (data <= root->val) {
		root->left = Insert(root->left, data);
	} else {
		root->right = Insert(root->right, data);
	}
}

TreeNode* trimTree(TreeNode* root, int min, int max) {
	if (root == NULL) return NULL;

	root->left = trimTree(root->left, min, max);
	root->right = trimTree(root->right, min, max);

	if (min <= root->val && root->val <= max)
		return root;

	if (root->val < min) return root->right;
	if (root->val > max) return root->left;
}

int main() {

	TreeNode *root = new TreeNode(5);
	Insert(root, 3);
	Insert(root, 6);
	Insert(root, 1);
	Insert(root, 8);
	Insert(root, 7);

	trimTree(root, 3, 7);

	return 0;
}
