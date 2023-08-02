/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:44:03 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 16:10:26 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_cmd(char *cmd_options)
{
	if (cmd_options == NULL)
		return (false);
	return (true);
}
/*
int	is_cmd(char *cmd_options, t_info *info)
{
	if (cmd_options == NULL)
		return (false);
	if (access(cmd_options, X_OK) != ERROR)
	{
		info->path = cmd_options;
		return (true);
	}
	else
		return (false);
}

int	path_access(char *cmd_options, t_info *info)
{
	int		i;
	char	*path;

	if (is_cmd(cmd_options, info) == false)
		return (false);
	else
		return (true);
	cmd_options = ft_strjoin("/", cmd_options);


*/

int	path_access(char **env, char *cmd_options, t_info *info)
{
	int		i;
	char	*path;
	if (is_cmd(cmd_options) == false)
		return (false);
	if (access(cmd_options, X_OK) != ERROR)
	{
		info->path = cmd_options;
		return (true);
	}
	cmd_options = ft_strjoin("/", cmd_options); // "/cat -e"

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		path = ft_strjoin(path, env[i]); //"/bin"
		path = ft_strjoin_free(path, cmd_options); //"bin/cat -e"
		if (access(path, X_OK) != ERROR)
		{
			info->path = path;
			return (true);
		}
		free(path);
		path = NULL;
		i++;
	}
	free(cmd_options);
	// free(info->env);
	perror("Not access");
	return (false);
}