#include "helpers.h"

#include <stdio.h>

long file_size(char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return -1;

  fseek(file, 0, SEEK_END);

  long result = ftell(file);
  fclose(file);

  return result;
}

void handle_input(char *info_msg, char *error_msg, char *format, void *result)
{
  char c;
  if (info_msg != NULL)
    printf("%s", info_msg);

  while(!scanf(format, result))
  {
    while((c = (char)getchar()) != '\n' && c != EOF);

    if (error_msg != NULL)
      printf("%s", error_msg);
  }
  while((c = (char)getchar()) != '\n' && c != EOF);
}