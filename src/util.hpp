#ifndef UTIL_H
#define UTIL_H

#include "input.hpp"
#include <string>
#include <vector>
#include <tuple>

using namespace std;

vector<string> getPatterns(const string &file, const string &pattern);
void processTxtFiles(const vector<string> &pats, argument args);
pair<vector<int>, int> getAlphabet(const vector<string> &pats);
pair<vector<int>, int> getAlphabet(const string &pat);

#endif
