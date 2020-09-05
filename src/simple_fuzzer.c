#include "argument_handler.h"
#include "words.h"
#include "utils.h"

int main(int argc, char** argv){

    Options opt;
    init_options(&opt);
    handle_parameters(argc, (const char**)argv, &opt);
    generate_random_file(opt.seed, opt.word_num, opt.input_file, opt.output_file);
    free_options(&opt);

    return EXIT_SUCCESS;
}

