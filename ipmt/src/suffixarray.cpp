#include "suffixarray.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

static int ceilLog2(int n);
const int sigma = 256;  // ASCII characters

void SuffixArray::buildOrderedHash() {
  hash = vector<int>(256);
  vector<int> count(256, 0);
  for (int i = 0; i < n; ++i) {
    unsigned char ch = txt[i];
    count[ch] = 1;
  }
  for (int i = 1; i < sigma; ++i) {
    count[i] += count[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    unsigned char ch = txt[i];
    hash[ch] = count[ch] - 1;
  }
}

void SuffixArray::buildP() {
  P.assign(log2n + 1, vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    unsigned char ch = txt[i];
    P[0][i] = hash[ch];
  }
  for (int k = 1; k <= log2n; ++k) {
    vector<tuple<int, int, int>> V;
    int j = 1 << (k - 1);
    for (int i = 0; i < n; ++i) {
      if (i + j >= n) {  // second block is empty string (rank -1)
        V.push_back(make_tuple(P[k - 1][i], -1, i));
      } else {
        V.push_back(make_tuple(P[k - 1][i], P[k - 1][i + j], i));
      }
    }
    sort(V.begin(), V.end());
    int rank = 0;
    P[k][get<2>(V[0])] = rank;
    for (int i = 1; i < n; ++i) {
      if (get<0>(V[i]) != get<0>(V[i - 1]) ||
          get<1>(V[i]) != get<1>(V[i - 1])) {
        rank += 1;
      }
      P[k][get<2>(V[i])] = rank;
    }
  }
}

void SuffixArray::buildSArr() {
  SArr.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    SArr[P[log2n][i]] = i;
  }
}

void SuffixArray::recurseLR(int l, int r) {
  if (r - l > 1) {
    int h = (l + r) / 2;
    Llcp[h] = lcpP(SArr[l], SArr[h]);
    Rlcp[h] = lcpP(SArr[r], SArr[h]);
    recurseLR(l, h);
    recurseLR(h, r);
  }
}

void SuffixArray::buildLR() {
  Llcp.assign(n, 0);
  Rlcp.assign(n, 0);
  recurseLR(0, n - 1);
}

int SuffixArray::lcpP(int i, int j) {  // computes lcp(txt[i:], txt[j:])
  if (i == j) return (n - i);
  int lcp = 0;
  for (int k = log2n; k >= 0 && i < n && j < n; k--) {
    if (P[k][i] == P[k][j]) {
      lcp += 1 << k;
      i += 1 << k;
      j += 1 << k;
    }
  }
  return lcp;
}

int SuffixArray::lcp(const char *u, const char *v) {
  int l = 0;
  while (u[l] != '\0' && v[l] != '\0' && u[l] == v[l]) {
    l += 1;
  }
  return l;
}

int SuffixArray::succ(const char *pat) {  // succ is in (l, r]
  int m = (int)strlen(pat);
  int L = lcp(pat, txt + SArr[0]), R = lcp(pat, txt + SArr[n - 1]);
  if (L == m || txt[SArr[0] + L] > pat[L]) {  // txt[SArr[0]] >=m pat
    return 0;
  }
  if (R < m && txt[SArr[n - 1] + R] < pat[R]) {  // txt[SArr[n - 1]] <m pat
    return n;
  }
  int l = 0, r = n - 1;
  while (r - l > 1) {
    int h = (l + r) / 2;
    int H = -1;
    if (L >= R) {
      if (Llcp[h] >= L) {
        H = L + lcp(pat + L, txt + SArr[h] + L);
      } else {
        H = Llcp[h];
      }
    } else {  // R > L
      if (Rlcp[h] >= R) {
        H = R + lcp(pat + R, txt + SArr[h] + R);
      } else {
        H = Rlcp[h];
      }
    }
    if (H == m || pat[H] < txt[SArr[h] + H]) {
      r = h;
      R = H;
    } else {
      l = h;
      L = H;
    }
  }
  return r;
}

int SuffixArray::pred(const char *pat) {  // pred is in [l, r)
  int m = (int)strlen(pat);
  int L = lcp(pat, txt + SArr[0]), R = lcp(pat, txt + SArr[n - 1]);
  if (R == m || txt[SArr[n - 1] + R] < pat[R]) {  // txt[SArr[n - 1]] <=m pat
    return n - 1;
  }
  if (L < m && txt[SArr[0] + L] > pat[L]) {  // txt[SArr[0]] >m pat
    return -1;
  }
  int l = 0, r = n - 1;
  while (r - l > 1) {
    int h = (l + r) / 2;
    int H = -1;
    if (L >= R) {
      if (Llcp[h] >= L) {
        H = L + lcp(pat + L, txt + SArr[h] + L);
      } else {
        H = Llcp[h];
      }
    } else {  // R > L
      if (Rlcp[h] >= R) {
        H = R + lcp(pat + R, txt + SArr[h] + R);
      } else {
        H = Rlcp[h];
      }
    }
    if (H == m || pat[H] > txt[SArr[h] + H]) {
      l = h;
      L = H;
    } else {
      r = h;
      R = H;
    }
  }
  return l;
}

SuffixArray::SuffixArray(char *txt) {
  this->txt = txt;
  n = (int)strlen(txt);
  log2n = ceilLog2(n);
  buildOrderedHash();
  buildP();
  buildSArr();
  buildLR();
}

SuffixArray::SuffixArray(vector<int> SArr, vector<int> Llcp, vector<int> Rlcp,
                         char *txt) {
  this->SArr = SArr;
  this->Llcp = Llcp;
  this->Rlcp = Rlcp;
  this->txt = txt;
  n = (int)strlen(txt);
}

int SuffixArray::search(const char *pat) {
  int l = succ(pat);
  int r = pred(pat);
  if (l > r)
    return 0;
  else
    return r - l + 1;
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
