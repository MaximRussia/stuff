#include<iostream>
#include<cmath>
#include "tree.h"
using namespace std;


int main(){
	node *root;
	root = NULL;
	int arr[] = { 4, 7, 2, 1, 6, 8 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		insertNode(root, arr[i]);
	cout << isBalanced(root);
}
