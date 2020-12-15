#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char * trim_front(char *str)
{
    while(*str == ' ')
        ++str; 
    return str; 
}

char * trim_back(char *str)
{
    char *tmp = str; 
    tmp += strlen(str) - 1; 
    while(*tmp == ' ')
        --tmp; 
    *(tmp + 1) = 0; 
    return str; 
}

char * trim(char *str)
{
    return trim_back(trim_front(str)); 
}

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

int redirect(char *cmd)
{
    int save = dup(STDOUT_FILENO);  
    if(strchr(cmd, '>'))
    {
        char *file = cmd; 
        cmd = strsep(&file, ">"); 
        file = trim(file); 
        int fd = open(file, O_WRONLY | O_CREAT, 0644); 
        dup2(fd, STDOUT_FILENO); 
    }
    return save; 
}

void reset(int save)
{
    close(STDOUT_FILENO); 
    dup2(save, STDOUT_FILENO); 
}
