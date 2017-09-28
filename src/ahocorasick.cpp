#include "ahocorasick.hpp"
#include "util.hpp"
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <tuple>

using namespace std;

namespace aho {

static vector<vector<int>> trie;
static vector<int> fail;
static vector<int> terminal;
static vector<string> pats;
static vector<int> alphabet_hash;
static int alphabet_size;

static void insert(string &s);
static void buildFsm();
static void buildFailure();


void build(const vector<string> &_pats) {
    pats = _pats;
    tie(alphabet_hash, alphabet_size) = getAlphabet(pats);
    trie.push_back(vector<int>(alphabet_size, -1));
    terminal.push_back(0);
    buildFsm();
    buildFailure();
}

int search(const string &txt) {
    int count = 0;
    int node = 0;
    for(unsigned char ch : txt) {
        int pos = alphabet_hash[ch];
        node = trie[node][pos];
        count += terminal[node];
    }

    return count;
}

static void insert(string &s) {
    int node = 0;
    for(char ch : s) {
        int pos = alphabet_hash[ch];
        if(trie[node][pos] == -1) {
            trie[node][pos] = (int) trie.size();
            trie.push_back(vector<int>(alphabet_size, -1));
            terminal.push_back(0);
        }
        node = trie[node][pos];
    }
    terminal[node] = 1;
}

static void buildFsm() {
    for(string &s : pats) {
        insert(s);
    }
}

static void buildFailure() {
    fail.assign(trie.size(), 0);
    queue<int> Q;
    
    for(int pos = 0; pos < alphabet_size; ++pos) {
        if(trie[0][pos] == -1) {
            trie[0][pos] = 0;
        }
        else {
            Q.push(trie[0][pos]);
        }
    }
    
    while(!Q.empty()) {
        int node = Q.front();
        Q.pop();
        
        for(int pos = 0; pos < alphabet_size; ++pos) {
            int &v = trie[node][pos];
            int f = trie[fail[node]][pos];
            
            if(v == -1) {
                v = f;
            }
            else {
                fail[v] = f;
                Q.push(v);
                terminal[v] += terminal[f];
            }
        }
    }
}

} //namespace aho
