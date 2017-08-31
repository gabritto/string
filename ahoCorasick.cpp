#include <bits/stdc++.h>

using namespace std;

class AhoCorasick
{
public:
    AhoCorasick(vector<string> &p, string &alpha)
    {
        this->alpha = alpha;
        hsh.resize(256);
        int i = 0;
        for(auto ch : alpha)
        {
            hsh[ch] = i;
            ++i;
        }
        pat = p;
        trie.push_back(vector<int>(alpha.size(), -1));
        fim.push_back(false);
        build_fsm();
        build_failure();
    }

private:
    vector<vector<int>> trie;
    vector<int> fail;
    vector<bool> fim;
    vector<string> pat;
    string alpha;
    vector<int> hsh;
    void insert(string &s)
    {
        int no = 0;
        for(auto ch : s)
        {
            int pos = hsh[ch];
            if(trie[no][pos] == -1)
            {
                trie[no][pos] = trie.size();
                trie.push_back(vector<int>(alpha.size(), -1));
                fim.push_back(false);
            }
            no = trie[no][pos];
        }
        fim[no] = true;
    }
    
    void build_fsm()
    {
        for(auto &s : pat)
        {
            insert(s);
        }
    }
    void build_failure()
    {
        fail.assign(trie.size(), 0);
        
        queue<int> Q;
        for(int pos = 0; pos < alpha.size(); ++pos)
        {
            if(trie[0][pos] == -1) trie[0][pos] = 0;
            else Q.push(trie[0][pos]);
        }
        
        while(!Q.empty())
        {
            int no = Q.front();
            Q.pop();
            
            for(int pos = 0; pos < alpha.size(); ++pos)
            {
                int &v = trie[no][pos];
                int f = trie[fail[no]][pos];
                
                if(v == -1)
                {
                    v = f;
                }
                else
                {
                    fail[v] = f;
                    Q.push(v);
                    
                    /* merge info */
                }
            }
        }
    }
};


int main()
{

}
