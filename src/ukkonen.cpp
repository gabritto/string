#include "util.hpp"
#include "ukkonen.hpp"

#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

namespace ukkonen {

static vector<vector<vector<int>>> trie;
static vector<vector<int>> node_id;
static vector<vector<vector<int>>> fsm;
static vector<int> alphabet_hash;
static vector<vector<bool>> is_final;
static int alphabet_size;
static int node_count = 0;
static int err;

static vector<int> next_column(const vector<int> &col, const string &pat, int ch);
static pair<int, bool> insert(const vector<int> &col, int p);

void build(const vector<string> &patterns, int r) {
  tie(alphabet_hash, alphabet_size) = getAlphabet(patterns);
  int pats_size = (int) patterns.size();
  trie.resize(pats_size);
  fsm.resize(pats_size);
  node_id.resize(pats_size);
  is_final.resize(pats_size);
  for(int p = 0; p < int(patterns.size()); ++p) {
    const string &pat = patterns[p];
    int m = (int) pat.size();
    err = r;
    vector<int> col(m + 1, 0);
    for(int i = 0; i < m + 1; ++i) {
      col[i] = min(i, err + 1);
    }
    fsm[p].push_back(vector<int>(alphabet_size, -1));
    
    trie[p].push_back(vector<int>(3, -1));
    node_id[p].push_back(-1);
    
    int col_id;
    bool is_new;
    tie(col_id, is_new) = insert(col, p);
    queue<pair<vector<int>, int>> Q;
    Q.push({col, col_id});
    
    while(!Q.empty()) {
      tie(col, col_id) = Q.front();
      Q.pop();
      for(int ch = 0; ch < alphabet_size; ++ch) {
        vector<int> newcol = next_column(col, pat, ch);
        bool is_new;
        int newcol_id;
        tie(newcol_id, is_new) = insert(newcol, p);
        if(is_new) {
          Q.push({newcol, newcol_id});
          fsm[p].push_back(vector<int>(alphabet_size, -1));
        }
        fsm[p][col_id][ch] = newcol_id;
      }
    }
  }
}

int search(const char *txt) {
  int cur = 0;
  int occ = 0;
  for(int p = 0; p < int(fsm.size()); ++p) {
    for(int i = 0; txt[i] != '\0'; ++i) {
      int c = alphabet_hash[(unsigned char) txt[i]];
      cur = fsm[p][cur][c];
      if(is_final[p][cur]) {
        ++occ;
      }
    }
  }
  return occ;
}

static vector<int> next_column(const vector<int> &col, const string &pat, int ch) {
  int m = (int) col.size();
  vector<int> newcol(m, 0);
  for(int i = 1; i < m; ++i) {
    int phi = 0;
    if(ch != alphabet_hash[(unsigned char) pat[i - 1]]) {
      phi = 1;
    }
    newcol[i] = min(err + 1, min(newcol[i - 1] + 1, min(col[i] + 1, col[i - 1] + phi)));
  }
  return newcol;
}

static pair<int, bool> insert(const vector<int> &col, int p) {
  int cur = 0;
  int m = (int) col.size();
  bool is_new = false;
  for(int i = 0; i < m; ++i) {
    int d = 1 + col[i];
    if(i > 0) {
      d -= col[i - 1];
    }
    if(trie[p][cur][d] == -1) {
      int nxt = (int) trie[p].size();
      trie[p].push_back(vector<int>(3, -1));
      node_id[p].push_back(-1);
      trie[p][cur][d] = nxt;
      
      if(i == m - 1) {
        is_new = true;
        is_final[p].push_back(col[m - 1] <= err);
        node_id[p][nxt] = node_count++;
      }
    }
    cur = trie[p][cur][d];
  }
  return {node_id[p][cur], is_new};
}

} //namespace ukkonen











