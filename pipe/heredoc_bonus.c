/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:17:43 by seok              #+#    #+#             */
/*   Updated: 2023/08/08 21:23:37 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_info *info, char **av, int i, char **envp)
{
	info->env = split_environ(envp);
	input_heredoc(info);
	while (++i < info->ac - 1)
	{
		if (i == info->ac - 2)
			outfile_heredoc(info, av, i, envp);
		else
			cmd_execution(info, av, i, envp);
	}
}

void	input_heredoc(t_info *info)
{
	pid_t	pid;
	char	*ret;

	pid = do_fork_pipe(info);
	if (pid == CHILD)
	{
		close_exit(info->fd[READ]);
		while (get_next_line(STDIN_FILENO, &ret) == true)
		{
			if (ft_strncmp(ret, info->limiter, \
				ft_strlen(info->limiter) + 1) == 0)
				exit(0);
			else
				write(info->fd[WRITE], ret, ft_strlen(ret));
			free(ret);
		}
		close_exit(info->fd[WRITE]);
	}
	else
	{
		wait(NULL);
		close_exit(info->fd[WRITE]);
		dup2(info->fd[READ], STDIN_FILENO);
		close_exit(info->fd[READ]);
	}
}

void	outfile_heredoc(t_info *info, char **av, int idx, char **envp)
{
	char	**cmd_options;
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
	{
		cmd_options = ft_split(av[idx], ' ');
		if (access_check(info->env, cmd_options[0], info) == false)
			return ;
		info->outfile_fd = open(av[info->ac - 1], \
							O_RDWR | O_CREAT | O_APPEND, 0644);
		if (dup2(info->outfile_fd, STDOUT_FILENO) == ERROR)
			my_error("outfile_heredoc dup2");
		if (execve(info->path, cmd_options, envp) == ERROR)
			my_error("outfile_heredoc execve");
	}
}
