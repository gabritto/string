#include "index.hpp"
#include <fstream>
#include <string>
//#include "suffixarray.hpp"

using namespace std;

static vector<int> countChars(string txt_filename);

void createIndex(string txtfile) {
  //vector<int> suffix_array = createSuffixArray(txtfile);
  vector<int> freq = countChars(txtfile);
  //encode(suffix_array, freq);
}

static vector<int> countChars(string txt_filename) {
  ifstream txt_file(txt_filename);
  if (txt_file.fail()) {
    printf("Error opening file: %s.", txt_filename.c_str());
    exit(0);
  }

  string txt;
  vector<int> freq(256, 0);
  while (getline(txt_file, txt)) {
    for (unsigned char ch : txt) {
      ++freq[ch];
    }
  }
  txt_file.close();
  return freq;
}