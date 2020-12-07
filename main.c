#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char ** parse_args(char *);

int main()
{

    int f; 
    int status;
    while(1) 
    {
        printf("$ "); 
        
        f = fork(); 
        if(f) 
            wait(&status); 
        else
        {

        }
        
    }
}

char ** parse_args(char *argsc)
{
    char ** argsv = (char **) malloc(sizeof(char *));

    int i = 0;
    while(argsc)
    {
        argsv[i] = strsep(argsc, " ");
        ++i;
    }
 
    return argsv;
}