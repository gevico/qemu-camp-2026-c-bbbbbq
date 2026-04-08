#include "mywc.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  const char* filepath = "./text.txt";

  (void)argc;
  (void)argv;
  process_file(filepath);
  return 0;
}
