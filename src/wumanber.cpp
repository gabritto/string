#include <vector>
#include <string>
#include <cstring>
#include <tuple>
#include "util.hpp"
#include "wumanber.hpp"

using namespace std;

typedef unsigned long long ulong;

namespace wumanber {
static vector<int> alphabet_hash;
static int alphabet_size;
static vector<vector<ulong>> C;
static vector<string> patterns;
static int err;

void build(const vector<string> &_patterns, int r) {
  patterns = _patterns;
  err = r;
  tie(alphabet_hash, alphabet_size) = getAlphabet(patterns);
  C.assign(patterns.size(), vector<ulong>(alphabet_size, ~0ULL));
  for(int p = 0; p < int(patterns.size()); ++p) {
    string &pat = patterns[p];
    for(int j = 0; j < int(pat.size()); ++j) {
      int c = alphabet_hash[(unsigned char) pat[j]];
      C[p][c] &= ~(1ULL << j);
    }
  }
}

int search(const char *txt) {
  int n = strlen(txt);
  int occ = 0;
  for(int p = 0; p < int(patterns.size()); ++p) {
    int m = patterns[p].size();
    ulong msb = 1ULL << (m - 1);
    vector<vector<ulong>> S(err + 1, vector<ulong>(n + 1, ~0ULL));
    for(int i = 1; i <= err; ++i) {
      S[i][0] = S[i - 1][0] << 1;
    }
    for(int j = 1; j <= n; ++j) {
      int c = alphabet_hash[(unsigned char) txt[j - 1]];
      S[0][j] = (S[0][j - 1] << 1) | C[p][c];
      for(int q = 1; q <= err; ++q) {
        S[q][j] = ((S[q][j - 1] << 1) | C[p][c]) & (S[q - 1][j - 1] << 1) &
          (S[q - 1][j] << 1) & (S[q - 1][j - 1]);
      }
      if(!(S[err][j] & msb)) {
        occ += 1;
      }
    }
  }
  return occ;
}

} //namespace wumanber






