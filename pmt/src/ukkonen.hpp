#ifndef UKKONEN_H
#define UKKONEN_H

#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

namespace ukkonen {

void build(const vector<string> &patterns, int r);
int search(const char *txt);

} //namespace ukkonen

#endif
