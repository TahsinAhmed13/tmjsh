char * expand_path(char *); 
char * shorten_path(char *); 

char * get_prompt(char *[6]); 

int redirect_out(char *); 
int redirect_in(char *); 

int exec_pipe(char **); 