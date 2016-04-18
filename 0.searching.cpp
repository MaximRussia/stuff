#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <algorithm>
#include <fstream>
using namespace std;

#define _p(v) { cout << v << endl; }
#define fillv(v, n) { for(int i = 0; i < n; i++) v.push_back(i); }
#define fillvinv(v, n) { for(int i = n-1; i >= 0; i--) v.push_back(i); }
#define fillvr(v, n) { srand (time(NULL)); for(int i = 0; i < n; i++) v.push_back(rand()%n); }
#define printv(v) { for(int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl; }

/// 0 problem
/**
    Move all 0 to the end of array
**/

void moveZeroes(vector<int>& v) {
    int count = 0;

    for(int i = 0; i < v.size(); i++) {
        if(v[i] != 0) {
            v[count++] = v[i];
        }
    }

    while(count != v.size()) {
        v[count++] = 0;
    }
}
/// 0 problem
/**
    Given n non-negative integers representing an elevation map where the width of each bar is 1,
    compute how much water it is able to trap after raining.
**/

int calculateVolume(int heights[], int N) {

  int left = 0,
      right = N - 1,
      leftMax = heights[left],
      rightMax = heights[right],
      volume = 0;

  while (left < right) {
    if (leftMax < rightMax) {
      int height = heights[left];
      leftMax = max(leftMax, height);
      volume += leftMax - height;
      left++;
    } else {
      int height = heights[right];
      rightMax = max(rightMax, height);
      volume += rightMax - height;
      right--;
    }
  }
  return volume;

  /**
    int N = 9;
    int myIntArray[] = {2, 5, 1, 2, 3, 4, 7, 7, 6};
    cout << calculateVolume(myIntArray, N) << endl;
  **/
}
//////////////////////////////////////////

////////////////////////////////////////////
/// Binary Search
////////////////////////////////////////////
int floor_sqrt(int x) {
    int left = 0;
    int right = x / 2;

    while(left <= right) {
        int mid = (left + right)/2;
        int mid_mid = mid*mid;
        if(mid_mid == x) return mid;
        if(mid_mid < x) left++;
        else right--;
    }

    return left - 1; /// return left;
}
////////////////////////////////////////////
/**
1.2 SEARCH A SORTED ARRAY FOR k
Write a method that takes a sorted array A of integers and a key k and
returns the index of first occurrence of k in A. Return -l if k does not
appear in A. Write tests to verify your code.
**/
int bin_search(const vector<int> &v, int k) {
    int left = 0;
    int right = v.size()-1;

    while(left <= right) {
        int mid = (right+left)/2;
        if(v[mid] == k) return mid;
        if(v[mid] < k) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}
////////////////////////////////////////////
/**
1.3 SEARCH A SORTED ARRAY FOR THE FIRST ELEMENT LARGER
THAN k
**/
int larger_then_k(const vector<int> &v, int k) {
    int left = 0;
    int right = v.size()-1;

    while(left <= right) {
        int mid = (right+left)/2;
        if(v[mid] == k) return mid >= v.size() - 1 ? -1 : v[mid+1];
        if(v[mid] < k) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}
////////////////////////////////////////////
/**
1.4 SEARCH A SORTED ARRAY FOR A[i] = i
**/
int bin_search_i(const vector<int> &v) {
    int left = 0;
    int right = v.size()-1;

    while(left <= right) {
        int mid = (right+left)/2;
        if(v[mid] == mid) return mid;
        if(v[mid] < mid) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}
////////////////////////////////////////////
/**
1.5 SEARCH IN ARRAY OF UNKNOWN LENGTH
**/
int bin_search_unknown(const vector<int> &v, int k) {
    int left = 0;
    int right = 1;

    while(v[right] < k) right *= 2;

    while(left <= right) {
        int mid = (left + right) / 2;
        if(v[mid] == k) return k;
        if(v[mid] < k) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
////////////////////////////////////////////
/**
1.6 MISSING ELEMENT, LIMITED RESOURCES
google it, bro
**/

/**
1.7 INTERSECT OF TWO SORTED ARRAYS
**/
vector<int> find_intersection(vector<int>& A, vector<int>& B) {
  vector<int> res;
  int n1 = A.size();
  int n2 = B.size();
  int i = 0, j = 0;
  while (i < n1 && j < n2) {
    if (A[i] > B[j]) {
      j++;
    } else if (B[j] > A[i]) {
      i++;
    } else {
      res.push_back(A[i]);
      i++;
      j++;
    }
  }
  return res;
}

////////////////////////////////////////////
/// Hashing
////////////////////////////////////////////
/**
1.8 Give a array of words. Return the map of sets with anagrams.
**/

string get_anagram_pattern(string s) {
    sort(s.begin(), s.end());
    return s;
}
map<string, vector<string>> get_anagrams(vector<string> &v) {
    map<string, vector<string>> res;
    if(v.empty()) res;

    for(int i = 0; i < v.size(); i++) {
        string sorted = get_anagram_pattern(v[i]);
        res[sorted].push_back(v[i]);
    }

    return res;
}
////////////////////////////////////////////
/**
Problem 1.9: Design an efficient algorithm for determining if there exist
a pair of indices i, j such that A[i] + A[j] = S.
**/

pair<int, int> get_pair_of_indices(const vector<int> &v, int k) {
    map<int, int> hash;
    for(int i = 0; i < v.size(); i++) {
        int diff = k - v[i];
        hash[v[i]] = i;
        if(hash.find(diff) != hash.end()) {
            return pair<int, int>(hash[diff], i);
        }
    }

     return pair<int, int>();
}
////////////////////////////////////////////
/**
1.10 You have 2 letters. Can you use 1st and write the 2nd one?
**/

bool letters_check(vector<string> &l1, vector<string> &l2) {
    map<string, int> hash; /// string => count
    for(int i = 0; i < l1.size(); i++) {
        if(hash.find(l1[i]) != hash.end()) hash[l1[i]]++;
        else hash[l1[i]] = 1;
    }

    for(int i = 0; i < l2.size(); i++) {
        if(hash.find(l2[i]) == hash.end()) return false;
        if(hash[l2[i]] == 0) return false;
        hash[l2[i]]--;
    }

    return true;
}
////////////////////////////////////////////
/**
1.12 MISSING ELEMENT
Devise an algorithm that uses only O(k) memory
**/
vector<string> missing_elements_in_stream(vector<int> &v, fstream f) {
    /**
        use map for non basic type
        use bit-vector of v.size() for int
    **/
}
////////////////////////////////////////////
/**
Problem 1.14: You are reading a sequence of words from a very long
stream. You know that more than half the words are repetitions of
a single word W but the positions where W occurs are unknown. Design
an efficient algorithm that reads this stream only once and uses only a
constant amount of memory to identify W.
**/
string find_W(ifstream f) {
    int count = 0;
    string res = "";
    string buff = "";
    while(f >> buff) {
        if(count == 0) {
            res = buff;
            count = 1;
        }
        else
        if(res == buff) count++;
        else count--;
    }

    return res;
}
////////////////////////////////////////////
/// Binary Search Trees
////////////////////////////////////////////

struct Node {
    int value;
    Node* left;
    Node* right;
    Node():value(0), left(NULL), right(NULL) {}
    Node(int i):value(i), left(NULL), right(NULL) {}
};
////////////////////////////////////////////
/**
1.16: Given a BST Tree write a recursive function that
searches for key K, then write an iterative function.
**/

int find_recursive(Node* root, int k) {
    if(root == NULL) return -1;
    if(k < root->value) return find_recursive(root->left, k);
    if(k > root->value) return find_recursive(root->right, k);
    return root->value;
}
////////////////////////////////////////////
/**
1.17: Given a BST T and a key K , write a method that searches
for the first entry larger than K.
**/

int find_large_then_k(Node* root, int k) {
    if(root == NULL) return -1;
    if(k < root->value) return find_recursive(root->left, k);
    if(k > root->value) return find_recursive(root->right, k);
    return root->right != NULL ? root->right->value : root->value;
}
////////////////////////////////////////////
/**
1.18: You are given two sorted arrays of lengths m and n. Give
a O(log m) time algorithm for compute the k-th smallest element
in the union of the two arrays. Keep in mind that the elements may be
repeated.

**/
////////////////////////////////////////////

int main() {

    vector<int> v = {1,2,0,8,0,7,6,7,8,0,9};

    moveZeroes(v);

    for(auto i : v) {
        cout << i << endl;
    }

    return 0;
}
