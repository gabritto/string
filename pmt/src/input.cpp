#include "input.hpp"
#include <getopt.h>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

static const struct option lopts[] = {
  {"edit", required_argument, NULL, 'e'},
  {"pattern", required_argument, NULL, 'p'},
  {"algorithm", required_argument, NULL, 'a'},
  {"count", no_argument, NULL, 'c'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

static const char *sopts = "e:p:a:ch";
static void print_help();


void getOptions(argument &args, int argc, char *argv[]) {
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
        print_help();
        exit(0);
      case '?':
        exit(0);
      default:
        abort();
    }
  }

  
}


void getTxtFiles(argument &args, int argc, char *argv[]) {
  bool need_pattern = args.patfile == "";
  for(int i = optind + need_pattern; i < argc; ++i) { 
    args.txtfiles.push_back(argv[i]);
  }

  sort(args.txtfiles.begin(), args.txtfiles.end());
  auto it = unique(args.txtfiles.begin(), args.txtfiles.end());
  args.txtfiles.resize(it - args.txtfiles.begin());
}


static void print_help() {
  puts("Usage: pmt [OPTION]... PATTERN FILE [FILE]...");
  puts("Search for PATTERN in each FILE");
  puts("Example: pmt -c 'hello world' text.txt");
  puts("");
  puts("Options:");
  puts("\t-e, --edit=e_max\tset maximum edit distance to e_max");
  puts("\t-p, --pattern=FILE\tobtain patterns from FILE");
  puts("\t-c, --count\t\tprint only counts of matching substrings and lines");
  puts("\t-h, --help\t\tdisplay this message");
  puts("\t-a, --algorithm=A\tforce algorithm A to process the search. A is one of 'aho' (Aho-Corasick), 'boy' (Boyer-Moore), 'bf' (Bruteforce), 'sho' (Shift-Or), 'ukk' (Ukkonen), 'sell' (Sellers), 'wum' (Wu-Manber)");
}