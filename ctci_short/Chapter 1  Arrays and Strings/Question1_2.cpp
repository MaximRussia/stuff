
/**
1.2 Implement a function void reverse(char* str) in C or C++ which reverses a null-
terminated string.
**/

#include<iostream>
using namespace std;

void swap(char& c1, char& c2) {
	char tmp = c1;
	c1 = c2;
	c2 = tmp;
}

void reverse(string& str) {
	int len = str.size();
	for (int i = 0, j = len - 1; i != j; i++, j--)
		swap(str[i], str[j]);
}

int main() {
	string input[] = { "abcde", "cat" };

	for (int i = 0; i < 2; i++) {
		cout << "reversing the string: " << input[i] << endl;
		reverse(input[i]);
		cout << "reverse of input string is " << input[i] << endl;
	}

	return 0;
}
