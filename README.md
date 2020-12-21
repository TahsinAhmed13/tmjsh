## tmjsh
by Tahsin Ahmed, Michael Hu, and Jin cheng Zhang
Team tmjsh

### Features:
- Forks and executes commands.
    - Allows change in working directory using cd.
    - You will never be stuck forever with the exit command!
- Parses multiple commands on a single line
- Can redirect with > and <.
- Allows for simple pipes with |.

---

### Attempted:
- 

---

### Bugs:
- 

---

### Files & Function Headers:
#### parse.c
- Handles the parsing of commands
  ```
  /*======== char * trim_front() ==========
  Inputs:  char *str
  Returns: Pointer to first character in string str that
  is not a whitespace

  Removes leading whitespace on the string str
  ====================*/
  
  
  /*======== char * trim_back() ==========
  Inputs:  char *str
  Returns: Pointer to the beginning of the string (original
  pointer)

  Removes trailing whitespace on the string str and places
  a terminator at the end
  ====================*/


  /*======== char * trim() ==========
  Inputs:  char *str
  Returns: Pointer to first character on the string str that
  is not a whitespace

  Removes leading and trailing whitespace on the string str
  and places a terminator at the end
  ====================*/


  /*======== int num_args() ==========
  Inputs:  char *cmd
  Returns: Number of arguments in cmd separated by a whitespace

  Counts the number of times a whitespace appears in the string cmd.
  The number of argument is 1 more than the number of appearances.
  If a whitespace does not appear, 1 is returned.
  ====================*/
  
  
  /*======== char ** parse_args() ==========
  Inputs:  char *cmd
  Returns: Array of strings where each entry is an argument
  separated by a whitespace from the string cmd

  Uses trim() to trim cmd
  Uses num_args() to dynamically allocate memory for the returned array.
  If there are multiple arguments in cmd, this function will separate
  them into and put each argument into an array of strings
  ====================*/
  ```

### shell.c
- Handles prompt display and certain shell functions like redirection and piping
```
  /*======== char * replace() ==========
  Inputs: char *str
          char *p1
          char *p2
  Returns: A string in which occurrences of string p1 are replaced by
  string p2

  Uses different string functions to find the occurences of string p1 in 
  the string str, then concatenating a version of string str in which p1
  is replaced by p2 
  ====================*/


  /*======== char * expand_path() ==========
  Inputs:  char *path
  Returns: A string of the full path

  Uses replace() to replace the tilda with the 
  full name of the initial working directory of the user
  ====================*/


  /*======== char * shorten_path() ==========
  Inputs:  char *path
  Returns: A string of the shortened path of the string path 

  Uses replace() to replace the full name of the initial 
  working directory to a tilda
  ====================*/


  /*======== char * get_last_dir() ==========
  Inputs:  char *path
  Returns: The last directory in the path

  ====================*/

  
  /*======== char * get_prompt() ==========
  Inputs:  None
  Returns: "$"

  Gets and returns the prompt
  ====================*/


  /*======== int redirect_out() ==========
  Inputs:  char *cmd
  Returns: A save of the file descriptor of STDOUT

  Sets up the redirection stream for "<" by using dup2()  
  to refer to the redirected file
  ====================*/
  
  
  /*======== int redirect_in() ==========
  Inputs:  char *cmd
  Returns: A save of the file descriptor of STDIN

  Sets up the redirection stream for ">" by using dup2()
  to refer to the redirected file
  ====================*/
  
  
  /*======== int exec_pipe() ==========
  Inputs:  char ** cmd
  Returns: A save of the file descriptor of STDIN

  Executes piping if the command contains a pipe
  ====================*/
  ```

### main.c
- Handles the reading, forking, and execution of commands
- Also implements the features of the other file including parsing, piping, and redirecting

### color.h
- Makes for a better stylistic prompt
