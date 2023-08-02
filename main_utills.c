/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:44:03 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 16:38:52 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	save_restore_fd(t_info *info, t_fd flag)
{
	if (flag == SAVE)
	{
		info->stdin_fd = dup(STDIN_FILENO);
		info->stdout_fd = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(info->stdin_fd, STDIN_FILENO);
		dup2(info->stdout_fd, STDOUT_FILENO);
	}
}

char	**split_environ(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
			break ;
	}
	envp[i] = ft_strtrim(envp[i], "PATH=");
	return (ft_split(envp[i], ':'));
}

int	is_cmd(char *cmd_options)
{
	if (cmd_options == NULL)
		return (false);
	return (true);
}

int	access_check(char **env, char *cmd_options, t_info *info)
{
	if (is_cmd(cmd_options) == false)
		return (false);
	if (access(cmd_options, X_OK) != ERROR)
	{
		info->path = cmd_options;
		return (true);
	}
	return (path_access(env, cmd_options, info));
}

int	path_access(char **env, char *cmd_options, t_info *info)
{
	int		i;
	char	*path;

	cmd_options = ft_strjoin("/", cmd_options);
	i = -1;
	path = NULL;
	while (env[++i] != NULL)
	{
		path = ft_strjoin(path, env[i]);
		path = ft_strjoin_free(path, cmd_options);
		if (access(path, X_OK) != ERROR)
		{
			info->path = path;
			return (true);
		}
		free(path);
		path = NULL;
	}
	free(cmd_options);
	perror("Not access");
	return (false);
}
