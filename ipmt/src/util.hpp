#ifndef UTIL_H
#define UTIL_H

using namespace std;
#include <string>
#include <vector>

struct argument {
  argument() : count(false) {}

  string patfile = "";
  bool count;
  bool mode;
  vector<string> pats;
  string file; //either the textfile (index mode) or the indexfile (search mode)
};
const bool INDEX = false;
const bool SEARCH = true;

void getArgs(argument &args, int argc, char *argv[]);
void getTxtFiles(argument &args, int argc, char *argv[]);

#endif