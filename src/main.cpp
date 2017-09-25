#include <getopt.h>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <regex>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  getOptions(argc, argv);
  if(argc - optind < 2) {
    printf("not enough arguments\n");
    exit(0);
  }
  args.pat = argv[optind];
  getTxtFiles(argc, argv);

  if(args.e_max > 0 && args.algo != "" && args.algo != "se" && args.algo != "uk") {
    printf("Algorithm not compatible with approximate matching.\n");
    exit(0);
  }

  if(args.algo != "") {
    switch args.algo:
      case "aho":
        
  }
  return 0;
}