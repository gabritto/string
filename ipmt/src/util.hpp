#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

struct argument {
  argument() : count(false) {}

  std::string patfile = "";
  bool count;
  bool mode;
  std::vector<std::string> pats;
  std::string
      file;  // either the textfile (index mode) or the indexfile (search mode)
};
const bool INDEX = false;
const bool SEARCH = true;

void getArgs(argument &args, int argc, char *argv[]);
void getTxtFiles(argument &args, int argc, char *argv[]);
char *read(std::string filename);
#endif