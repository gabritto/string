#include "util.hpp"
#include "parser.hpp"
#include "input.hpp"
#include "ahocorasick.hpp"
#include "boyermoore.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

static int max_pat_len;
static void processAho(bool count);

pair<vector<int>, int> getAlphabet(const vector<string> &pats) {
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

pair<vector<int>, int> getAlphabet(const string &pat) {
  int i = 1;
  vector<int> hsh(256, 0);
  for(unsigned char ch : pat) {
    if(hsh[ch] == 0) {
      hsh[ch] = i++;
    }
  }
  return {hsh, i};
}


static void processAho(bool count) {
  long long line_count = 0;
  long long occ_count = 0;
  const char* txt;
  while((txt = parser::readLine()) != NULL) {
    int occ = aho::search(txt);
    occ_count += occ;
    if(occ > 0) {
      ++line_count;
      if(!count) {
        printf("%s\n", txt);
      }
    }
  }
  printf("(%lld/%lld)\n", line_count, occ_count);
}

static void processBoyer(bool count) {
  long long line_count = 0;
  long long occ_count = 0;
  const char *txt;
  while((txt = parser::readLine()) != NULL) {
    int occ = boyer::search(txt);
    occ_count += occ;
    if(occ > 0) {
      ++line_count;
      if(!count) {
        printf("%s\n", txt);
      }
    }
  }

  printf("(%lld/%lld)\n", line_count, occ_count);
}

vector<string> getPatterns(const string &pat_filename, const string &pattern) {
  vector<string> pat;
  if(!pattern.empty()) {
    pat.push_back(pattern);
    max_pat_len = max(max_pat_len, (int) pattern.size());
  }

  if(pat_filename == "") {
    return pat; 
  }

  ifstream pat_file;
  pat_file.open(pat_filename);
  if(pat_file.fail()) {
    printf("Invalid pattern file: %s\n", pat_filename.c_str());
    exit(0);
  }
  string str;
  while(getline(pat_file, str)) {
    if(str.size() > 0) {
      pat.push_back(str);
      max_pat_len = max(max_pat_len, (int) str.size());

    }
  }

  return pat;
}

void processTxtFiles(const vector<string> &pats, const vector<string> &txt_filenames, argument args) {
  
  if(args.e_max > 0 && (args.algo == "aho" || args.algo == "boy" || args.algo == "sh")) {
    printf("Invalid approximate matching algorithm. --help for more info.\n");
  }
  if(args.algo == "") {
    if(args.e_max == 0) {
      if(pats.size() > 1) {
        args.algo = "aho";
      }
      else {
        args.algo = "boy";
      }
    }
  }
  
  if(args.algo == "aho") {
    aho::build(pats);
  }
  else if(args.algo == "boy") {
    boyer::build(pats);
  }
  else {
    printf("Invalid algorithm: %s. --help for more info.\n", args.algo.c_str());
    exit(0);
  }
  printf("\nFormat of the output: \n\tFILENAME: (LINE_OCURRENCES/OCURRENCES)\n\n");
  for(string txt_filename : txt_filenames) {
    printf("%s: ", txt_filename.c_str());
    parser::open(txt_filename);
    if(args.algo == "aho") {
      processAho(args.count);
    }
    else if(args.algo == "boy") {
      processBoyer(args.count);
    }
  }
}
