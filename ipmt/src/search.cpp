#include "search.hpp"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include "lz77.hpp"
#include "suffixarray.hpp"

using namespace std;

static void decode(vector<int> &dest, char *src, int n, int bytes);
static char *buildTxt(vector<int> &SArr, vector<int> freq);

void search(vector<string> &pats, string &idxfile) {
  int n, bytes, ls, la;
  FILE *file = fopen(idxfile.c_str(), "rb");
  if (file == NULL) {
    printf("Couldn't open file: %s.", idxfile.c_str());
    exit(0);
  }
  fread(&n, sizeof(int), 1, file);
  fread(&bytes, sizeof(int), 1, file);
  fread(&ls, sizeof(int), 1, file);
  fread(&la, sizeof(int), 1, file);

  char *str = new char[n + 1];
  str[n] = '\0';
  vector<int> SArr(n / bytes), Llcp(n / bytes), Rlcp(n / bytes);

  fread(str, sizeof(char), n, file);
  char *encoded_SArr = lz77::decode(str, n, ls, la);
  decode(SArr, encoded_SArr, n, bytes);

  /*
  printf("%d %d %d %d\n", n, bytes, ls, la);
  for(int i = 0; i < n; ++i) {
    printf("%d ", encoded_SArr[i]);
  }
  puts("");
  */

  fread(str, sizeof(char), n, file);
  char *encoded_Llcp = lz77::decode(str, n, ls, la);
  decode(Llcp, encoded_Llcp, n, bytes);

  fread(str, sizeof(char), n, file);
  char *encoded_Rlcp = lz77::decode(str, n, ls, la);
  decode(Rlcp, encoded_Rlcp, n, bytes);

  fread(&n, sizeof(int), 1, file);
  fread(&bytes, sizeof(int), 1, file);
  printf("%d %d\n", n, bytes);
  delete[] str;
  str = new char[n + 1];
  str[n] = '\0';
  fread(str, sizeof(char), n, file);
  char *encoded_freq = lz77::decode(str, n, ls, la);
  vector<int> freq(sigma);
  decode(freq, encoded_freq, n, bytes);
  char *txt = buildTxt(SArr, freq);

  SuffixArray SA(SArr, Llcp, Rlcp, txt);
  for (string pat : pats) {
    char *p = new char[pat.size() + 1];
    pat.copy(p, string::npos, 0);
    p[pat.size()] = '\0';
    printf("Ocurrences of %s: %d\n", p, SA.search(p));
    delete[] p;
  }
}

static void decode(vector<int> &dest, char *src, int n, int bytes) {
  for (int i = 0; i < n; i += bytes) {
    int c = decodeInt(src + i, sizeof(char) * bytes);
    dest[i / bytes] = c;
  }
}

static char *buildTxt(vector<int> &SArr, vector<int> freq) {
  int n = (int)SArr.size();
  int m = (int)freq.size();
  char *txt = new char[n + 1];
  txt[n] = '\0';
  int ptr = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < freq[i]; ++j) {
      txt[SArr[ptr]] = i;
      ++ptr;
    }
  }
  printf("%d %d %d\n", n, m, ptr);
  return txt;
}