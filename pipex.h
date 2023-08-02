/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:00 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 16:51:30 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h> //read, write
# include <stdio.h> // BUFSIZ, perror
// # include <string.h> //strerror
# include <sys/errno.h> //errno
# include <stdlib.h> //exit
# include <fcntl.h> //open
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
	char	*limiter;
	char	**env;
}t_info;

// main.c
pid_t	do_fork_pipe(t_info *info);

// main_utills.c
void	save_restore_fd(t_info *info, t_fd flag);
char	**split_environ(char **envp);
int		is_cmd(char *cmd_options);
int		access_check(char **env, char *cmd_options, t_info *info);
int		path_access(char **env, char *cmd_options, t_info *info);

// multiple.c
void	multiple_pipe(t_info *info, char **av, int i, char **envp);
void	infile_execution(t_info *info, char **av, int idx, char **envp);
void	cmd_execution(t_info *info, char **av, int idx, char **envp);
void	outfile_execution(t_info *info, char **av, int idx, char **envp);

// heredoc.c
void	here_doc(t_info *info, char **av, int idx, char **envp);
void	input_heredoc(t_info *info);
void	outfile_heredoc(t_info *info, char **av, int idx, char **envp);
#endif