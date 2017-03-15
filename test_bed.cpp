#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;

////////////////////////
// MEMORY
////////////////////////

void* alloc_str(const char *str) {
    /// strlen(str) == strlen(str) * sizeof(char), char == 1 byte
    /// +1 for '\0'
    return malloc(strlen(str) + 1);
}

void my_cpy(char **res, const char *str) {
	if (!str) return;
	if (!*res) *res = (char*)alloc_str(str);
	char *ptr = *res;
	while (*ptr++ = *str++);
}

void my_cpy_mem(char **res, const char *str) {
	if (!str) return;
	size_t size = strlen(str) + 1;
	if (!*res) *res = (char*)malloc(size);
	char *ptr = *res;
	memcpy(ptr, str, size);
}

void my_cat(char **res, const char *str) {
	if (!str) return;
	char *ptr = *res;
	size_t size_res = strlen(*res);
	size_t size_str = strlen(str);
	size_t size = size_res + size_str + 1;
	ptr = (char*)realloc(*res, size);
	ptr += size_res; /// jump at '\0'
	while (*ptr++ = *str++);
}

void my_cat_mem(char **res, const char *str) {
	if (!str) return;
	char *ptr = *res;
	size_t len_res = strlen(*res);
	size_t len_str = strlen(str);
	size_t size = len_res + len_str + 1;
	ptr = (char*)realloc(*res, size);
	ptr += len_res;
	memcpy(ptr, str, len_str + 1);
}

void my_sprintf(char **res, const char *fmt, const char *str) {
	sprintf(*res, fmt, str);
}

void my_free(char **str) {
	free(*str);
	*str = NULL;
}

int my_cmp(char *str1, char *str2) {
	if (!str1 || !str2) return 1;

	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2) {
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

char* my_strstr(char* str1, char* str2) {
	if (!str1 || !str2) return "-1";

	for (; *str1 != '\0'; str1++) {
		if (*str1 != *str2) continue;

		char* move1 = str1;
		char* move2 = str2;
		while (*move1 != '\0' && *move2 != '\0') {
			if (*move1 != *move2)
				break;
			move1++;
			move2++;
		}

		if (*move2 == '\0')
			return str1;
	}

	return "-1";
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
	if (!root) {
		root = new tnode(v);
		return;
	}

	if (v < root->v) insert(root->left, v);
	else insert(root->right, v);
}

void BFS(tnode* &root) {
	if (!root)  {
		return;
	}

	queue<tnode*> q;
	q.push(root);

	while (!q.empty()) {
		tnode* n = q.front(); q.pop();

		cout << n->v << " ";
		if (n->left) q.push(n->left);
		if (n->right) q.push(n->right);
	}

	cout << endl;
}

//////////////////////
// DFS variations
//////////////////////
/******
Preorder  =   V-L-R
Inorder   =   L-V-R
Postorder =   L-R-V
*******/
void preorder(tnode* &root) {
	if (!root)  {
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

	cout << endl;
}

void inorder(tnode* &root) {
	if (!root)  {
		return;
	}

	inorder(root->left);
	cout << root->v << " ";
	inorder(root->right);
}

void iterativeInorder(tnode* &root) {
	if (!root)  {
		return;
	}

	stack<tnode*> s;
	tnode *node = root;

	while (!s.empty() || node) {
		if (node) {
			s.push(node);
			node = node->left;
		}
		else {
			node = s.top(); s.pop();
			cout << node->v << " ";
			node = node->right;
		}
	}

	cout << endl;
}

void postorder(tnode* &root) {
	if (!root)  {
		return;
	}

	postorder(root->left);
	postorder(root->right);
	cout << root->v << " ";
}

void iterativePostorder(tnode* &root) {
	if (!root) return;

	stack<tnode*> s;
	stack<tnode*> out;

	s.push(root);
	while (!s.empty()) {
		tnode *node = s.top(); s.pop();
		out.push(node);

		if (node->left) s.push(node->left);
		if (node->right) s.push(node->right);
	}

	while (!out.empty()) {
		tnode* node = out.top(); out.pop();
		cout << node->v << " ";
	}

	cout << endl;
}

int getHeight(tnode* root) {
	if (!root) return 0;
	return max(getHeight(root->right), getHeight(root->left)) + 1;
}

int maxValue(tnode* root) {
    int result = root->v;

    if(root->right) {
        result = std::max(result, maxValue(root->right));
    }

    if(root->left) {
        result = std::max(result, maxValue(root->left));
    }

    return result;
}

int minValue(tnode* root) {
    int result = root->v;

    if(root->right) {
        result = std::min(result, maxValue(root->right));
    }

    if(root->left) {
        result = std::min(result, maxValue(root->left));
    }

    return result;
}

int isBST(tnode* root) {
	if (!root) return 1;

	if (root->left != NULL && root->left->v >= root->v)
		return 0;

	if (root->right != NULL && root->right->v < root->v)
		return 0;

	return isBST(root->left) && isBST(root->right);
}

template<typename T = int>
int isBST2(tnode* root,
	T min = numeric_limits<T>::min(),
	T max = numeric_limits<T>::max()) {
	if (!root) return true;

	if (root->v <= min || root->v > max)
		return false;

	return isBST2(root->left, min, root->v) && isBST2(root->right, root->v, max);
}

/// BST
tnode* lowestCommonAcessor(tnode* root, int value1, int value2){
	if (!root) return NULL;
	if (root->v == value1 || root->v == value2)
		return root;

	while (root){
		if (root->v > max(value1, value2)){
			root = root->left;
		}
		else if (root->v < min(value1, value2)){
			root = root->right;
		}
		else {
			return root;
		}
	}
}

/// non BST
tnode* lowestCommonAcessor2(tnode* root, int value1, int value2){
	if (!root) return NULL;
	if (root->v == value1 || root->v == value2)
		return root;

	tnode* left = lowestCommonAcessor2(root->left, value1, value2);
	tnode* right = lowestCommonAcessor2(root->right, value1, value2);

	if (left && right)
		return root;

	return left ? left : right;
}

//////////////////////

void insertArray(tnode* &root, int arr[], int start, int end) {
	if (start > end) return;
	// same as (start+end)/2, avoids overflow.
	int mid = start + (end - start) / 2;
	root = new tnode(arr[mid]);
	insertArray(root->left, arr, start, mid - 1);
	insertArray(root->right, arr, mid + 1, end);
}

void printLevelByLevel(tnode* &root) {
	if (!root)  { cout << "empty" << endl; return; }

	queue<tnode*> q1;
	queue<tnode*> q2;
	q1.push(root);

	while (!q1.empty() || !q2.empty()) {
		if (!q1.empty()) {
			while (!q1.empty()) {
				tnode* node = q1.front(); q1.pop();
				cout << node->v << " ";
				if (node->left) q2.push(node->left);
				if (node->right) q2.push(node->right);
			}
		}
		else if (!q2.empty()) {
			while (!q2.empty()) {
				tnode* node = q2.front(); q2.pop();
				cout << node->v << " ";
				if (node->left) q1.push(node->left);
				if (node->right) q1.push(node->right);
			}
		}

		cout << endl;
	}
}

void clean(tnode* &root) {
	if (!root) return;
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
	if (!head) {
		head = new node(v);
		return;
	}
	insert(head->next, v);
}

void print(node* &head) {
	if (!head) {
		cout << endl;
		return;
	}

	cout << head->v << " ";
	print(head->next);
}

void removeNode(node* &head) {
	if (!head) return;
	if (!head->next) {
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

    int cnt = 0;
    node *move = head;
    while(cnt < k) {
        if(!move) return;
        move = move->next;
        cnt++;
    }

    node *res = head;
    while(move) {
        move = move->next;
        res = res->next;
    }

    cout << res->v << endl;
}

void appendHead(node* &head, node* n) {
	if (!head) {
		head = n;
		return;
	}

	n->next = head;
	head = n;
}

void clean(node* &head) {
	if (!head) return;
	clean(head->next);
	delete head;
	head = NULL;
}

void revert_inplace(node* &head) {
	if (!head || !head->next) return;

	node* prev = NULL;
	node* move = head;

	while (move) {
		node* next = move->next;
		move->next = prev;
		prev = move;
		move = next;
	}

	head = prev;
}

void revert_inplace_ptr(node** head) {
	if (!(*head) || !(*head)->next) return;

	node* prev = NULL;
	node* move = (*head);

	while (move) {
		node* next = move->next;
		move->next = prev;
		prev = move;
		move = next;
	}

	(*head) = prev;
}

void reverse_inpalce_rec(node*& head) {
	if (!head || !head->next) return;

	node* prev = head->next;

	reverse_inpalce_rec(prev);

	head->next->next = head;
	head->next = NULL;

	head = prev;
}

void selectSort(node* &head) {
	if (!head) return;

	node* first = head;

	while (first) {
		node* minn = first;
		node* fast = first;
		while (fast){
			if (fast->v < first->v) minn = fast;
			fast = fast->next;
		}

		if (minn != first)
			swap(minn->v, first->v);

		first = first->next;
	}
}

/////////////////////////////////
// ARRAYS
/////////////////////////////////
int mostFrequentInt(const vector<int> &v) {
	if (v.empty()) return -999999;

	int res = 0;
	int cnt = 0;
	map<int, int> hash;

	for (int i = 0; i < v.size(); i++) {
		if (hash.find(v[i]) == hash.end()) {
			hash[v[i]] = 1;
		}
		else {
			int buff = ++hash[v[i]];
			if (buff > cnt) {
				cnt = buff;
				res = v[i];
			}
		}
	}

	return res;
}

vector<pair<int, int>> pairOfSumm(const vector<int> &v, int summ) {
	vector<pair<int, int>> res;
	if (v.empty()) res;

	map<int, int> hash;
	for (int i = 0; i < v.size(); i++) {
		if (hash.find(v[i]) != hash.end()) {
			res.push_back(pair<int, int>(v[i], hash[v[i]]));
		}
		else {
			hash[summ - v[i]] = v[i];
		}
	}

	return res;
}

int findElementOnlyOnce(const vector<int> &v) {
	if (v.empty()) return -1;

	map<int, int> hash;

	for (int i = 0; i < v.size(); i++) {
		if (hash.find(v[i]) == hash.end()) {
			hash[v[i]] = 1;
		}
		else {
			hash[v[i]]++;
		}
	}

	for (auto i : hash) {
		if (i.second == 1) return i.first;
	}

	return -1;
}

vector<int> findCommonElements(const vector<int> &v1, const vector<int> &v2) {
	if (v1.empty() || v2.empty()) return{};

	vector<int> res;
	map<int, int> hash;

	for (int i = 0; i < v1.size(); i++) {
		hash[v1[i]] = v1[i];
	}

	for (int i = 0; i < v2.size(); i++) {
		if (hash.find(v2[i]) != hash.end()) {
			res.push_back(v2[i]);
		}
	}

	return res;
}

int maxProfit(vector<int> v) {
	int max_profit = 0;
	int min_cost = 99999999;

	for (auto i : v) {
		min_cost = min(min_cost, i);
		max_profit = max(i - min_cost, max_profit);
	}

	return max_profit;
}

/*
	CALCULATE SOME MULTIPLY/STATISTICS IN VERY LARGE DATA
	[1,2,3] -> [2*3, 1*3, 1*2] -> [6, 3, 2]
	*/
vector<int> multiply(vector<int> v) {

	vector<int> res(v.size());
	for (int i = 0; i < res.size(); i++)
		res[i] = 1;

	int product = 1;

	for (int i = 0; i < v.size(); i++) {
		res[i] *= product;
		product *= v[i];
	}

	product = 1;
	for (int i = v.size() - 1; i >= 0; i--) {
		res[i] *= product;
		product *= v[i];
	}

	return res;
}

int mostContSubsiquence(vector<int> v) {

	int prev = 0, curr = 0, res = 0;
	for (int i = 0; i < v.size(); i++) {
		curr += v[i];
		if (curr > prev) {
			res = curr;
		}
		else {
			curr = 0;
		}

		prev = curr;
	}

	return res;
}

/**
Partition problem is to determine whether a given set can be partitioned
into two subsets such that the sum of elements in both subsets is same.
**/
int findPartition(vector<int> &arr) {

	int sum = 0;
	for (int i = 0; i < arr.size(); i++)
		sum += arr[i];

	if (sum % 2 != 0) return -1;

	int buff_sum = sum / 2;
	int i = arr.size() - 1;
	for (; i >= 0; i--) {
		buff_sum -= arr[i];
		if (buff_sum == 0) break;
	}

	buff_sum = sum / 2;
	for (int j = 0; j < i; j++) {
		buff_sum -= arr[j];
	}

	return buff_sum == 0 ? i : -1;
}


/////////////////////////////////
// STRINGS
/////////////////////////////////
bool isBalanced(char ch1, char ch2) {
	if(ch1 == '(' && ch2 == ')') return true;
	if(ch1 == '[' && ch2 == ']') return true;
	if(ch1 == '{' && ch2 == '}') return true;
	return false;
}

bool checkBreakets(string str) {
	if (str.empty()) return false;

	stack<char> st;
	for(int i = 0; i < str.size(); i++) {
		if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
			st.push(str[i]);
		}
		else if(str[i] == ')' || str[i] == ']' || str[i] == '}') {
			if(st.empty()) return false;
			if(!isBalanced(st.top(), str[i])) return false;
			st.pop();
		}
	}

	return str.empty();
}


bool isAnagram(string s1, string s2) {
	if (s1.empty() || s2.empty()) return false;
	if (s1.size() != s2.size()) return false;

	int buff[26] = { 0 };

	for (int i = 0; i < s1.size(); i++) {
		buff[s1[i]]++;
	}

	for (int i = 0; i < s2.size(); i++) {
		buff[s1[i]]--;
	}

	for (int i = 0; i < 26; i++) {
		if (buff[i] != 0) return false;
	}

	return true;
}

char firstNonRepeated(string str) {
	if (str.empty()) return '\0';

	int buff[256] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		buff[str[i]]++;
	}

	for (int i = 0; i < str.size(); i++) {
		if (buff[str[i]] == 1) return str[i];
	}

	return '\0';
}

string revertIter(string s) {
	for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
		swap(s[i], s[j]);
	}

	return s;
}

string revertRec(string s, int l, int r) {
	if (l >= r) return s;

	swap(s[l], s[r]);
	l++;
	r--;

	return revertRec(s, l, r);
}

char firstUniqueChar(string s) {
	if (s.empty()) return '\0';

	char buff[256] = { 0 };

	for (size_t i = 0; i < s.size(); ++i) {
		++buff[s[i]];
	}

	for (size_t i = 0; i < s.size(); ++i) {
		if (buff[s[i]] == 1) return s[i];
	}

	return '\0';
}

string removeChars(string str, string rem) {
	if (str.empty() || rem.empty()) return str;

	bool buff[65535] = { false };
	for (size_t i = 0; i < rem.size(); i++) {
		buff[rem[i]] = true;
	}

	int dst = 0;

	for (size_t i = 0; i < str.size(); i++) {
		if (!buff[str[i]]) {
			str[dst] = str[i];
			dst++;
		}
	}

	return str.substr(0, dst);
}

string dec2bin(int dec) {
	string res;
	int len = 8 * sizeof(dec);

	while (len) {
		res = (dec & 1 ? "1" : "0") + res;
		dec >>= 1;
		len--;
	}

	return res;
}

int bin2dec(string s){
	if (s.empty()) return 0;

	int res = 0;
	int pwr = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		res += (s[i] - '0')*pow(2, pwr);
		pwr++;
	}

	return res;
}

int hex2num(char ch) {
	if (ch >= '0' && ch <= '9') return ch - '0';
	if (ch >= 'a' && ch <= 'f') return 10 + ch - 'a';
	if (ch >= 'A' && ch <= 'F') return 10 + ch - 'A';
	return -1;
}

int base2dec(string s, int base) {
	if (s.empty()) return -1;

	if (s[0] == '0' && s[1] == 'x') {
		s = s.substr(2);
	}

	int res = 0;
	int pwr = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		res += hex2num(s[i])*pow(base, pwr);
		pwr++;
	}

	return res;
}

int my_atoi(string str) {
	if (str.empty()) return 0;

	int res = 0;
	int i = 0;

	/// skip spaces
	while (str[i] == ' ') i++;

	/// get sign
	int sign = 1;
	if (str[i] == '-') {
		sign = -1;
		i++;
	}


	/// main convert loop
	while (i < str.size()) {
		if (!isdigit(str[i])) {
			break;
		}
		res = res * 10 + str[i] - '0';
		i++;
	}

	return sign*res;
}

void reverse(string &str, size_t l, size_t r) {

	for (size_t i = l, j = r; i < j; i++, j--) {
		swap(str[i], str[j]);
	}
}

/// "123 456 789"
string reverseWords(string str) {
	if (str.size() < 2) return str;

	reverse(str, 0, str.size() - 1);

	int prevIndex = 0;
	// reverse spaces
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			reverse(str, prevIndex, i - 1);
			prevIndex = i + 1;
		}
	}

	// reverse 'last space' to end
	reverse(str, prevIndex, str.size() - 1);

	return str;
}

int lengthOfLongestUniqueSubstring(string s) {
	if (s.empty()) return 0;
	int prev = 0;

	map<char, int> hash;
	for (int i = 0; i < s.size(); i++) {
		if (hash.find(s[i]) == hash.end()) {
			hash[s[i]] = i;
		}
		else {
			prev = max(prev, (int)hash.size());
			i = hash[s[i]];
			hash.clear();
		}
	}

	return max(prev, (int)hash.size());
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
	mask << (i + j);
	int mask2 = (1 << i) - 1;
	int res_mask = mask2 | mask;
	return (a & res_mask) | (b << i);
}

bool isPowerOfTwo(int x) {
	return (x != 0) && ((x & (x - 1)) == 0);
}

bool isPowerOfN1(int i, int n) {
	if (i > 1) {
		while (i%n == 0) i /= n;
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
class Factorial < 0 > {
public:
	enum {
		value = 1
	};
};

int factIter(int v) {
	int res = 1;
	for (int i = 1; i <= v; i++)
		res = res * i;

	return res;
}

int factRec(int v) {
	if (v == 0) return 1;
	return v * factRec(v - 1);
}

template<int U, int V>
class GCD {
public:
	enum {
		value = GCD<V, U%V>::value
	};
};

template<int U>
class GCD < U, 0 > {
public:
	enum {
		value = U
	};
};

int gcdIter(int u, int v) {
	if (v == 0) return u;

	while (v) {
		int tmp = u%v;
		u = v;
		v = tmp;

	}
	return u;
}

int gcdRec(int u, int v) {
	if (v == 0) return u;

	return gcdRec(v, u%v);
}

template<int N>
class Fib {
public:
	enum {
		value = Fib<N - 1>::value + Fib<N - 2>::value
	};
};

template<>
class Fib < 2 > {
public:
	enum {
		value = 1
	};
};

template<>
class Fib < 1 > {
public:
	enum {
		value = 1
	};
};

int fibIter(int n) {
	if (n < 1) return 0;
	if (n < 3) return 1;

	int A[2] = { 1, 1 };
	int res = 0;

	for (int i = 3; i <= n; i++) {
		res = A[0] + A[1];
		A[0] = A[1];
		A[1] = res;
	}
	return res;
}

int fibRec(int n) {
	if (n <= 1)
		return n;

	return fibRec(n - 1) + fibRec(n - 2);
}

int mult(int m, int n) {
	if (m == 0 || n == 0) return 0;
	int sign = 1;
	if (m < 0) { sign = -sign; m = -m; }
	if (n < 0) { sign = -sign; n = -n; }

	if (m < n) {
		swap(m, n);
	}

	int res = m;
	for (int i = 2; i <= n; i++) {
		res += m;
	}

	return sign*res;
}

int my_sqrt(int n) {
	if (n <= 0) return 0;
	if (n < 4) return 1;

	int l = 0;
	int r = n / 2;

	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (mid*mid == n) return mid;
		if (mid*mid > n) r = mid - 1;
		else l = mid + 1;
	}

	return l - 1;
}

// n^m
int PowN(int m, int n) {
	if (m <= 0) return 1;
	if (m == 1) return n;

	int res = m;
	for (int i = 2; i <= n; i++) {
		res *= m;
	}

	return res;
}

bool isPrime(int n) {

	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	int sqrtn = sqrt(n);
	for (int i = 3; i <= sqrtn; i += 2) {
		if (n % i == 0) return false;
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
	bool prime[n + 1];
	memset(prime, true, sizeof(prime));

	for (int p = 2; p*p <= n; p++)
	{
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true)
		{
			// Update all multiples of p
			for (int i = p * 2; i <= n; i += p)
				prime[i] = false;
		}
	}

	// Print all prime numbers
	for (int p = 2; p <= n; p++)
		if (prime[p])
			cout << p << " ";

	cout << endl;
}

/////////////////////////////////
// TEMPLATES
/////////////////////////////////

/**********
	Random
	Heap << Shell << Merge << Quick << Insertion << Bubble << Selection
	Nearly Sorted
	Insertion << Bubble << Shell << Heap << Merge << Quick << Selection
	Reversed
	Shell << Heap << Merge << Quick << Insertion << Bubble << Selection
	Few Unique
	Shell << Heap << Insertion << Merge << Quick << Bubble << Selection
	Out of memory
	External Merge Sort
	***********/

// O(n^2)
// Auxiliary Space: O(1)
// Sorting In Place: Yes
// Stable: Yes
template<typename T>
void selection_sort_t(vector<T> &v) {
	if (v.size() < 2) return;

	for (size_t i = 0; i < v.size(); ++i) {
		size_t idx = i;
		for (size_t j = i + 1; j < v.size(); ++j) {
			if (v[idx] > v[j]) idx = j;
		}

		if (i != idx)
			swap(v[i], v[idx]);
	}
}

// O(n^2)
// Auxiliary Space: O(1)
// Sorting In Place: Yes
// Stable: Yes
template<typename T>
void insertion_sort_t(vector<T> &v) {
	if (v.size() < 2) return;

	for (size_t i = 0; i < v.size(); ++i) {
		size_t idx = i;
		while (idx) {
			if (v[idx] < v[idx - 1]) swap(v[idx], v[idx - 1]);
			idx--;
		}
	}
}

// O(nlgn)
// Auxiliary Space: O(n) // stack
// Sorting In Place: Yes
// Stable: No
template<typename T>
void quick_sort_t(vector<T> &A, int l, int r){
	if (l >= r) return;

	int ll = l, rr = r;
	int mid = A[((ll + rr) >> 1)];

	while (ll <= rr){
		while (A[ll] < mid) ll++;
		while (A[rr] > mid) rr--;

		if (ll <= rr){
			swap(A[ll], A[rr]);
			ll++;
			rr--;
		}
	}

	quick_sort_t(A, l, rr);
	quick_sort_t(A, ll, r);
}

// O(nlgn)
// Auxiliary Space: O(n) // temp
// Sorting In Place: No
// Stable: Yes
template<class T>
void merge_t(vector<T> &A, long l, long mid, long r) {
	long ll = l;
	long size = r - l + 1;
	long rr = mid + 1;
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
		A[l + i] = temp[i];
}

template<class T>
void merge_sort_t(vector<T> &A, long l, long r) {
	if (l >= r) return;

	int mid = l + (r - l) / 2;
	merge_sort_t(A, l, mid);
	merge_sort_t(A, mid + 1, r);
	merge_t(A, l, mid, r);
}

template<typename T>
int bin_search_t(vector<T> &v, T n) {
	if (v.empty()) return 0;

	int l = 0;
	int r = v.size() - 1;

	while (l <= r) {
		int mid = l + (r - l) / 2;

		if (v[mid] == n) return mid;
		else
			if (n < v[mid]) r = mid - 1;
			else l = mid + 1;
	}

	return 0;
}

template<typename T>
int bin_search_rotated_t(vector<T> &v, T key) {
	int l = 0;
	int r = v.size() - 1;

	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (v[mid] == key) return mid;

		// the bottom half is sorted
		if (v[l] <= v[mid]) {
			if (v[l] <= key && key < v[mid])
				r = mid - 1;
			else
				l = mid + 1;
		}
		else { // the upper half is sorted
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

void breakets(string s, int left, int right, int pairs) {
	if (right == left && left == pairs) {
		cout << s << endl;
		return;
	}

	cout << "call " << s << " " << left << " " << right << endl;

	if (left < pairs)
		breakets(s + "(", left + 1, right, pairs);

	if (right < left)
		breakets(s + ")", left, right + 1, pairs);
}

void printPermute(string s, int l, int r) {
	if (l == r) {
		cout << s << endl;
		return;
	}

	cout << "call " << s << " " << l << " " << r << endl;

	for (int i = l; i <= r; i++) {
		swap(s[l], s[i]);
		printPermute(s, l + 1, r);
		swap(s[l], s[i]); //backtrack
	}
}

vector< vector<int> > allsubsets(vector<int> v) {
    vector< vector<int> > res;
    if(v.empty()) return res;

    size_t max = 1 << v.size();

    for(size_t flag = 1; flag < max; flag++) {
        size_t idx = 0;
        size_t t = flag;
        res.push_back({});
        while(t) {
            idx++;
            if(t & 1) {
                res.back().push_back(v[v.size()-idx]);
            }
            t >>= 1;
        }
    }
}

/////////////////////////
// DYNAMIC
/////////////////////////

// 0(n*n) O(1)
// Given a center, either one letter or two letter,
// Find longest palindrome
string expandFrmCenter(string s, int lidx, int ridx) {
	while (lidx >= 0 && ridx < s.size() && s[lidx] == s[ridx]) {
		--lidx;
		++ridx;
	}
	return s.substr(lidx + 1, ridx - lidx - 1);
}

string longestPalindrome(string s) {
	string res;
	for (int i = 0; i < s.size(); ++i) {
		// get longest palindrome with center of i
		string s1 = expandFrmCenter(s, i, i);
		if (s1.size() > res.size()) res = s1;
		if (i + 1 < s.size()) {
			// get longest palindrome with center of i, i+1
			string s2 = expandFrmCenter(s, i, i + 1);
			if (s2.size() > res.size()) res = s2;
		}
	}
	return res;
}

// backtracking
int countCoinChangeRec(const vector<int>& S, int m, int n) {
    if (n == 0) return 1;
     
    if (n < 0) return 0;
 
    // If there are no coins and n is greater than 0, then no solution exist
    if (m <=0 && n >= 1) return 0;
 
    return countCoinChangeRec( S, m - 1, n ) + countCoinChangeRec( S, m, n-S[m-1] );
}

// dynamic
int countCoinChangeIter( const vector<int>& S, int m, int n ) {
    // table[i] will be storing the number of solutions for
    // value i. We need n+1 rows as the table is consturcted
    // in bottom up manner using the base case (n = 0)
    int table[n+1];
 
    memset(table, 0, sizeof(table));
    table[0] = 1;
 
    // Pick all coins one by one and update the table[] values
    // after the index greater than or equal to the value of the
    // picked coin
    for(int i=0; i<m; i++)
        for(int j=S[i]; j<=n; j++)
            table[j] += table[j-S[i]];
 
    return table[n];
}

///1
///11
///121
///1331
///14641

// backtracking
int PascalRec(int row, int column) {
	if (row < 0) return 0;
	if (row == 0) return 1;
	if (column == 0 || column == row - 1) return 1;

	return PascalRec(row - 1, column - 1) + PascalRec(row - 1, column);
}

// dynamic
vector<vector<int>> PascalIter(int row) {
	if (row < 0) return{ {} };

	vector<vector<int>> res;
	res.push_back({ { 1 } });
	if (row == 0) return res;

	for (int i = 1; i < row; i++) {
		res.push_back({ { 1 } });
		for (int j = 1; j < i; j++) {
			res[i].push_back(res[i - 1][j - 1] + res[i - 1][j]);
		}
		res[i].push_back({ 1 });
	}

	return res;
}

int NumWays(int N) {
    if(N <= 0 ) return 0;
    if(N == 1) return 1;

    vector< vector<int> > cache;
    cache.resize(N);
    for(int i = 0; i < cache.size(); i++) {
        cache[i].resize(N);
        cache[i][0] = 1;
    }

    for(int i = 0; i < N; i++) {
        cache[0][i] = 1;
    }

    for(int i = 1; i < N; i++) {
        for(int j = 1; j < N; j++) {
            cache[i][j] = cache[i-1][j] + cache[i][j - 1];
        }
    }

    return cache.back().back();
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
	adj[w].push_back(v); // Add v to w's list.
}

void Graph::BFS(int s, int e) {
	bool visited[V];

	memset(visited, 0, sizeof(visited[0]) * V);

	queue<int> q;

	visited[s] = true;
	q.push(s);

	while (!q.empty()) {
		s = q.front();
		cout << s << " ";
		q.pop();

		for (int i = 0; i < adj[s].size(); ++i) {
			if (e == adj[s][i]) {
				cout << "-> " << e << endl;
				return;
			}
			if (!visited[adj[s][i]]) {
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

	while (!q.empty()) {
		s = q.top();
		cout << s << " ";
		q.pop();

		for (int i = 0; i < adj[s].size(); ++i) {
			if (e == adj[s][i]) {
				cout << "-> " << e << endl;
				return;
			}
			if (!visited[adj[s][i]]) {
				visited[adj[s][i]] = true;
				q.push(adj[s][i]);
			}
		}
	}

	cout << "no way" << endl;
}


/// 'A'..'z' implementation
map<string, vector<string>> generateGraph(vector<string> &dict) {
	map<string, vector<string>> graph;

	set<char> cached; /// cache characters
	cout << "dict: ";
	for (auto word : dict) {
		cout << word << " ";
		for (auto ch : word) {
			cached.insert(ch);
		}
	}

	cout << endl;

	cout << "cached size : " << cached.size() << endl;
	cout << "cached : ";

	for (auto ch : cached) {
		cout << ch;
	}

	cout << endl;

	for (int i = 0; i < dict.size(); i++) {
		/// process every single word in dictionary
		for (int j = 0; j < dict[i].size(); j++) {

			/// remove j-th char
			string remove = dict[i].substr(0, j) + dict[i].substr(j + 1);
			if (find(dict.begin(), dict.end(), remove) != dict.end()) {
				// find in dictionary! add this like adjective!
				graph[dict[i]].push_back(remove);
			}

			/// change j-th char
			for (auto ch : cached) {
				string change = dict[i].substr(0, j) + string(1, ch) + dict[i].substr(j + 1);
				if (find(dict.begin(), dict.end(), change) != dict.end() && change != dict[i]) {
					// find in dictionary! add this like adjective!
					graph[dict[i]].push_back(change);
				}
			}

			/// add at j-th char
			for (auto ch : cached) {
				string add = dict[i].substr(0, j) + string(1, ch) + dict[i].substr(j);
				if (find(dict.begin(), dict.end(), add) != dict.end()) {
					// find in dictionary! add this like adjective!
					graph[dict[i]].push_back(add);
				}
			}
		}
	}

	return graph;
}

vector<string> transformWordBFS(map<string, vector<string>> &graph,
	string start, string goal) {
	/// Breadth First Search
	queue<vector<string>> paths;
	paths.push({ start });

	while (!paths.empty()) {
		vector<string> currentPath = paths.front(); paths.pop();
		string currentWord = currentPath.back();

		if (currentWord == goal) {
			return currentPath;
		}

		vector<string> transforms = graph[currentWord];
		for (auto word : transforms) {
			if (find(currentPath.begin(), currentPath.end(), word)
				== currentPath.end()) {
				currentPath.push_back(word);
				paths.push(currentPath);
			}
		}
	}

	cout << "path is empty" << endl;
	return vector<string>();
}

vector<string> transformWordDFS(map<string, vector<string>> &graph,
	string start, string goal) {
	/// Depth First Search
	stack<vector<string>> paths;
	paths.push({ start });

	while (!paths.empty()) {
		vector<string> currentPath = paths.top(); paths.pop();
		string currentWord = currentPath.back();

		if (currentWord == goal) {
			return currentPath;
		}

		vector<string> transforms = graph[currentWord];
		for (auto word : transforms) {
			if (find(currentPath.begin(), currentPath.end(), word)
				== currentPath.end()) {
				currentPath.push_back(word);
				paths.push(currentPath);
			}
		}
	}

	cout << "path is empty" << endl;
	return vector<string>();
}

int main() {
	cout << "/////////////////////////////////" << endl;
	cout << "// MEMORY" << endl;
	cout << "/////////////////////////////////" << endl;
	char *str = NULL;
	my_cpy_mem(&str, "HELLO WORLD");
	my_cat_mem(&str, " GOODBYE");
	my_cat(&str, "-BYE");
	my_cat_mem(&str, "-BYE");
	my_cat(&str, "-BYE");
	my_cat_mem(&str, "-BYE");
	my_cat(&str, "-BYE");
	my_cat_mem(&str, "-BYE");
	my_cat(&str, "-BYE");
	my_sprintf(&str, "%s!", str);
	puts(str);
	my_free(&str);
	cout << my_cmp("123", "123") << " ";
	cout << my_cmp("", "123") << " ";
	cout << my_cmp("123", "") << " ";
	cout << my_cmp(NULL, "123") << " ";
	cout << my_cmp("123", NULL) << " ";
	cout << my_cmp("123", "1234567") << " ";
	cout << my_cmp("123qwerty", "123") << " ";
	cout << my_cmp(NULL, NULL) << endl;

	cout << my_strstr("123", "123") << " ";
	cout << my_strstr("", "123") << " ";
	cout << my_strstr("123", "") << " ";
	cout << my_strstr(NULL, "123") << " ";
	cout << my_strstr("123", NULL) << " ";
	cout << my_strstr("123", "1234567") << " ";
	cout << my_strstr("123qwerty", "123") << " ";
	cout << my_strstr(NULL, NULL) << endl;

	cout << endl << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// TREE" << endl;
	cout << "/////////////////////////////////" << endl;

	tnode* root = NULL;

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	insertArray(root, arr, 0, 8);
	printLevelByLevel(root);

	if (!root) cout << "TREE IS NULL" << endl;

	cout << "BFS :" << endl;
	BFS(root);

	cout << "DFS" << endl;

	cout << "preorder :" << endl;
	preorder(root); cout << endl;
	iterativePreorder(root);

	cout << "inorder :" << endl;
	inorder(root); cout << endl;
	iterativeInorder(root);

	cout << "postorder :" << endl;
	postorder(root); cout << endl;
	iterativePostorder(root);

	cout << maxValue(root) << endl;
	cout << minValue(root) << endl;
	cout << getHeight(root) << endl;
	cout << isBST(root) << endl;
	cout << isBST2(root) << endl;

	cout << "lca : " << lowestCommonAcessor(root, 3, 7)->v << endl;
	cout << "lca2 : " << lowestCommonAcessor2(root, 3, 7)->v << endl;

	cout << endl << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// LIST" << endl;
	cout << "/////////////////////////////////" << endl;

	node *head = NULL;

	for (int i = 0; i < 10; i++) {
		insert(head, i);
	}

	print(head);

	printKthLast(head, 7);

	cout << "remove node :" << endl;
	removeNode(head->next->next->next);
	print(head);

	cout << "revert inplace :" << endl;
	revert_inplace(head);
	print(head);

	cout << "revert inplace ptr:" << endl;
	revert_inplace_ptr(&head);
	print(head);

	cout << "reverse inpalce rec :" << endl;
	reverse_inpalce_rec(head);
	print(head);

	cout << "sort :" << endl;
	selectSort(head);
	print(head);

	cout << endl << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// ARRAYS" << endl;
	cout << "/////////////////////////////////" << endl;

	cout << mostFrequentInt({ 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 7, 7 }) << endl;

	auto res = pairOfSumm({ 1, 2, 3, 4, 5, 6, 7, 5 }, 10);
	for (auto i : res) cout << i.first << " " << i.second << endl;

	cout << findElementOnlyOnce({ 1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 9, 9 }) << endl;

	auto res1 = findCommonElements({ 1, 2, 3, 4, 5, 6, 7 }, { 8, 9, 0, 3, 4, 5 });
	for (auto i : res1) cout << i << " "; cout << endl;

	cout << maxProfit({ 2, 3, 4, 1, 5, 6, 8, 2, 3 }) << endl;

	auto res2 = multiply({ 1, 2, 3 });
	for (auto i : res2) cout << i << " ";

	cout << endl;

	vector<int> v = { 1, 2, 3, 4, -1, 7, 7, 7 };
	cout << mostContSubsiquence(v) << endl;

	vector<int> arr2 = { 1, 2, 3, 4, 6, 4, 0 };
	cout << findPartition(arr2) << endl;

	cout << endl << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// STRINGS" << endl;
	cout << "/////////////////////////////////" << endl;
    cout << checkBreakets("(()()())[[[]]]{{}}") << endl;
    cout << checkBreakets("()(){}{}{}()(())]") << endl;
	cout << isAnagram("qwerty", "erwqyt") << endl;
	cout << firstNonRepeated("qwertqwefrt") << endl;
	cout << revertIter("1234qwerty") << endl;
	cout << revertRec("1234qwerty", 0, 9) << endl;
	cout << removeChars("hello world goodby", "hlrg") << endl;
	cout << reverseWords("123 456 789") << endl;
	cout << lengthOfLongestUniqueSubstring("abcabcbb") << endl;
	cout << dec2bin(21) << endl;
	cout << bin2dec("010101") << endl;
	cout << base2dec("010101", 2) << endl;
	cout << base2dec("0x1", 16) << endl;
	cout << base2dec("1", 16) << endl;
	cout << base2dec("0xA", 16) << endl;
	cout << base2dec("0xE", 16) << endl;
	cout << base2dec("0xF", 16) << endl;
	cout << my_atoi("-32 hello") << " ";
	cout << my_atoi("   -32 hello ") << " ";
	cout << my_atoi(" 32 hello ") << " ";
	cout << my_atoi(" +64 hello ") << endl;

	cout << endl << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// BIN" << endl;
	cout << "/////////////////////////////////" << endl;

	cout << dec2bin(swp(bin2dec("10110"))) << endl;
	cout << bin2dec("10101010101") << endl;
	cout << bin2dec("01010101010") << endl;
	cout << dec2bin(5) << endl;
	cout << dec2bin(ins(bin2dec("100001"), bin2dec("101"), 1, 3)) << endl;

	cout << endl;

	for (int i = 0; i < 10; i++) {
		cout << i << " : " << isPowerOfTwo(i) << endl;
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		cout << i << " : " << isPowerOfN1(i, 3) << endl;
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		cout << i << " : " << isPowerOfN2(i, 3) << endl;
	}

	cout << endl << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// MATH" << endl;
	cout << "/////////////////////////////////" << endl;

	cout << PowN(2, 3) << endl;
	cout << PowN(3, 2) << endl;
	cout << PowN(4, 2) << endl;

	cout << my_sqrt(5) << " ";
	cout << my_sqrt(7) << " ";
	cout << my_sqrt(9) << " ";
	cout << my_sqrt(17) << endl;

	cout << endl;

	cout << "PRIME :" << endl;

	for (int i = 0; i < 20; i++) {
		cout << i << " : " << isPrime(i) << endl;
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		cout << i << " : " << nextPrime(i) << endl;
	}

	sieveOfEratosthenes(15);


	cout << mult(0, 0) << " ";
	cout << mult(0, 1) << " ";
	cout << mult(1, 0) << " ";
	cout << mult(1, 1) << " ";
	cout << mult(1, -1) << " ";
	cout << mult(-1, 1) << " ";
	cout << mult(0, -1) << " ";
	cout << mult(-1, 0) << " ";
	cout << mult(2, 1) << " ";
	cout << mult(1, 2) << " ";
	cout << mult(3, 2) << " ";
	cout << mult(4, 3) << " ";
	cout << mult(9, 1000) << endl;

	cout << Factorial<5>::value << " ";
	cout << factIter(5) << " ";
	cout << factRec(5) << endl;

	cout << Fib<40>::value << " ";
	cout << fibIter(40) << " ";
	cout << fibRec(40) << endl;

	cout << GCD<6, 4>::value << " ";
	cout << gcdIter(6, 4) << " ";
	cout << gcdRec(6, 4) << endl;

	cout << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// TEMPLATES" << endl;
	cout << "/////////////////////////////////" << endl;

	vector<int> a = { 6, 5, 4, 7, 8, 3, 2, 3, 4 };
	selection_sort_t(a);
	for (auto i : a) cout << i << " ";

	cout << endl;

	a = { 6, 5, 4, 7, 8, 3, 2, 3, 4 };
	insertion_sort_t(a);
	for (auto i : a) cout << i << " ";

	cout << endl;

	a = { 6, 5, 4, 7, 8, 3, 2, 3, 4 };
	quick_sort_t(a, 0, a.size() - 1);
	for (auto i : a) cout << i << " ";

	cout << endl;

	a = { 6, 5, 4, 7, 8, 3, 2, 3, 4 };
	merge_sort_t(a, 0, a.size() - 1);
	for (auto i : a) cout << i << " ";

	cout << endl;
	cout << endl;

	a = { 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << bin_search_t(a, 3) << endl;

	cout << endl;

	a = { 6, 7, 8, 9, 2, 3, 4, 5 };
	cout << bin_search_rotated_t(a, 3) << endl;

	cout << endl;

	a = { 6, 7, 8, 9, 2, 3, 4, 5 };
	cout << find_sorted_array_rotation_t(a) << endl;

	cout << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// BACKTRAKING/PERMUTATIONS" << endl;
	cout << "/////////////////////////////////" << endl;

	breakets("", 0, 0, 3);

	cout << endl;

	printPermute("ABC", 0, 2);

	auto res_sub = allsubsets({1,2,3});

	for (auto i : res_sub) {
		for (auto j : i)
			cout << j;
		cout << endl;
	}

	cout << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// DYNAMIC" << endl;
	cout << "/////////////////////////////////" << endl;


	cout << longestPalindrome("1qq2qawaq123") << endl;

	cout << endl;
	cout << countCoinChangeIter({ 1, 2, 3 }, 3, 4) << endl;
	cout << countCoinChangeRec({ 1, 2, 3 }, 3, 4) << endl;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < i; j++) {
			cout << PascalRec(i, j);
		}
		cout << endl;
	}

	cout << endl;

	auto res3 = PascalIter(5);

	for (auto i : res3) {
		for (auto j : i)
			cout << j;
		cout << endl;
	}

	cout << endl;

	cout << NumWays(5) << endl;

	cout << "/////////////////////////////////" << endl;
	cout << "// GRAPH" << endl;
	cout << "/////////////////////////////////" << endl;


	/**********
	0->[1,2]
	1->[2,4]
	2->[0,3]
	3->[4]
	***********/
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(1, 4);

	cout << "Following is BFS : ";
	g.BFS(0, 4);

	cout << "Following is DFS : ";
	g.DFS(0, 4);

	vector<string> dict = { "cat", "bat", "bet", "bed", "at", "ad", "ed" };
	map<string, vector<string>> graph = generateGraph(dict);
	for (auto x : graph) {
		std::cout << x.first << " : ";
		for (auto v : x.second) cout << v << " ";
		cout << std::endl;
	}

	cout << endl;

	cout << "DFS : " << endl;
	vector<string> res4 = transformWordDFS(graph, "cat", "bed");
	for (string v : res4) cout << v << endl;

	cout << endl;

	cout << "BFS : " << endl;
	res4 = transformWordBFS(graph, "cat", "bed");
	for (string v : res4) cout << v << endl;

	cout << "Press any key ... " << endl;
	cin.get();

	return 0;
}
