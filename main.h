#ifndef MAIN_H
#define MAIN_H 
#include <stddef.h>

void validate_args(int argc, char *argv[]);

int unable_to_convert(int line, int not_loaded); 

void perform_operation(char *operation, int line, str_array_list county, str_array_list state, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, int_array_list inc_median, int_array_list inc_capita, float_array_list inc_poverty, int_array_list pop_2014, int_array_list use); 

void load_data(char *file_name, char *operation_file); 

#endif 
