/**
	First Non Repeated Character in String
	Find the first non­repeated (unique) character in a given string.
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cstring>
using namespace std;

char first_non_repeated(string str) {
	char res = '\0';
	bool duplicated = false;

	for (int i = 0; i < str.size(); i++) {
		for (int j = i + 1; j < str.size(); j++) {
			if (str[i] == str[j]) {
				duplicated = true;
				break;
			}
		}
		if (duplicated) continue;

		return str[i];
	}

	return '\0';
}

int main() {

	cout << first_non_repeated("abc") << endl;

	return 0;
}
