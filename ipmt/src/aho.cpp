#include "aho.hpp"
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

static const int sigma = 256;

namespace aho {

vector<int> alphabet_hash;
static int getAlphabetHash(const char *pat, int l, int r);

vector<vector<int>> buildFSM(const char *pat, int l, int r) {
  int m = r - l;
  int alphabet_size = getAlphabetHash(pat, l, r);
  vector<vector<int>> fsm(m, vector<int>(alphabet_size, 0));
  for (int i = 0; i < alphabet_size; ++i) {
    fsm[0][i] = 0;
  }
  if (l >= r) {
    return fsm;
  }
  fsm[0][alphabet_hash[pat[l]]] = 1;
  int brd = 0;
  for (int i = 1; i <= m; ++i) {
    for (int s = 0; s < alphabet_size; ++s) {
      fsm[i][s] = fsm[brd][s];
    }
    if (i < m) {
      fsm[i][alphabet_hash[pat[l + i]]] = i + 1;
      brd = fsm[brd][alphabet_hash[pat[l + i]]];
    }
  }
  return fsm;
}

// builds aho-corasick fsm for string pat[l:r]
static int getAlphabetHash(const char *pat, int l, int r) {
  int i = 1;
  alphabet_hash.assign(sigma, 0);
  for (int j = l; j < r; ++j) {
    unsigned char ch = pat[j];
    if (alphabet_hash[ch] == 0) {
      alphabet_hash[ch] = i++;
    }
  }
  return i;
}

}  // namespace aho
