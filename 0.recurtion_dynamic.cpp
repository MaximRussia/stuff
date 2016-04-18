
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

///
/// get all subsets
///
vector<vector<int>> all_subsets(vector<int> data) {
	vector<vector<int>> res;

	if (data.size() == 0) {
		res.push_back(vector<int>());
		return res;
	}

	int val = data.back();
	data.pop_back();

	vector<vector<int>> r1 = all_subsets(data);
	for (int i = 0; i < r1.size(); i++) {
		res.push_back(r1[i]);
		r1[i].push_back(val);
		res.push_back(r1[i]);
	}

	return res;
}
///

///
/// get all string permutations
///
vector<string> permutations(string str) {
    vector<string> res;
    if(str.empty()) return res;
    if(str.size() == 1)  { res.push_back(str); return res; }

    vector<string> perms = permutations(str.substr(1));

    for( auto perm : perms) {
        for(int i = 0; i <= perm.size(); i++) {
            string s = perm;
            s.insert(i, 1, str[0]);
            res.push_back(s);
        }
    }

    return res;
}
///

///
/// print all brackets variants
///
void Brackets(string output, int open, int close, int pairs) {
    if((open == pairs)&&(close == pairs)) {
        cout << output << endl;
    }
    else
    {
        if(open < pairs)
            Brackets(output + "(", open + 1, close, pairs);
        if(close < open)
            Brackets(output + ")", open, close + 1, pairs);
    }
}

void Brackets(int n) {
    Brackets("", 0, 0, n);
}
///

///
/// climbing stairs
///
int climbing_stairs(int n, map<int, int> &m) {
    if (m.find(n) == m.end()) {
        m[n] = climbing_stairs(n-1, m) + climbing_stairs(n-2, m) + climbing_stairs(n-3, m);
    }
    return m[n];
}

int climbing_stairs(int n) {
    if (n <= 0) { return 0; }

    map<int, int> m;
    m[1] = 1;
    m[2] = 2;
	m[3] = 3;

    return climbing_stairs(n, m);
}
///

int main() {

    Brackets(3);

	return 0;
}
