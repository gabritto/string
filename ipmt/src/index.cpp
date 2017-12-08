#include "index.hpp"
#include <cstdio>
#include <string>
#include "lz77.hpp"
#include "suffixarray.hpp"
#include "util.hpp"

using namespace std;

static vector<int> countChars(char *txt);
static void *encode(char *dest, vector<int> &src, int log2n);

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
    printf("Error creating file %s.", idx_filename);
    exit(0);
  }
  int size = SA.n * SA.log2n;
  char *code = new char[size + 1];
  code[size] = '\0';
  int ls, la;
  ls = la = 8;
  fwrite(&size, sizeof(int), 1, idxfile);
  fwrite(&ls, sizeof(int), 1, idxfile);
  fwrite(&la, sizeof(int), 1, idxfile);

  encode(code, SA.SArr, SA.log2n);
  char *encoded_SArr = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);
  delete[] encoded_SArr;

  encode(code, SA.Llcp, SA.log2n);
  char *encoded_Llcp = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);
  delete[] encoded_Llcp;
  
  encode(code, SA.Rlcp, SA.log2n);
  char *encoded_Rlcp = lz77::encode(code, size, ls, la);
  fwrite(code, sizeof(char), size, idxfile);
  delete[] encoded_Rlcp;
  
  fclose(idxfile);
  delete[] txt;
  delete[] code;
}

static void *encode(char *dest, vector<int> &src, int log2n) {
  int n = src.size();
  int ptr = 0;
  for (int i = 0; i < n; ++i) {
    string c = encodeInt(src[i], log2n);
    for (int j = 0; j < (int)c.size(); ++j) {
      dest[ptr] = c[j];
      ++ptr;
    }
  }
}

static vector<int> countChars(char *txt) {
  vector<int> freq(256, 0);
  for (int i = 0; txt[i] != '\0'; ++i) {
    ++freq[(unsigned char)txt[i]];
  }
  return freq;
}