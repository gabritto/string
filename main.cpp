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
const struct option lopts[] = {
  {"edit", required_argument, NULL, 'e'},
  {"pattern", required_argument, NULL, 'p'},
  {"algorithm", required_argument, NULL, 'a'},
  {"count", no_argument, NULL, 'c'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

const char *help_msg = "help";

const char *sopts = "e:p:a:ch";

struct argument {
  argument() : e_max(0), count(false) {}
  
  int e_max;
  string patfile;
  string algo;
  bool count;

  string pat;
  vector<string> txtfile;
};

struct argument args;

void getOptions(int argc, char *argv[]) {
  int c;
  int idxptr;

  while((c = getopt_long(argc, argv, sopts, lopts, &idxptr)) != -1) {
    switch(c) {
      case 'e':
        for(int i = 0; optarg[i] != '\0'; ++i) {
          if(optarg[i] < '0' || optarg[i] > '9') {
            printf("missing argument --edit\n");
            exit(0);
          }
        }
        args.e_max = atoi(optarg);
        break;
      case 'p':
        args.patfile = optarg;
        break;
      case 'a':
        args.algo = optarg;
        break;
      case 'c':
        args.count = true;
        break;
      case 'h':
        printf("%s\n", help_msg);
        exit(0);
      case '?':
        exit(0);
    }
  }
}


void getTxtFiles(int argc, char *argv[]) {

  for(int i = optind + 1; i < argc; ++i) { 
    args.txtfile.push_back(argv[i]);
  }

  sort(args.txtfile.begin(), args.txtfile.end());
  auto it = unique(args.txtfile.begin(), args.txtfile.end());
  args.txtfile.resize(it - args.txtfile.begin());

  for(string &s : args.txtfile) {
    cout << s << endl;
  }

}

int main(int argc, char *argv[]) {

  getOptions(argc, argv);
  args.pat = argv[optind];
  getTxtFiles(argc, argv);



  return 0;
}