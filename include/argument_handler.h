#ifndef ARGUMENT_HANDLER
#define ARGUMENT_HANDLER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    size_t max_time;
    size_t max_str_len;
    size_t max_arg_num;
}Options;


void handle_parameters(const int argc, const char ** argv, Options* opt);
int is_argument(const int argc, const char** argv, const char* test_arg);
size_t read_default_uint_parameter(const int argc, const char** argv, const char* par_name, const size_t def_val);
void handle_parameters(const int argc, const char ** argv, Options* opt);


#endif
