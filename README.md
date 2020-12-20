## tmjsh
by Tahsin Ahmed, Michael Hu, and Jin cheng Zhang
Team tmjsh

### Features:
- Forks and executes commands
    - Allows change in workkng directory using cd
    - You will never be stuck forever with the exit command
- Parses multiple commands on a single line
- Can redirect with > and <
- Allows for simple pipes with |

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
  Returns: Pointer to first character following str that is not a whitespace

  Removes leading whitespace on the string str
  ====================*/
  
  
  /*======== char * trim_back() ==========
  Inputs:  char *str
  Returns: Pointer to the beginning of str

  Removes trailing whitespace on the string str
  A terminator is placed at the end
  ====================*/


  /*======== char * trim() ==========
  Inputs:  char *str
  Returns: Pointer to first character following str that is not a whitespace

  Removes leading and trailing whitespace on the string str
  A terminator is placed at the end
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
  separated by a whitespace

  Uses trim() to trim cmd
  Uses num_args() to dynamically allocate memory for the returned array.
  If there are multiple arguments in cmd, this function will separate
  them into and put each argument into an array of strings
  ====================*/
  ```

### shell.c
- Handles prompt display and certain shell function like redirection and piping
```
  /*======== char * expand_path() ==========
  Inputs:  char *path
  Returns: 


  ====================*/
  
  
  /*======== char * get_prompt() ==========
  Inputs:  None
  Returns: "$"

  Returns the prompt
  ====================*/


  /*======== int redirect_out() ==========
  Inputs:  char *cmd
  Returns: A save of the file descriptor of STDOUT


  ====================*/
  
  
  /*======== int redirect_in() ==========
  Inputs:  char *cmd
  Returns: A save of the file descriptor of STDIN


  ====================*/
  
  
  /*======== int exec_pipe() ==========
  Inputs:  char ** cmd
  Returns: A save of the file descriptor of STDIN


  ====================*/
  ```

### main.c
- Handles the reading, forking, and execution of commands
- Also implements the features of the other file including parsing, piping, and redirecting