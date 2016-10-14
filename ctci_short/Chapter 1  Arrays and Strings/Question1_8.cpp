
/**
1.8 Assume you have a method isSubstring which checks if one word is a
substring of another. Given two strings, si and s2, write code to check if s2 is
a rotation of si using only one call to isSubstring (e.g.,"waterbottle" is a rota-
tion of "erbottlewat").
**/

#include<iostream>
#include<string>
using namespace std;

bool isRotation(const string& s1, const string& s2) {
	return (s1 + s1).find(s2) != string::npos;
}

int main() {
	string a = "apple";
	string b = "leapp";
	cout << "Checking if string: " << a << " is a rotation of string: " << b << ": "
		<< isRotation(a, b) << endl;

	a = "james";
	b = "mesje";
	cout << "Checking if string: " << a << " is a rotation of string: " << b << ": "
		<< isRotation(a, b) << endl;

	return 0;
}
