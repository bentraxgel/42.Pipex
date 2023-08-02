/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:30:27 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 15:58:18 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_execution(t_info *info, char **av, int idx, char **envp)
{
	pid_t	pid;
	char	**cmd_options;

(void)envp;
	pipe(info->fd);
	pid = fork();
	if (pid == ERROR)
		my_error("Fail fork");
	else if (pid == CHILD)
	{
		info->infile_fd = open(av[1], O_RDONLY | O_CLOEXEC);
		if (info->infile_fd == ERROR)
			my_error("In infile open");
		cmd_options = ft_split(av[idx], ' ');
		if (path_access(info->env, cmd_options[0], info) == false)
		{
			// my_free(cmd_options);
			exit(1) ;
		}
		dup2(info->infile_fd, STDIN_FILENO);
		close(info->fd[READ]);
		dup2(info->fd[WRITE], STDOUT_FILENO);
		if (execve(info->path, cmd_options, 0) == ERROR)
			my_error("execve");
		// my_free(cmd_options);
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

	pipe(info->fd);
	pid = fork();
	if (pid == ERROR)
		my_error("Fail fork");
	else if (pid == CHILD)
	{
		cmd_options = ft_split(av[idx], ' ');
		if (path_access(info->env, cmd_options[0], info) == false)
		{
			// my_free(cmd_options);
			exit(1) ;
		}
		close(info->fd[READ]);
		dup2(info->fd[WRITE], STDOUT_FILENO);
		if (execve(info->path, cmd_options, envp) == ERROR)
			my_error("execve");
		// my_free(cmd_options);
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


// int	path_access(char **env, char *cmd_options, t_info *info)
// {
// 	int		i;
// 	char	*path;
// 	if (is_cmd(cmd_options) == false)
// 		return (false);
// 	if (access(cmd_options, X_OK) != ERROR)
// 	{
// 		info->path = cmd_options;
// 		return (true);
// 	}
// 	cmd_options = ft_strjoin_free("/", cmd_options);

// 	i = 0;
// 	path = NULL;
// 	while (env[i] != NULL)
// 	{
// 		path = ft_strjoin_free(path, env[i]);
// 		path = ft_strjoin_free(path, cmd_options);
// 		if (access(path, X_OK) == ERROR)
// 		{
// 			free(path);
// 			path = NULL;
// 		}
// 		else
// 		{
// 			info->path = path;
// 			return (true);
// 		}
// 		i++;
// 	}
// 	perror("Not access");
// 	return (false);
// }

// TODO don't need?
char	*str_cmd(char **cmd_options)
{
	char	*cmd;
	int		i;

	i = -1;
	while (cmd_options[++i])
		cmd = ft_strjoin_free(cmd, cmd_options[i]);
	return (cmd);
}

void	outfile_execution(t_info *info, char **av, int idx, char **envp)
{
	char	**cmd_options;

	cmd_options = ft_split(av[idx], ' ');
	if (path_access(info->env, cmd_options[0], info) == false)
	{
		// my_free(cmd_options);
		exit(1) ;
	}
	info->outfile_fd = open(av[info->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(info->outfile_fd, STDOUT_FILENO);
	if (execve(info->path, cmd_options, envp) == ERROR)
		my_error("execve_last");
	// my_free(cmd_options);
}