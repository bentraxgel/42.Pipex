#include "pipex.h"


int main(int ac, char **av, char **envp)
{
    t_pipex     pipex;
    int         pipefd[2];
    pid_t       pid;
    int         outfile_fd;
    // int      idx;
    if (ac != 5)
        perror_message("사용법: ./pipex infile cmd1 cmd2 outfile\n");
    int         infile_fd;
                                                                    // pipex = pipex_init(av, envp);
    pipex.infile = av[1];
    pipex.outfile = av[4];
    pipex.cmd1 = av[2];
    pipex.cmd2 = av[3];
    pipex.envp = envp;
    infile_fd = open(pipex.infile, O_RDONLY, 0644);
    if (infile_fd == -1)
        perror_message("infile error");
    dup2(infile_fd, STDIN_FILENO);
    if (access(pipex.infile, F_OK | R_OK) == -1)
        perror_message("파일 접근 오류");
    if (pipe(pipefd) == -1)
        perror_message("파이프 생성 오류");
    pid = fork();
    if (pid < 0)
        perror_message("프로세스 생성 오류");
                                                                    // make_pipe(av, envp, &pipex, pipefd);
                                                                    // make_process(&pid);
    if (pid == CHILD) // 자식이 여러개여야해서 else로 자식을 뺀 것임
    {
        close(pipefd[READ]);
        if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
            perror_message("파이프 리다이렉션 오류");
        // char *cmd1_args[] = {"/bin/ls", "-al", NULL};
        char    *cmd1_args[] = {"/bin/cat", NULL};
        execve("/bin/cat", cmd1_args, envp);
    }
    close(pipefd[WRITE]);
    outfile_fd = open(pipex.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1)
        perror_message("출력 파일 열기 오류");
    if (dup2(pipefd[READ], STDIN_FILENO) == -1)
        perror_message("파이프 리다이렉션 오류");
    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        perror_message("출력 리다이렉션 오류");
    // char *cmd2_args[] = {"/bin/cat", NULL};
    char    *cmd2_args[] = {"/bin/ls", "-al", NULL};
    execve("/bin/ls", cmd2_args, envp);
    return (0);
}
