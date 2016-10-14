#include<iostream>
#include "tree.h"
using namespace std;

int main(){
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	node* root;
	root = NULL;
	createBst(root, arr, 0, 8);
	cout << root->left->data << " " << root->data << " " << root->right->data << '\n';
}
