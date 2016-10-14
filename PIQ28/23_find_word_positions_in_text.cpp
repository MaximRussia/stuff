/**
	Find Word Positions in Text
	Given a text file and a word, find the positions that the word occurs in the file. We’ll be asked to
	find the positions of many words in the same file.
	**/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
	Node() { mLetter = ' '; mTerminator = false; }
	~Node() {}
	void setLetter(char c) { mLetter = c; }
	char getLetter() { return mLetter; }
	void setTerminator() { mTerminator = true; }
	bool hasTerminator() { return mTerminator; }
	void appendChild(Node* child) { mChildren.push_back(child); }
	Node* findChild(char c);
	void printNode();
	void printBranch(Node*, char *, int count);
	vector<Node*> children() { return mChildren; }

private:
	char mLetter;
	bool mTerminator;
	vector<Node*> mChildren;
};

Node* Node::findChild(char c) {
	for (size_t i = 0; i < mChildren.size(); i++) {
		Node* ptr = mChildren.at(i);
		if (ptr->getLetter() == c) {
			return ptr;
		}
	}

	return NULL;
}

void Node::printBranch(Node *node, char *word, int count) {
	if (node->mLetter != ' ')  {
		word[count++] = node->mLetter;
	}
	if (node->hasTerminator()) {
		cout << endl;
		for (int i = 0; i < count; i++) {
			cout << word[i];
		}
	}

	for (int i = 0; i < (node->mChildren).size(); i++) {
		printBranch((node->mChildren).at(i), word, count);
	}
}

void Node::printNode() {
	char *word = new char[200];
	for (size_t i = 0; i < mChildren.size(); i++) {
		Node* ptr = mChildren.at(i);
		printBranch(ptr, word, 0);
	}
}

class Trie {
public:
	Trie();
	void addWord(string s);
	bool searchWord(string s);
	void printTrie();
	void printBranch(Node*);
private:
	Node* root;
};


void Trie::printTrie() {
	root->printNode();
}

Trie::Trie() {
	root = new Node();
}

void Trie::addWord(string s) {
	Node* current = root;

	if (s.length() == 0) {
		current->setTerminator();
		return;
	}

	for (size_t i = 0; i < s.length(); i++) {
		Node* child = current->findChild(s[i]);
		if (child != NULL) {
			current = child;
		}
		else {
			Node* ptr = new Node();
			ptr->setLetter(s[i]);
			current->appendChild(ptr);
			current = ptr;
		}
		if (i == s.length() - 1) {
			current->setTerminator();
		}
	}
}

bool Trie::searchWord(string s) {
	Node* current = root;

	while (current != NULL) {
		for (size_t i = 0; i < s.length(); i++) {
			Node* ptr = current->findChild(s[i]);
			if (ptr == NULL)
				return false;
			current = ptr;
		}

		if (current->hasTerminator())
			return true;
		else
			return false;
	}
	return false;
}

int main() {
	Trie* trie = new Trie();
	trie->addWord("cat");
	trie->addWord("cats");
	trie->addWord("catsdogcats");
	trie->addWord("catxdogcatsrat");
	trie->addWord("dog");
	trie->addWord("dogcatsdog");
	trie->addWord("hippopotamuses");
	trie->addWord("rat");
	trie->addWord("ratcatdogcat");

	if (!trie->searchWord("hippopotamus"))
		cout << "Not Found hippopotamus" << endl;

	if (trie->searchWord("catsdogcats"))
		cout << "Found catsdogcats" << endl;

	if (trie->searchWord("ratcatdogcat"))
		cout << "Found ratcatdogcat" << endl;

	trie->printTrie();

	delete trie;

	return 0;
}
