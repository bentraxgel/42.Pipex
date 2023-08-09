/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:00 by seok              #+#    #+#             */
/*   Updated: 2023/08/08 21:29:42 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

typedef enum e_fd
{
	READ = 0,
	WRITE,
	SAVE,
	RESTORE
}t_fd;

typedef enum e_prc
{
	ERROR = -1,
	CHILD = 0,
}t_prc;

typedef struct s_info
{
	int		stdin_fd;
	int		stdout_fd;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		ac;
	char	*path;
	char	**env;
}t_info;

// main.c
void	close_exit(int this);
pid_t	do_fork_pipe(t_info *info);

// main_utils.c
void	save_restore_fd(t_info *info, t_fd flag);
char	**split_environ(char **envp);
int		is_cmd(char *cmd_options);
int		access_check(char **env, char *cmd_options, t_info *info);
int		path_access(char **env, char *cmd_options, t_info *info);

// execution.c
void	infile_execution(t_info *info, char **av, int idx, char **envp);
void	outfile_execution(t_info *info, char **av, int idx, char **envp);
void	dup2_exit(int old, int new);

#endif