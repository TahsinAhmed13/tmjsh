#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int strspace(char *str)
{
    if(!(*str)) return 0; 
    int s = 0; 
    ++str; 
    while(*str)
    {
        if(*str == ' ' && *(str-1) != ' ') ++s;
        ++str;
    }
    if(*(str-1) == ' ') --s; 
    return s + 1;
}

char **parse_args(char *argsc)
{
    int s = strspace(argsc);
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