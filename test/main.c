
// main.c
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{
    size_t    idx;

    (void)argc;
    (void)argv;
    idx = 0;
    while (idx < 3)
        printf("%s\n", envp[idx++]);
    return (0);
    
}