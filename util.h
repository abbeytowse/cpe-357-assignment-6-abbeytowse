#ifndef UTIL_H
#define UTIL_H 
#include <stddef.h>

char* remove_quotes(char *s);

void remove_trailing_newline(char *str); 

int check_string(char *s); 

int check_float(char *s); 

int check_int(char *s); 

#endif 
