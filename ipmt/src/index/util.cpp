#include <string>
#include <vector>
using namespace std;

vector<int> countChars(string txt_filename) {
  ifstream txt_file(txt_filename);
  if (txt_file.fail()) {
    printf("Error opening file: %s", txt_filename.c_str());
    exit(0);
  }

  string txt;
  vector<int> freq(256, 0);
  while (getline(txt_file, txt)) {
    for (unsigned char ch : txt) {
      ++freq[ch];
    }
  }
  return txt;
}