#include "util.hpp"
#include "parser.hpp"
#include "input.hpp"
#include "ahocorasick.hpp"
#include "boyermoore.hpp"
#include "bruteforce.hpp"
#include "ukkonen.hpp"
#include "sellers.hpp"
#include "shiftor.hpp"
#include "wumanber.hpp"
#include <cstring>
#include <string>
#include <vector>

using namespace std;

static int max_pat_len = 0;
static string algo_fullname;
typedef int (*search_function)(const char *);
static search_function search;

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


static void match(string txt_filename, bool count) {
  long long line_count = 0;
  long long occ_count = 0;
  const char *txt;
  while((txt = parser::readLine()) != NULL) {
    int occ = search(txt);
    occ_count += occ;
    if(occ > 0) {
      ++line_count;
      if(!count) {
        printf("%s: %s\n", txt_filename.c_str(), txt);
      }
    }
  }

  printf("%s: (%lld/%lld), by %s\n", txt_filename.c_str(), line_count, occ_count, algo_fullname.c_str());
}

vector<string> getPatterns(const string &pat_filename, const string &pattern) {
  vector<string> pats;
  if(!pattern.empty()) {
    pats.push_back(pattern);
    max_pat_len = max(max_pat_len, (int) pattern.size());
  }

  if(pat_filename == "") {
    if(pats.empty()) {
      printf("No pattern given.\n");
      exit(0);
    }
    return pats; 
  }

  parser::open(pat_filename);
  const char *str;
  while((str = parser::readLine()) ) {
    int sz = (int) strlen(str);
    if(sz > 0) {
      pats.push_back(str);
      max_pat_len = max(max_pat_len, sz);
    }
  }
  parser::close();
  if(pats.empty()) {
    printf("No pattern given\n");
    exit(0);
  }
  return pats;
}

void processAlgorithm(const vector<string> &pats, argument &args) {

  if(args.e_max > 0 && (args.algo == "aho" || args.algo == "boy" || args.algo == "sh")) {
    printf("Invalid approximate matching algorithm. --help for more info.\n");
  }
  if(args.algo == "") {
    if(args.e_max == 0) {
      if(pats.size() > 1) {
        args.algo = "aho";
      }
      else if(pats[0].size() >= 5){
        args.algo = "boy";
      }
      else {
        args.algo = "bf";
      }
    }
  }

  if(args.algo == "aho") {
    aho::build(pats);
    search = aho::search;
    algo_fullname = "Aho-Corasick";
  }
  else if(args.algo == "boy") {
    boyer::build(pats);
    search = boyer::search;
    algo_fullname = "Boyer-Moore";
  }
  else if(args.algo == "bf") {
    bruteforce::build(pats);
    search = bruteforce::search;
    algo_fullname = "Bruteforce";
  }
  else if(args.algo == "ukk") {
    ukkonen::build(pats, args.e_max);
    search = ukkonen::search;
    algo_fullname = "Ukkonen";
  }
  else if(args.algo == "sell") {
    sellers::build(pats, args.e_max);
    search = sellers::search;
    algo_fullname = "Sellers";
  }
  else if(args.algo == "sho") {
    shiftor::build(pats);
    search = shiftor::search;
    algo_fullname = "Shift-Or";
  }
  else if(args.algo == "wum") {
    wumanber::build(pats, args.e_max);
    search = wumanber::search;
    algo_fullname = "Wu-Manber";
  }
  else {
    printf("Invalid algorithm: %s. --help for more info.\n", args.algo.c_str());
    exit(0);
  }
}

void processTxtFiles(argument &args) {
  printf("\nFormat of the output: \n\tFILENAME: (LINE_OCURRENCES/OCURRENCES)\n\n");
  for(string &txt_filename : args.txtfiles) {
    parser::open(txt_filename);
    match(txt_filename, args.count);
    parser::close();
  }
}
