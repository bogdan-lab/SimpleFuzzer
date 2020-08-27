#include <time.h>

#include "argument_handler.h"

void generate_random_string(char** str, const size_t str_len);
size_t get_random_in_range(const size_t low, const size_t high);
size_t generate_random_arguments(char*** args, const size_t max_str_len, const size_t max_arg_num);
void print_arguments(const char** args, const size_t count);
void free_arguments(char** args, const size_t count);


int main(int argc, char** argv){
    time_t t_start, t_current;
    time(&t_start);
    Options opt;
    handle_parameters(argc, (const char**)argv, &opt);
    srand((uint)(time(NULL)));
    time(&t_current);
    while(difftime(t_current,t_start)<opt.max_time){
        char** args;
        size_t arg_num = generate_random_arguments(&args, opt.max_str_len, opt.max_arg_num);
        print_arguments((const char**)args, arg_num);
        free_arguments(args, arg_num);
        time(&t_current);
    }
    return EXIT_SUCCESS;
}

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
    char* tmp_str = calloc(str_len, sizeof(char));
    for(size_t i=0; i<str_len; i++){
        tmp_str[i] = (char)(get_random_in_range(32, 127));
    }
    *str = tmp_str;
}

size_t generate_random_arguments(char*** args, const size_t max_str_len, const size_t max_arg_num){
    size_t arg_num = get_random_in_range(1, max_arg_num);
    char** tmp_args = calloc(arg_num, sizeof(char*));
    for(size_t i=0; i<arg_num; i++){
        generate_random_string(&tmp_args[i], max_str_len);
    }
    *args = tmp_args;
    return arg_num;
}

void free_arguments(char** args, const size_t count){
    for(size_t i=0; i<count; i++){
        free(args[i]);
    }
    free(args);
}

void print_arguments(const char** args, const size_t count){
    for(size_t i=0; i<count; i++){
        printf("%s ", args[i]);
    }
    printf("\n");
}
