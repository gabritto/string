#ifndef AHO_H
#define AHO_H

#include <vector>

namespace aho {

extern std::vector<int> alphabet_hash;
std::vector<std::vector<int>> buildFSM(const char *pat, int l, int r);

}  // namespace aho

#endif