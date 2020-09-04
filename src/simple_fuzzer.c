#include <time.h>

#include "argument_handler.h"
#include "generators.h"
#include "utils.h"

int main(int argc, char** argv){

    Options opt;
    init_options(&opt);
    handle_parameters(argc, (const char**)argv, &opt);
    generate_random_file(&opt);
    free_options(&opt);
    /*
    time_t t_start, t_current;
    time(&t_start);
    Options opt;
    handle_parameters(argc, (const char**)argv, &opt);
    srand((uint)(time(NULL)));
    time(&t_current);
    while(difftime(t_current,t_start)<opt.max_time){
        char** args;
        size_t arg_num = generate_cmd_arguments(&args, &opt);
        print_arguments((const char**)args, arg_num);
        free_string_array(args, arg_num);
        time(&t_current);
    }
    free_options(&opt);
    */
    return EXIT_SUCCESS;
}

