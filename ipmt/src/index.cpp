#include "index.hpp"
#include <cstdio>
#include <string>
#include "lz77.hpp"
#include "suffixarray.hpp"
#include "util.hpp"

using namespace std;

static vector<int> countChars(char *txt);
static void encode(char *dest, vector<int> &src, int log2n);


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
  SuffixArray SA(txt);
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
  int bytes = SA.log2n / 8 + 1;
  int size = SA.n * bytes;
  char *code = new char[size + 1];
  code[size] = '\0';
  int ls, la;
  ls = la = 8;
  fwrite(&size, sizeof(int), 1, idxfile);
  fwrite(&bytes, sizeof(int), 1, idxfile);
  fwrite(&ls, sizeof(int), 1, idxfile);
  fwrite(&la, sizeof(int), 1, idxfile);

  encode(code, SA.SArr, bytes);
  
  /*
  printf("%d %d %d %d\n ", size, bytes, ls, la);
  for(int i = 0; i < size; ++i) {
    printf("%d ", code[i]);
  }
  puts("");
  */
  char *encoded_SArr = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);
  delete[] encoded_SArr;

  encode(code, SA.Llcp, bytes);
  char *encoded_Llcp = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);
  delete[] encoded_Llcp;

  encode(code, SA.Rlcp, bytes);
  char *encoded_Rlcp = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);
  delete[] encoded_Rlcp;

  bytes = 32 - __builtin_clz(*max_element(freq.begin(), freq.end()));
  if(size < freq.size() * bytes) {
    delete[] code;
    code = new char[freq.size() * bytes];
  }
  size = freq.size() * bytes;

  fwrite(&size, sizeof(int), 1, idxfile);
  fwrite(&bytes, sizeof(int), 1, idxfile);
  printf("%d %d\n", size, bytes);
  encode(code, freq, bytes);
  char *encoded_freq = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);

  fclose(idxfile);
  delete[] txt;
  delete[] code;
}
static void encode(char *dest, vector<int> &src, int bytes) {
  int n = (int)src.size();
  int ptr = 0;
  for (int i = 0; i < n; ++i) {
    string c = encodeInt(src[i], sizeof(char) * bytes);
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