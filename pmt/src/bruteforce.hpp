#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <string>
#include <vector>

using namespace std;

namespace bruteforce {
	void build(const vector<string> &_pats);
	int search(const char *txt);
}

#endif