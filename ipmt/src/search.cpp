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
static int ceilLog2(int n);

void search(vector<string> &pats, string &idxfile) {
  int n, ls, la;
  FILE *file = fopen(idxfile.c_str(), "rb");
  if (file == NULL) {
    printf("Couldn't open file: %s.", idxfile.c_str());
    exit(0);
  }
  fread(&n, sizeof(int), 1, file);
  fread(&ls, sizeof(int), 1, file);
  fread(&la, sizeof(int), 1, file);
  int bytes = (ceilLog2(n + 1) + 7) / 8;

  int on = ftell(file);
  fseek(file, 0, SEEK_END);
  int sz = ftell(file) - on;
  fseek(file, on, SEEK_SET);

  char *compressed = new char[sz];
  fread(compressed, sizeof(char), sz, file);

  char *code;
  int d_sz;
  double t = clock();
  tie(code, d_sz) = lz77::decode(compressed, sz, ls, la);
  delete[] compressed;
  /*
  printf("%d\n", d_sz);
  for(int i = 0; i < d_sz; ++i) {
    printf("%d ", decompressed[i]);
  }
  puts("");
  */
  /*
  for(int i = 0; i < d_sz; ++i) {
    printf("%d ", code[i]);
  }
  puts("");
  */
  
  vector<int> SArr(n), Llcp(n), Rlcp(n), freq(sigma);
  decode(SArr, code, n * bytes, bytes);

  decode(Llcp, code + n * bytes, n * bytes, bytes);
  decode(Rlcp, code + 2 * n * bytes, n * bytes, bytes);
  decode(freq, code + 3 * n * bytes, sigma * bytes, bytes);
  delete[] code;
  for (int i = 0; i < Rlcp.size(); ++i) {
    //printf("%d\n", Rlcp[i]);
  }
  char *txt = buildTxt(SArr, freq);
  //printf("%s", txt);
  printf("Elapsed DEC: %lf\n", (clock() - t) / CLOCKS_PER_SEC);

  SuffixArray SA(SArr, Llcp, Rlcp, txt);
  t = clock();
  for (string &pat : pats) {
    char *p = new char[pat.size() + 1];
    pat.copy(p, string::npos, 0);
    p[pat.size()] = '\0';
    printf("Ocurrences of %s: %d\n", p, SA.search(p));
    delete[] p;
  }
  printf("Elapsed Search: %lf\n", (clock() - t) / CLOCKS_PER_SEC);
  delete[] txt;
  fclose(file);
}

static void decode(vector<int> &dest, char *src, int n, int bytes) {
  for (int i = 0; i < n; i += bytes) {
    int c = decodeInt(src + i, 8 * bytes);
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
      assert(ptr < n);
      assert(SArr[ptr] < n);
      txt[SArr[ptr]] = i;
      ++ptr;
    }
  }
  return txt;
}

static int ceilLog2(int n) {
  int k = 1;
  int l = 0;
  while (k < n) {
    k <<= 1;
    l += 1;
  }
  return l;
}