#include <cstring>
#include <cstdio>
#include <string>
using namespace std;


namespace parser {

static const int buf_size = 1024 * 1024 * 16;
static char str[2 * buf_size + 1];
static char *ptr, *ptr_right;
static int str_len;
static FILE *txt;
static bool endd;

void open(string filename) {
	txt = fopen(filename.c_str(), "rb");
	if(txt == NULL) {
		printf("Error opening file: %s\n", filename.c_str());
		exit(0);
	}
  
	str[0] = '\0';
	str_len = 0;
  ptr_right = str - 1;
  endd = false;
}

const char* readLine() {
  if(endd) {
    return NULL;
  }

  ptr = ptr_right + 1;
  ptr_right = NULL;
  int size = (int) (str + str_len - ptr);
  if(size > 0) {
    ptr_right = (char*) memchr(ptr, '\n', size);
  }
  if(ptr_right == NULL) {
    if(feof(txt)) {
      endd = true;
      return ptr;
    }
    if(ptr == str && str[0] != '\0') {
      printf("%s\n", str);
      printf("Internal Error: line from input file is too large (size: %d). Cannot be greater than %d.\n", str_len, buf_size);
      exit(0);
    }

    int cpy_size = max(0, size);
    int offset = max(0, str_len - cpy_size);
    if(cpy_size > 0) {
      memmove(str, str + offset, cpy_size);
    }
    str_len = (int) (cpy_size + fread(str + cpy_size, 1, buf_size, txt));
    str[str_len] = '\0';
    ptr_right = str - 1;

    return readLine();
  }

  *ptr_right = '\0';
  return ptr;
}

} //namespace parser