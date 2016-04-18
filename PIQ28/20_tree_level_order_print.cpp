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
#include <cstring>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode() : val(0), left(NULL), right(NULL) {}
};

TreeNode* Insert(TreeNode *root, char data){
  if(root == NULL){
    root = new TreeNode(data);
    return root;
  } else if(data <= root->val){
    root->left = Insert(root->left, data);
  } else {
    root->right = Insert(root->right, data);
  }
}

void printBinaryTreeByLevel(TreeNode * node){
    if(node == NULL) return;
    int currentCount = 1, nextCount = 0;

    queue<TreeNode*> q;
    q.push(node);

    while(!q.empty()){
        TreeNode* currentNode = q.front();
        q.pop();
        currentCount--;
        cout << currentNode->val << " ";

        if(currentNode->left != NULL) {
            q.push(currentNode->left);
            nextCount++;
        }

        if(currentNode->right != NULL) {
            q.push(currentNode->right);
            nextCount++;
        }

        if(currentCount == 0)
            cout << endl;

        swap(currentCount, nextCount);
    }
 }

int main() {

    TreeNode *root = new TreeNode(5);
    Insert(root, 3);
    Insert(root, 6);
    Insert(root, 1);
    Insert(root, 8);
    Insert(root, 7);

    printBinaryTreeByLevel(root);

    return 0;
}
