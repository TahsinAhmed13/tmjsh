#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parse.h"

/* Removes leading whitespace on the string str */
char * trim_front(char *str)
{
    while(*str == ' ')
        ++str; 
    return str; 
}

/* Removes trailing whitespace on the string str */
char * trim_back(char *str)
{
    char *tmp = str; 
    tmp += strlen(str) - 1; 
    while(*tmp == ' ')
        --tmp; 
    *(tmp + 1) = 0; 
    return str; 
}

/* Removes both leading and trailing whitespace on
   the string str */
char * trim(char *str)
{
    return trim_back(trim_front(str)); 
}

/* Counts the number of times a whitespace appears in the string cmd */
int num_args(char *cmd)
{
    int args = 0; 
    while(*cmd)
    {
        if(*cmd == ' ') ++args; 
        ++cmd; 
    }
    return args + 1; 
}

/* Turns string cmd into an array of arguments */
char ** parse_args(char *cmd)
{
    cmd = trim(cmd); 
    int n = num_args(cmd); 
    char ** argsv = (char **) malloc(sizeof(char *) * (n + 1));  
    
    int i = 0; 
    while(cmd)
    {
        argsv[i] = strsep(&cmd, " "); 
        ++i; 
    }
    argsv[i] = NULL; 

    return argsv; 
}
