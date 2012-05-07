#include <stdlib.h>
#include <stdio.h>
#include "path_lookup.h"
#include <string.h>

int main(int argc, char *argv[])
{
  char* path1 = strdup("/home/sean/Code/sh142"); // avoid a hard coded string. dynamically allocates memory with malloc
  char* path2 = strdup("/home/sean/Code/sh142/src"); // avoid a hard coded string. dynamically allocates memory with malloc
  setenv("DATA", "/home/sean/Dropbox/Lotus", 1);

  char* result1 = searchPath(path1, "Gemfile.lock");
  char* result2 = searchPath(path2, "fifo.c");
  char* result3 = searchPath(path2, "fifo.h");
  char* result4 = resolve_path("ls");
  char* result5 = resolve_path("doesnotExist.cmpe");
  char* result6 = resolve_data("mods.txt");
  char* result7 = resolve_data("doesnotExist.cmpe");

  printf("%s\n", result1);
  printf("%s\n", result2);

  if(result3 == NULL)
    printf("fifo.h could not be found in: %s\n", path2);
  else
    printf("%s\n", result3);

  printf("%s\n", result4);

  if(result5 == NULL)
    printf("doesnotExist.cmpe could not be found in: PATH\n");
  else
    printf("%s\n", result5);

  printf("%s\n", result6);

  if(result7 == NULL)
    printf("doesnotExist.cmpe could not be found in: DATA\n");
  else
    printf("%s\n", result7);
  
  return 0;
}