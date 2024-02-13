#define _GNU_SOURCE 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "array_list.h"
#include "main.h"
#include "operations.h"
#include "util.h"
#define NUM_ARGS 3
#define NUM_ARRS 15
#define NUM_COLS 52

void validate_args(int argc, char *argv[]) {
    char *file_name = NULL; 
	
    if (argc != NUM_ARGS) { 
        fprintf(stderr, "ERROR: invalid number of command-line arguments\n"); 
        exit(1); 
    }

    for (int i = 1; i < NUM_ARGS; i++) { 
        file_name = argv[i];
        FILE *file = fopen(file_name, "r");
	if (file == NULL) { 
	    fprintf(stderr, "ERROR: %s does not exist or does not have permission\n", file_name);
            exit(1); 	    
        } 

        fclose(file); 	
    } 
} 

int unable_to_convert(int line, int not_loaded) {

     fprintf(stderr, "ERROR: Unable to convert data field on line %i\n", line);
     not_loaded++; 
     return not_loaded; 
}

void perform_operations(char *operations_file, int_array_list indexes, str_array_list county, str_array_list state, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white,float_array_list ethnic_white_not_hisp, int_array_list inc_median, int_array_list inc_capita, float_array_list inc_poverty, int_array_list pop_2014) {	
     FILE *op = fopen(operations_file, "r"); 
     char *operation = NULL; 
     size_t size = 0; 
     int line = 0;
     int print = 1; 
     int characters = 0;   
     int_array_list filtered; 
     int_array_list use = indexes;  

   while ((characters = getline(&operation, &size, op)) != -1) {
       line++;  
       remove_trailing_newline(operation);

       if (strlen(operation) == 0) { 
        
       } else if (strcmp(operation, "display") == 0) { 
           display(use, county, state, edu_bach, edu_hs, ethnic_native, ethnic_asian, ethnic_black, ethnic_hsp, ethnic_islander, ethnic_multi, ethnic_white, ethnic_white_not_hisp, inc_median, inc_capita, inc_poverty, pop_2014);  
       } else if (strstr(operation, "filter-state")) { 
           filtered = filter_state(operation, state, use);
           int_free_array_list(use);
	   use = filtered;   
       } else if (strstr(operation, "filter:")) { 
           filtered = general_filter(operation, edu_bach, edu_hs, ethnic_native, ethnic_asian, ethnic_black, ethnic_hsp, ethnic_islander, ethnic_multi, ethnic_white, ethnic_white_not_hisp, inc_median, inc_capita, inc_poverty, pop_2014, use, line); 
           int_free_array_list(use);
	   use = filtered;  
       } else if (strcmp(operation, "population-total") == 0) { 
           population_total(pop_2014, print, use); 	   
       } else if (strstr(operation, "population:")) { 
           population_field(operation, line, pop_2014, edu_bach, edu_hs, ethnic_native, ethnic_asian, ethnic_black, ethnic_hsp, ethnic_islander, ethnic_multi, ethnic_white, ethnic_white_not_hisp, inc_poverty, print, use); 
       } else if (strstr(operation, "percent:")) { 
           print = 0; 
           percent_field(operation, line, pop_2014, edu_bach, edu_hs, ethnic_native, ethnic_asian, ethnic_black, ethnic_hsp, ethnic_islander, ethnic_multi, ethnic_white, ethnic_white_not_hisp, inc_poverty, print, use); 
       } else { 
           fprintf(stderr, "ERROR: Line %i does not contain a valid operation\n", line); 
       } 

   }

   fclose(op); 
   free(operation);
   int_free_array_list(use);  
} 

void load_data(char *file_name, char *operations_file) {
     FILE *csv = fopen(file_name, "r"); 
     char *row = NULL;
     char *header = NULL;  
     char *token = NULL; 
     size_t size = 0; 
     size_t characters;  
     int i = 0; 
     int max = 0; 
     int line = 0; 
     int not_loaded = 0; 
     int error = 0;  
     int county_index = 0; 
     int read = 0; 
     int state_index = 0; 
     int edu_bach_index = 0; 
     int edu_hs_index = 0; 
     int ethnic_native_index = 0; 
     int ethnic_asian_index =0; 
     int ethnic_black_index = 0; 
     int ethnic_hsp_index = 0; 
     int ethnic_islander_index = 0; 
     int ethnic_multi_index = 0; 
     int ethnic_white_index = 0; 
     int ethnic_white_not_hisp_index = 0; 
     int inc_median_index = 0; 
     int inc_capita_index = 0; 
     int inc_poverty_index = 0; 
     int pop_2014_index = 0; 
     int_array_list indexes = int_array_list_new(); 
     str_array_list county  = str_array_list_new();
     str_array_list state = str_array_list_new(); 
     float_array_list edu_bach = float_array_list_new();
     float_array_list edu_hs = float_array_list_new();  
     float_array_list ethnic_native = float_array_list_new(); 
     float_array_list ethnic_asian = float_array_list_new(); 
     float_array_list ethnic_black = float_array_list_new(); 
     float_array_list ethnic_hsp = float_array_list_new(); 
     float_array_list ethnic_islander = float_array_list_new(); 
     float_array_list ethnic_multi = float_array_list_new(); 
     float_array_list ethnic_white = float_array_list_new(); 
     float_array_list ethnic_white_not_hisp = float_array_list_new(); 
     int_array_list inc_median = int_array_list_new(); 
     int_array_list inc_capita = int_array_list_new(); 
     float_array_list inc_poverty = float_array_list_new(); 
     int_array_list pop_2014 = int_array_list_new();   

     if (csv == NULL) { 
         fprintf(stderr, "ERROR: cannot open csv file %s\n", file_name); 
	 exit(1); 
     } 

     // get column names
     getline(&header, &size, csv);
     token = strtok(header, ","); 
     while (token != NULL) {
	 token = remove_quotes(token); 
	 if (strcmp(token, "County") == 0) { 
             county_index = i; 
	 } else if (strcmp(token, "State") == 0) {
             state_index = i; 
         } else if (strcmp(token, "Education.Bachelor's Degree or Higher") == 0) {
             edu_bach_index = i; 
         } else if (strcmp(token, "Education.High School or Higher") == 0) {
             edu_hs_index = i; 
         } else if (strcmp(token, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
             ethnic_native_index = i; 
         } else if (strcmp(token, "Ethnicities.Asian Alone") == 0) {
             ethnic_asian_index = i; 
         } else if (strcmp(token, "Ethnicities.Black Alone") == 0) {
             ethnic_black_index = i; 
	 } else if (strcmp(token, "Ethnicities.Hispanic or Latino") == 0) { 
             ethnic_hsp_index = i; 
         } else if (strcmp(token, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
             ethnic_islander_index = i; 
         } else if (strcmp(token, "Ethnicities.Two or More Races") == 0) {
             ethnic_multi_index = i; 
         } else if (strcmp(token, "Ethnicities.White Alone") == 0) {
             ethnic_white_index = i; 
         } else if (strcmp(token, "Ethnicities.White Alone not Hispanic or Latino") == 0) {
             ethnic_white_not_hisp_index = i; 
         } else if (strcmp(token, "Income.Median Household Income") == 0) {
             inc_median_index = i;
         } else if (strcmp(token, "Income.Per Capita Income") == 0) {
             inc_capita_index = i;
         } else if (strcmp(token, "Income.Persons Below Poverty Level") == 0) {
             inc_poverty_index = i;
         } else if (strcmp(token, "Population.2014 Population") == 0) {
             pop_2014_index = i; 
         } 
        
	 token = strtok(NULL, ",");  
	 i++; 
     }
     free(header);  

     // get observations 
     while ((characters = getline(&row, &size, csv)) != -1) {
	  line++;  
	  i = 0;
	  error = 0;  
	  read = 0; 
          token = strtok(row, ","); 
	  while (token != NULL) {
	      
	      token = remove_quotes(token); 
              if ((strcmp(token, " ") == 0) || (strcmp(token, "") == 0)) {
                  fprintf(stderr, "ERROR: Missing entry on line %i\n", line); 
		  not_loaded++; 
		  error = 1;  
	      } 
 
	      if (i == county_index) {
		   county = str_array_list_add_to_end(county, token); 
		   read++;
              }  else if (i == state_index) { 
		  if (check_string(token)) {
                      state = str_array_list_add_to_end(state, token); 
		      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);
		      error = 1; 
	          } 
	      } else if (i == edu_bach_index) { 
		  if (check_float(token)) { 
                      edu_bach = float_array_list_add_to_end(edu_bach, atof(token));
		      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1; 
	          } 
	      } else if (i == edu_hs_index) { 
		  if (check_float(token)) { 
                      edu_hs = float_array_list_add_to_end(edu_hs, atof(token)); 
		      read++; 
                  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1; 
	          } 
	      } else if (i == ethnic_native_index) { 
		  if (check_float(token)) { 
                      ethnic_native = float_array_list_add_to_end(ethnic_native, atof(token));
		      read++;
                  } else {
                      not_loaded = unable_to_convert(line, not_loaded);
		      error = 1; 
	          }
	      } else if (i == ethnic_asian_index) {
		  if (check_float(token)) {  
                      ethnic_asian = float_array_list_add_to_end(ethnic_asian, atof(token));
		      read++; 
                  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);
		      error = 1; 
	          }
	      } else if (i == ethnic_black_index) { 
                  if (check_float(token)) { 
		      ethnic_black = float_array_list_add_to_end(ethnic_black, atof(token));
		      read++; 
                  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);
		      error = 1; 
	          }
	      } else if (i == ethnic_hsp_index) { 
                  if (check_float(token)) { 
		      ethnic_hsp = float_array_list_add_to_end(ethnic_hsp, atof(token)); 
                      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1; 
	          }
	      } else if (i == ethnic_islander_index) {
		  if (check_float(token)) {  
                      ethnic_islander = float_array_list_add_to_end(ethnic_islander, atof(token));
		      read++; 
		  } else {
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1; 
	          } 
	      } else if (i == ethnic_multi_index) {
                  if (check_float(token)) { 
		      ethnic_multi = float_array_list_add_to_end(ethnic_multi, atof(token)); 
                      read++; 
		  } else {
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1; 
	          }
	      } else if (i == ethnic_white_index) {
                  if (check_float(token)) { 
		      ethnic_white = float_array_list_add_to_end(ethnic_white, atof(token)); 
                      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1; 
	          }
	      } else if (i == ethnic_white_not_hisp_index) { 
                  if (check_float(token)) { 
		      ethnic_white_not_hisp = float_array_list_add_to_end(ethnic_white_not_hisp, atof(token));
	              read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1;
	          }	   
	      } else if (i == inc_median_index) { 
                  if (check_int(token)) {
		      inc_median = int_array_list_add_to_end(inc_median, atoi(token)); 
                      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1;
	          }
	      } else if (i == inc_capita_index) { 
                  if (check_int(token)) {
		      inc_capita = int_array_list_add_to_end(inc_capita, atoi(token)); 
                      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1;
	          }
	      } else if (i == inc_poverty_index) { 
                  if (check_float(token)) { 
		      inc_poverty = float_array_list_add_to_end(inc_poverty, atof(token));
		      read++;  
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded);  
		      error = 1;
	          }
	      } else if (i == pop_2014_index) { 
                  if (check_int(token)) { 
		      pop_2014 = int_array_list_add_to_end(pop_2014, atoi(token)); 
                      read++; 
		  } else { 
                      not_loaded = unable_to_convert(line, not_loaded); 
		      error = 1; 
	          }
	      } 

	      if (error == 1) { 
                  break; 
	      }
	      token = strtok(NULL, ","); 
	      i++;
          }

	  if ((i < NUM_COLS) && (error == 0)) { 
                 fprintf(stderr, "ERROR: Missing entry on line %i\n", line); 
		 not_loaded++;
		 error = 1; 
          }   

	  if (error == 1) { 
              for (int j = 0; j < read; j++) {
		   // There are a maximum of 16 columns per row that we are reading in
		   // Depending on how many columns we read before an error we need to remove from the end of the corresponding list 
		   if (j == 0) { // read 1 
                       county = str_array_list_remove_from_end(county); 
	           } else if (j == 1) { // read 2 
                       state = str_array_list_remove_from_end(state);  
		   } else if (j == 2) { // read 3
                       edu_bach = float_array_list_remove_from_end(edu_bach); 
		   } else if (j == 3) { // read 4
                       edu_hs = float_array_list_remove_from_end(edu_hs); 
		   } else if (j == 4) { // read 5
                       ethnic_native = float_array_list_remove_from_end(ethnic_native); 
		   } else if (j == 5) { // read 6 
                       ethnic_asian = float_array_list_remove_from_end(ethnic_asian); 
		   } else if (j == 6) { // read 7
                       ethnic_black = float_array_list_remove_from_end(ethnic_black); 
		   } else if (j == 7) { // read 8
                       ethnic_hsp = float_array_list_remove_from_end(ethnic_hsp); 
		   } else if (j == 8) { // read 9
                       ethnic_islander = float_array_list_remove_from_end(ethnic_islander); 
		   } else if (j == 9) { // read 10
                       ethnic_multi = float_array_list_remove_from_end(ethnic_multi); 
		   } else if (j == 10) { // read 11
                       ethnic_white = float_array_list_remove_from_end(ethnic_white); 
		   } else if (j == 11) { // read 12
                       ethnic_white_not_hisp = float_array_list_remove_from_end(ethnic_white_not_hisp); 
		   } else if (j == 12) { // read 13
                       inc_median = int_array_list_remove_from_end(inc_median); 
		   } else if (j == 13) { // read 14
                       inc_capita = int_array_list_remove_from_end(inc_capita); 
		   } else if (j == 14) { // read 15 
                       inc_poverty = float_array_list_remove_from_end(inc_poverty); 
		   } else if (j == 15) { // read 16 
                       pop_2014 = int_array_list_remove_from_end(pop_2014); 
		   } 	   
	      } 
          } 
     }
     
     max = pop_2014.length; 
     for (int i = 0; i < max; i++) { 
         indexes = int_array_list_add_to_end(indexes, i); 
     }

     line = line - not_loaded; 
     fprintf(stdout, "%i records loaded\n", line);

     perform_operations(operations_file, indexes, county, state, edu_bach, edu_hs, ethnic_native, ethnic_asian, ethnic_black, ethnic_hsp, ethnic_islander, ethnic_multi, ethnic_white, ethnic_white_not_hisp, inc_median, inc_capita, inc_poverty, pop_2014); 
          
     free(row); 
     str_free_array_list(county, line);
     str_free_array_list(state, line); 
     float_free_array_list(edu_bach); 
     float_free_array_list(edu_hs); 
     float_free_array_list(ethnic_native);
     float_free_array_list(ethnic_asian);
     float_free_array_list(ethnic_black); 
     float_free_array_list(ethnic_hsp); 
     float_free_array_list(ethnic_islander); 
     float_free_array_list(ethnic_multi); 
     float_free_array_list(ethnic_white); 
     float_free_array_list(ethnic_white_not_hisp); 
     int_free_array_list(inc_median); 
     int_free_array_list(inc_capita); 
     float_free_array_list(inc_poverty); 
     int_free_array_list(pop_2014); 
     fclose(csv); 
} 

int main (int argc, char *argv[]) { 
    validate_args(argc, argv);
    load_data(argv[1], argv[2]);  
    return 0; 
}
