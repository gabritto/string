#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;


class SuffixArray {
 private:
  vector<vector<int>> P;
  int log2n;
  int n;
  const char *txt;
  vector<int> hash;
  
  void buildOrderedHash();
  void buildP();
  void buildSArr();
  void recurseLR(int l, int r);
  void buildLR();
  int lcpP(int i, int j);  // computes lcp(txt[i:], txt[j:])
  int lcp(const char *u, const char *v);
  int succ(const char *pat);
  int pred(const char *pat);

 public:
  SuffixArray(char *txt);
  SuffixArray(vector<int> SArr, vector<int> Llcp, vector<int> Rlcp, char *txt);
  vector<int> SArr, Llcp, Rlcp;
  int search(const char *pat);
};
