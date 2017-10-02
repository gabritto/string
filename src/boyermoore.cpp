//#include "boyermoore.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace boyer {

static vector<vector<int>> bad_char;
static vector<string> pat;
static vector<vector<int>> good_suffix_shift;
static vector<int> border;

static void buildBadChar();
void buildGoodSuffix();
static void buildBorder(const string &s);

void build (const vector<string> &_pat) {
  pat = _pat;
  buildBadChar();
  buildGoodSuffix();
}

int search(const char *txt) {
  int n = (int) strlen(txt);
  int count = 0;
  
  for(int k = 0; k < (int) pat.size(); ++k)
  {
    int m = (int) pat[k].size();
    int i = 0;

    int last_alignment_pos = -1;
    int last_comparison_pos = -1;
    while(i <= n - m) {
      int j = m - 1;
      while(j >= 0 && txt[i + j] == pat[k][j]) {
        --j;
        if(i > last_comparison_pos && i <= last_alignment_pos && i + j == last_alignment_pos) {
          j = -1;
        }
      }
      last_alignment_pos = i + m - 1;
      last_comparison_pos = i + max(j, 0);
      if(j == -1) {
        ++count;
        i += good_suffix_shift[k][0];

      }
      else {
        i += max(j - bad_char[k][txt[i + j]], good_suffix_shift[k][j + 1]);
      }
    }
  }    
  return count;
}

static void buildBadChar() {
  bad_char = vector<vector<int>>(pat.size(), vector<int>(256, 0));
  for(int k = 0; k < (int) pat.size(); ++k)
  {
    int m = (int) pat[k].size();
    for(int i = 0; i < m; ++i) {
      bad_char[k][pat[k][i]] = i;
    }
  }
}


void buildGoodSuffix() {
  good_suffix_shift = vector<vector<int>>(pat.size());
  for(int k = 0; k < (int) pat.size(); ++k)
  {
    int m = (int) pat[k].size();

    buildBorder(pat[k]);
    good_suffix_shift[k] = vector<int>(m + 1, m - border[m]);
    string rev_pat = pat[k];
    reverse(rev_pat.begin(), rev_pat.end());
    buildBorder(rev_pat);

    for(int l = 1; l <= m; ++l) {
      int j = m - border[l];
      good_suffix_shift[k][j] = min(good_suffix_shift[k][j], l - border[l]);
    }
  }
}

static void buildBorder(const string &s) {
  int m = (int) s.size();

  border = vector<int>(m + 1);
  border[0] = -1;
  int i = 0, j = -1;
  while(i < m) {
    while(j >= 0 && s[i] != s[j]) {
      j = border[j];
    }
    ++i;
    ++j;
    border[i] = j;
  }
}

} //namespace boyer


