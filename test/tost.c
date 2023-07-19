//test.c
#include <unistd.h>
#include <stdio.h>

extern char **environ;

int    main(int ac, char **av, char **envp)
{
    // execve("print_envp", NULL, environ);
    execve("print_envp", NULL, envp);
    perror(NULL);
    return (1);
}