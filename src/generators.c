#include "generators.h"

size_t get_random_in_range(const size_t low, const size_t high){
    if(low>high){
        printf("Incorrect range for random number \n");
        exit(1);
    }
    double res = (double)low + 1.0*rand()/RAND_MAX*((double)(high - low));
    return (size_t)(res);
}

void generate_random_string(char** str, const size_t max_str_len){
    size_t str_len = get_random_in_range(0, max_str_len);
    char* tmp_str = calloc(str_len+1, sizeof(char));
    for(size_t i=0; i<str_len; i++){
        tmp_str[i] = (char)(get_random_in_range(32, 127));
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
        generate_random_string(value, max_str_len);
        return;
    }
    printf("Case in swithc was not found\n");
    exit(1);
}

size_t generate_cmd_arguments(char*** gen_argv, const Options* opt){
    int* range_arr;
    range(&range_arr, 0, (int)opt->arg_name_count, 1);
    shuffle(&range_arr, opt->arg_name_count);
    size_t current_arg_count = get_random_in_range(0, opt->arg_name_count);
    size_t gen_argc = 1 + 2*current_arg_count;
    char** tmp_argv = calloc((size_t)gen_argc, sizeof(char*));
    tmp_argv[0] = calloc(25, sizeof(char));
    strcpy(tmp_argv[0], "program_name");
    for(size_t i=0; i<current_arg_count; i++){
        size_t idx = (size_t)range_arr[i];
        tmp_argv[1+2*i] = calloc(strlen(opt->arg_names[idx])+1, sizeof(char));
        strcpy(tmp_argv[1+2*i], opt->arg_names[idx]);
    }
    for(size_t i=0; i<current_arg_count; i++){
        get_random_arg_value(&tmp_argv[2+2*i], opt->max_str_len);
    }
    *gen_argv = tmp_argv;
    free(range_arr);
    return gen_argc;
}


void generate_words_for_file(char*** words, const size_t word_num, const char** db, const size_t db_count){
    char** tmp_words = calloc(word_num, sizeof(char*));
    for(size_t i=0; i<word_num; i++){
        size_t idx = (size_t)((double)rand()/RAND_MAX * (double)(db_count-1));
        tmp_words[i] = calloc(strlen(db[idx])+1, sizeof(char));
        strcpy(tmp_words[i], db[idx]);
    }
    *words = tmp_words;
}

void generate_random_file(const Options *opt){
    srand((uint)opt->seed);
    char** words = calloc(opt->word_num, sizeof(char*));
    if(strlen(opt->input_file)==0){
        generate_words_for_file(&words, opt->word_num, word_db, word_db_count);
    }
    else{
        char** new_db;
        size_t new_db_count = download_database(&new_db, opt->input_file);
        generate_words_for_file(&words, opt->word_num, (const char**)new_db, new_db_count);
        free_string_array(new_db, opt->word_num);
    }
    write_words_to_file((const char**)words, opt->word_num, opt->output_file);
    free_string_array(words, opt->word_num);
}

