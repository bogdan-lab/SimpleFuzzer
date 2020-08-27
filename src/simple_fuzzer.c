#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct{
    size_t max_time;
    size_t max_str_len;
}Options;

void handle_parameters(const int argc, const char ** argv, Options* opt);
int is_argument(const int argc, const char** argv, const char* test_arg);
size_t read_default_uint_parameter(const int argc, const char** argv, const char* par_name, const size_t def_val);
void handle_parameters(const int argc, const char ** argv, Options* opt);
void generate_random_string(char** str, size_t str_len);


int main(int argc, char** argv){
    time_t t_start, t_current;
    time(&t_start);
    Options opt;
    handle_parameters(argc, (const char**)argv, &opt);
    srand((uint)(time(NULL)));
    time(&t_current);
    while(difftime(t_current,t_start)<opt.max_time){
        char* str;
        generate_random_string(&str, opt.max_str_len);
        printf("%s\n", str);
        free(str);
        time(&t_current);
    }
    return EXIT_SUCCESS;
}


int is_argument(const int argc, const char** argv, const char* test_arg){
    for(int i=0; i<argc; i++){
        if(!strcmp(argv[i], test_arg)){
            return i;
        }
    }
    return -1;
}


size_t read_default_uint_parameter(const int argc, const char** argv, const char* par_name, const size_t def_val){
    size_t par = def_val;
    int idx = is_argument(argc, argv, par_name);
    if(idx<0){
        fprintf(stderr, "Parameter %s was not set --> will use default value %zu\n", par_name, def_val);
        return par;
    }
    if(argc<=idx){
        fprintf(stderr, "Please specify value of parameter %s\n", par_name);
        exit(EXIT_FAILURE);
    }
    int tmp = atoi(argv[idx+1]);
    if(tmp<0){
        fprintf(stderr, "Parameter %s should have positive value\n", par_name);
        exit(EXIT_FAILURE);
    }
    return (size_t)tmp;
}

void handle_parameters(const int argc, const char ** argv, Options* opt){
    opt->max_time = read_default_uint_parameter(argc, argv, "-max_time", 60);
    opt->max_str_len = read_default_uint_parameter(argc, argv, "-max_str_len", 100);
}


void generate_random_string(char** str, size_t str_len){
    char* tmp_str = calloc(str_len, sizeof(char));
    for(size_t i=0; i<str_len; i++){
        tmp_str[i] = (char)(32+rand()%95);
    }
    *str = tmp_str;
}
