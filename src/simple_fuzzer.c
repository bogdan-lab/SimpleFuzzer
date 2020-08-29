#include <time.h>
#include <stdint.h>
#include <limits.h>
#include "argument_handler.h"

void generate_random_string(char** str, const size_t str_len);
int generate_random_int();
double generate_random_double();
void get_random_arg_value(char** value, const size_t max_str_len);
size_t get_random_in_range(const size_t low, const size_t high);
size_t generate_random_arguments(char*** args, const size_t max_str_len, const size_t max_arg_num);
size_t generate_cmd_arguments(char*** gen_argv, const Options* opt);
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
        //size_t arg_num = generate_random_arguments(&args, opt.max_str_len, opt.max_arg_num);
        size_t arg_num = generate_cmd_arguments(&args, &opt);
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

size_t generate_random_arguments(char*** args, const size_t max_str_len, const size_t max_arg_num){
    size_t arg_num = get_random_in_range(1, max_arg_num);
    char** tmp_args = calloc(arg_num, sizeof(char*));
    for(size_t i=0; i<arg_num; i++){
        generate_random_string(&tmp_args[i], max_str_len);
    }
    *args = tmp_args;
    return arg_num;
}


size_t generate_cmd_arguments(char*** gen_argv, const Options* opt){
    size_t gen_argc = 1 + 2*opt->arg_name_count;
    char** tmp_argv = calloc((size_t)gen_argc, sizeof(char*));
    tmp_argv[0] = calloc(25, sizeof(char));
    strcpy(tmp_argv[0], "program_name");
    for(size_t i=0; i<opt->arg_name_count; i++){
        tmp_argv[1+2*i] = calloc(strlen(opt->arg_names[i]), sizeof(char));
        strcpy(tmp_argv[1+2*i], opt->arg_names[i]);
    }
    for(size_t i=0; i<opt->arg_name_count; i++){
        get_random_arg_value(&tmp_argv[2+2*i], opt->max_str_len);
    }
    *gen_argv = tmp_argv;
    return gen_argc;
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
