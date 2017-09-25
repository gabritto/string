#include "ahocorasick.hpp"

#include <vector>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

#include <assert.h>
AhoFSM::AhoFSM(const vector<string> &pats, const vector<int> &alphabet_hash, const int alphabet_size) {
    this->alphabet_hash = alphabet_hash;
    this->pats = pats;
    this->alphabet_size = alphabet_size;
    trie.push_back(vector<int>(alphabet_size, -1));
    terminal.push_back(0);
    build_fsm();
    build_failure();
}

int AhoFSM::search(const string &txt) {
    int count = 0;
    int node = 0;
    for(unsigned char ch : txt) {
        int pos = alphabet_hash[ch];
        node = trie[node][pos];
        count += terminal[node];
    }

    return count;
}

void AhoFSM::insert(string &s) {
    int node = 0;
    for(char ch : s) {
        int pos = alphabet_hash[ch];
        if(trie[node][pos] == -1) {
            trie[node][pos] = trie.size();
            trie.push_back(vector<int>(alphabet_size, -1));
            terminal.push_back(0);
        }
        node = trie[node][pos];
    }
    terminal[node] += 1;
}

void AhoFSM::build_fsm() {
    for(string &s : pats) {
        insert(s);
    }
}

void AhoFSM::build_failure() {
    fail.assign(trie.size(), 0);
    
    queue<int> Q;
    for(int pos = 0; pos < alphabet_size; ++pos) {
        if(trie[0][pos] == -1) trie[0][pos] = 0;
        else Q.push(trie[0][pos]);
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

