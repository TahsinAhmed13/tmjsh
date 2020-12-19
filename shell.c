#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "shell.h"
#include "parse.h"

char * expand_path(char *path)
{
    int sz = strlen(path); 
    char *home = getenv("HOME"); 
    int home_len = strlen(home); 
    char *e_path = (char *) malloc(sizeof(char) * (sz+1));  
    e_path[0] = 0; 

    char *last = path; 
    char *tilda = strchr(path, '~'); 
    while(tilda)
    {
        sz += home_len; 
        e_path = (char *) realloc(e_path, sizeof(char) * (sz+1)); 
        strncat(e_path, last, tilda-last);  
        strcat(e_path, home); 
        last = tilda + 1; 
        tilda = strchr(last, '~'); 
    }
    strcat(e_path, last); 
    return e_path; 
}

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
        close(fd); 
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
        close(fd); 
    }
    return save; 
}

int exec_pipe(char ** cmd)
{
    int save = dup(STDIN_FILENO); 
    char *sub = strsep(cmd, "|"); 
    if(*cmd)
    {
        FILE * fptr = popen(sub, "r"); 
        int fd = fileno(fptr); 
        dup2(fd, STDIN_FILENO);     
        pclose(fptr); 
    }
    else 
        *cmd = sub; 
    return save; 
}