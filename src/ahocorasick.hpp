#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <vector>
#include <string>
#include <queue>

using namespace std;

class AhoFSM {
public:
    AhoFSM(const vector<string> &pats, const vector<int> &alphabet_hash, const int alphabet_size);
    int search(const string &txt);

private:
    vector<vector<int>> trie;
    vector<int> fail;
    vector<int> terminal;
    vector<string> pats;
    vector<int> alphabet_hash;
    int alphabet_size;

    void insert(string &s);   
    void build_fsm();
    void build_failure();
};

#endif