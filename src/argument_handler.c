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
    if(idx<0){
        fprintf(stderr, "Parameter %s was not set --> will use default value '%s'\n", par_name, def_val);
        char* tmp_str = calloc(strlen(def_val)+1, sizeof(char));
        strcpy(tmp_str, def_val);
        *str = tmp_str;
        return;
    }
    if(argc<=idx+1){
        fprintf(stderr, "Please specify value of parameter %s\n", par_name);
        exit(EXIT_FAILURE);
    }
    char* tmp_str = calloc(strlen(argv[idx+1])+1, sizeof(char));
    strcpy(tmp_str, argv[idx+1]);
    *str = tmp_str;
    return;
}

void handle_parameters(const int argc, const char ** argv, Options* opt){
    read_default_string_parameter(&opt->input_file, argc, argv, "-input_file", "");
    read_default_string_parameter(&opt->output_file, argc, argv, "-output_file", "generated_file");
    opt->word_num = read_default_uint_parameter(argc, argv, "-word_num", 100);
    opt->seed = read_default_uint_parameter(argc, argv, "-seed", (size_t)time(NULL));
}


void init_options(Options* opt){
    opt->word_num = 0;
    opt->input_file = NULL;
    opt->output_file = NULL;
    opt->seed = 0;
}


void free_options(Options* opt){
    free(opt->input_file);
    free(opt->output_file);
}


