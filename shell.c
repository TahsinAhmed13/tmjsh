#include <stdlib.h>
#include <string.h>

char ** parse_args(char *argsc)
{
    char ** argsv = (char **) malloc(sizeof(char *));

    int i = 0;
    while(argsc)
    {
        argsv[i] = strsep(&argsc, " ");
        ++i;
    }
 
    return argsv;
}