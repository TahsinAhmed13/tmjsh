#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "shell.h"
#include "color.h"

int main()
{
    int f; 
    int status;
    char cwd[80]; 
    char cmd[256]; 
    char **argsv; 

    getcwd(cwd, sizeof(cwd)); 
    while(1) 
    {
        // TODO: allow users to set colors
        printf("%s%s\n", ANSI_GREEN, cwd); 
        printf("%s->%s ", ANSI_YELLOW, ANSI_RESET); 

        if(!fgets(cmd, sizeof(cmd), stdin)) 
            continue;
        char *line = strchr(cmd, '\n'); 
        if(line) *line = 0;

        argsv = parse_args(cmd);  
        if(!argsv[0])
            continue; 
        else if(!strcmp(argsv[0], "exit"))   
            break;                                                                                                                                                                         
        else if(!strcmp(argsv[0], "cd"))
        {
            if(argsv[1])    chdir(argsv[1]); 
            // TODO: find a better way to do this
            else            chdir(getenv("HOME")); 
            getcwd(cwd, sizeof(cwd)); 
        }
        else 
        {
            f = fork(); 
            if(f)   wait(&status); 
            else    
            {
                execvp(argsv[0], argsv); 
                printf("tmjsh:\t%d:\t%s\n", errno, strerror(errno));
                return 0;
            }
        }        

        free(argsv); 
        printf("\n"); 
    }
    
    return 0; 
}