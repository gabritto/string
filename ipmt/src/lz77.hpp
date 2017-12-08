#ifndef LZ77_H
#define LZ77_H

#include <string>

int decodeInt(const char* n,
              int size);  //@size in bits of @n's codification. size <= 32
std::string encodeInt(int n, int size);

namespace lz77 {
std::pair<char*, int> encode(const char* txt, int n, int ls, int la);
std::pair<char*, int> decode(const char* code, int m, int ls, int la);

}  // namespace lz77

#endif
