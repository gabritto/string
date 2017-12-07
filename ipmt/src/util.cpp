#include "util.hpp"
#include <getopt.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static const struct option lopts[] = {{"pattern", required_argument, NULL, 'p'},
                                      {"count", no_argument, NULL, 'c'},
                                      {"help", no_argument, NULL, 'h'},
                                      {0, 0, 0, 0}};

static const char *sopts = "p:ch";
static void print_help();
static bool findMode(int argc, char *argv[]);
static void getPatterns(argument &args);

void getArgs(argument &args, int argc, char *argv[]) {
  int c;
  int idxptr;

  args.mode = findMode(argc, argv);

  if (args.mode == INDEX) {
    if (argc == 3) {
      args.file = argv[2];
    } else {
      printf("Invalid format. --help for more info\n");
      exit(0);
    }
  }

  else {  // mode == SEARCH
    while ((c = getopt_long(argc, argv, sopts, lopts, &idxptr)) != -1) {
      switch (c) {
        case 'p':
          args.patfile = optarg;
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

    if (args.patfile == "") {
      if (argc - optind == 2) {
        args.pats.push_back(argv[optind]);
        args.file = argv[optind + 1];
      } else {
        printf("Invalid format. --help for more info\n");
        exit(0);
      }
    } else {
      getPatterns(args);
    }
  }
}

char *read(string filename) {
  FILE *file = fopen(filename.c_str(), "rb");
  if (file == NULL) {
    printf("Failed to open file: %s.\n", filename.c_str());
    exit(0);
  } else {
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    char *data = new char[size];
    fread(data, 1, size, file);
    fclose(file);
    return data;
  }
}

static bool findMode(int argc, char *argv[]) {
  bool mode;
  if (argc < 2) {
    printf("Invalid format. --help for more info.\n");
    exit(0);
  } else {
    if (strcmp(argv[1], "index") == 0) {
      mode = false;
    } else if (strcmp(argv[1], "search") == 0) {
      mode = true;
    } else {
      printf("Invalid format. --help for more info.\n");
      exit(0);
    }
  }
  return mode;
}

static void getPatterns(argument &args) {
  ifstream pat_file(args.patfile);
  if (pat_file.fail()) {
    printf("Failed to open file: %s.\n", args.patfile.c_str());
    exit(0);
  } else {
    string pat;
    while (getline(pat_file, pat)) {
      args.pats.push_back(pat);
    }
  }

  pat_file.close();
}

static void print_help() {
  puts("Usage (index mode): ipmt index TEXTFILE");
  puts("Create a encoded index of TEXTFILE");
  puts("Example: ipmt index text.txt");
  puts("");
  puts("Usage (search mode): ipmt search [OPTIONS] PATTERN INDEXFILE");
  puts("Search for PATTERNFILE in the text file that originated INDEXFILE");
  puts("Example: ipmt search -c 'hello world' text.idx");
  puts("");
  puts("Options:");
  puts("\t-p, --pattern=FILE\tobtain a list of patterns from FILE");
  puts("\t-c, --count\t\tprint only counts of matching substrings and lines");
  puts("\t-h, --help\t\tdisplay this message");
}
