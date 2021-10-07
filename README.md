# Minishell
The objective of this project is for you to create a simple shell. Yes, your
own little bash or zsh. You will learn a lot about processes and file descriptors.

## Overview :

[Tutorial - Write a Shell in C - Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)

[Want to build a simple shell? Here's how you do it.](https://nickolasteixeira.medium.com/want-to-build-a-simple-shell-heres-how-you-do-it-75890647bae8)

## What is a shell?

The shell is a command line interface (CLI) program that takes commands from the keyboard and gives them to the operating system to perform.

## Man for somfunctions :

`fork`  

creates a new process by duplicating the calling process. The new process is referred to as the child process. The calling process is referred to as the parent process. After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.

It takes no parameters and returns an integer value. Below are different values returned by fork().

***Negative Value***: the creation of a child process was unsuccessful. ***Zero***: Returned to the newly created child process.***Positive value***: Returned to parent or caller. The value contains the process ID of the newly created child process.

[Fork() system call tutorial](https://www.youtube.com/watch?v=xVSPv-9x3gk)

`wait` 

A call to wait() blocks the calling process until one of its child processes exits or a signal is received. After the child process terminates, the parent continues its execution after wait system call instruction.

We know if more than one child processes are terminated, then wait() reaps any arbitrarily child process but if we want to reap any specific child process, we use `waitpid` function.

`wait3`     `wait4`

The wait3() and wait4() system calls are similar to `waitpid`(2), but additionally, return resource usage information about the child in the structure pointed to by rusage.

The difference is  wait3() waits of any child, while wait4() can be used to select a specific child, or children, on which to wait.

`signal`

A signal is a software generated interrupt that is sent to a process by the OS because of when the user press ctrl-c or another process tells something to this process. There are fixed set of signals that can be sent to a process. signal are identified by integers.

```c
#include<stdio.h>
#include<signal.h>
**int** main()
{
	**signal**(SIGINT, handle_sigint);
	while(1)
	{
		**printf**(“hello world\n”);
		sleep(1);
	}
	return 0;
}
```

Output: Print hello world infinite times. If user presses ctrl-c to terminate the process because of SIGINT signal sent and its default handler to terminate the process.

`dup` `dup2`

[https://www.youtube.com/watch?v=EqndHT606Tw](https://www.youtube.com/watch?v=EqndHT606Tw)

[What does dup2() do in C](https://stackoverflow.com/questions/24538470/what-does-dup2-do-in-c)

[The dup2 Function in C](https://www.delftstack.com/howto/c/dup2-in-c/)

`pipe`

Conceptually, a pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process.

[Pipe() tutorial for linux](https://www.youtube.com/watch?v=uHH7nHkgZ4w)

`execve`

execve() executes the program pointed to by filename. filename must be either a binary executable or a script starting with a line of the form "#! interpreter [arg]". On success, execve() does not return, on error -1 is returned, and errno is set appropriately.

`getenv`

searches for the environment string pointed to by name and returns the associated value to the string.

`isatty`

is a function that returns 1 if the file descriptor refers to a terminal.

Further investigation would lead you to the discovery that file descriptors 0, 1 and 2 (aka STDIN_FILENO, STDOUT_FILENO and STDERR_FILENO) are by convention set up to point to your terminal when your program is running from a terminal.

## Termcap and Terminfo

[Termcap et Terminfo * Tutoriels * Zeste de Savoir](https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/)

[General Terminal Interface](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap11.html#tag_11_01_07)

### Termios Functions:

[terminfo(4) [osf1 man page]](https://www.unix.com/man-page/osf1/4/terminfo/)

[termcap(4) [osf1 man page]](https://www.unix.com/man-page/osf1/4/termcap/)

## Notion :
 [https://www.notion.so/ikram9/MiniShell-b2a9017a1f784f4da4e55b79c3c46975](https://www.notion.so/ikram9/MiniShell-b2a9017a1f784f4da4e55b79c3c46975)
