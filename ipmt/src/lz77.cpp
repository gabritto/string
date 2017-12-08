#include "lz77.hpp"
#include <algorithm>
#include <cstring>
#include <string>
#include <tuple>
#include "aho.hpp"

using namespace std;

static const int char_size = sizeof(char);

string encodeInt(int n,
                 int size) {  //@size in bits of @n's codification
  int encoded = 0;
  string code;
  while (encoded < size) {
    unsigned char ch = n;
    code.push_back(ch);
    n >>= char_size;
    encoded += char_size;
  }
  return code;
}

int decodeInt(char *n,
              int size) {  //@size in bits of @n's codification. size <= 32
  int decoded = 0;
  int decode = 0;
  while (decoded < size) {
    decode = (decode << char_size) | *n;
    ++n;
    decoded += char_size;
  }
  return decode;
}

namespace lz77 {

static int p_size, l_size;
static pair<int, int> prefixMatch(const char *w, int start, int mid, int end);
static tuple<int, int, char> decode(const char *code);
static int ceilLog2(int n);

char *encode(const char *txt, int n, int ls, int la) {
  string code;
  int start = -ls, mid = 0, end = la;
  p_size = ceilLog2(ls);
  l_size = ceilLog2(la + 1);

  while (mid <= n) {
    int p, l;
    tie(p, l) = prefixMatch(txt, max(0, start), mid, min(end, n));
    code += encodeInt(p, p_size) + encodeInt(l, l_size) + txt[mid + l];
    start += l + 1, mid += l + 1, end += l + 1;
  }
  char *ret = new char[code.size() + 1];
  code.copy(ret, string::npos, 0);
  ret[code.size()] = '\0';
  return ret;
}

char *decode(const char *code, int ls, int la) {
  string txt;
  p_size = ceilLog2(ls);
  l_size = ceilLog2(la + 1);

  int c_size = p_size + l_size + 1;
  int m = strlen(code);
  int k = m / c_size;

  int start = -ls, mid = 0, end = la;

  for (int i = 0; i < k; ++i) {
    int p, l;
    unsigned char ch;
    tie(p, l, ch) = decode(code + c_size * i);
    for (int s = 0; s < l; ++s) {
      txt.push_back(txt[start + p + s]);
    }
    txt.push_back(ch);
    start += l + 1;
    mid += l + 1;
    end += l + 1;
  }

  char *ret = new char[txt.size()];
  memcpy(ret, txt.c_str(), txt.size());
  return ret;
}

// state is the current state in the aho-corasick fsm but also
// the size of the largest prefix of look ahead buffer that matches a suffix
// of w up to position i
static pair<int, int> prefixMatch(const char *w, int start, int mid, int end) {
  vector<vector<int>> fsm = aho::buildFSM(w, mid, end);
  int p = 0, l = 0;
  int state = 0;

  for (int i = start; i < end; ++i) {

    int c = aho::alphabet_hash[(unsigned char)w[i]];
    state = fsm[state][c];
    if (state > l && i - state + 1 < mid) {
      p = i - state + 1;
      l = state;
    }
  }

  return make_pair(p, l);
}

static tuple<int, int, char> decode(const char *code) {
  int p = 0;
  int pos = 0;
  while (pos < (p_size + char_size - 1) / char_size) {
    p <<= char_size;
    p |= code[pos];
    pos += 1;
  }
  int l = 0;
  while (pos < (l_size + char_size - 1) / char_size) {
    l <<= char_size;
    l |= code[pos];
    pos += 1;
  }
  return make_tuple(p, l, code[pos]);
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

//@ls is the size of search buffer, @la is the size of lookahead buffer
// p is match offset (inside search buffer), l is size of match

}  // namespace lz77
