#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>

#include "shell.h"
#include "parse.h"
#include "color.h"

#define PATH_MAX 80

/* Finds the occurences of string p1 in the string str, then
   concatenates a version of string str in which p1 is replaced by p2 */
char * replace(char *str, char *p1, char *p2)
{
    int sz = strlen(str); 
    int len1 = strlen(p1); 
    int len2 = strlen(p2); 

    char *rep = (char *) malloc(sizeof(char) * (sz+1));
    rep[0] = 0; 

    char *last = str; 
    char *next = strstr(str, p1); 
    while(next)
    {
        sz += len2 - len1; 
        rep = (char *) realloc(rep, sizeof(char) * (sz+1)); 
        strncat(rep, last, next - last); 
        strcat(rep, p2); 
        last = next + len1;         
        next = strstr(last, p1); 
    }
    strcat(rep, last); 

    return rep; 
}

/* Replace "~" with the full name of the
    initial working directory of the user */
char * expand_path(char *path)
{
    return replace(path, "~", getpwuid(getuid())->pw_dir); 
}

/* Replace the full name of the initial
   working directory to a "~" */
char * shorten_path(char *path)
{
    return replace(path, getpwuid(getuid())->pw_dir, "~"); 
}

/* */
char * get_last_dir(char *path)
{
    char *end = path + strlen(path) - 1; 
    while(end != path && *end != '/')
        --end;
    if(end == path) return end; 
    else            return end+1; 
}

/* Gets and returns the prompt */
char * get_prompt(char *colors[6])
{
    char *user = getpwuid(getuid())->pw_name; 

    char host[_SC_HOST_NAME_MAX]; 
    gethostname(host, sizeof(host));  

    char cwd[PATH_MAX]; 
    getcwd(cwd, sizeof(cwd)); 
    char *scwd = shorten_path(cwd); 
    char *dir = get_last_dir(scwd); 

    // 5 extra characters + 8 ansi codes
    int sz = strlen(user) + strlen(host) + strlen(dir) + 5 + (CODE_SIZE * 8);       
    char *prompt = (char *) malloc(sizeof(char) * (sz+1));  
    sprintf(prompt, "%s[%s%s%s@%s%s %s%s%s]%s$%s", 
        colors[0],          // bracket color 
        colors[1], user,    // user color 
        colors[2],          // @ color 
        colors[3], host,    // host color 
        colors[4], dir,     // dir color 
        colors[0],          // brack color
        colors[5],          // $ color 
        ANSI_RESET);        // reset 
    free(scwd); 

    return prompt; 
}

/* Sets up the redirection stream for "<" */
int redirect_out(char *cmd)
{
    int save = dup(STDOUT_FILENO);  
    if(strchr(cmd, '>'))
    {
        char *file = cmd; 
        cmd = strsep(&file, ">"); 
        
        file = trim(file); 
        if(!file[0])
            return -1; 

        int fd = open(file, O_WRONLY | O_CREAT, 0644); 
        dup2(fd, STDOUT_FILENO); 
        close(fd); 
    }
    return save; 
}

/* Sets up the redirection stream for ">" */
int redirect_in(char *cmd)
{
    int save = dup(STDIN_FILENO);  
    if(strchr(cmd, '<'))
    {
        char *file = cmd; 
        cmd = strsep(&file, "<"); 

        file = trim(file); 
        if(!file[0])
            return -1; 

        int fd = open(file, O_RDONLY | O_CREAT, 0644); 
        dup2(fd, STDIN_FILENO); 
        close(fd); 
    }
    return save; 
}

/* Executes piping if the command contains a pipe */
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
