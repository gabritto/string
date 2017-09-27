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
  if(argc - optind < 2) {
    printf("not enough arguments\n");
    exit(0);
  }
  args.pat = argv[optind];
  getTxtFiles(args, argc, argv);
  vector<string> pat = getPatterns(args.patfile, args.pat);

  processTxtFiles(pat, args.txtfile, args);

  return 0;
}