#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <getopt.h>
#include "input.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  argument args;
  getOptions(args, argc, argv);
  bool need_pattern = args.patfile == "";
  if(argc - optind < 1 + need_pattern) {
    printf("not enough arguments\n");
    exit(0);
  }
  if(need_pattern) {
  	args.pat = argv[optind];
  }
  getTxtFiles(args, argc, argv);
  vector<string> pat = getPatterns(args.patfile, args.pat);

  processTxtFiles(pat, args);

  return 0;
}