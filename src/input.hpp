#ifndef INPUT_H
#define INPUT_H

using namespace std;
#include <vector>
#include <string>

struct argument {
  argument() : e_max(0), count(false) {}
  
  int e_max;
  string patfile;
  string algo;
  bool count;

  string pat;
  vector<string> txtfiles;
};


void getOptions(argument &args, int argc, char *argv[]);
void getTxtFiles(argument &args, int argc, char *argv[]);

#endif