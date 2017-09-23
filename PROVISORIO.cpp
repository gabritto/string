#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <algorithm>

#define dbg(x) if(1) cerr << ">>> " << x << endl;
#define _ << " , " <<

using namespace std;


struct Options {
  Options() : e_max(-1), count(false) {}
  
  int e_max;
  string patfile;
  string algo;
  bool count;
  
  string pat;
  vector<string> txtfile;
};



bool wildMatch(string &txt, string &pat) {
  int n = txt.size();
  int m = pat.size();
  bool *old = new bool[m];
  bool *cur = new bool[m];

  cur[0] = true;
  for(int i = 1; i <= m; ++i) {
        if(pat[i] == '*') {
          cur[i] = cur[i - 1];
        }
        else {
          cur[i] = false;
        }
  }

  for(int i = 1; i <= n; ++i) {
    swap(cur, old);
    for(int j = 1; j <= m; ++j) {
      if(pat[j] == '*') {
        cur[j] = old[j] || cur[j - 1];
      }
      else
        cur[j] = txt[i] == pat[j] && old[j - 1];
    }
  }
  
  bool res = cur[m];
  delete[] old;
  delete[] cur;
  return res;
}

vector<string> getFiles() {
  DIR *dir;
  dirent *pdir;
  vector<string> files;
  dir = opendir(".");

  while(pdir = readdir(dir)) {
    files.push_back(pdir->d_name);
  }
  return files;
}

Options processOptions(int argc, char *argv[]) {
  Options op;
  int i = 1;
  for(; i < argc; ++i) {
    char *option = argv[i];
    if(strcmp(option, "-e") == 0 || strcmp(option, "--edit") == 0) {
      ++i;
      op.e_max = atoi(argv[i]);
    } 
    else if(strcmp(option, "-p") == 0 || strcmp(option, "--pattern") == 0) {
      ++i;
      op.patfile = argv[i];
    } 
    else if(strcmp(option, "-a") == 0 || strcmp(option, "--algorithm") == 0) {
      ++i;
      op.algo = argv[i];
    } 
    else if(strcmp(option, "-c") == 0 || strcmp(option, "--count") == 0) {
      op.count = true;
    } 
    else {
      break;
    }
  }

  op.pat = argv[i++];
  dbg(op.pat)
  vector<string> dirFiles = getFiles();

  for(; i < argc; ++i) { 
    string txtfile = argv[i];
    bool wild = false;
    for(char ch : txtfile) {
      if(ch == '*') {
        wild = true;
        break;
      }
    }
    if(wild) {
      for(string &filename : dirFiles) {
        if(wildMatch(filename, txtfile)) {
          op.txtfile.push_back(txtfile);
        }
      }
    } 
    else {
      op.txtfile.push_back(txtfile);
    }
  }
  unique(op.txtfile.begin(), op.txtfile.end());
  for(auto &s : op.txtfile) {
    cout << s << endl;
  }
  return op;
}
int main(int argc, char *argv[]) { 
  Options ops = processOptions(argc, argv);

  return 0;
}