/**
	Tree Level Order Print
	Given a binary tree of integers, print it in level order. The output will contain space between the
	numbers in the same level, and new line between different levels.
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
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

void printNodesByReverseLevels(TreeNode *root) {
	queue<TreeNode*> nodes;
	deque<TreeNode*> allNodes;
	stack<int> countAtLevelI;
	int currentLevelCount = 0;
	int nextLevelCount = 0;

	if (root == NULL) {
		return;
	} else {
		nodes.push(root);
		allNodes.push_back(root);
		currentLevelCount = 1;
		countAtLevelI.push(currentLevelCount);

		while (!nodes.empty()) {
			TreeNode *cur = nodes.front();
			nodes.pop();
			currentLevelCount--;

			if (cur->left != NULL) {
				nodes.push(cur->left);
				allNodes.push_back(cur->left);
				nextLevelCount++;
			}

			if (cur->right != NULL) {
				nodes.push(cur->right);
				allNodes.push_back(cur->right);
				nextLevelCount++;
			}
			if (currentLevelCount == 0) {
				currentLevelCount = nextLevelCount;
				countAtLevelI.push(currentLevelCount);
				nextLevelCount = 0;
			}
		}

		while (!countAtLevelI.empty()) {
			int countAtI = countAtLevelI.top();
			countAtLevelI.pop();

			// this is to make sure the nodes are printed in the left to right order.
			for (int j = allNodes.size() - countAtI; j < allNodes.size(); j++) {
				cout << allNodes[j]->val << "  ";
			}

			for (int i = 0; i < countAtI; i++) {
				allNodes.pop_back();
			}
			cout << endl;
		}
	}
}

int main() {

	TreeNode *root = new TreeNode(5);
	Insert(root, 3);
	Insert(root, 6);
	Insert(root, 1);
	Insert(root, 8);
	Insert(root, 7);

	printNodesByReverseLevels(root);

	return 0;
}
