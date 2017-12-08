#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

extern const int sigma;  // ASCII characters

class SuffixArray {
 private:
  std::vector<std::vector<int>> P;
  const char *txt;
  std::vector<int> hash;
  
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
  SuffixArray(std::vector<int> SArr, std::vector<int> Llcp, std::vector<int> Rlcp, char *txt);
  std::vector<int> SArr, Llcp, Rlcp;
  int n, log2n;
  int search(const char *pat);
};
