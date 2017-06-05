/**
	Find Next Higher Number With Same Digits
	Given  a  number,  find  the  next  higher  number  using  only  the  digits  in  the  given  number.  For
	example if the given number is 1234, next higher number with same digits is 1243.
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

int _atoi(string s) {
	return atoi(s.c_str());
}

string next_higher_number(string num) {
	char n = num[0];
	int index = 0;
	int buf = _atoi(num);
	for (int i = 1; i < num.size(); i++) {
		if (num[i] > n) {
			n = num[i];
			index = i;
		}
	}

	for (int i = num.size() - 1; i >= 0; i--) {
		if (_atoi(num) <= buf) {
			swap(num[i], num[index]);
			index = i;
		} else return num;
	}

	return "";
}

int main() {

	cout << next_higher_number("1233") << endl;

	return 0;
}
