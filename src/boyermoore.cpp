#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace boyer {

static vector<int> bad_char;
static string pat;
static vector<int> good_suffix_shift;
static vector<int> border;

static void buildBadChar(const string &pat);
void buildGoodSuffix(const string &pat);
static void buildBorder(const string &s);

void build (const string &_pat) {
  pat = _pat;
  buildBadChar(pat);
  buildGoodSuffix(pat);
}

int search(string &txt) {
  int n = (int) txt.size();
  int m = (int) pat.size();
  int count = 0;
  int i = 0;

  int last_alignment_pos = -1;
  int last_comparison_pos = -1;
  while(i <= n - m) {
    int j = m - 1;
    while(j >= 0 && txt[i + j] == pat[j]) {
      --j;
      if(i > last_comparison_pos && i <= last_alignment_pos && i + j == last_alignment_pos) {
        j = -1;
      }
    }
    last_alignment_pos = i + m - 1;
    last_comparison_pos = i + max(j, 0);
    if(j == -1) {
      ++count;
      i += good_suffix_shift[0];

    }
    else {
      i += max(j - bad_char[txt[i + j]], good_suffix_shift[j + 1]);
    }
  }
  return count;
}

static void buildBadChar(const string &pat) {
  bad_char = vector<int>(256, 0);
  int m = (int) pat.size();
  for(int i = 0; i < m; ++i) {
    bad_char[pat[i]] = i;
  }
}


void buildGoodSuffix(const string &pat) {
  int m = (int) pat.size();

  buildBorder(pat);
  good_suffix_shift = vector<int>(m + 1, m - border[m]);
  string rev_pat = pat;
  reverse(rev_pat.begin(), rev_pat.end());
  buildBorder(rev_pat);

  for(int l = 1; l <= m; ++l) {
    int j = m - border[l];
    good_suffix_shift[j] = min(good_suffix_shift[j], l - border[l]);
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

