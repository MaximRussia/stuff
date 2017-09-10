#include <iostream>
#include <map>
using namespace std;

class Node {
public:
    Node(char ch) { mContent = ch; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren[child->content()] = child; }

private:
    char mContent;
    bool mMarker;
    map<char, Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

Node* Node::findChild(char c) {

    map<char, Node*>::const_iterator it = mChildren.find(c);
    if(it != mChildren.end())
        return it->second;

    return NULL;
}

Trie::Trie() {
    root = new Node(' ');
}

Trie::~Trie() {
    // Free memory
}

void Trie::addWord(string s) {
    Node* current = root;

    if (s.empty()) {
        current->setWordMarker(); // an empty word
        return;
    }

    for (int i = 0; i < s.length(); i++) {
        Node* child = current->findChild(s[i]);
        if (child) {
            current = child;
        } else {
            Node* tmp = new Node(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if (i == s.length() - 1)
            current->setWordMarker();
    }
}


bool Trie::searchWord(string s) {
    Node* current = root;

    while (current) {
        for (int i = 0; i < s.length(); i++) {
            Node* tmp = current->findChild(s[i]);
            if (!tmp) return false;
            current = tmp;
        }

        return current->wordMarker();
    }

    return false;
}


// Test program
int main() {
    Trie* trie = new Trie();
    trie->addWord("Hello");
    trie->addWord("Balloon");
    trie->addWord("Ball");

    if (trie->searchWord("Hell"))
        cout << "Found Hell" << endl;

    if (trie->searchWord("Hello"))
        cout << "Found Hello" << endl;

    if (trie->searchWord("Helloo"))
        cout << "Found Helloo" << endl;

    if (trie->searchWord("Ball"))
        cout << "Found Ball" << endl;

    if (trie->searchWord("Balloon"))
        cout << "Found Balloon" << endl;

    delete trie;
}
