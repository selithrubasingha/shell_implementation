#include <stdlib.h>


int main(int argc, char** argv ){
    
    //load config files

    //run the loop
    lsh_loop();
    
    //perform any shutdown cleanup
    return EXIT_SUCCESS ;// fancy way of saying return 0
}