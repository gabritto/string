#include "index.hpp"
#include <string>
#include "suffixarray"
#include "util.hpp"

using namespace std;

void mainIndex(string txtfile) {
  vector<int> suffix_array = createSuffixArray(txtfile);
  vector<int> freq = countChars(txtfile);
  encode(suffix_array, freq);
}