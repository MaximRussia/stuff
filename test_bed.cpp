#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <climits>
#include <cstdio>
using namespace std;

////////////////////////
// MEMORY
////////////////////////

void mycpy(char **res, const char *str) {
    if(!str) return;
    if(!*res) *res = (char*)malloc(strlen(str)*sizeof(*str)+1);
    char *ptr = *res;
    while((*ptr++ = *str++) != '\0');
}

void mycpy_mem(char **res, const char *str) {
    if(!str) return;
    size_t size = strlen(str)*sizeof(*str)+1;
    if(!*res) *res = (char*)malloc(size);
    char *ptr = *res;
    memcpy(ptr, str, size);
}

void mycat(char **res, const char *str) {
    if(!str) return;
    char *ptr = *res;
    size_t size_res = strlen(*res);
    size_t size_str = strlen(str);
    size_t size = size_res + size_str + 1;
    ptr = (char*)realloc(*res, size);
    ptr += size_res;
    while((*ptr++ = *str++) != '\0');
}

void mycat_mem(char **res, const char *str) {
    if(!str) return;
    char *ptr = *res;
    size_t len_res = strlen(*res);
    size_t len_str = strlen(str);
    size_t size = len_res + len_str;
    ptr = (char*)realloc(*res, size * sizeof(*str));
    ptr += len_res;
    memcpy(ptr, str, len_str+1);
}

void mysprintf(char **res, const char *fmt, const char *str) {
    sprintf(*res, fmt, str);
}

void myfree(char **str) {
    free(*str);
    *str = NULL;
}

int mycmp(char *str1, char *str2) {
    if(!str1 || !str2) return 1;

    while(*str1 != '\0' && *str2 != '\0') {
        if(*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}
/////////////////////////////////
// TREE
/////////////////////////////////
struct tnode {
    int v;
    tnode* right;
    tnode* left;
    tnode() : v(0), right(NULL), left(NULL){}
    tnode(int v) : v(v), right(NULL), left(NULL){}
};

void insert(tnode* &root, int v) {
    if(!root) {
        root = new tnode(v);
        return;
    }

    if(v < root->v) insert(root->left, v);
    else insert(root->right, v);
}

//////////////////////
// DFS variations
//////////////////////
void preorder(tnode* &root) {
    if(!root)  {
        return;
    }

    cout << root->v << " ";
    preorder(root->left);
    preorder(root->right);
}

void iterativePreorder(tnode* &root) {
    if (!root) {
    	return;
    }

    stack<tnode*> q;
    q.push(root);

    while (!q.empty()) {
        tnode *node = q.top(); q.pop();
        cout << node->v << " ";

        if (node->right) q.push(node->right);
        if (node->left) q.push(node->left);
    }
}

void inorder(tnode* &root) {
    if(!root)  {
        return;
    }

    inorder(root->left);
    cout << root->v << " ";
    inorder(root->right);
}

void iterativeInorder(tnode* &root) {
    if(!root)  {
        return;
    }

	stack<tnode*> s;
  	tnode *current = root;
  	bool done = false;
  	while (!done) {
        if (current) {
            s.push(current);
            current = current->left;
        } else {
            if (s.empty()) {
                done = true;
            } else {
                current = s.top();
                s.pop();
                cout << current->v << " ";
                current = current->right;
            }
        }
  	}
}

void postorder(tnode* &root) {
    if(!root)  {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->v << " ";
}

void iterativePostorder(tnode* &root) {
    if (!root) return;

    stack<tnode*> s;
    stack<tnode*> output;

    s.push(root);
    while (!s.empty()) {
        tnode *curr = s.top(); s.pop();
        output.push(curr);

        if (curr->left) s.push(curr->left);
        if (curr->right) s.push(curr->right);
    }

    while (!output.empty()) {
        cout << output.top()->v << " ";
        output.pop();
    }
}


tnode* LowestCommonAcessor(tnode* root, int value1, int value2 ){
    while( root ){
        if( root->v > value1 && root->v > value2 ){
            root = root->left;
        } else if( root->v < value1 && root->v < value2 ){
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL; // only if empty tree
}

//////////////////////

void BFS(tnode* &root) {
    if(!root)  {
        return;
    }

    queue<tnode*> q;
    q.push(root);

    while(!q.empty()) {
        tnode* n = q.front(); q.pop();

        cout << n->v << " ";
        if(n->left) q.push(n->left);
        if(n->right) q.push(n->right);
    }
}

void DFS(tnode* &root) {
    if(!root)  {
        return;
    }

    stack<tnode*> q;
    q.push(root);

    while(!q.empty()) {
        tnode* n = q.top(); q.pop();

        cout << n->v  << " ";
        if(n->left) q.push(n->left);
        if(n->right) q.push(n->right);
    }
}

void insertarray(tnode* &root,int arr[], int start, int end) {
    if (start > end) return;
    // same as (start+end)/2, avoids overflow.
    int mid = start + (end - start) / 2;
    root = new tnode(arr[mid]);
    insertarray(root->left, arr, start, mid-1);
    insertarray(root->right, arr, mid+1, end);
}

void insertarray(tnode* &root, int arr[], int n) {
  return insertarray(root, arr, 0, n-1);
}

void clean(tnode* &root) {
    if(!root) return;
    clean(root->left);
    clean(root->right);
    delete root;
    root = NULL;
}

/////////////////////////////////
// LIST
/////////////////////////////////
struct node {
    int v;
    node* next;
    node() : v(0), next(NULL){}
    node(int v) : v(v), next(NULL){}
};

void insert(node* &head, int v) {
    if(!head) {
        head = new node(v);
        return;
    }
    insert(head->next, v);
}

void print(node* &head) {
    if(!head) return;

    cout << head->v << " ";
    print(head->next);
}

void removenode(node* &head) {
    if(!head) return;
    if(!head->next) {
        delete head;
        head = NULL;
        return;
    }

    node *rm = head->next;
    head->v = rm->v;
    head->next = rm->next;
    delete rm;
}

void printKthLast(node* &head, int k) {
    if(!head) return;

    int len = 0;
    node* first = head;
    node* second = NULL;

    while(first) {
        len++;
        first = first->next;
    }

    if(len < k) return;

    first = head;
    second = head;

    while(k--) {
        first = first->next;
    }

    while(first) {
        first = first->next;
        second = second->next;
    }

    cout << second->v << " ";


}

void append_head(node* &head, node* n) {
    if(!head) {
        head = n;
    }

    n->next = head;
    head = n;
}

void clean(node* &head) {
    if(!head) return;
    clean(head->next);
    delete head;
    head = NULL;
}

void revert_inplace(node* &head) {
	if(!head || !head->next) return;

	node* prev = NULL;
	node* move = head;

	while(move) {
		node* next = move->next;
		move->next = prev;
		prev = move;
		move = next;
	}

	head = prev;
}

bool revert_inplace_ptr(node** head) {
	if(!(*head)) return false;
	if(!(*head)->next) return true;

	node* prev = NULL;
	node* move = (*head);

	while(move) {
		node* next = move ->next;
		move->next = prev;
		prev = move;
		move = next;
	}

	(*head) = prev;
	return true;
}

void reverse_inpalce_rec(node*& head) {
    if (!head || !head->next) return;

    node* prev = head->next;
    node* move = head->next;

    reverse_inpalce_rec(prev);

    move->next = head;
    head->next = NULL;

    head = prev;
}

void selectSort(node* &head) {
    if(!head) return;

    node* first = head;

    while(first) {
        node* minn = first;
        node* fast = first;
        while(fast){
            if(fast->v < first->v) minn = fast;
            fast = fast->next;
        }

        if(minn != first)
            swap(minn->v, first->v);

        first = first->next;
    }
}

void rotateList(node* &head, int v) {
    if(v <= 0 || !head) return;

    node* first = head;

    while(first && v) {
        v--;
        first = first->next;
    }

    if(!first) return;

    node* last = head;

    while(last->next) {
        last = last->next;
    }

    last->next = head;
    head = first;

    node *for_null = head;
    while(for_null->next != head) {
        for_null = for_null->next;
    }

    for_null->next = NULL;
}

/////////////////////////////////
// STRINGS
/////////////////////////////////

char firstUniqueChar(string s) {
    if(s.empty()) return '\0';

    char buff[256] = {0};

    for(size_t i = 0; i < s.size(); ++i) {
        ++buff[s[i]];
    }

    for(size_t i = 0; i < s.size(); ++i) {
        if(buff[s[i]] == 1) return s[i];
    }

    return '\0';
}

string removeChars(string str, string rem) {
    if(str.empty() || rem.empty()) return str;

    bool buff[65535] = {false};
    for(size_t i = 0; i < rem.size(); i++) {
        buff[rem[i]] = true;
    }

    int dst = 0;

    for(size_t i = 0; i < str.size(); i++) {
        if(!buff[str[i]]) {
            str[dst] = str[i];
            dst++;
        }
    }

    return str.substr(0, dst);
}

string dec2bin(int dec) {
    string res;

    while(dec) {
        res = (dec&1 ? "0" : "1") + res;
        dec >>= 1;
    }

    return res;
}

int bin2dec(string s){
    if(s.empty()) return 0;

    int res = 0;
    int pwr = 0;
    for(int i = s.size()-1; i >= 0; i--) {
        res += (s[i] - '0')*pow(2, pwr);
        pwr++;
    }

    return res;
}

int hex2num(char ch) {
	if(ch >= '0' && ch <= '9') return ch - '0';
	if(ch >= 'a' && ch <= 'f') return 10 + ch - 'a';
	if(ch >= 'A' && ch <= 'F') return 10 + ch - 'A';
	return -1;
}

int base2dec(string str, int base) {
	if(str.empty()) return -1;

	int res = 0;
	if(str[0] == '0' && str[1] == 'x') {
		str = str.substr(2);
	}

	for(int i = 0; i < str.size(); i++) {
		res += hex2num(str[i]) * pow(base, str.size() - 1 - i);
	}

	return res;
}

/*****
Implement atof()
So given a string like "2.23" your function should return double 2.23. This might seem easy in the first place but this is a highly ambiguous question. Also it has some interesting test cases. So overall a good discussion can revolve around this question. We are not going to support here scientific notation like 1.45e10 etc. We will also not support hex and octal strings just for the sake of simplicity. But these are good assumption to state upfront. Let's write code for this.
double atof(char* num) {
     if (!num || !*num) return 0;

     double integerPart = 0;
     double fractionPart = 0;
     int divisorForFraction = 1;
     int sign = 1;
     bool inFraction = false;

     //Take care of +/- sign
     if (*num == '-') {
         ++num;
         sign = -1;
     }
     else if (*num == '+') {
         ++num;
     }

     while (*num != '\0') {
         if (*num >= '0' && *num <= '9') {
             if (inFraction) {
                 //See how are we converting a character to integer
                 fractionPart = fractionPart*10 + (*num - '0');
                 divisorForFraction *= 10;
             }
             else {
                 integerPart = integerPart*10 + (*num - '0');
             }
         }
         else if (*num == '.') {
             if (inFraction)
                 return sign * (integerPart + fractionPart/divisorForFraction);
             else
                 inFraction = true;
         }
         else {
             return sign * (integerPart + fractionPart/divisorForFraction);
         }
         ++num;
     }
     return sign * (integerPart + fractionPart/divisorForFraction);
 }

Fun time - Breaking the code
1. Pass NULL/empty string
2. Pass string with +ve and -ve sign, +2.0/-5.5
3. Pass pure character string. What is expected?
4. Pass mix of character and numbers, 2.33abc/2abc/2.abc
5. Check what happens if string passed results in overflow/underflow, our code doesn't take care of it
6. String with leading/trailing zeroes, +0000.002/-1.0000
7. Pass all zeroes, 0.000/000
8. What happens if there are more than one decimal point like 1.234.5/1..2?
9. Also look for some corner cases like +.1/-.2/etc. These are all valid cases.
Complexity of the code
Constant space and O(N) run time considering length of string is N.
Similar problems
1. Write atoi(char* str)
******/

int myatoi(string str) {
    if(str.empty()) return 0;

    int res = 0;
    int i = 0;

    /// skip spaces
    while(str[i] == ' ') {
        i++;
    }

    /// get sign
    int sign = 1;
    if(!isdigit(str[i])) {
        if(str[i] == '-') {
            sign = 0;
        } else if(str[i] == '+') {
            sign = 1;
        } else {
            return 0;
        }
        i++;
    }

    /// main convert loop
    while(i < str.size()) {
        if(!isdigit(str[i])) {
            break;
        }
        res = res * 10 + str[i] - '0';
        i++;
    }

    return sign > 0 ? res : -res;
}

void reverse(string &str, size_t l, size_t r) {

    for(size_t i = l, j = r; i < j; i++, j--) {
        str[i] ^= str[j] ^= str[i] ^= str[j];
    }
}

/// "123 456 789"
string reverseWords(string str) {
    if(str.size() < 2) return str;

	reverse(str, 0, str.size()-1);

    int prevIndex = 0;
	// reverse spaces
	for(int i = 0; i < str.size(); i++) {
		if(str[i] == ' ') {
			reverse(str, prevIndex, i-1);
			prevIndex = i+1;
		}
	}

	// reverse 'last space' to end
	reverse(str, prevIndex, str.size()-1);

	return str;
}

/////////////////////////////////
// BIN
/////////////////////////////////


int swp(int v) {
    int mask1 = 0xaaaaaa; /// 10101010
    int mask2 = 0x555555; /// 01010101
    int r1 = v & mask1;
    int r2 = v & mask2;
    return (r1 >> 1) | (r2 << 1);
}

int ins(int a, int b, int i, int j) {
    int mask = ~0;
    mask << (i+j);
    int mask2 = (1 << i)-1;
    int res_mask = mask2 | mask;
    return (a & res_mask) | (b << i);
}

bool isPowerOfTwo(int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

bool isPowerOfN1(int i, int n) {
    if(i > 1) {
        while(i%n == 0) i /= n;
    }

    return i == 1;
}

/**
    logA(B) = logC(B)/logC(A)
**/
bool isPowerOfN2(int i, int n) {
    if (i < 1) return false;

    return i == pow(n, round((log(i) / log(n))));
}
/////////////////////////////////
// MATH
/////////////////////////////////
template<int n>
class Factorial {
public:
    enum {
        value = Factorial<n - 1>::value * n
    };
};

template<>
class Factorial<0> {
public:
    enum {
        value = 1
    };
};

int fact(int v) {
    int res = 1;
    for(int i = 1; i <= v; i++)
        res  = res * i;

    return res;
}

int fact2(int v) {
    if(v == 0) return 1;
    return v * fact2(v-1);
}

template<int U, int V>
class GCD {
public:
    enum {
        value = GCD<V, U%V>::value
    };
};

template<int U>
class GCD<U, 0> {
public:
    enum {
        value = U
    };
};

int gcd(int u, int v) {
    if(v == 0) return u;

    while(v) {
        int tmp = u%v;
        u = v;
        v = tmp;

    }
    return u;
}

int gcd2(int u, int v) {
    if(v == 0) return u;

    return gcd2(v, u%v);
}

template<int N>
class Fib {
public:
    enum {
        value = Fib<N-1>::value + Fib<N-2>::value
    };
};

template<>
class Fib<2> {
public:
    enum {
        value = 1
    };
};

template<>
class Fib<1> {
public:
    enum {
        value = 1
    };
};

int fib(int n) {
    if(n < 1) return 0;
    if(n < 3) return 1;

    int A[2] = {1,1};
    int res = 0;

    for(int i = 3; i <= n; i++) {
        res = A[0] + A[1];
        A[0] = A[1];
        A[1] = res;
    }
    return res;
}

int fib2(int n)
{
   if (n <= 1)
      return n;
   return fib2(n-1) + fib2(n-2);
}

int mult(int m, int n) {
    if(m == 0 || n == 0) return 0;
    int sign = 1;
    if(m < 0) { sign = -sign; m = -m; }
    if(n < 0) { sign = -sign; n = -n; }

    if(m < n) {
        swap(m, n);
    }

    int res = 0;
    for(int i = 0; i < n; i++) {
        res += m;
    }

    return sign < 0 ? -res : res;
}

int my_sqrt(int n) {
    if(n <= 0) return 0;
    if(n < 4) return 1;

    int l = 0;
    int r = n/2;

    while(l <= r) {
        int mid = l+(r-l)/2;
        if(mid*mid == n) return mid;
        if(mid*mid > n) r = mid - 1;
        else l = mid + 1;
    }

    return l-1;
}

int PowN(int m, int n) {
    if( m == 0) return 0;
    if(n <= 1 ) return m;

    int mm = m;
    int nn = n;

    while( nn /= 2) mm *= mm;

    if(n & 1 != 0) mm *= m;

    return mm;
}

bool isPrime(int n) {

    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    int sqrtn = sqrt(n);
    for(int i = 3; i <= sqrtn; i += 2) {
        if(n % i == 0) return false;
    }

    return true;

}

// The capacity of a new submap is calculated as the prime number
int nextPrime(int n) {

    if (n <= 2)
        return 2;

    if (n % 2 == 0)
        n++;

    while (!isPrime(n)) {
        n += 2;
    }

    return n;

}

void sieveOfEratosthenes(int n) {
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    bool prime[n+1];
    memset(prime, true, sizeof(prime));

    for (int p=2; p*p<=n; p++)
    {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples of p
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    for (int p=2; p<=n; p++)
       if (prime[p])
          cout << p << " ";
}

/////////////////////////////////
// INTERVIEW
/////////////////////////////////

namespace INTERVIEW {
	namespace E_COMERCE {

	    /*
            0) 2 EGGS AND 100 FLOORS
	    */

	    /*
            CALCULATE MOST PROFIT DEAL IN VERY LARGE ARRAY OF DEALS
	    */
		int MAXPROFIT(vector<int> v) {
			int max_profit = 0;
			int min_cost = 99999999;

			for(auto i : v) {
				min_cost = min(min_cost, i);
				int diff = i - min_cost;
				max_profit = max(diff, min_cost);
			}

			return max_profit;
		}

        /*
            CALCULATE SOME MULTIPLY/STATISTICS IN VERY LARGE DATA

            [1,2,3] -> [2*3, 1*3, 1*2]
        */
		vector<int> MULTIPLY(vector<int> v) {
			vector<int> res(v.size());
			res = {1};

			int product = 1;

			for(int i = 0; i < v.size(); i++) {
				res[i] *= product;
				product *= v[i];
			}

			product = 1;
			for(int i = v.size()-1; i >= 0; i++) {
				res[i] *= product;
				product *= v[i];
			}

			return res;
		}

		/*
            CALCULATE INTERSECTION OF RECTANGLES FOR STATISTIC DIAGRAMM
		*/

		/*
            return !(y1 > (y0 + h0) || x1 > (x0 + w0) || (y1 + h1) < y0 || (x1 + w1) < x0)
		*/
	}

	namespace SEARCH_ENGINE {
        /*
            Write a function that computes the Nth fibonacci number
            1) recursive
            2) dynamic
            3) iteration
        */

        int fib(int n) {
            return ::fib2(n);
        }


        /*
            SIMULATE 5 SIDE-DICE BY 7 SIDE-DICE
            res += _7_side_dice(); / 5 times
            return res % 5;
        */

        /*
            SIMULATE 7 SIDE-DICE BY 5 SIDE-DICE
            res += _5_side_dice(); / 7 times
            return res % 7;
        */

        /*
            WRITE A FUNCTION FOR REVERSE STRING RECURSIVE
        */
        void revert(string& s, int l, int r) {
            if(l > r) return;

            swap(s[l], s[r]);
            revert(s, l+1, r-1);
        }

        /*
            WRITE MY SQROOT
            // or use binary search
        */
        int my_sqrt(int i) {
            return ::my_sqrt(i);
        }
	}
}

/////////////////////////////////
// TEMPLATES
/////////////////////////////////


template<typename T>
void selection_sort_t(vector<T> &v) {
    if(v.size() < 2) return;

    for(size_t i = 0; i < v.size(); ++i) {
        size_t idx = i;
        for(size_t j = i+1; j < v.size(); ++j) {
            if(v[idx] > v[j]) idx = j;
        }

        if(i != idx)
            swap(v[i], v[idx]);
    }
}

template<typename T>
void insertion_sort_t(vector<T> &v) {
    if(v.size() < 2) return;

    for(size_t i = 0; i < v.size(); ++i) {
        size_t idx = i;
        while(idx) {
            if(v[idx] < v[idx-1]) swap(v[idx], v[idx-1]);
            idx--;
        }
    }
}


template<typename T>
void quick_sort_t(vector<T> &A, int l, int r){
    if(l >= r) return;

    int ll = l, rr = r;
    int mid = A[((ll + rr) >> 1)];

    while(ll <= rr){
        while (A[ll] < mid) ll++;
        while (A[rr] > mid) rr--;

        if(ll <= rr){
            swap(A[ll], A[rr]);
            ll++;
            rr--;
        }
    }

    quick_sort_t(A, l, rr);
    quick_sort_t(A, ll, r);
}

template<class T>
void merge_t(vector<T> &A, long l, long mid, long r) {
  	long ll = l;
    long size = r-l+1;
  	long rr = mid+1;
  	vector<T> temp;

  	while (ll <= mid && rr <= r) {
    	if (A[ll] < A[rr])
      		temp.push_back(A[ll++]);
    	else
      		temp.push_back(A[rr++]);
  	}

 	while (ll <= mid)
    		temp.push_back(A[ll++]);

  	while (rr <= r)
    		temp.push_back(A[rr++]);

  	for (int i = 0; i < size; i++)
    		A[l+i] = temp[i];
}

template<class T>
void merge_sort_t(vector<T> &A, long l, long r) {
	if (l >= r) return;

  int mid = (l + r)/2;
  merge_sort_t(A, l, mid);  
  merge_sort_t(A, mid+1, r);
  merge_t(A, l, mid, r); 
}

template<typename T>
size_t bin_search_t(vector<T> &v, T n) {
    if(v.empty()) return 0;

    size_t l = 0;
    size_t r = v.size()-1;

    while(l <= r) {
        size_t mid = l+(r-l)/2;

        if(v[mid] == n) return mid;
        else
        if(n < v[mid]) r = mid-1;
        else l = mid+1;
    }

    return 0;
}

template<typename T>
int bin_search_rotated_t(vector<T> &v, T key) {
  int l = 0;
  int r = v.size() - 1;

  while (l <= r) {
    // Avoid overflow, same as M=(L+R)/2
    int mid = l + ((r - l) / 2);
    if (v[mid] == key) return mid;

    // the bottom half is sorted
    if (v[l] <= v[mid]) {
      if (v[l] <= key && key < v[mid])
        r = mid - 1;
      else
        l = mid + 1;
    }
    // the upper half is sorted
    else {
      if (v[mid] < key && key <= v[r])
        l = mid + 1;
      else
        r = mid - 1;
    }
  }
  return -1;
}

template<typename T>
int find_sorted_array_rotation_t(vector<T> &v) {
  int l = 0;
  int r = v.size() - 1;

  while (v[l] > v[r]) {
    int mid = l + (r - l) / 2;
    if (v[mid] > v[r])
      l = mid + 1;
    else
      r = mid - 1;
  }
  return l;
}

/////////////////////////
// BACKTRAKING/PERMUTATIONS
/////////////////////////

void breakets_1(string s, int left, int right, int pairs) {
    if(right == left && left == pairs) {
        cout << s << endl;
        return;
    }

    cout << "call " << s << " " << left << " " << right << endl;

    if(left < pairs)
        breakets_1(s+"(", left+1, right, pairs);

    if(right < left)
        breakets_1(s+")", left, right+1, pairs);
}

void printPermute(string s, int l, int r) {
    if (l == r) {
        cout << s << endl;
        return;
    }

    cout << "call " << s << " " << l << " " << r << endl;

    for (int i = l; i <= r; i++) {
        swap(s[l], s[i]);
        printPermute(s, l+1, r);
        swap(s[l], s[i]); //backtrack
    }
}

/////////////////////////
// DYNAMIC
/////////////////////////

// 0(n*n) 0(n*n)
string longestPalindrome1(string s) {
    int len = s.size();
    bool P[len][len];

    memset(P, 0, sizeof(P[0][0]) * len * len);

    int maxL = 0, start = 0, end = 0;
    for(int i =0; i < s.size(); i++) {
        for(int j = 0; j < i; j++) {
            P[j][i] = (s[j] == s[i] && ( i - j < 2 || P[j+1][i-1]));
            if(P[j][i] && maxL < ( i - j + 1 )) {
                maxL = i - j + 1;
                start = j;
                end = i;
            }
        }
        P[i][i] = true;
    }

    cout << "  ";
    for(int i = 0; i < len; i++) {
        cout << s[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < len; i++) {
            cout << s[i] << " ";
        for(int j = 0; j < len; j++) {
            cout << P[i][j] << " ";
        }
        cout << endl;
    }

    return s.substr(start, end - start + 1);
}

// 0(n*n) O(1)
// Given a center, either one letter or two letter,
// Find longest palindrome
string expandFrmCenter(string s, int lidx, int ridx) {
    while(lidx >= 0 && ridx < s.size()) {
        if(s[lidx] != s[ridx]) {
            return s.substr(lidx+1, ridx-lidx-1);
        }
        --lidx;
        ++ridx;
    }
    return s.substr(lidx+1, ridx-lidx-1);
}

string longestPalindrome2(string s) {
    string res("");
    for(int i = 0; i < s.size(); ++i) {
        // get longest palindrome with center of i
        string s1 = expandFrmCenter(s,i,i);
        if(s1.size() > res.size()) res = s1;
        if(i+1 < s.size()) {
            // get longest palindrome with center of i, i+1
            string s2 = expandFrmCenter(s,i,i+1);
            if(s2.size() > res.size()) res = s2;
        }
    }
    return res;
}

// backtracking
int countCoinChange1(int S[], int m, int n ) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    if (m <= 0 && n >= 1) return 0;

    return countCoinChange1( S, m - 1, n ) + countCoinChange1( S, m, n - S[m-1] );
}

// dynamic
int countCoinChange2(int S[], int m, int n ) {
    int i, j, x, y;
    int table[n+1][m];

    for (i=0; i<m; i++)
        table[0][i] = 1;

    // Fill rest of the table enteries in bottom up manner
    for (i = 1; i < n+1; i++) {
        for (j = 0; j < m; j++) {
            // Count of solutions including S[j]
            x = (i-S[j] >= 0) ? table[i - S[j]][j] : 0;
            // Count of solutions excluding S[j]
            y = (j >= 1)? table[i][j-1]: 0;
            // total count
            table[i][j] = x + y;
        }
    }
    return table[n][m-1];
}

int lengthOfLongestSubstring(string s) {
    if(s.empty()) return 0;
    int prev = 0;

    map<char, int> hash;
    for(int i = 0; i < s.size(); i++) {
        if(hash.find(s[i]) == hash.end()) {
            hash[s[i]] = i;
        } else {
            prev = max(prev, (int)hash.size());
            i = hash[s[i]];
            hash.clear();
        }
    }

    return max(prev, (int)hash.size());
}

///1
///11
///121
///1331
///14641

// backtracking
int Pascal_1(int row, int column) {
    if(row < 0) return 0;
    if(row == 0) return 1;
    if(column == 0 || column == row-1) return 1;

    return Pascal_1(row-1, column-1) + Pascal_1(row-1, column);
}

// dynamic
vector<vector<int>> Pascal_2(int row) {
    if(row < 0) return {{}};

    vector<vector<int>> res;
    res.push_back({{1}});
    if(row == 0) return res;

    for(int i = 1; i < row; i++) {
        res.push_back({{1}});
        for(int j = 1; j < i; j++) {
            res[i].push_back(res[i-1][j-1] + res[i-1][j]);
        }
        res[i].push_back({1});
    }

    return res;
}

int MCS(vector<int> v) {
    int curr = 0;
    int buff = 0;

    for(int i = 0; i < v.size(); i++) {
        buff += v[i];
        if(buff < 0) buff = 0;
        else if(buff > curr) curr = buff;
    }

    return curr;
}

/**
Partition problem is to determine whether a given set can be partitioned
into two subsets such that the sum of elements in both subsets is same.
**/
int findPartition(vector<int> &arr, int n) {

    int sum = 0;
    for (int i = 0; i < n; i++)
       sum += arr[i];

    if (sum%2 != 0) return false;

    int i = n-1;
    int buff_sum = sum;
    for(; i >= 0; i--) {
        buff_sum -= arr[i];
        if(buff_sum == 0) break;
    }

    for(int j = 0; j <= i; j++) {
        sum -= arr[j];
    }

    return sum == 0 ? i : -1;
}

/////////////////////////
// GRAPHS
/////////////////////////

// This class represents a directed graph using adjacency list representation
class Graph {
    int V;    // No. of vertices
    vector<vector<int>> adj;    // an array containing adjacency lists
public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    void BFS(int s, int e);  // prints BFS traversal from a given source s
    void DFS(int s, int e);  // prints DFS traversal from a given source s
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v's list.
}

void Graph::BFS(int s, int e) {
    bool visited[V];

    memset(visited, 0, sizeof(visited[0]) * V);

    queue<int> q;

    visited[s] = true;
    q.push(s);

    while(!q.empty()) {
        s = q.front();
        cout << s << " ";
        q.pop();

        for(int i = 0; i < adj[s].size(); ++i) {
            if(e == adj[s][i]) {
                cout << "-> " << e << endl;
                return;
            }
            if(!visited[adj[s][i]]) {
                visited[adj[s][i]] = true;
                q.push(adj[s][i]);
            }
        }
    }

    cout << "no way" << endl;
}

void Graph::DFS(int s, int e) {
    bool visited[V];

    memset(visited, 0, sizeof(visited[0]) * V);

    stack<int> q;

    visited[s] = true;
    q.push(s);

    while(!q.empty()) {
        s = q.top();
        cout << s << " ";
        q.pop();

        for(int i = 0; i < adj[s].size(); ++i) {
            if(e == adj[s][i]) {
                cout << "-> " << e << endl;
                return;
            }
            if(!visited[adj[s][i]]) {
                visited[adj[s][i]] = true;
                q.push(adj[s][i]);
            }
        }
    }

    cout << "no way" << endl;
}

int main() {

    cout << "/////////////////////////////////" << endl;
    cout << "// MEMORY" << endl;
    cout << "/////////////////////////////////" << endl;

    char *str = NULL;
    mycpy_mem(&str, "HELLO WORLD");
    mycat_mem(&str, " GOODBYE");
    mycat(&str, "-BYE");
    mycat_mem(&str, "-BYE");
    mycat(&str, "-BYE");
    mycat_mem(&str, "-BYE");
    mycat(&str, "-BYE");
    mycat_mem(&str, "-BYE");
    mycat(&str, "-BYE");
    mysprintf(&str, "%s!", str);
    puts(str);
    myfree(&str);

    cout << endl;

    cout << mycmp("123", "123") << " ";
    cout << mycmp("", "123") << " ";
    cout << mycmp("123", "") << " ";
    cout << mycmp(NULL, "123") << " ";
    cout << mycmp("123", NULL) << " ";
    cout << mycmp("123", "1234567") << " ";
    cout << mycmp("123qwerty", "123") << " ";
    cout << mycmp(NULL, NULL) << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// TREE" << endl;
    cout << "/////////////////////////////////" << endl;

    tnode* root = NULL;

    int arr[] = {1,2,3,4,5,6,7,8,9};
    int l = 0;
    int r = 9;

    insertarray(root, arr, 9);

    if(!root) cout << "TREE IS NULL" << endl;

    cout << "BFS :" << endl;
    BFS(root);

    cout << endl;

    cout << "DFS :" << endl;
    DFS(root);

    cout << endl;

    cout << "inorder :" << endl;
    inorder(root);
    cout << endl;
    iterativeInorder(root);

    cout << endl;

    cout << "postorder :" << endl;
    postorder(root);
    cout << endl;
    iterativePostorder(root);

    cout << endl;

    cout << "preorder :" << endl;
    preorder(root);
    cout << endl;
    iterativePreorder(root);

    cout << endl;

    cout << "lca :" << endl << LowestCommonAcessor(root, 3, 7)->v << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// LIST" << endl;
    cout << "/////////////////////////////////" << endl;

    node *head = NULL;

    for(int i = 0; i < 10; i++) {
        insert(head, i);
    }

    print(head);

    cout << endl;

    cout << "rotate :" << endl;
    rotateList(head, 5);
    print(head);

    cout << endl;

    cout << "remove node :" << endl;
    removenode(head->next->next->next);
    print(head);

    cout << endl;

    cout << "revert inplace :" << endl;
    revert_inplace(head);
    print(head);

    cout << endl;

    cout << "revert inplace ptr:" << endl;
    revert_inplace_ptr(&head);
    print(head);

    cout << endl;

    cout << "reverse inpalce rec :" << endl;
    reverse_inpalce_rec(head);
    print(head);

    cout << endl;

    cout << "sort :" << endl;
    selectSort(head);
    print(head);

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// STRINGS" << endl;
    cout << "/////////////////////////////////" << endl;

    cout << firstUniqueChar("asdefrgtb") <<  endl;
    cout << removeChars("qwegfhrtnd", "derfh") <<  endl;
    cout << reverseWords("123 456 789") << endl;

    cout << endl;

    cout << dec2bin(21) << endl;
    cout << bin2dec("010101") << endl;

	cout << endl;

	cout << base2dec("010101", 2) << endl;
	cout << base2dec("0x1", 16) << endl;
	cout << base2dec("1", 16) << endl;
	cout << base2dec("0xAAA", 16) << endl;
	cout << base2dec("0xEEE", 16) << endl;
	cout << base2dec("0xABC", 16) << endl;

    cout << endl;

    cout << myatoi("-32 hello") <<  " ";
    cout << myatoi("   -32 hello ") <<  " ";
    cout << myatoi(" 32 hello ") <<  " ";
    cout << myatoi(" +64 hello ") << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// BIN" << endl;
    cout << "/////////////////////////////////" << endl;

    cout << dec2bin(swp(bin2dec("10110"))) << endl;
    cout << bin2dec("10101010101") << endl;
    cout << bin2dec("01010101010") << endl;
    cout << dec2bin(5) << endl;
    cout << dec2bin(ins(bin2dec("100001"), bin2dec("101"), 1, 3)) << endl;

    cout << endl;

    for(int i = 0; i < 10; i++) {
        cout << i << " : " << isPowerOfTwo(i) << endl;
    }

    cout << endl;

    for(int i = 0; i < 10; i++) {
        cout << i << " : " << isPowerOfN1(i, 3) << endl;
    }

    cout << endl;

    for(int i = 0; i < 10; i++) {
        cout << i << " : " << isPowerOfN2(i, 3) << endl;
    }

    cout << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// MATH" << endl;
    cout << "/////////////////////////////////" << endl;

    cout << my_sqrt(5) << " ";
    cout << my_sqrt(7) << " ";
    cout << my_sqrt(9) << " ";
    cout << my_sqrt(17) << endl;

    cout << endl;

    cout << "PRIME :" << endl;

    for(int i = 0; i < 20; i++) {
        cout << i << " : " << isPrime(i) << endl;
    }

    cout << endl;

    for(int i = 0; i < 10; i++) {
        cout << i << " : " << nextPrime(i) << endl;
    }

    cout << endl;

    sieveOfEratosthenes(15);

    cout << endl;

    cout << "-----------" << endl;

    cout << endl;

    cout << mult(0,0) <<  " ";
    cout << mult(0,1) <<  " ";
    cout << mult(1,0) <<  " ";
    cout << mult(1,1) <<  " ";
    cout << mult(1,-1) <<  " ";
    cout << mult(-1,1) <<  " ";
    cout << mult(0,-1) <<  " ";
    cout << mult(-1,0) <<  " ";
    cout << mult(2,1) <<  " ";
    cout << mult(1,2) <<  " ";
    cout << mult(9,1000) << endl;

    cout << endl;

    cout << Factorial<5>::value <<  " ";
    cout << fact(5) <<  " ";
    cout << fact2(5) << endl;

    cout << endl;

    cout << Fib<40>::value <<  " ";
    cout << fib(40) <<  " ";
    cout << fib2(40) << endl;

    cout << endl;

    cout << GCD<6, 4>::value <<  " ";
    cout << gcd(6, 4) <<  " ";
    cout << gcd2(6, 4) << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// INTERVIEW" << endl;
    cout << "/////////////////////////////////" << endl;

    cout << INTERVIEW::SEARCH_ENGINE::fib(6) << endl;
    string s = "asdfg";
    cout << "revert " << s << " : " ;
    INTERVIEW::SEARCH_ENGINE::revert(s, 0, 4);
    cout << s << endl;
    cout << INTERVIEW::SEARCH_ENGINE::my_sqrt(10) << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// TEMPLATES" << endl;
    cout << "/////////////////////////////////" << endl;

    vector<int> a = {6,5,4,7,8,3,2,3,4};
    selection_sort_t(a);
    for(auto i : a) cout << i <<  " ";

    cout << endl;

    a = {6,5,4,7,8,3,2,3,4};
    insertion_sort_t(a);
    for(auto i : a) cout << i <<  " ";

    cout << endl;

    a = {6,5,4,7,8,3,2,3,4};
    quick_sort_t(a, 0, a.size()-1);
    for(auto i : a) cout << i <<  " ";

    cout << endl;

    a = {6,5,4,7,8,3,2,3,4};
    merge_sort_t(a, 0, a.size()-1);
    for(auto i : a) cout << i <<  " ";

    cout << endl;
    cout << endl;

    a = {2,3,4,5,6,7,8,9};
    cout << bin_search_t(a, 3) << endl;

    cout << endl;

    a = {6,7,8,9,2,3,4,5};
    cout << bin_search_rotated_t(a, 3) << endl;

    cout << endl;

    a = {6,7,8,9,2,3,4,5};
    cout << find_sorted_array_rotation_t(a) << endl;

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// BACKTRAKING/PERMUTATIONS" << endl;
    cout << "/////////////////////////////////" << endl;

    breakets_1("", 0, 0, 3);

    cout << endl;

    printPermute("ABC", 0, 2);

    cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// DYNAMIC" << endl;
    cout << "/////////////////////////////////" << endl;


    cout << longestPalindrome1("1qq2qawaq123") << endl;
    cout << longestPalindrome2("1qq2qawaq123") << endl;

    cout << endl;

    int coins[] = {1,2,3};
    cout << countCoinChange1(coins, 3, 4) << endl;
    cout << countCoinChange2(coins, 3, 4) << endl;

    cout << endl;

    cout << lengthOfLongestSubstring("abcabcbb") << endl;

    cout << endl;

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < i; j++) {
            cout << Pascal_1(i,j);
        }
        cout << endl;
    }

    cout << endl;

    auto res = Pascal_2(5);

    for(auto i : res) {
        for(auto j : i)
            cout << j;
        cout << endl;
    }

    cout << endl;

    vector<int> v = {-2, -3, 4, -1, -2, 1, 5, -3};
    cout << MCS(v) << endl;

    cout << endl;

    vector<int> arr2 = {0, 4, -1, 1, -2, 2};
	cout << findPartition(arr2, arr2.size()) << endl;

	cout << endl;

    cout << "/////////////////////////////////" << endl;
    cout << "// GRAPH" << endl;
    cout << "/////////////////////////////////" << endl;

    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(1, 4);

    cout << "Following is Breadth First Traversal : ";
    g.BFS(0, 4);
    cout << endl << endl;

    cout << "Following is Depth First Traversal : ";
    g.DFS(0, 4);
    cout << endl << endl;

    cout << "Press any key ... " << endl;
    cin.get();

    return 0;
}
