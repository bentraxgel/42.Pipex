/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:17:43 by seok              #+#    #+#             */
/*   Updated: 2023/07/31 22:53:24 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_info *info, char **av, int i, char **envp)
{
	char	**env;
	char	**cmd_options;

	// write(1, "here", 4);
	env = split_environ(envp);
	input_heredoc(info);
	while (++i < info->ac - 1)
	// while ( 1)
	{
		// char *v = ft_itoa(i);
		// write(1, "\n", 1);
		// write(1, v, ft_strlen(v));
		// write(1, " : ", 1);
		// write(1, av[i], ft_strlen(av[i]));
		// write(1, "\n", 1);
		cmd_options = ft_split(av[i], ' ');
		info->path = path_access(env, cmd_options[0]);
		// if (i == 2) //heredoc은 first_e필요없음
		if (i == info->ac - 2)
			outfile_heredoc(info, av, i, envp);
		// heredoc last_e도 따로 처리해야함 APPEND땜시
		else
			cmd_execution(info, av, i, envp);
	}
}

void	input_heredoc(t_info *info)
{
	pid_t	pid;
	char	*ret;

	pipe(info->fd);
	pid = fork();
	if (pid == ERROR)
		my_error("Fail fork");
	else if (pid == CHILD)
	{
		close(info->fd[READ]);
		// write(1, "H", 1);
		while (get_next_line(STDIN_FILENO, &ret) == true)
		{
			if (ft_strncmp(ret, info->limiter, ft_strlen(info->limiter) + 1) == 0) {
				// break ; //프로세스가 종료되지 않고 실행중이야 바보야!
				exit(0);
				// close(info->fd[WRITE]);
			}
			else
				write(info->fd[WRITE], ret, ft_strlen(ret));
				// write(1, ret, ft_strlen(ret));
		}
		close(info->fd[WRITE]);
	}
	else
	{
		wait(NULL);
		fprintf(stderr, "**********\n");
		close(info->fd[WRITE]);
		dup2(info->fd[READ], STDIN_FILENO);
		close(info->fd[READ]);
	}
}

// void	input_heredoc(t_info *info)
// {
// 	// pid_t	pid;
// 	char	*ret;

// 	pipe(info->fd);
	
// 		write(1, "H", 1);
// 		while (get_next_line(STDIN_FILENO, &ret) == true)
// 		{
// 			if (ft_strncmp(ret, info->limiter, ft_strlen(info->limiter) + 1) == 0)
// 				break ;
// 			else
// 				write(info->fd[WRITE], ret, ft_strlen(ret));
// 				// write(1, ret, ft_strlen(ret));
// 		}
// 		close(info->fd[WRITE]);
	
// 		dup2(info->fd[READ], STDIN_FILENO);
// 		close(info->fd[READ]);
// 		close(info->fd[READ]);
// }

void	outfile_heredoc(t_info *info, char **av, int idx, char **envp)
{
	char	**cmd_options;

	cmd_options = ft_split(av[idx], ' ');
	info->outfile_fd = open(av[info->ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(info->outfile_fd, STDOUT_FILENO);
	if (execve(info->path, cmd_options, envp) == ERROR)
		my_error("execve_last");
}