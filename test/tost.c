#include "pipex.h"


int main(int ac, char **av, char **envp)
{
    int in;
    int fd[2];
    char buffer[BUFSIZ];
    pid_t  pid;
    int outfile_fd;

    if (in == -1)
    {
        exit(EXIT_FAILURE);
    }
    char *c[3] = {"cat","-e", NULL};
    char *s[3] = {"cat","-e", NULL};

        
    pipe(fd);
    pid = fork();
    if (pid == -1)
    {
        perror("pid");
        exit(0);
    }
    if (pid == 0)
    {
        in = open("infile", O_RDONLY);
        dup2(in, STDIN_FILENO);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[READ]);
        execve("/bin/cat", c, envp);
    }
    outfile_fd = open("outfile2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd[READ], STDIN_FILENO);
        dup2(outfile_fd, STDOUT_FILENO);
        close(fd[WRITE]);
        execve("/bin/cat", s, envp);

    return (0);
}

