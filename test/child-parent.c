#include "pipex.h"

void	last(char **cmd)
{
	int outfile_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(outfile_fd, STDOUT_FILENO);
	char *cmd1[] = {"ls", NULL};
	execve("/bin/cat", cmd, 0);
}

void	exec_process(char *cmd[])
{
	pid_t	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == CHILD)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		execve("/bin/cat", cmd, 0);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
	}
}

void	info_init(t_info *info)
{
	info->stdin_fd = dup(STDIN_FILENO);
	info->stdout_fd = dup(STDOUT_FILENO);
	info->infile_fd = open("infile", O_RDONLY | O_CLOEXEC); //infile아니고 av[1]
}

void	info_close(t_info *info)
{
	close(info->outfile_fd);
	dup2()
}

int	main(int ac, char *av[], char **envp)
{
	t_info	info;

	info_init(&info);
	dup2(info.infile_fd, STDIN_FILENO);
	char *cmd[] = {"cat", "-e", NULL}; //PARSING_av[]

	for (int i = 0; i < 5; i++)
	{
		exec_process(cmd);
	}
	info_close(&info);
	last(cmd);
}
