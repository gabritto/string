#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include "util.hpp"

#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

namespace boyer {

void build(const vector<string> &pat);
int search(const char *txt);

} //namespace boyer

#endif
