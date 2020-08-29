#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argument_handler.h"

void shuffle(int** arr, const size_t arr_len);
void swap(int* lhs, int* rhs);
size_t range(int** range_arr, const int low, const int high, const int step);
void print_arguments(const char** args, const size_t count);
void free_arguments(char** args, const size_t count);
void free_options(Options* opt);



#endif
