#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "parse.h"
#include "shell.h"

#define CMD_SIZE 256

int main()
{
    int proc; 
    int status; 
    char buffer[CMD_SIZE]; 
    char *cmd = NULL; 

    while(1)
    {
        if(!cmd)    // no command in buffer
        {
            printf("\n%s ", get_prompt());  

            fgets(buffer, CMD_SIZE, stdin);  
            if(strchr(buffer, '\n'))
                *strchr(buffer, '\n') = 0; 

            cmd = buffer; 
        }

        // save next command for later
        char * next = cmd; 
        cmd = strsep(&next, ";"); 

        // execute piped commands
        int save_pipe = exec_pipe(&cmd); 

        // setup redirection stream
        int save_out = redirect_out(cmd); 
        int save_in = redirect_in(cmd); 

        // parse
        char ** argsv = parse_args(cmd);
        
        // execute
        if(!strcmp(argsv[0], "exit"))
            return 0; 
        else 
        {
            proc = fork(); 
            if(proc)
                // parent
                wait(&status); 
            else 
            {
                // child
                execvp(argsv[0], argsv); 
                printf("tmjsh:\t%s:\t%s\n", argsv[0], "command not found"); 
                return 0; 
            }
        }
        free(argsv); 

        // undo redirection stream
        dup2(save_out, STDOUT_FILENO); 
        dup2(save_in, STDIN_FILENO); 

        // undo piping
        dup2(save_pipe, STDIN_FILENO); 

        // handle next command 
        cmd = next; 
    }
    return 0; 
}
