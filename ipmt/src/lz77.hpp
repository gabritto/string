#ifndef LZ77_H
#define LZ77_H

#include <string>

namespace lz77 {
std::pair<char*, int> encode(const char* txt, int n, int ls, int la);
std::pair<char*, int> decode(const char* code, int m, int ls, int la);

}  // namespace lz77

int decodeInt(const char* n, int size);
std::string encodeInt(int n, int size);
#endif
