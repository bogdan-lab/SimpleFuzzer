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

    return EXIT_SUCCESS;
}

