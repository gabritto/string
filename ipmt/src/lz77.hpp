#ifndef LZ77_H
#define LZ77_H

namespace lz77 {

char* encode(const char* txt, int ls, int la);
char* decode(const char* code, int ls, int la);

}  // namespace lz77

#endif
