#ifndef ARGUMENT_HANDLER
#define ARGUMENT_HANDLER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct{
    char* input_file;
    char* output_file;
    size_t word_num;
    size_t seed;
}Options;


int is_argument(const int argc, const char** argv, const char* test_arg);
size_t read_default_uint_parameter(const int argc, const char** argv, const char* par_name, const size_t def_val);
void handle_parameters(const int argc, const char ** argv, Options* opt);
void read_default_string_parameter(char** str, const int argc, const char** argv, const char* par_name, const char* def_val);
void init_options(Options* opt);
void free_options(Options* opt);

#endif
