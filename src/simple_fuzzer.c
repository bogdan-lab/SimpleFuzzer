#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char** argv){

    if(argc!=2){
        printf("INVALID ARGUMENTS\n");
        return EXIT_FAILURE;
    }
    srand((uint)(time(NULL)));
    size_t str_len = (size_t)(atoi(argv[1]));
    char* str = calloc(str_len, sizeof(char));
    for(size_t i=0; i<str_len; i++){
        str[i] = (char)(32+rand()%95);
    }
    printf("%s\n", str);
    free(str);
    return EXIT_SUCCESS;
}
