#include "utils.h"

size_t range(int** range_arr, const int low, const int high, const int step){
    if(low>high){
        printf("Incorrect range!\n");
        exit(1);
    }
    size_t count = (size_t)((high-low)/step);
    int* tmp_range_arr = calloc(count, sizeof(int));
    for(size_t i=0; i<count; i++){
        tmp_range_arr[i] = low + (int)i*step;
    }
    *range_arr = tmp_range_arr;
    return count;
}

void swap(int* lhs, int* rhs){
    int tmp = *rhs;
    *rhs = *lhs;
    *lhs = tmp;
}

void shuffle(int** arr, const size_t arr_len){
    for(size_t i=0; i<arr_len; i++){
        size_t j = i + (size_t)rand()%(arr_len-i);
        swap(&((*arr)[i]), &((*arr)[j]));
    }
}

void free_string_array(char** args, const size_t count){
    for(size_t i=0; i<count; i++){
        free(args[i]);
    }
    free(args);
}


size_t download_database(char*** new_db, const char* input_file){
    FILE* input;
    input = fopen(input_file, "r");
    if(input){
        size_t full_size = 1024;
        char** input_data = calloc(full_size, sizeof(char*));
        size_t idx = 0;
        char buff[255];
        while(fscanf(input, "%s", buff)!=EOF){
            input_data[idx] = calloc(strlen(buff)+1, sizeof(char));
            strcpy(input_data[idx], buff);
            idx++;
            if(idx == full_size){
                full_size*=2;
                input_data = realloc(input_data, sizeof(char*)*full_size);
            }
        }
        input_data  = realloc(input_data, sizeof(char*)*idx);
        fclose(input);
        *new_db = input_data;
        return idx;
    }
    else{
        printf("Could not open file %s\n", input_file);
        exit(EXIT_FAILURE);
    }
}

void write_words_to_file(const char** words, const size_t word_num, const char* out_fname){
    FILE* output = fopen(out_fname, "w");
    if(output){
        fprintf(output, "%zu\n", word_num);
        for(size_t i=0; i<word_num; i++){
            fprintf(output, "%s\n", words[i]);
        }
        fclose(output);
    }
    else{
        printf("Could not open file %s\n", out_fname);
        exit(EXIT_FAILURE);
    }
}

