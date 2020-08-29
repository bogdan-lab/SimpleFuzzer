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

void free_arguments(char** args, const size_t count){
    for(size_t i=0; i<count; i++){
        free(args[i]);
    }
    free(args);
}


void free_options(Options* opt){
    for(size_t i=0; i<opt->arg_name_count; i++){
        free(opt->arg_names[i]);
    }
    free(opt->arg_names);
}


void print_arguments(const char** args, const size_t count){
    for(size_t i=0; i<count; i++){
        printf("%s ", args[i]);
    }
    printf("\n");
}
