#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int lsh_cd(char** args);
int lsh_help(char** args);
int lsh_exit(char** args);

char* builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char**) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char** args){
    if (args[1]==NULL){
       fprintf(stderr, "lsh: expected argument to \"cd\"\n"); 
    }else{
        int result = chdir(args[1]);

        if (result !=0){
            perrr("lsh");
        }
    }
    return 1;

}

int lsh_help(char** args){
    int i;
    printf("Selith Rubasingha's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i=0; i< lsh_num_builtins();i++){
        printf(" %s\n",builtin_str);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
  return 0;
}


int lsh_launch(char **args){
    /*
    in UNIX systems when the computer starts , the main process that starts is called Init.
    Init runs until the computer turns off . when we need to run another function init duplicates
    itself and the copy turns itself into a different process , this copy is called the child.
    and while the child is doing processes the parent init has to wwait
    */
    pid_t pid , wpid ;//process id type
    int status;

    pid = fork();

    if (pid ==0 ){//pid = 0 means it's the child process
        if (execvp(args[0],args) == -1){
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }else if (pid<0){ //pid is negative when there is a error
        perror("lsh");
    }else{//pid>0 means it's the parent process

        do{
            //wait for the child to chagnge the state(pause , finish , crash)
            wpid = waitpid(pid,&status,WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
        /*
        keep the parent paused until the child is completely dead or finsihed
        */
    }

    return 1;
}


#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char** lsh_split_line(char* line){
    int bufsize = LSH_TOK_BUFSIZE , position = 0 ;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line , LSH_TOK_DELIM);

  while (token != NULL){
    tokens[position] = token ;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL , LSH_TOK_DELIM);
  }

  tokens[position] = NULL;
  return tokens;

  

}

#define LSH_RL_BUFSIZE 1024
char* lsh_read_line(void){
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char)*bufsize);
    int c ;
    
    if (!buffer){
        fprintf(stderr, "lsh: allocation error\n");
        exit( EXIT_FAILURE);
    }

    while (1){
        c = getchar();

        if (c==EOF || c=='\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }

        buffer[position] = c;

        position++;


        if (position>=bufsize){
            bufsize+=LSH_RL_BUFSIZE;

            buffer = realloc(buffer,bufsize);

            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
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