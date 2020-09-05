#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "utils.h"

#include "generators.h"


void generate_string_for_argument(char** str, const size_t max_str_len);
void get_random_arg_value(char** value, const size_t max_str_len);


size_t get_random_in_range(const size_t low, const size_t high){
    if(low>high){
        printf("Incorrect range for random number \n");
        exit(1);
    }
    double res = (double)low + 1.0*rand()/RAND_MAX*((double)(high - low));
    return (size_t)(res);
}

void generate_random_string(char** str, const size_t seed, const size_t max_str_len){
    srand((uint)seed);
    size_t str_len = get_random_in_range(0, max_str_len);
    char* tmp_str = calloc(str_len+1, sizeof(char));
    for(size_t i=0; i<str_len; i++){
        tmp_str[i] = (char)(get_random_in_range(32, 126));
    }
    tmp_str[str_len] = '\0';
    *str = tmp_str;
}

int generate_random_int(){
    int rand_val = (int)get_random_in_range(0, 1000);
    int variants[5] = {INT_MIN, -1*rand_val, 0, rand_val, INT_MAX};
    int pick = rand()%5;
    return variants[pick];
}

double generate_random_double(){
    double rand_double = 1.0*rand()/rand();
    double variants[5] = {-1e100, -1*rand_double, 0, rand_double, 1e100};
    int pick = rand()%5;
    return variants[pick];
}

void generate_string_for_argument(char** str, const size_t max_str_len){
    const char characters[] = {'.', ',', ':', ';', '/', '\\', '=', '-', '_',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            'a','b','c','d','e','f','g','h','i','j','k','l','m',
                             'n','o','p','q','r','s','t','u','v','w','x','y','z'};
    const size_t char_count = 45;
    size_t str_len = get_random_in_range(0, max_str_len);
    char* tmp_str = calloc(str_len+1, sizeof(char));
    for(size_t i=0; i<str_len; i++){
        size_t idx = (size_t)rand()%(char_count+1);
        tmp_str[i] = characters[idx];
    }
    tmp_str[str_len] = '\0';
    *str = tmp_str;

}

void get_random_arg_value(char** value, const size_t max_str_len){
    switch (rand()%3) {
    case 0:
        //write int value
        *value = calloc(25, sizeof(char));
        sprintf(*value, "%i", generate_random_int());
        return;
    case 1:
        //write double value
        *value = calloc(25, sizeof(char));
        sprintf(*value, "%.4e", generate_random_double());
        return;
    case 2:
        //write string value
        generate_string_for_argument(value, max_str_len);
        return;
    }
    printf("Case in swithc was not found\n");
    exit(1);
}

size_t generate_cmd_arguments(char*** gen_argv, const size_t seed, const char* arg_names[], const size_t arg_name_count, const size_t max_str_len){
    srand((uint)seed);
    int* range_arr;
    range(&range_arr, 0, (int)arg_name_count, 1);
    shuffle(&range_arr, arg_name_count);
    size_t current_arg_count = get_random_in_range(0, arg_name_count-1);
    size_t gen_argc = 1 + 2*current_arg_count;
    char** tmp_argv = calloc((size_t)gen_argc, sizeof(char*));
    tmp_argv[0] = calloc(25, sizeof(char));
    strcpy(tmp_argv[0], "program_name");
    for(size_t i=0; i<current_arg_count; i++){
        size_t idx = (size_t)range_arr[i];
        tmp_argv[1+2*i] = calloc(strlen(arg_names[idx])+1, sizeof(char));
        strcpy(tmp_argv[1+2*i], arg_names[idx]);
    }
    for(size_t i=0; i<current_arg_count; i++){
        get_random_arg_value(&tmp_argv[2+2*i], max_str_len);
    }
    *gen_argv = tmp_argv;
    free(range_arr);
    return gen_argc;
}

