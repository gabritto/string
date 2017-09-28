#ifndef UKKONEN_H
#define UKKONEN_H

#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

namespace ukkonen {

void build(const string &pat, int r);
int search(const string &txt);

} //namespace ukkonen

#endif
