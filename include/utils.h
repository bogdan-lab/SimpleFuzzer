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
void free_string_array(char** args, const size_t count);
void write_words_to_file(const char** words, const size_t word_num, const char* out_fname);
size_t download_database(char*** new_db, const char* input_file);

#endif
