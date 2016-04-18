#include<iostream>
#include<climits>
#include "tree.h"
using namespace std;


bool isBst(node* root, int lower, int upper){
    if(root==NULL){
        return true;
    }
    if(root->data<=upper && root->data>=lower){
        return (isBst(root->left, lower, root->data) && isBst(root->right, root->data+1, upper));
    }
    else
        return false;
}

int main(){
    ///int arr[] = {1, 2, 2, 4, 5, 6, 7, 8, 9};    //Not a BST
    int arr[] = {2, 2, 3, 4, 5, 6, 7, 8, 9};    //is BST
    node* root;
    root = NULL;
    createBst(root, arr, 0, 8);
    cout<<isBst(root, INT_MIN, INT_MAX);
}
