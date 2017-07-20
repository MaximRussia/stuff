/**
	Find Word Positions in Text
	Given a text file and a word, find the positions that the word occurs in the file. We’ll be asked to
	find the positions of many words in the same file.
	**/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

int main() {

    map<string, int> cache;

    ifstream file("wordsforproblem.txt");

    stringstream ss;
    ss << file.rdbuf();
    file.close();

    while(!ss.eof()) {
        string s;
        ss >> s;
        if(cache.find(s) == cache.end()) {
            cache[s] = 1;
        } else {
            cache[s]++;
        }
    }

	return 0;
}
