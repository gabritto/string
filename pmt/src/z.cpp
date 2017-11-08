#include "z.hpp"
#include <string>
#include <vector>

using namespace std;

namespace z {
static vector<int> z;
vector<int> build(string &s) {
  int l = 0, r = 0;
  int m = (int) s.size();
  z.resize(m);
  z[0] = 0;
  for(int i = 1; i < m; ++i) {
    if(i > r) {
      l = r = i;
      while(r < m && s[r] == s[r - i]) {
        ++r;
      }
      z[i] = r - i;
      --r;
    }
    else if(z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    }
    else {
      l = i;
      ++r;
      while(r < m && s[r] == s[r - i]) {
        ++r;
      }
      z[i] = r - i;
      --r;
    }
  }
  return z;
}

}