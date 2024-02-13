#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#define _GNU_SOURCE
#include <stddef.h>
#include <unistd.h> 

typedef struct str_array_list str_array_list;
typedef struct float_array_list float_array_list; 
typedef struct int_array_list int_array_list;  

struct str_array_list {
    int length; 
    int capacity; 
    char **array; 
};

struct float_array_list {
    int length; 
    int capacity; 
    float *array; 
};

struct int_array_list {
    int length; 
    int capacity; 
    int *array; 
};

void *checked_malloc_str(size_t size);

str_array_list str_array_list_new(); 

str_array_list str_array_list_add_to_end(str_array_list al, char *observ);

str_array_list str_array_list_remove_from_end(str_array_list al);

void str_free_array_list(str_array_list al, int line);

void *checked_malloc_float(size_t size);

float_array_list float_array_list_new(); 

float_array_list float_array_list_add_to_end(float_array_list al, float observ); 

float_array_list float_array_list_remove_from_end(float_array_list al);
 
void float_free_array_list(float_array_list al);

void *checked_malloc_int(size_t size);

int_array_list int_array_list_new(); 

int_array_list int_array_list_add_to_end(int_array_list al, int observ);

int_array_list int_array_list_remove_from_end(int_array_list al);
 
void int_free_array_list(int_array_list al);

#endif
