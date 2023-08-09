/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:30:27 by seok              #+#    #+#             */
/*   Updated: 2023/08/08 22:18:21 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_execution(t_info *info, char **av, int idx, char **envp)
{
	pid_t	pid;
	char	**cmd_options;

	pid = do_fork_pipe(info);
	if (pid == CHILD)
	{
		info->infile_fd = open(av[1], O_RDONLY | O_CLOEXEC);
		if (info->infile_fd == ERROR)
			my_error("In infile open");
		cmd_options = ft_split(av[idx], ' ');
		if (access_check(info->env, cmd_options[0], info) == false)
			exit(-1);
		dup2_exit(info->infile_fd, STDIN_FILENO);
		close_exit(info->fd[READ]);
		dup2_exit(info->fd[WRITE], STDOUT_FILENO);
		if (execve(info->path, cmd_options, envp) == ERROR)
			my_error("execve");
	}
	else
	{
		close_exit(info->fd[WRITE]);
		dup2_exit(info->fd[READ], STDIN_FILENO);
		close_exit(info->fd[READ]);
	}
}

void	outfile_execution(t_info *info, char **av, int idx, char **envp)
{
	char	**cmd_options;
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
	{
		cmd_options = ft_split(av[idx], ' ');
		info->outfile_fd
			= open(av[info->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (access_check(info->env, cmd_options[0], info) == false)
			exit(-1);
		dup2_exit(info->outfile_fd, STDOUT_FILENO);
		if (execve(info->path, cmd_options, envp) == ERROR)
			my_error("execve_last");
	}
}

void	dup2_exit(int old, int new)
{
	if (dup2(old, new) == ERROR)
		my_error("execution file error by dup2");
}
