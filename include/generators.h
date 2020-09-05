#ifndef GENERATORS_HEADER
#define GENERATORS_HEADER

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "argument_handler.h"
#include "utils.h"
#include "words.h"

void generate_random_string(char** str, const size_t seed, const size_t str_len);
int generate_random_int();
double generate_random_double();
void get_random_arg_value(char** value, const size_t max_str_len);
size_t get_random_in_range(const size_t low, const size_t high);
size_t generate_cmd_arguments(char*** gen_argv, const size_t seed, const char* arg_names[], const size_t arg_name_count, const size_t max_str_len);
void generate_random_file(const Options* opt);
void generate_string_for_argument(char** str, const size_t max_str_len);

#endif
