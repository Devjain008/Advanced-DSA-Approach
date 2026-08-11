#include<bits/stdc++.h>
using namespace std;


class Node {
  public:
  Node* links[26];
  bool end = false;
  Node() {
    for(int i = 0; i<26; i++) {
      links[i] = nullptr;
    }
  }
  bool containKey(char c) {
    return links[c - 'a'];
  }
  void put(char c, Node* node) {
    links[c - 'a'] = node;
  }
  Node* get(char c) {
    return links[c - 'a'] ;
  }
  bool isEnd() {
    return end;
  }
  bool setEnd() {
    end = true;
  }
};

class Trie{
  Node* root;
  public:
  Trie() {
    root = new Node();
  }

  void insert(string& s) {
    Node* node = root;
    for(char c : s) {
      if(!node->containKey(c)) {
        node->put(c, new Node());
      }
      node = node->get(c);
    }
    node->setEnd();
  }

  bool startWith(string &s) {
    Node* node = root;
    for(char c : s) {
      if(!node->containKey(c)) return false;
      node = node->get(c);
    }
    return true;
  }
  bool match(string &s) {
    Node* node = root;
    for(char c : s) {
      if(!node->containKey(c)) return false;
      node = node->get(c);
    }
    return node->isEnd();
  }
};


int main() {

    Trie trie;

    string s1 = "apple";
    string s2 = "app";
    string s3 = "bat";

    trie.insert(s1);
    trie.insert(s2);
    trie.insert(s3);

    string s = "app";

    cout << trie.match(s) << endl;      // 1
    cout << trie.startWith(s) << endl; // 1

    string x = "ap";
    cout << trie.match(x) << endl;      // 0
    cout << trie.startWith(x) << endl; // 1

    return 0;
  
}