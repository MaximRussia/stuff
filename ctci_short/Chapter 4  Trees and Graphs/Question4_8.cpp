#include<iostream>
#include "tree.h"
using namespace std;

bool isIdentical(node* root1, node* root2){
	if (root1 == NULL && root2 == NULL)
		return true;
	if (root1 == NULL || root2 == NULL)
		return false;
	if (root1->data == root2->data && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right))
		return true;
	return false;
}

bool isSubTree(node* root, node* subRoot){
	if (root == NULL && subRoot == NULL)
		return true;
	if (root == NULL || subRoot == NULL)
		return false;
	return isIdentical(root, subRoot) || isSubTree(root->left, subRoot) || isSubTree(root->right, subRoot);
}

int main(){
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };    // Bigger Tree
	int arr1[] = { 1, 2, 3, 4 };                  // Subtree
	node *root, *subRoot;
	root = subRoot = NULL;
	createBst(root, arr, 0, 8);
	createBst(subRoot, arr1, 0, 3);
	//cout<<isIdentical(root->left->left->left, subRoot->left);
	cout << isSubTree(root, subRoot);
	return 0;
}
