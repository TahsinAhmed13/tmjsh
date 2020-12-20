#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "parse.h"
#include "shell.h"
#include "color.h"

#define CMD_SIZE 256

char *PROMPT_COLORS[6] = {
    ANSI_RED, 
    ANSI_YELLOW, 
    ANSI_GREEN, 
    ANSI_BLUE, 
    ANSI_PURPLE, 
    ANSI_WHITE
}; 

int main()
{
    int proc; 
    int status; 
    char buffer[CMD_SIZE]; 
    char *cmd = NULL; 

    while(1)
    {
        if(!cmd)    // no command in buffer
        {
            if(ftell(stdin) < 0)
            {
                char *prompt = get_prompt(PROMPT_COLORS); 
                printf("\n%s ", prompt);  
                free(prompt); 
            }

            fgets(buffer, CMD_SIZE, stdin);  
            if(strchr(buffer, '\n'))
                *strchr(buffer, '\n') = 0; 

            cmd = buffer; 
        }

        // save next command for later
        char * next = cmd; 
        cmd = strsep(&next, ";"); 

        // execute piped commands
        int save_pipe = exec_pipe(&cmd); 

        // setup redirection stream
        int save_out = redirect_out(cmd); 
        int save_in = redirect_in(cmd); 

        // parse
        cmd = expand_path(cmd);   
        char ** argsv = parse_args(cmd);
        
        // execute
        if(!strcmp(argsv[0], "exit"))
            return 0; 
        else if(!strcmp(argsv[0], "cd"))
            if(argsv[1])    chdir(argsv[1]); 
            else            chdir(getenv("HOME")); 
        else 
        {
            proc = fork(); 
            if(proc)
            {
                // parent
                waitpid(proc, &status, 0); 
            }
            else 
            {
                // child
                execvp(argsv[0], argsv); 
                printf("tmjsh:\t%s:\t%s\n", argsv[0], "command not found"); 
                return 0; 
            }
        }
        free(cmd); 
        free(argsv); 

        // undo redirection stream
        dup2(save_in, STDIN_FILENO); 
        dup2(save_out, STDOUT_FILENO); 

        // undo piping
        dup2(save_pipe, STDIN_FILENO); 

        // handle next command 
        cmd = next; 
    }
    return 0; 
}
