#include "index.hpp"
#include "search.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  argument args;
  getArgs(args, argc, argv);

  if (args.mode == INDEX) {
    buildIndex(args.file);
  } else {
    search(args.pats, args.file);
  }

  return 0;
}