#include "util.hpp"
#include "input.hpp"
#include "ahocorasick.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

static pair<vector<int>, int> getAlphabet(const vector<string> &pats) {
  int i = 1;
  vector<int> hsh(256, 0);
  for(string pat : pats) {
    for(unsigned char ch : pat) {
      if(hsh[ch] == 0) {
        hsh[ch] = i++;
      }
    }
  }
  return {hsh, i};
}

static pair<vector<int>, int> getAlphabet(const string &pat) {
  int i = 1;
  vector<int> hsh(256, 0);
  for(unsigned char ch : pat) {
    if(hsh[ch] == 0) {
      hsh[ch] = i++;
    }
  }
  return {hsh, i};
}


static void processAho(const vector<string> &pats, ifstream &txt_file, bool count) {
  string txt;
  vector<int> alphabet_hash;
  int alphabet_size;
  tie(alphabet_hash, alphabet_size) = getAlphabet(pats);
  AhoFSM f(pats, alphabet_hash, alphabet_size);

  int line_count = 0, occ_count = 0;

  while(getline(txt_file, txt)) {
    int occ = f.search(txt);
    occ_count += occ;
    if(occ > 0) {
      ++line_count;
      if(!count) {
        printf("%s\n", txt.c_str());
      }
    }
  }

  printf("number of occurrences: %d\n", occ_count);
  printf("number of line occurrences: %d\n", line_count);
}


vector<string> getPatterns(const string &pat_filename) {
  if(pat_filename == "") {
    return vector<string>(); 
  }
  ifstream pat_file;
  pat_file.open(pat_filename);
  if(pat_file.fail()) {
    printf("Invalid pattern file: %s\n", pat_filename.c_str());
    exit(0);
  }
  string str;
  vector<string> pat;
  while(pat_file >> str) {
    pat.push_back(str);
  }
  return pat;
}


void processTxtFile(const vector<string> &pats, const string &txt_filename, const argument args) {
  ifstream txt_file;
  printf("Processing file: %s\n", txt_filename.c_str());
  txt_file.open(txt_filename);
  if(txt_file.fail()) {
    printf("Invalid text file: %s\n", txt_filename.c_str());
    exit(0);
  }

  if(args.e_max > 0 && (args.algo == "aho" || args.algo == "boy" || args.algo == "shi")) {
    printf("Invalid approximate matching algorithm. --help for more info.\n");
  }


  if(args.algo == "") {
    if(args.e_max == 0) {
      if(pats.size() >= 1) {
        processAho(pats, txt_file, args.count);
      }
      else {

      }
    }
  }
  else if(args.algo == "aho") {
    processAho(pats, txt_file, args.count);
  }

}