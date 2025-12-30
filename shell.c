#include <stdlib.h>
void lsh_loop(void){
    char* line;
    char** args;
    int status ; 

    do{
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);


    }while (status);
}

int main(int argc, char** argv ){
    
    //load config files

    //run the loop
    lsh_loop();
    
    //perform any shutdown cleanup
    return EXIT_SUCCESS ;// fancy way of saying return 0
}