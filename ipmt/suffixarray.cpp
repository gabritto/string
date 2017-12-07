#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <tuple>

using namespace std;

int ceilLog2(int n) {
  int k = 1;
  int l = 0;
  while(k < n) {
    k <<= 1;
    l += 1;
  }
  return l;
}

const int sigma = 256; //ASCII characters

class SuffixArray {
private: 
  vector<vector<int>> P;
  vector<int> SArr;
  int log2n;
  int n;
  const char *txt;
  int hash[sigma];
  vector<int> Llcp, Rlcp;
  
  void buildOrderedHash() {
    vector<int> count(256, 0);
    for(int i = 0; i < n; ++i) {
      unsigned char ch = txt[i];
      count[ch] = 1;
    }
    for(int i = 1; i < sigma; ++i) {
      count[i] += count[i - 1];
    }
    for(int i = 0; i < n; ++i) {
      unsigned char ch = txt[i];
      hash[ch] = count[ch] - 1;
    }
  }

  void build_P() {
    P.assign(log2n + 1, vector<int>(n, -1));
    for(int i = 0; i < n; ++i) {
      unsigned char ch = txt[i];
      P[0][i] = hash[ch];
    }
    for(int k = 1; k <= log2n; ++k) {
      vector<tuple<int, int, int>> V;
      int j = 1 << (k - 1);
      for(int i = 0; i < n; ++i) {
        if(i + j >= n) { //second block is empty string (rank -1)
          V.push_back(make_tuple(P[k - 1][i], -1, i));
        }
        else {
          V.push_back(make_tuple(P[k - 1][i], P[k - 1][i + j], i));
        }
      }
      sort(V.begin(), V.end());
      int rank = 0;
      P[k][get<2>(V[0])] = rank;
      for(int i = 1; i < n; ++i) {
        if(get<0>(V[i]) != get<0>(V[i - 1]) || get<1>(V[i]) != get<1>(V[i - 1])) {
          rank += 1;
        }
        P[k][get<2>(V[i])] = rank;
      }
    }
  }

  void build_SArr() {
    SArr.assign(n, -1);
    for(int i = 0; i < n; ++i) {
      SArr[P[log2n][i]] = i;
    }
  }

  void recurse_LR(int l, int r) {
    if(r - l > 1) {
      int h = (l + r)/2;
      Llcp[h] = lcp_P(SArr[l], SArr[h]);
      Rlcp[h] = lcp_P(SArr[r], SArr[h]);
      recurse_LR(l, h);
      recurse_LR(h, r);
    }
  }

  void build_LR() {
    Llcp.assign(n, 0);
    Rlcp.assign(n, 0);
    recurse_LR(0, n - 1);
  }

  int lcp_P(int i, int j) { //computes lcp(txt[i:], txt[j:])
    if(i == j)
      return (n - i);
    int lcp = 0;
    for(int k = log2n; k >= 0 && i < n && j < n; k--) {
      if(P[k][i] == P[k][j]) {
        lcp += 1 << k;
        i += 1 << k;
        j += 1 << k;
      }
    }
    return lcp;
  }

  int lcp(const char *u, const char *v) {
    int l = 0;
    while(u[l] != '\0' && v[l] != '\0' && u[l] == v[l]) {
      l += 1;
    }
    return l;
  }

  int succ(const char *pat) { //succ is in (l, r]
    int m = strlen(pat);
    int L = lcp(pat, txt + SArr[0]), R = lcp(pat, txt + SArr[n - 1]);
    if(L == m || txt[SArr[0] + L] > pat[L]) { //txt[SArr[0]] >=m pat
      return 0;
    }
    if(R < m && txt[SArr[n - 1] + R] < pat[R]) { //txt[SArr[n - 1]] <m pat
      return n;
    }
    int l = 0, r = n - 1;
    while(r - l > 1) {
      int h = (l + r)/2;
      int H = -1;
      if(L >= R) {
        if(Llcp[h] >= L) {
          H = L + lcp(pat + L, txt + SArr[h] + L);
        }
        else {
          H = Llcp[h];
        }
      }
      else {// R > L
        if(Rlcp[h] >= R) {
          H = R + lcp(pat + R, txt + SArr[h] + R);
        }
        else {
          H = Rlcp[h];
        }
      }
      if(H == m || pat[H] < txt[SArr[h] + H]) {
        r = h;
        R = H;
      }
      else {
        l = h;
        L = H;
      }
    }
    return r;
  }

  int pred(const char *pat) { //pred is in [l, r)
    int m = strlen(pat);
    int L = lcp(pat, txt + SArr[0]),
        R = lcp(pat, txt + SArr[n - 1]);
    if(R == m || txt[SArr[n - 1] + R] < pat[R]) { //txt[SArr[n - 1]] <=m pat
      return n - 1;
    }
    if(L < m && txt[SArr[0] + L] > pat[L]) { //txt[SArr[0]] >m pat
      return -1;
    }
    int l = 0, r = n - 1;
    while(r - l > 1) {
      int h = (l + r)/2;
      int H = -1;
      if(L >= R) {
        if(Llcp[h] >= L) {
          H = L + lcp(pat + L, txt + SArr[h] + L);
        }
        else {
          H = Llcp[h];
        }
      }
      else {// R > L
        if(Rlcp[h] >= R) {
          H = R + lcp(pat + R, txt + SArr[h] + R);
        }
        else {
          H = Rlcp[h];
        }
      }
      if(H == m || pat[H] > txt[SArr[h] + H]) {
        l = h;
        L = H;
      }
      else {
        r = h;
        R = H;
      }
    }
    return l;
  }

public:
 
  SuffixArray(char *str) :
  log2n(ceilLog2(strlen(str))), n(strlen(str)), txt(str) {
    buildOrderedHash();
    build_P();
    build_SArr();
    build_LR();
  }

  int search(const char *pat) {
    int l = succ(pat);
    int r = pred(pat);
    cout << l << " " << r << endl;
    if(l > r)
      return 0;
    else
      return r - l + 1;
  }

  vector<int> getSuffixArray() {
    return SArr;
  }


};
char txt[200];
char pat[100];

int main () {
  scanf(" %s", txt);
  SuffixArray SA(txt);
  scanf(" %s", pat);
  /*
  vector<int> sa = SA.getSuffixArray();
  for(int i = 0; txt[i] != '\0'; ++i) {
    cout << sa[i] << " ";
  }
  cout << endl;
  for(int i = 0; txt[i] != '\0'; ++i) {
    printf("%s\n", txt + sa[i]);
  }
  cout << endl;
  */
  printf("%d\n", SA.search(pat));
}