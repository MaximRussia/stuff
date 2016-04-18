#include<iostream>
#include "tree.h"
using namespace std;

///root1 is decendent of root
bool isDecendent(node *root, node *root1){
    if(root == NULL)
        return false;
    if(root == root1)
        return true;
    return isDecendent(root->left, root1) || isDecendent(root->right, root1);
}

node* commonAncestor(node *root, node *root1, node *root2){
    if(root==NULL)
        return NULL;
    if(root == root1 || root == root2)
        return root;
    bool root1_on_left = isDecendent(root->left, root1);
    bool root2_on_left = isDecendent(root->left, root2);
    if(root1_on_left && root2_on_left)
        return commonAncestor(root->left, root1, root2);
    else if(root1_on_left || root2_on_left)
        return root;
    else
        return commonAncestor(root->right, root1, root2);
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    node* root;
    root = NULL;
    createBst(root, arr, 0, 8);
    node *ancestor = commonAncestor(root, root->left->left, root->left->right->right);
    cout<<ancestor->data;
}
