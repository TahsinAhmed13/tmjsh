#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "shell.h"
#include "parse.h"

char * get_prompt()
{
    return "$"; 
}

int redirect_out(char *cmd)
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

int redirect_in(char *cmd)
{
    int save = dup(STDIN_FILENO);  
    if(strchr(cmd, '<'))
    {
        char *file = cmd; 
        cmd = strsep(&file, "<"); 
        file = trim(file); 
        int fd = open(file, O_RDONLY | O_CREAT, 0644); 
        dup2(fd, STDIN_FILENO); 
    }
    return save; 
}