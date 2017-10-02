#include <cstring>
#include <cstdio>
#include <string>
using namespace std;


namespace parser {

static int buf_size = 1024 * 1024 * 32;
static char *str = NULL;
static char *ptr, *ptr_right;
static int str_len;
static FILE *txt = NULL;
static bool endd;

void open(string filename) {
  if(txt != NULL) {
    printf("Error during call to parser::open(). A file is already opened. Use parser::close() before opening a new file.\n");
    exit(0);
  }
  txt = fopen(filename.c_str(), "rb");
  if(txt == NULL) {
    printf("Error opening file: %s\n", filename.c_str());
    exit(0);
  }

  str = new char[2 * buf_size + 1];
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

    else if(ptr == str && str[0] != '\0') { //|line| > buf_size
      buf_size *= 2;
      char *new_str = new char[2 * buf_size + 1];
      delete[] str;
      str = new_str;
    } 

    int cpy_size = max(0, size);
    fseek(txt, -cpy_size, SEEK_CUR);
    str_len = (int) fread(str, 1, buf_size, txt);
    str[str_len] = '\0';
    ptr_right = str - 1;

    return readLine();
  }
  else {
    *ptr_right = '\0';
    //printf("%s\n", ptr);
    return ptr;
  }
}

void close() {
  if(fclose(txt) != EOF) {
    delete[] str;
    str = NULL;
    txt = NULL;
  }
  else {
    printf("Error closing during parser::close(). Couldn't close file.\n");
    exit(0);    
  }
}

} //namespace parser