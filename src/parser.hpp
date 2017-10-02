#ifndef PARSER_H
#define PARSER_H

namespace parser {
  void open(string filename);
  const char* readLine();
  void close();

} 

#endif