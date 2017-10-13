#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const vector<int> lens {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100};
const int words = 4;
const int sigma = 4;
const char alphabet[] = "ACGT";

int main() {
  srand(time(0));
  for(int s: lens) {
    for(int w = 0; w < words; ++w) {
      string pat(s, 0);
      for(int i = 0; i < s; ++i) {
        pat[i] = alphabet[rand() % sigma];
      }
      cout << pat << endl;
    }
  }
  return 0;
}