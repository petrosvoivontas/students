#ifndef HELPERS_H
#define HELPERS_H

// Returns the size of a file (used for replacing feof)
long file_size(char *filename);

// Asks the user for input until the user types something that complies with the format
void handle_input(char *info_msg, char *error_msg, char *format, void *result);

#endif
