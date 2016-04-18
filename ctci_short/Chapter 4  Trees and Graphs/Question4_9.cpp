#include<iostream>
#include "tree.h"
using namespace std;

void printIfSum(int* arr, int sum, int len){
    for(int i=0; i<len; i++){
        int s=0;
        for(int j=i; j<len; j++){
            s += arr[j];
            if(s == sum){
                for(int k=i; k<=j; k++)
                    cout<<arr[k]<<" ";
                cout<<'\n';
            }
        }
    }
}

void print(node *root, int sum, int *path, int level){
    if(root==NULL){
        return;
    }
    path[level] = root->data;
    int s = 0;
    for(int i=level; i>=0; i--){
        s += path[i];
        if(s==sum){
            for(int j=level; j>=i; j--)
                cout<<path[j]<<" ";
            cout<<'\n';
        }
    }
    if(root->left)
        print(root->left, sum, path, level+1);
    if(root->right)
        print(root->right, sum, path, level+1);
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    node *root;
    root = NULL;
    createBst(root, arr, 0, 8);
    int path[100];
    print(root, 7, path, 0);
}
