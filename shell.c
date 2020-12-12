#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int num_args(char *str)
{
    if(!(*str)) return 0; 
    int s = 0; 
    ++str; 
    while(*str)
    {
        if(*str == ' ' && *(str-1) != ' ') ++s;
        ++str;
    }
    if(*(str-1) != ' ') ++s; 
    return s;
}

char **parse_args(char *argsc)
{
    int s = num_args(argsc);
    char ** argsv = (char **) malloc((s+1) * sizeof(char *));

    int i = 0;
    while(i < s)
    {
        argsv[i] = strsep(&argsc, " ");
        if(argsv[i][0]) ++i;
    }
    argsv[s] = NULL;
 
    return argsv;
}