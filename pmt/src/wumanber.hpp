#ifndef WUMANBER_H
#define WUMANBER_H

#include <vector>
#include <string>

using namespace std;

namespace wumanber {
    
const int max_pat_len = 64;
void build(const vector<string> &_patterns, int r);
int search(const char *txt);

} //namespace wumanber

#endif




