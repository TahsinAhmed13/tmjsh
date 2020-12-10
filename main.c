#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "shell.h"

int main()
{
    int f; 
    int status;
    char cmd[256]; 
    char **argsv; 

    while(1) 
    {
        printf("$ "); 

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
            if(argsv[1])    chdir(argsv[1]); 
            else            chdir("/"); 
        else 
        {
            f = fork(); 
            if(f)   wait(&status); 
            else    
            {
                execvp(argsv[0], argsv); 
                printf("%s\n", strerror(errno));
                return 0;
            }
        }        

        free(argsv); 
    }
    
    return 0; 
}