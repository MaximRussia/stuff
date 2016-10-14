#include<iostream>
#include<stack>
#include "tree.h"
using namespace std;

node* inOrderSuccessor(node* root, int k){
	stack<node*> S;
	node *ptr = root;
	bool searched = false;
	while (true){
		while (ptr){
			S.push(ptr);
			ptr = ptr->left;
		}
		if (S.empty())
			break;
		ptr = S.top();
		S.pop();
		//cout<<ptr->data<<" ";
		if (searched)
			return ptr;
		if (ptr->data == k){
			searched = true;
		}
		ptr = ptr->right;
	}
	return false;
}

int main(){
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	node* root;
	root = NULL;
	createBst(root, arr, 0, 8);
	node* searchedNode = inOrderSuccessor(root, 4);
	cout << searchedNode->data << '\n';
}
