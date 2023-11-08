0x16. C - Simple Shell ( COLLABORATIVE PROJECT)
the above project is to show our knowledge in c and the shell in linux operating system

below are allowed functions for the project
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

task 0
we are to create a Repo: simple_shell
and write a code which will pass Betty coding style; task 0 to task 5 and linked and as such 
we will try to create files which will be linked to each other, also header files will be created also, not 
forgetting main.c files, this will prevent us from having to describe it in every of our files 
and now have serious problems of compilation error.

Task 1
 we are to write a unix shell with command interpreter without arguments it should :
Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
we dont need to :
use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments

plus execve in an intergral part of whatever program we are to write.

Task 2 

the program must be able to handle commandline with arguments.


Task 3

handle the PATH

task 4

Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit

task 5 

Implement the env built-in, that prints the current environment

THE ABOVE ARE THE MANDATORY TASK and after the above there other Advanced task for us to try our hands on.

the program must   have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when  an error printed, the name of the program must be equivalent to our argv[0]

all the files are compiled with: 
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

If possible the Advanced task below will be attempted;

Task 6

Write your own getline function
Use a buffer to read many chars at once and call the least possible the read system call
You will need to use static variables
You are not allowed to use getline

Task 7 
You are not allowed to use strtok

task 8

handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell

Task 9Implement the setenv and unsetenv builtin commands

setenv
Initialize a new environment variable, or modify an existing one
Command syntax: setenv VARIABLE VALUE
Should print something on stderr on failure
unsetenv
Remove an environment variable
Command syntax: unsetenv VARIABLE
Should print something on stderr on failure

Task 10
Implement the builtin command cd:

Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory
man chdir, man getcwd

task 11
Handle the commands separator ;

task 12
Handle the && and || shell logical operators

task 13

Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
alias name='value' [...]: Defines an alias for each name whose value is given. 
If name is already an alias, replaces its value with value

Task 14

Handle variables replacement
Handle the $? variable
Handle the $$ variable

Task 15

Handle comments (#)

Task 16

Usage: simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin

