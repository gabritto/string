#include <vector>
#include <string>
#include <cstring>
#include <tuple>
#include "util.hpp"
#include "shiftor.hpp"

using namespace std;

typedef unsigned long long ulong;

namespace shiftor {
static vector<int> alphabet_hash;
static int alphabet_size;
static vector<vector<ulong>> C;
static vector<string> patterns;

void build(const vector<string> &_patterns) {
  patterns = _patterns;
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
    ulong S = ~0ULL;
    int m = patterns[p].size();
    ulong msb = 1ULL << (m - 1);
    for(int j = 0; j < n; ++j) {
      int c = alphabet_hash[(unsigned char) txt[j]];
      S = (S << 1) | C[p][c];
      if(!(S & msb)) {
        occ += 1;
      }
    }
  }
  return occ;
}

} //namespace shiftor






