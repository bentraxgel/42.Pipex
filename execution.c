/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:30:27 by seok              #+#    #+#             */
/*   Updated: 2023/07/30 16:46:09 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_execution(t_info *info, char **av, int idx, char **envp)
{
	pid_t	pid;
	char	**cmd_options;

	pipe(info->fd);
	pid = fork();
	cmd_options = ft_split(av[idx], ' ');
	if (pid == ERROR)
		my_error("Fail fork");
	else if (pid == CHILD)
	{
		info->infile_fd = open(av[1], O_RDONLY | O_CLOEXEC);
		if (info->infile_fd == ERROR)
			my_error("In infile open");
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

	cmd_options = ft_split(av[idx], ' ');
	pipe(info->fd);
	pid = fork();
	if (pid == ERROR)
		my_error("Fail fork");
	else if (pid == CHILD)
	{
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

// char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	int		s1_len;
// 	int		s2_len;
// 	char	*ret;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	ret = (char *)malloc(s1_len + s2_len + 1);
// 	if (!ret)
// 		return (0);
// 	ft_memcpy(ret, s1, s1_len);
// 	// if (s1 != NULL)
// 	// 	free(s1);
// 	ft_memcpy(ret + s1_len, s2, s2_len);
// 	ret[s1_len + s2_len] = 0;
// 	return (ret);
// }

char	*path_access(char **env, char *cmd_options)
{
	int		i;
	char	*path;
	// char	*path1;
	char	*slash = "/";
	cmd_options = ft_strjoin_free(slash, cmd_options);

	i = 0;
	path = NULL;
	for (int i = 0; env[i]; i++)
		printf("[%d] -> %s\n",i, env[i]);
	while (env[i] != NULL)
	{
		path = ft_strjoin_free(path, env[i]);
		printf("+ env[%d] : %s +\n", i, env[i]);
		// path = ft_strjoin(path, slash);
		path = ft_strjoin_free(path, cmd_options);
		printf("%s\n", path);
		if (access(path, X_OK) == ERROR)
		{
			free(path);
			path = NULL;
			// printf("<%s>\n", path);
		}
		else
			return (path);
		i++;
	}
	my_error("Not access");
	return (0);
}

// don't need?
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
	info->outfile_fd = open(av[info->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(info->outfile_fd, STDOUT_FILENO);
	if (execve(info->path, cmd_options, envp) == ERROR)
		my_error("execve_last");
}