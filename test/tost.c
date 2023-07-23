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
    char *s[3] = {"ls","-al", NULL};

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
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        execve("/bin/cat", c, envp);
    }
    pid = fork();
    pipe(fd);

    if (pid == -1)
    {
        perror("pid");
        exit(0);
    }
    if (pid == 0)
    {
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        // close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        // dup2(STDIN_FILENO, fd[WRITE]);
        execve("/bin/cat", c, envp);
    }
    pipe(fd);
    // wait(NULL);
    outfile_fd = open("outfile1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd[READ], STDIN_FILENO);
        dup2(outfile_fd, STDOUT_FILENO);
        close(fd[WRITE]);
        execve("/bin/cat", c, envp);

    return (0);
}

