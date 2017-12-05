#include <getopt.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "index/index.hpp"
#include "search/search.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (!strcmp(argv[1], "index")) {
      if (argc == 3) {
        main_index(argv[2]);
      } else {
        printf(
            "Invalid format. Index mode needs a textfile and textfile only.");
      }
    } else if (!strcmp(argv[1], "search")) {
      // mainSearch();
    } else {
      printf("Invalid format. --help for more info");
    }
  }
  printf("Invalid format. --help for more info.");
  return 0;
}