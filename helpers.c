#include "helpers.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

void handle_input(char *info_msg, char *error_msg, char *format, void *dest)
{
  char c;
  if (info_msg != NULL)
    printf("%s", info_msg);

  while(!scanf(format, dest))
  {
    // clean up any unread characters
    // C: Από την θεωρία στην εφαρμογή (Τσελίκης / Τσελίκας) (σελ. 65)
    while((c = (char)getchar()) != '\n' && c != EOF);

    if (error_msg != NULL)
      printf("%s", error_msg);
  }
  while((c = (char)getchar()) != '\n' && c != EOF);
}

char *trim(char *string)
{
  if (string == NULL || !strlen(string))
    return string;

  int start, end;

  // find the first character that is not a space
  for (start = 0; isspace(string[start]); ++start);

  if (string[start] == '\0')
    // the string only contains spaces
    return NULL;

  // find the index of the first character from the end
  for (end = 0; string[end + 1] != '\0'; ++end);

  // find the index of the first alphanumeric character from the end
  for (; end >= 0 && isspace(string[end]); --end);

  // terminate the string
  string[end + 1] = '\0';

  return string + start;
}

int is_valid_name(const char *name)
{
  if (name == NULL || !strlen(name))
    return 0;

  int i;
  for (i = 0; name[i] != '\0'; ++i)
    if (!isalpha(name[i]))
      return 0;

  return 1;
}