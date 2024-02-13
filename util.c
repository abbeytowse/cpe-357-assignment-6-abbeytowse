#define _GNU_SOURCE 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

char* remove_quotes(char *s) { 
    int idx = 0; 
    int len = strlen(s);  
    
    // 34 is '"' on the ascii table
    while ((s[idx] == 34) && (s[idx] != '\0')) { 
        idx++; 
    } 

    while (s[len - 1] != 34) {
        len--;
    } 

    s[len - 1] = '\0'; 
    return &s[idx]; 
}

void remove_trailing_newline(char *str) { 
    if (str == NULL) {
        return; 
    } 

    int len = strlen(str); 

    if (str[len-1] == '\n') {
        str[len-1] = '\0'; 
    } else if (str[len-1] == ' ') { 
        str[len-1] = '\0'; 
    } 
}

int check_string(char *s) { 

    if (atof(s) || atoi(s)) { 
        return 0; 
    } 

    return 1; 
} 

int check_float(char *s) {
     
    if (atof(s)) {
        return 1; 
    } else if (strcmp(s, "0.0") == 0) {
        return 1; 
    }

    return 0; 
} 

int check_int(char *s) {

    if (atoi(s)) {
        return 1;  
    } else if (strcmp(s, "0") == 0) { 
       return 1; 
    } 

    return 0; 
}
