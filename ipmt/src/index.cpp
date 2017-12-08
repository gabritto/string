#include "index.hpp"
#include <cassert>
#include <cstdio>
#include <string>
#include "lz77.hpp"
#include "suffixarray.hpp"
#include "util.hpp"

using namespace std;

static vector<int> countChars(char *txt);
static void encode(char *dest, vector<int> &src, int log2n);
static int ceilLog2(int n);

/* index vai ter as seguintes informacoes:
n bytes ls la SArr Llcp Rlcp n' bytes' freq

n = tamanho de sarr, llcp e rlcp (apos conversao pra char*)
bytes = qtd de bytes de cada inteiro
ls, la = argumentos do lz77
n' = tamanho de freq (apos conversao pra char*)
bytes' = qtd de bytes de cada inteiro de freq
sarr, llcp, rlcp, freq = codificacao
*/

void buildIndex(string txtfile) {
  char *txt = read(txtfile);
  printf("%d\n", strlen(txt));
  SuffixArray SA(txt);
  printf("vish\n");
  vector<int> freq = countChars(txt);
  /*for(auto v : SA.SArr) {
    printf("%d ", v);
  }
  puts("");
  for(int i = 0; i < freq.size(); ++i) {
    if(freq[i] > 0) printf("(%c %d %d) ", i, i, freq[i]);
  }
  puts("");*/

  // encode
  string idx_filename = txtfile.substr(0, txtfile.size() - 4) + ".idx";
  FILE *idxfile = fopen(idx_filename.c_str(), "wb");
  if (idxfile == NULL) {
    printf("Couldn't create file: %s.", idx_filename.c_str());
    exit(0);
  }
  int n = SA.n;
  int bytes = (ceilLog2(n + 1) + 7) / 8;
  int size = (3 * SA.n + sigma) * bytes;
  char *code = new char[size + 1];
  code[size] = '\0';
  int ls, la;
  ls = la = 255;

  fwrite(&n, sizeof(int), 1, idxfile);
  fwrite(&ls, sizeof(int), 1, idxfile);
  fwrite(&la, sizeof(int), 1, idxfile);

  encode(code, SA.SArr, bytes);
  encode(code + n * bytes, SA.Llcp, bytes);
  encode(code + 2 * n * bytes, SA.Rlcp, bytes);
  encode(code + 3 * n * bytes, freq, bytes);
  /*for (int i = 0; i < n; ++i) {
    printf("%d ", SA.Llcp[i]);
  }
  puts("");*/
  /*
  for (int i = 0; i < size; ++i) {
    printf("%d ", (unsigned char) code[i]);
  }
  puts("");
  */
  char *compressed;
  int c_size;
  tie(compressed, c_size) = lz77::encode(code, size, ls, la);
  fwrite(compressed, sizeof(char), c_size, idxfile);


  fclose(idxfile);
  delete[] compressed;
  delete[] txt;
  delete[] code;
}

static void encode(char *dest, vector<int> &src, int bytes) {
  int n = (int)src.size();
  int ptr = 0;
  for (int i = 0; i < n; ++i) {
    string c = encodeInt(src[i], 8 * bytes);
    assert(c.size() == bytes);
    for (int j = 0; j < bytes; ++j) {
      dest[ptr] = c[j];
      ++ptr;
    }
  }
}

static vector<int> countChars(char *txt) {
  vector<int> freq(sigma, 0);
  for (int i = 0; txt[i] != '\0'; ++i) {
    ++freq[(unsigned char)txt[i]];
  }
  return freq;
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