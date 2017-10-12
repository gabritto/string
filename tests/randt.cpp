#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
  srand(time(0));
  int s;
  cin >> s;
  string pat;
  for(int i = 0; i < s; ++i) {
    char ch = (rand() % 26) + 'a';
    pat += ch;
  }
  cout << pat << endl;
  return 0;
}