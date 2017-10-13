#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const vector<string> algorithms {"boy", "aho", "bf", "sho", "grep"};

int main() {
  vector<int> lens;
  for(int i = 1; i < 10; i += 1) {
    lens.push_back(i);
  }
  for(int i = 10; i < 50; i += 5) {
    lens.push_back(i);
  }
  for(int i = 50; i <= 100; i += 10) {
    lens.push_back(i);
  }
  bool space = false;
  cout << "[";
  for(int s: lens) {
    if(space) {
      cout << ", ";
    }
    cout << s;
    space = true;
  }
  cout << "]" << endl;
  for(const string &a: algorithms) {
    cout << a << ":\n[";
    bool space = false;
    for(int s: lens) {
      if(a == "sho" && s > 60) {
        break;
      }
      string file = a + to_string(s) + ".txt";
      ifstream timefile;
      timefile.open(file);
      double total = 0;
      string str;
      int runs = 0;
      while(getline(timefile, str)) {
        if(str == "Command exited with non-zero status 1") {
          continue;
        }
        runs += 1;
        int mt = 0;
        int spos = 0;
        for(int i = 0; i < int(str.size()); i += 1) {
          if(str[i] == 'm') {
            mt = stoi(str.substr(0, i));
            spos = i + 1;
          }
        }
        double s = stod(str.substr(spos));
        total += mt * 60 + s;
        //cout << mt << "m" << s << endl;
      }
      if(space) {
        cout << ", ";
      }
      if(runs == 0) {
        cout << file << " banana" << endl;
      }
      cout << total / runs;
      space = true;
    }
   cout << "]" << endl;
  }
  return 0;
}