#ifndef SHIFTOR_H
#define SHIFTOR_H

#include <vector>
#include <string>

using namespace std;

namespace shiftor {

const int max_pat_len = 64;
void build(const vector<string> &_patterns);
int search(const char *txt);

} //namespace shiftor

#endif