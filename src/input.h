#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>

struct argument {
  argument() : e_max(0), count(false) {}
  
  int e_max;
  string patfile;
  string algo;
  bool count;

  string pat;
  vector<string> txtfile;
};


void getOptions(int argc, char *argv[]);
void getTxtFiles(int argc, char *argv[]);

#endif