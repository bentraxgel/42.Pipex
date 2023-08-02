/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:30:27 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 16:51:19 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	multiple_pipe(t_info *info, char **av, int i, char **envp)
{
	while (++i < info->ac - 1)
	{
		if (i == 2)
			infile_execution(info, av, i, envp);
		else if (i == info->ac - 2)
			outfile_execution(info, av, i, envp);
		else
			cmd_execution(info, av, i, envp);
	}
}

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
		dup2(info->infile_fd, STDIN_FILENO);
		close(info->fd[READ]);
		dup2(info->fd[WRITE], STDOUT_FILENO);
		if (execve(info->path, cmd_options, envp) == ERROR)
			my_error("execve");
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(info->fd[WRITE]);
		dup2(info->fd[READ], STDIN_FILENO);
		close(info->fd[READ]);
	}
}

void	cmd_execution(t_info *info, char **av, int idx, char **envp)
{
	char	**cmd_options;
	pid_t	pid;

	pid = do_fork_pipe(info);
	if (pid == CHILD)
	{
		cmd_options = ft_split(av[idx], ' ');
		if (access_check(info->env, cmd_options[0], info) == false)
			exit(-1);
		close(info->fd[READ]);
		dup2(info->fd[WRITE], STDOUT_FILENO);
		if (execve(info->path, cmd_options, envp) == ERROR)
			my_error("execve");
	}
	else
	{
		close(STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
		dup2(info->fd[READ], STDIN_FILENO);
		close(info->fd[WRITE]);
		close(info->fd[READ]);
	}
}

void	outfile_execution(t_info *info, char **av, int idx, char **envp)
{
	char	**cmd_options;

	cmd_options = ft_split(av[idx], ' ');
	if (access_check(info->env, cmd_options[0], info) == false)
		exit(-1);
	info->outfile_fd = open(av[info->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(info->outfile_fd, STDOUT_FILENO);
	if (execve(info->path, cmd_options, envp) == ERROR)
		my_error("execve_last");
}
