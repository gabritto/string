#ifndef UTIL_H
#define UTIL_H

#include "input.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> getPatterns(const string &file);
void processTxtFile(const vector<string> &pats, const string &txt_filename, const argument args);

#endif