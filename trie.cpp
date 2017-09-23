#include <atomic>
#include <future>
#include <thread>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Node {
    Node(char ch) : ch(ch) {
    }

    Node* is(char ch) {
         map<char, Node*>::const_iterator it = children.find(ch);
         if(it != children.end()) {
            return it->second;
         }
         return NULL;
    }

    Node* add(char ch) {
        children[ch] = new Node(ch);
        return children[ch];
    }

    char ch;
    bool end;
    map<char, Node*> children;
};

class Trie {
    Node *root;

    public:
    Trie() : root(NULL){
        root = new Node('\0');
    }

    bool find(string s) {
        Node* current = root;
        for(int i = 0; i < s.size(); i++) {
            Node* find = current->is(s[i]);
            if(find) {
                current = find;
                continue;
            }
            return false;
        }
        return true;
    }

    void add(string s) {
        Node* current = root;
        for(int i = 0; i < s.size(); i++) {
            Node* find = current->is(s[i]);
            if(!find) {
                current = current->add(s[i]);
                continue;
            }
            current = find;
        }
    }

    void BFS() {
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* r = q.front(); q.pop();
            for(auto &i : r->children) {
                cout << i.first << " ";
                q.push(i.second);
            }
            cout << endl;
        }
    }
};

int main(void) {

    Trie t;

    t.add("dog");
    t.add("daaag");
    t.add("friend");

    t.BFS();

    cout << t.find("dog") << endl;
    cout << t.find("dag") << endl;
    cout << t.find("daag") << endl;
    cout << t.find("daaag") << endl;
    cout << t.find("daaa") << endl;
    cout << t.find("frnd") << endl;

    return 0;
}
