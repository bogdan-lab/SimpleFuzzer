#ifndef GENERATORS_HEADER
#define GENERATORS_HEADER

#include <stdlib.h>

/*generates random string in str with random length from 0 to max_str_le*/
void generate_random_string(char** str, const size_t seed, const size_t max_str_len);

/*generate random int number. applied stupid solution in order to increase probability
 * of generating 0 and huge positive and negative numbers*/
int generate_random_int();

/*Similarly to 'generate_random_int' generates double with increased probability to generate
 * ridiculously large positive and negative number and 0*/
double generate_random_double();

/*generate random size_t value in given range [lhs, rhs]*/
size_t get_random_in_range(const size_t low, const size_t high);

/*Generate array of cmd line arguments according to the given arg_names. Number of arguments is randomly changed after each run.
 * Argument values are also randomly chosen between int double and string. When string is added to the argument its length is
 * randomly chosen between 0 and max_str_len*/
size_t generate_cmd_arguments(char*** gen_argv, const size_t seed, const char* arg_names[], const size_t arg_name_count, const size_t max_str_len);

#endif
