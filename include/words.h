#ifndef WORDS_HEADER
#define WORDS_HEADER

#include <stdlib.h>

/*Word data base parameters*/
extern const size_t word_db_count;
extern const char* word_db[];

/*will fill output_file with random sequence of words in input_file.
 * If input_file is empty string it will use local word_db for generating random words*/
void generate_random_file(const size_t seed, const size_t word_num, const char* input_file, const char* output_file);

/*Function generates array of words into 'words' randomly selecting word_num from data base array 'db'*/
void generate_words_for_file(char*** words, const size_t word_num, const char** db, const size_t db_count);

#endif
