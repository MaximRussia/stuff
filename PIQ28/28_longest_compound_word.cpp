/**
	28. Longest Compound Word
	Given a sorted list of words, find the longest compound word in the list that is constructed by
	concatenating the words in the list. For example, if the input list is: [‘cat’, ‘cats’, ‘catsdogcats’,
	‘catxdogcatsrat’,  ‘dog’,  ‘dogcatsdog’,  ‘hippopotamuses’,  ‘rat’,  ‘ratcat’,  ‘ratcatdog’,  ‘ratcatdogcat’].
	Then  the  longest  compound  word  is  ‘ratcatdogcat’  with  12  letters.  Note  that  the  longest
	individual words are ‘catxdogcatsrat’ and ‘hippopotamuses’ with 14 letters, but they’re not fully
	constructed by other words. Former one has an extra ‘x’ letter, and latter is an individual word by
	itself not a compound word.
	**/

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Comparision structure to be passed in the set,
 * such that the words are inserted into the list
 * in an ordered way based on their length
 *
 */
struct compare {
	bool operator() (const string& lhs, const string& rhs) const {
		return lhs.length() >= rhs.length();
	}
};


class Words {
private:
	set<string, compare> storage;			// Container for storing the words
	// in order based on the length of
	// the word.

	set<string, compare>::iterator storageIterator; // Iterator on the storage container

	vector<string> sortedList;			// Container for storing the words.
	// Assumes that the list is already
	// sorted.

	bool isWordInList(string w);			// Finds if the word is present
	// in the list. It assumes that
	// the list is sorted and uses
	// binay search.
	//
	// Returns true/false

	bool isWordACompound(string w, int len);	// Finds if the word is a combination
	// of smaller words present in the file
	//
	// Returns true/false

public:
	Words(char *filename);				// Constructor
	void displayStorage();				// Debugging method to print out the contents
	// of the storage container

	vector<string> findNLongestCompoundWord(int num);
	int findCountofAllCompoundedWords();

};


/*
 * Constructor
 */
Words::Words(char *filename) {

	ifstream fd(filename);

	if (!fd.is_open()) {
		throw string("Error opening file: " + string(filename));
	}

	string word;
	while (getline(fd, word)) {
		if (!word.empty()) {
			storage.insert(word);
			sortedList.push_back(word);
			word.clear();
		}
	}

	fd.close();
}

/*
 * search if the word is in the list or not
 * It assumes that the list is sorted and uses
 * binary search.
 *
 * Other alternative is to use Trie as the storage,
 * thus reducing the search time complexity
 */
bool Words::isWordInList(string w) {
	return binary_search(sortedList.begin(), sortedList.end(), w);
}

/*
 * Debugging method to display all the words
 * in the storage member, sorted by length of
 * the word
 */
void Words::displayStorage() {

	for (storageIterator = storage.begin(); storageIterator != storage.end(); storageIterator++) {
		cout << *storageIterator << endl;
	}
}

/*
 * Method to find if a word is compound or not.
 */
bool Words::isWordACompound(string s, int origLen) {
	if (s.length() == 0) {
		return true;
	}
	for (unsigned int i = 0; i <= s.length(); ++i) {
		if (i < (unsigned int)origLen &&
			isWordInList(s.substr(0, i)) &&
			isWordACompound(s.substr(i, s.length()), origLen)) {
			return true;
		}
	}
	return false;

}

/*
 * Method to return a set of N longest compound strings
 *
 * arg: int N
 * returns: vector
 */
vector<string> Words::findNLongestCompoundWord(int num) {
	vector<string> result;
	int count = 0;
	for (storageIterator = storage.begin(); storageIterator != storage.end(); storageIterator++) {
		if (count >= num)
			break;
		if (isWordACompound(*storageIterator, (*storageIterator).length())) {
			result.push_back(*storageIterator);
			++count;
		}
	}
	return result;
}

/*
 * Count the number of compunded strings in the list
 *
 */
int Words::findCountofAllCompoundedWords() {
	int count = 0;
	for (storageIterator = storage.begin(); storageIterator != storage.end(); storageIterator++) {
		if (isWordACompound(*storageIterator, (*storageIterator).length())) {
			++count;
		}
	}
	return count;
}

int main(int argc, char **argv) {

	try {
		Words w("wordsforproblem.txt");
		vector<string> res = w.findNLongestCompoundWord(2);
		if (res.size() == 2) {
			cout << "First Longest Compounded Word   : " << res.front() << endl;
			cout << "Second Longest Compounded Word  : " << res.back() << endl << endl;
		}
		cout << "Total number of compounded words: " << w.findCountofAllCompoundedWords() << endl;
	} catch (string s) {
		cout << "Exception: " << s << endl;
	}
} // end of main function
