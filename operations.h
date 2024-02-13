#ifndef OPERATIONS_H
#define OPERATIONS_H 
#include <stddef.h>

int is_num(char *num); 

int check_present(int i, int_array_list use);

float perc_of_pop(float per, int pop); 

int population_total(int_array_list pop_2014, int print, int_array_list use); 

float population_field(char *operation, int line, int_array_list pop_2014, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, float_array_list inc_poverty, int print, int_array_list use); 

void percent_field(char *operation, int line, int_array_list pop_2014, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, float_array_list inc_poverty, int print, int_array_list use); 

int_array_list filter_state(char *operation, str_array_list state, int_array_list use);

int_array_list general_filter(char *operation, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, int_array_list inc_median, int_array_list inc_capita, float_array_list inc_poverty, int_array_list pop_2014, int_array_list use, int line); 

void display(int_array_list use, str_array_list county, str_array_list state, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white,float_array_list ethnic_white_not_hisp, int_array_list inc_median, int_array_list inc_capita, float_array_list inc_poverty, int_array_list pop_2014); 

#endif 
