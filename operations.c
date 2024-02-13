#define _GNU_SOURCE 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "array_list.h"
#include "operations.h" 
#include "util.h" 

int check_present(int i, int_array_list use) {
    int present = 0;
    int use_len = use.length;

    for (int j = 0; j < use_len; j++) {
        if (use.array[j] == i) {
            present = 1;
            break;
	}
    }

    return present;
}

int is_num(char *num) {

    if (check_float(num)) {
        return atof(num);
    } else if (check_int(num)) {
        return atoi(num);
    }

    return 0;
}

float perc_of_pop(float per, int pop) { 
    float calc = 0.0;    

    calc = per * pop; 
    return calc; 
} 

int population_total(int_array_list pop_2014, int print, int_array_list use) {
    int len = pop_2014.length; 
    int total = 0; 

    for (int i = 0; i < len; i++) { 
	if (check_present(i, use)) { 
            total += pop_2014.array[i]; 
	} 
    } 
    
    if (print) { 
        fprintf(stdout, "2014 population: %i\n", total);
    } 
    return total;     
} 

float population_field(char *operation, int line, int_array_list pop_2014, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, float_array_list inc_poverty, int print, int_array_list use) {
    char *token = NULL;
    char *field = NULL;  
    int len = pop_2014.length;
    float per = 0.0;  
    int pop = 0; 
    float total = 0.0; 
    char copy[strlen(operation) + 1];

    strcpy(copy, operation); 
    strtok(copy, ":");
    field = strtok(NULL, "");   
    token = strtok(operation, ".");  
    if ((strcmp(token, "population:Education") == 0) || (strcmp(token, "percent:Education") == 0)) { 
         token = strtok(NULL, ".");
	 if (strcmp(token, "Bachelor's Degree or Higher") == 0) {
              for (int i = 0; i < len; i++) { 
		  if (check_present(i, use)) { 
                      per = edu_bach.array[i];
		      pop = pop_2014.array[i];
		      total += perc_of_pop(per, pop); 
		  } 	      
	      } 
         } else if (strcmp(token, "High School or Higher") == 0) {
             for (int i = 0; i < len; i++) {
     		 if (check_present(i, use)) { 
                     per = edu_hs.array[i];
		     pop = pop_2014.array[i];
	             total += perc_of_pop(per, pop); 
	         } 	     
	     } 
	 } else { 
             print = 2; 
	 } 
    } else if ((strcmp(token, "population:Ethnicities") == 0) || (strcmp(token, "percent:Ethnicities") == 0)) { 
         token = strtok(NULL, ".");
	 if (strcmp(token, "American Indian and Alaska Native Alone") == 0) {
              for (int i = 0; i < len; i++) { 
		  if (check_present(i, use)) { 
                      per = ethnic_native.array[i];
		      pop = pop_2014.array[i];
	              total += perc_of_pop(per, pop); 
	          } 	  
	      } 
         } else if (strcmp(token, "Asian Alone") == 0) {
              for (int i = 0; i < len; i++) { 
                  if (check_present(i, use)) { 
		      per = ethnic_asian.array[i];
		      pop = pop_2014.array[i];
	              total += perc_of_pop(per, pop); 
	          } 	      
	      } 
         } else if (strcmp(token, "Black Alone") == 0) {
               for (int i = 0; i < len; i++) { 
                  if (check_present(i, use)) { 
		      per = ethnic_black.array[i];
		      pop = pop_2014.array[i];
	              total += perc_of_pop(per, pop); 
	          } 	      
	      } 
         } else if (strcmp(token, "Hispanic or Latino") == 0) {
               for (int i = 0; i < len; i++) { 
                  if (check_present(i, use)) { 
                      per = ethnic_hsp.array[i];
		      pop = pop_2014.array[i];
	              total += perc_of_pop(per, pop); 
	          } 	      
	      } 
         } else if (strcmp(token, "Native Hawaiian and Other Pacific Islander Alone") == 0) {
               for (int i = 0; i < len; i++) { 
		  if (check_present(i, use)) { 
                      per = ethnic_islander.array[i];
		      pop = pop_2014.array[i];
		      total += perc_of_pop(per, pop); 
	          } 	      
	      } 
         } else if (strcmp(token, "Two or More Races") == 0) {
               for (int i = 0; i < len; i++) { 
                  if (check_present(i, use)) { 
		      per = ethnic_multi.array[i];
		      pop = pop_2014.array[i];
		      total += perc_of_pop(per, pop); 
	          } 	      
	      } 
         } else if (strcmp(token, "White Alone") == 0) {
               for (int i = 0; i < len; i++) { 
                  if (check_present(i, use)) { 
		      per = ethnic_white.array[i];
		      pop = pop_2014.array[i];
		      total += perc_of_pop(per, pop); 
	          } 	      
	      } 
         } else if (strcmp(token, "White Alone, not Hispanic or Latino") == 0) {
               for (int i = 0; i < len; i++) { 
                  if (check_present(i, use)) { 
		      per = ethnic_white_not_hisp.array[i];
		      pop = pop_2014.array[i];
		      total += perc_of_pop(per, pop); 
	          } 	      
	      } 
	 } else { 
             print = 2;
	 } 
    } else if ((strcmp(token, "population:Income") == 0) || (strcmp(token, "percent:Income") == 0)) { 
         token = strtok(NULL, ".");
	 if (strcmp(token, "Persons Below Poverty Level") == 0) {
              for (int i = 0; i < len; i++) {
		  if (check_present(i, use)) {  
                      per = inc_poverty.array[i];
		      pop = pop_2014.array[i];
		      total += perc_of_pop(per, pop); 	  
		  } 
	      } 
	 } else { 
	     print = 2; 
	 }  
    } else { 
	print = 0; 
        fprintf(stderr, "ERROR: field prefix passed is not viable on line %i\n", line); 
    } 
   if (print == 1) {
       fprintf(stdout, "2014 %s population: %f\n", field, total);
   } else if (print == 2) { 
       fprintf(stderr, "ERROR: field passed is not viable on line %i\n", line); 
   } 

   return total;  
}

void percent_field(char *operation, int line, int_array_list pop_2014, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, float_array_list inc_poverty, int print, int_array_list use) {
    char *field = NULL; 
    char copy[strlen(operation) + 1]; 
    int total = 0; 
    float subtotal = 0.0; 
    float perc = 0.0; 

    strcpy(copy, operation); 
    strtok(copy, ":"); 
    field = strtok(NULL, ""); 
    total = population_total(pop_2014, print, use);
    subtotal = population_field(operation, line, pop_2014, edu_bach, edu_hs, ethnic_native, ethnic_asian, ethnic_black, ethnic_hsp, ethnic_islander, ethnic_multi, ethnic_white, ethnic_white_not_hisp, inc_poverty, print, use);  
    perc = subtotal / total; 
    fprintf(stdout, "2014 %s percentage: %f\n", field, perc); 
}

int_array_list filter_state(char *operation, str_array_list state, int_array_list use) { 
     int_array_list keep = int_array_list_new();  
     int len = state.length; 
     int remaining = 0; 
     char *abbrev = NULL; 

     strtok(operation, ":"); 
     abbrev = strtok(NULL, ""); 
     for (int i = 0; i < len; i++) {
	 if (check_present(i, use)) { 
             if (strcmp(state.array[i], abbrev) == 0) { 
                 keep = int_array_list_add_to_end(keep, i);  
             }
	 }  
     } 

     remaining = keep.length; 
     fprintf(stdout, "Filter: state == %s (%i entries)\n", abbrev, remaining); 
     return keep;  
} 

int_array_list general_filter(char *operation, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white, float_array_list ethnic_white_not_hisp, int_array_list inc_median, int_array_list inc_capita, float_array_list inc_poverty, int_array_list pop_2014, int_array_list use, int line) { 
    int_array_list keep = int_array_list_new(); 
    char *token = NULL;
    char *next = NULL;
    char *field = NULL; 
    char *comparison = NULL;  
    char *num = NULL;
    char *sign;  
    int len = pop_2014.length;  
    float value = 0.0; 
    int remaining = 0; 

    token = strtok(operation, "."); 
    next = strtok(NULL, ".");  
    char copy[strlen(next) + 1];
    strcpy(copy, next); 
    field = strtok(next, ":"); 
    strtok(copy, ":"); 
    comparison = strtok(NULL, "");  
    char copy2[strlen(comparison) + 1]; 
    strcpy(copy2, comparison); 
    strtok(copy2, ":"); 
    num = strtok(NULL, ""); 
    char copy3[strlen(comparison) + 1];
    strcpy(copy3, comparison);  
    sign = strtok(copy3, ":"); 
    if ((strcmp(token, "filter:Education") == 0)) {   
	 if (strcmp(field, "Bachelor's Degree or Higher") == 0) {
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (edu_bach.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (edu_bach.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "High School or Higher") == 0) {
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (edu_hs.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (edu_hs.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
	 } else { 
             fprintf(stderr, "ERROR: field not viable on line %i\n", line); 
	     return use; 
	 } 
    } else if ((strcmp(token, "filter:Ethnicities") == 0)) { 
	 if (strcmp(field, "American Indian and Alaska Native Alone") == 0) {
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_native.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_native.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "Asian Alone") == 0) {
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_asian.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_asian.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "Black Alone") == 0) {
              if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_black.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_black.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "Hispanic or Latino") == 0) {
              if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_hsp.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_hsp.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "Native Hawaiian and Other Pacific Islander Alone") == 0) {
              if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_islander.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_islander.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "Two or More Races") == 0) {
              if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_multi.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_multi.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "White Alone") == 0) {
              if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_white.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_white.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "White Alone, not Hispanic or Latino") == 0) {
              if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_white_not_hisp.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (ethnic_white_not_hisp.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
	 } else { 
             fprintf(stderr, "ERROR: field not viable on line %i\n", line); 
	     return use; 
	 } 
    } else if ((strcmp(token, "filter:Income") == 0)) { 
         if (strcmp(field, "Median Household Income") == 0) { 
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (inc_median.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (inc_median.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else if (strcmp(field, "Per Capita Income") == 0) { 
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (inc_capita.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (inc_capita.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line);
		 return use; 
	     }  
         } else if (strcmp(field, "Persons Below Poverty Level") == 0) {
             if (strstr(comparison, "le")) { 
	         if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (inc_poverty.array[i] <= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 } 
             } else if (strstr(comparison, "ge")) { 
                  if ((value = is_num(num))) {  
		     for (int i = 0; i < len; i++) { 
		         if (check_present(i, use)) { 
                              if (inc_poverty.array[i] >= value) { 
                                  keep = int_array_list_add_to_end(keep, i); 
			      } 
	                 } 	      
	             }
		 }
	     } else { 
                 fprintf(stderr, "ERROR: comparison not supported on line %i\n", line); 
		 return use; 
	     }  
         } else { 
             fprintf(stderr, "ERROR: field not viable on line %i\n", line);
	     return use; 
	 }  
    } else {
        fprintf(stderr, "ERROR: field prefix passed is not viable on line %i\n", line); 
	return use;
    }  

    remaining = keep.length; 
    fprintf(stdout, "Filter: %s %s %f (%i entries)\n", field, sign, value, remaining); 
    return keep;     
} 

void display(int_array_list use, str_array_list county, str_array_list state, float_array_list edu_bach, float_array_list edu_hs, float_array_list ethnic_native, float_array_list ethnic_asian, float_array_list ethnic_black, float_array_list ethnic_hsp, float_array_list ethnic_islander, float_array_list ethnic_multi, float_array_list ethnic_white,float_array_list ethnic_white_not_hisp, int_array_list inc_median, int_array_list inc_capita, float_array_list inc_poverty, int_array_list pop_2014) {
    int len = county.length; 
    char *p = "%"; 

    for (int i = 0; i < len; i++) { 
        if (check_present(i, use)) { 
            fprintf(stdout, "%s, %s\n", county.array[i], state.array[i]); 
	    fprintf(stdout, "\tPopulation: %i\n", pop_2014.array[i]);
	    fprintf(stdout, "\tEducation\n"); 
	    fprintf(stdout, "\t\t>= High School: %f%s\n", edu_hs.array[i], p);  
	    fprintf(stdout, "\t\t>= Bachelor's: %f%s\n", edu_bach.array[i], p);
	    fprintf(stdout, "\tEthnicity Percentages\n"); 
	    fprintf(stdout, "\t\tAmerican Indian and Alaska Native: %f%s\n", ethnic_native.array[i], p); 
	    fprintf(stdout, "\t\tAsian Alone: %f%s\n", ethnic_asian.array[i], p); 
	    fprintf(stdout, "\t\tBlack Alone: %f%s\n", ethnic_black.array[i], p); 
	    fprintf(stdout, "\t\tHispanic or Latino: %f%s\n", ethnic_hsp.array[i], p); 
	    fprintf(stdout, "\t\tNative Hawaiian and Other Pacific Islander Alone: %f%s\n", ethnic_islander.array[i], p); 
	    fprintf(stdout, "\t\tTwo or More Races: %f%s\n", ethnic_multi.array[i], p); 
	    fprintf(stdout, "\t\tWhite Alone: %f%s\n", ethnic_white.array[i], p); 
	    fprintf(stdout, "\t\tWhite Alone, not Hispanic or Latino: %f%s\n", ethnic_white_not_hisp.array[i], p); 
	    fprintf(stdout, "\tIncome\n"); 
	    fprintf(stdout, "\t\tMedian Household: %i\n", inc_median.array[i]); 
	    fprintf(stdout, "\t\tPer Capita: %i\n", inc_capita.array[i]); 
	    fprintf(stdout, "\t\tBelow Poverty Level: %f%s\n", inc_poverty.array[i], p); 
	} 
    } 	    

} 
