#include "lz77.hpp"
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <tuple>
#include "aho.hpp"

using namespace std;

static const int char_size = 8;

string encodeInt(int n,
                 int size) {  //@size in bits of @n's codification
  int encoded = 0;
  string code;
  while (encoded < size) {
    code.push_back(n & 255);
    n >>= char_size;
    encoded += char_size;
  }
  return code;
}

int decodeInt(const char *n,
              int size) {  //@size in bits of @n's codification. size <= 32
  int decoded = 0;
  int decode = 0;
  while (decoded < size) {
    decode = (decode << char_size) | (unsigned char) *n;
    ++n;
    decoded += char_size;
  }
  return decode;
}

namespace lz77 {

static int p_size, l_size;
static pair<int, int> prefixMatch(const char *w, int start, int mid, int end);
static tuple<int, int, char> decodeTuple(const char *code);
static int ceilLog2(int n);

pair<char *, int> encode(const char *txt, int n, int ls, int la) {
  string code;
  int start = -ls, mid = 0, end = la;
  p_size = ceilLog2(ls);
  l_size = ceilLog2(la + 1);
  int p_bytes = (p_size + char_size - 1) / char_size;
  int l_bytes = (l_size + char_size - 1) / char_size;
  /*
  printf("p_bytes: %d l_bytes: %d\n", p_bytes, l_bytes);
  puts("texto antes da compressao");
  for(int i = 0; i < n; ++i) {
    printf("%d ", (unsigned char) txt[i]);
  }
  puts("");
  */
  while (mid <= n) {
    int p, l;
    tie(p, l) = prefixMatch(txt, max(0, start), mid, min(end, n));
    code += encodeInt(p, p_size) + encodeInt(l, l_size) + txt[mid + l];
    //printf("%d %d %d\n", p, l, (unsigned char) txt[mid + l]);
    start += l + 1, mid += l + 1, end += l + 1;
  }
  char *ret = new char[code.size()];
  code.copy(ret, string::npos, 0);
  /*
  puts("texto depois da compressao");
  for (int i = 0; i < code.size(); ++i) {
    printf("%d ", (unsigned char) ret[i]);
  }
  puts("");
  */
  return {ret, code.size()};
}

pair<char *, int> decode(const char *code, int m, int ls, int la) {
  string txt;
  p_size = ceilLog2(ls);
  l_size = ceilLog2(la + 1);
  int p_bytes = (p_size + char_size - 1) / char_size;
  int l_bytes = (l_size + char_size - 1) / char_size;
  int c_size = p_bytes + l_bytes + 1;
  int k = m / c_size;

  int start = -ls, mid = 0, end = la;
  /*
  printf("p_bytes: %d l_bytes: %d\n", p_bytes, l_bytes);
  puts("texto antes da decompressao");
  for (int i = 0; i < m; ++i) {
    printf("%d ", (unsigned char) code[i]);
  }
  puts("");
  */
  for (int i = 0; i < k; ++i) {
    int p, l;
    unsigned char ch;
    tie(p, l, ch) = decodeTuple(code + c_size * i);
    /*
    printf("%d %d %d\n", p, l, (unsigned char) ch);
    printf("start %d mid %d end %d\n", start, mid, end);
    */
    for (int s = 0; s < l; ++s) {
      txt.push_back(txt[max(start, 0) + p + s]);
    }
    txt.push_back(ch);
    start += l + 1;
    mid += l + 1;
    end += l + 1;
  }

  char *ret = new char[txt.size()];
  txt.copy(ret, string::npos, 0);
  /*
  puts("texto depois da decompressao");
  for (int i = 0; i < txt.size() - 1; ++i) {
    printf("%d ", (unsigned char) ret[i]);
  }
  puts("");
  */
  return {ret, txt.size() - 1};
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
      p = i - start - state + 1;
      l = state;
    }
  }

  return make_pair(p, l);
}

static tuple<int, int, char> decodeTuple(const char *code) {
  int p = 0;
  int p_bytes = (p_size + char_size - 1) / char_size;
  int l = 0;
  int l_bytes = (l_size + char_size - 1) / char_size;
  p = decodeInt(code, p_bytes * char_size);
  l = decodeInt(code + p_bytes, l_bytes * char_size);
  char ch = code[p_bytes + l_bytes]; 
  return make_tuple(p, l, ch);
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
