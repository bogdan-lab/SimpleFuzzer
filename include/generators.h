#ifndef GENERATORS_HEADER
#define GENERATORS_HEADER

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "argument_handler.h"
#include "utils.h"

void generate_random_string(char** str, const size_t str_len);
int generate_random_int();
double generate_random_double();
void get_random_arg_value(char** value, const size_t max_str_len);
size_t get_random_in_range(const size_t low, const size_t high);
size_t generate_cmd_arguments(char*** gen_argv, const Options* opt);



#endif
