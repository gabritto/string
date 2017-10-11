#include <vector>
#include <string>
#include <cstring>
#include <tuple>
#include "util.hpp"
#include "wumanber.hpp"

using namespace std;

typedef unsigned long long ulong_t;

namespace wumanber {
static vector<int> alphabet_hash;
static int alphabet_size;
static vector<vector<ulong_t>> C;
static vector<string> patterns;
static int err;

void build(const vector<string> &_patterns, int r) {
  patterns = _patterns;
  err = r;
  tie(alphabet_hash, alphabet_size) = getAlphabet(patterns);
  C.assign(patterns.size(), vector<ulong_t>(alphabet_size, ~0ULL));
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
    ulong_t msb = 1ULL << (m - 1);
    vector<ulong_t> S(err + 1, ~0ULL);
    for(int i = 1; i <= err; ++i) {
      S[i] = S[i - 1] << 1;
    }
    for(int j = 0; j < n; ++j) {
      int c = alphabet_hash[(unsigned char) txt[j]];
      ulong_t oldS = S[0];
      S[0] = (S[0] << 1) | C[p][c];
      for(int q = 1; q <= err; ++q) {
        ulong_t newOldS = S[q];
        S[q] = ((S[q] << 1) | C[p][c]) & (oldS << 1) &
          (S[q - 1] << 1) & oldS;
        oldS = newOldS;
      }
      if(!(S[err] & msb)) {
        occ += 1;
      }
    }
  }
  return occ;
}

} //namespace wumanber






