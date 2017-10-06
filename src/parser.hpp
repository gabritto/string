#ifndef PARSER_H
#define PARSER_H

#include <string>

using namespace std;

namespace parser {
  void open(const string &filename);
  const char* readLine();
  void close();

} 

#endif