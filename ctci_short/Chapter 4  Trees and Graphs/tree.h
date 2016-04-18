
#ifndef _TREE_
#define _TREE_

#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;

    node() : data(0), left(NULL), right(NULL) {}
    node(int v) : data(v), left(NULL), right(NULL) {}
};

void createBst(node* &root, int arr[], int start, int end){
    if(start>end)
        return;
    if(root==NULL){
        node *ptr = new node;
        int ind = start + (end-start)/2;
        ptr->data = arr[ind];
        ptr->left = NULL;
        ptr->right = NULL;
        root = ptr;
        createBst(root->left, arr, start, ind-1);
        createBst(root->right, arr, ind+1, end);
    }
}


void PreOrder(node* &root) {
    if(!root) return;

	cout << root->data << endl;
	PreOrder(root->left);
	PreOrder(root->right);
}

void InOrder(node* &root) {
    if(!root) return;

	InOrder(root->left);
	cout << root->data << endl;
	InOrder(root->right);
}

void PostOrder(node* &root) {
    if(!root) return;

	PostOrder(root->left);
	PostOrder(root->right);
	cout << root->data << endl;
}

void DFS(node* &root) {
    if(!root) return;

    stack<node*> s;
    s.push(root);

    while(!s.empty()) {
        node* first = s.top(); s.pop();

        cout << first->data << endl;
        if(first->right) s.push(first->right);
        if(first->left) s.push(first->left);
    }
}


void BFS(node* &root) {
    if(!root) return;

    queue<node*> q;
    q.push(root);

    while(!q.empty()) {
        node* first = q.front(); q.pop();

        cout << first->data << endl;
        if(first->right) q.push(first->right);
        if(first->left) q.push(first->left);
    }
}

void insertNode(node* &head, int data){
    if(head==NULL){
        node *p = new node;
        p->data = data;
        p->left = NULL;
        p->right = NULL;
        head = p;
        return;
    }
    if(data<=head->data){
        if(head->left==NULL){
            node *p = new node;
            p->data = data;
            p->left = NULL;
            p->right = NULL;
            head->left = p;
            return;
        }
        insertNode(head->left, data);
    }
    else{
        if(head->right==NULL){
            node *p = new node;
            p->data = data;
            p->left = NULL;
            p->right = NULL;
            head->right = p;
            return;
        }
        insertNode(head->right,data);
    }
}

int height(node* root){
    if(root==NULL)
        return 0;
    return max(height(root->left), height(root->right))+1;
}

bool isBalanced(node* root){
    if(root==NULL)
        return true;
    int diff = height(root->left) - height(root->right);
    if(abs(diff)>1)
        return false;
    else
        return (isBalanced(root->left) && isBalanced(root->right));
}

void insert(node* &root, vector<int> v, int l, int r) {
    if(l > r) {
        return;
    }

    int mid = l+(r-l)/2;
    root = new node(v[mid]);
    insert(root->left, v, l, mid-1);
    insert(root->right, v, mid+1, r);
}

int height(node * &root) {
    if(!root) return 0;

    return 1 + max(height(root->left), height(root->right));
}

bool isBalanced(node * &root) {
    return height(root->right) == height(root->left);
}

bool isBST(node * &root) {
    if(!root) return true;

    if(root->left && root->left->data > root->data) return false;
    if(root->right && root->right->data <= root->data) return false;

    return isBST(root->left) && isBST(root->right);

}

#endif // _TREE_
