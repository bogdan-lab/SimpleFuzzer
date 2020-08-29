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
    if(argc<=idx+1){
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

void read_default_string_parameter(char** str, const int argc, const char** argv, const char* par_name, const char* def_val){
    int idx = is_argument(argc, argv, "-arg_names");
    char* tmp_str = calloc(strlen(def_val), sizeof(char));
    strcpy(tmp_str, def_val);
    if(idx<0){
        fprintf(stderr, "Parameter %s was not set --> will use default value '%s'\n", par_name, def_val);
        *str = tmp_str;
        return;
    }
     if(argc<=idx+1){
        fprintf(stderr, "Please specify value of parameter %s\n", par_name);
        exit(EXIT_FAILURE);
    }
    tmp_str = (char*)realloc(tmp_str, sizeof(char)*strlen(argv[idx+1]));
    strcpy(tmp_str, argv[idx+1]);
    *str = tmp_str;
    return;
}

void handle_parameters(const int argc, const char ** argv, Options* opt){
    opt->max_time = read_default_uint_parameter(argc, argv, "-max_time", 60);
    opt->max_str_len = read_default_uint_parameter(argc, argv, "-max_str_len", 100);
    opt->max_arg_num = read_default_uint_parameter(argc, argv, "-max_arg_num", 1);
    char* args_str;
    read_default_string_parameter(&args_str, argc, argv, "-arg_names", "");
    if(strlen(args_str)==0){
        opt->arg_name_count=0;
    }
    else {
        opt->arg_names = calloc(strlen(args_str), sizeof(char*));
        size_t idx=0;
        char* pch;
        pch = strtok(args_str, " ");
        while(pch!=NULL){
            opt->arg_names[idx] = calloc(strlen(pch), sizeof(char));
            strcpy(opt->arg_names[idx], pch);
            pch = strtok(NULL, " ");
            idx++;
        }
        opt->arg_name_count = idx;
        opt->arg_names = realloc(opt->arg_names, sizeof(char*)*opt->arg_name_count);
    }
}


