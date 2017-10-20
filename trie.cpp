
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    char ch;
    map<char, Node*> children;

    Node(char ch) : ch(ch) {
    }

    Node* is(char ch) {
        auto res = children.find(ch);
        return res == children.end() ? NULL : res->second;
    }

    Node* add(char ch) {
        Node* tmp = new Node(ch);
        children[ch] = tmp;
        return tmp;
    }
};

struct Trie {
    Node* root;

    Trie() {
        root = new Node(' ');
    }

    void add(string str) {
        Node * curr = root;
        for(int i = 0; i < str.size(); ++i) {
            Node *find = curr->is(str[i]);
            if(find) {
                curr = find;
            } else {
                curr = curr->add(str[i]);
            }
        }
    }

    bool find(string str) {
        Node * curr = root;
        for(int i = 0; i < str.size(); ++i) {
            Node *find = curr->is(str[i]);
            if(find) {
                curr = find;
            } else {
                return false;
            }
        }

        return true;
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

int main() {

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

}
