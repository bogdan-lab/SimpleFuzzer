#include "argument_handler.h"


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
    opt->max_arg_num = read_default_uint_parameter(argc, argv, "-max_arg_num", 1);
}


