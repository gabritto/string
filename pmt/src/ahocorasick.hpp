#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <vector>
#include <string>
#include <queue>

using namespace std;

namespace aho {

void build(const vector<string> &_pats);
int search(const char *txt);

}

#endif