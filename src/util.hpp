#ifndef UTIL_H
#define UTIL_H

#include "input.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> getPatterns(const string &file);
void processTxtFiles(const vector<string> &pats, const vector<string> &txt_filename, argument args);
pair<vector<int>, int> getAlphabet(const vector<string> &pats);
pair<vector<int>, int> getAlphabet(const string &pat);

#endif