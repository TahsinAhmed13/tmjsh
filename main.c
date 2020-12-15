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

        // setup redirection stream
        int save = redirect(cmd); 

        // parse and execute 
        char ** argsv = parse_args(cmd); 
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
        reset(save); 

        // handle next command 
        cmd = next; 
    }
    return 0; 
}
