# LINUX SHELL : MYSHELL

## Running the Shell

1. Clone the directory with: `git@github.com:mallika2011/Linux-C-Shell.git`
2. `cd` into the `Linux-C-Shell` directory.
3. Run the `make` command
4. Run `./run` to start the shell
5. Enter `quit` to exit the shell.
## Brief Overview

This shell is a complete working linux shell. It supports most linux shell functionalities including semicolon separated commands, piping, redirection, all basic linux commands etc. Foreground and Background processes can also be executed.
The commands that are supported are as follows :

* pwd : prints the present working directory.
* cd  : changes the directory based on the flags given.

  * ``` bash
    cd
    cd .
    cd ..
    cd ~
    cd <directory>
    ```

* ls : lists the contents of a particular directory based on the flags given.

  * ```bash
    ls
    ls -a
    ls -l
    ls -al
    ls -la
    ls <directory>

* echo : prints a message on the terminal

  * ```bash
    echo <"Hello World">
    ```

* pinfo : lists the details of a particular process (may be based on a process ID that is given).
  
  * ```bash
    pinfo
    pinfo <pid>
    ```

* Foreground Processes: Processes that require the terminal to halt until their completion. Example:
  
  * ```bash
    vi
    emacs
    ```

* Background Processes: Processes that run simultaneuosly without interrupting the terminal. Example:

  * ```bash
    emacs &
    ```

* Input output redirection : Redirects input or output to appropriate files. Example:

  * ```bash
    cat file1.txt > file2.txt
    sort < sort.txt > sorted.txt
    ```

* Piping commands : Pipes two or more commands together. Example:

  * ```bash
    cat test.txt | grep a
    ```

* Piping with redirection : Example :

  * ```bash
    sort < sort.txt  | grep a | wc > lines.txt
    ```

* setenv : setting new environment variables. Example :

  * ```bash
    setenv a 15
    ```

* unsetenv : unsetting an environment variable

  * ```bash
    unsetenv a
    ```

* jobs : prints all the  background jobs

  * ```bash
    jobs
    ```

* kjob : Sends a signal to  a particular job number

  * ```bash
    kjob 1 9
    ```

* fg : brings a running or a stopped background job with given job number to foreground.

  * ```bash
    fg 1
    ```

* bg : changes a stopped background job to a running background job.

  * ```bash
    bg 1
    ```

* overkill : kills all background process at once.

  * ```bash
    overkill
    ```

* The terminal also supports

  * CTRL + Z

  * CTRL + C

## Running the Shell

In order to run the shell run the following command.

```bash
    make
    ./run
```

## Exiting From the shell

To exit from the shell, use the command

```bash
quit
```

## Pseudo Home

If the executable is being run from a different directory, specify the corresponding path. <br>
The "Pseudo Home" directory for the shell will be the directory in which the executable ./run resides.

## Code Files and Files

* myshell.c:

  * promptprint(): function to print th shell promt.

  * loop(): runs the main loop of the code for the continuous execution of the shell.

  * del_process(): function that accounts for the child processes that have terminated and thereby removes them from the process array.

  * done(): function that is to be executed as soon the parent process is interrupted by a signal of the termination of any of its child processes.

* pwd.c:

  * pwd(): function that prints the present working directory.

* ls.c:
  * The flags -a, -l, -la, -al can be used. Complete or absolute path of a directory can also be provided to list the contents of that directory.
  
  * lsa(): lists files and directories including hidden files.

  * lsl(): lists all information about files and directories excluding header files.

  * onlyls(): simply lists all files and directories.

  * ls() : driver function to choose amongst the above functions.

* cd.c:
  
  * cd (): Absolute or relative path of a directory must provided. The directory will then be changed the argument provided.

* echo.c:

  * echo(): Prints a string argument on the terminal. Handles cases with and without quotes.

* pinfo.c():

  *pinfo(): Provides details about currently active/running processes. A particular process ID can also be provided as an argument to obtain its details.

* foreground.c:

  * fore(): Forks the existing process and runs a child process in the foreground. The parent process resumes once the child terminates and waits till then.

* background.c:

  * back(): Forks the existing process and runs a child process in the background. The parent process continues to run alongside the child process. Once the child terminates, the exit satus of the child process prints on the screen.

  _background processes for built in commands are not supported_

* history.c:

  * his_load(): loads the history from an earlier terminal session.

  * his_check(): checks if the latest command has already been accounted for in the history. If it hasn't then it writes it into the file.

  * his_print(): prints the history upto 10 commands earlier.

  * wr() and del(): writes and deletes from the history respectively using a queue.

  * To load the history from previous sessions, the "his.txt" file must be present in the directory from where the executable is run.
