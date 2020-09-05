#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdlib.h>


void* allocate(const size_t num, const size_t size);
void shuffle(int** arr, const size_t arr_len);
void swap(int* lhs, int* rhs);
size_t range(int** range_arr, const int low, const int high, const int step);
void free_string_array(char** args, const size_t count);
void write_words_to_file(const char** words, const size_t word_num, const char* out_fname);
size_t download_database(char*** new_db, const char* input_file);

#endif
