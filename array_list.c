#include "array_list.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <dirent.h> 
#include <unistd.h>
#define PATH_SIZE 256 
#define CAPACITY 52

void *checked_malloc_str(size_t size) {
    int *p; 

    p = malloc(sizeof(char *) * size); 
    if (p == NULL) {
	perror("malloc"); 
	exit(1); 
    } 

    return p; 
}

str_array_list str_array_list_new() {
    str_array_list al; 

    al.length = 0; 
    al.capacity = CAPACITY;
    al.array = checked_malloc_str(CAPACITY); 
    return al;     
}

str_array_list str_array_list_add_to_end(str_array_list al, char *observ) {
    if (al.capacity == al.length) { 
        al.array = realloc(al.array, sizeof(char *) * (al.length+CAPACITY)); 
        al.capacity += CAPACITY; 
    }
 
    int size = strlen(observ) + 1; 
    char *string = malloc(sizeof(char *) * size);
    
    strcpy(string, observ); 
    strcat(string, "\0");
    al.array[al.length] = string;   
    al.length += 1; 
    //free(string); 
    return al;
}

str_array_list str_array_list_remove_from_end(str_array_list al) { 
     if (al.length == 0) {
         fprintf(stderr, "ERROR: str cannot remove end of array with length 0\n"); 
	 return al; 
     }
     
     al.length -= 1; // this might create a memory leak???? 
     return al; 
}

void str_free_array_list(str_array_list al, int line) {
     
    for (int i = 0; i < line; i++) { 
        free(al.array[i]); 
    }	    

    free(al.array); 
}

void *checked_malloc_float(size_t size) {
    int *p; 

    p = malloc(sizeof(float) * size); 
    if (p == NULL) {
	perror("malloc"); 
	exit(1); 
    } 

    return p; 
}

float_array_list float_array_list_new() {
    float_array_list al; 

    al.length = 0; 
    al.capacity = CAPACITY;
    al.array = checked_malloc_float(CAPACITY); 
    return al;     
}

float_array_list float_array_list_add_to_end(float_array_list al, float observ) {
    if (al.capacity == al.length) {  
	al.array = realloc(al.array, sizeof(float) * (al.length + CAPACITY)); 
        al.capacity += CAPACITY; 
    }

    al.array[al.length] = observ;  
    al.length += 1;  
    return al; 
}

float_array_list float_array_list_remove_from_end(float_array_list al) {	
     if (al.length == 0) {
         fprintf(stderr, "ERROR: float cannot remove end of array with length 0\n"); 
	 return al; 
     }
     
     al.length -= 1; // this might create a memory leak???? 
     return al; 
}

void float_free_array_list(float_array_list al) {
     
    free(al.array); 
} 

void *checked_malloc_int(size_t size) {
    int *p; 

    p = malloc(sizeof(int) * size); 
    if (p == NULL) {
	perror("malloc"); 
	exit(1); 
    } 

    return p; 
}

int_array_list int_array_list_new() {
    int_array_list al; 

    al.length = 0; 
    al.capacity = CAPACITY;
    al.array = checked_malloc_int(CAPACITY); 
    return al;     
}

int_array_list int_array_list_add_to_end(int_array_list al, int observ) {
    if (al.capacity == al.length) {  
	al.array = realloc(al.array, sizeof(int) * (al.length + CAPACITY)); 
        al.capacity += CAPACITY; 
    }

    al.array[al.length] = observ;  
    al.length += 1;  
    return al; 
}

int_array_list int_array_list_remove_from_end(int_array_list al) { 
     if (al.length == 0) {
         fprintf(stderr, "ERROR: int cannot remove end of array with length 0\n"); 
	 return al; 
     }
     
     al.length -= 1; // this might create a memory leak???? 
     return al; 
}

void int_free_array_list(int_array_list al) {
     
    free(al.array); 
} 
