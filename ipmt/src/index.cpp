#include "index.hpp"
#include <fstream>
#include <string>
#include "suffixarray.hpp"
#include "util.hpp"

using namespace std;

static vector<int> countChars(char *txt);

void createIndex(string txtfile) {
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
}

static vector<int> countChars(char *txt) {
  vector<int> freq(256, 0);
  for (int i = 0; txt[i] != '\0'; ++i) {
    ++freq[(unsigned char)txt[i]];
  }
  return freq;
}