/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/06 13:19:21 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include "lexer.h"

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	int				is_quoted;
}					t_redir;

typedef struct s_cmd
{
	int				nbr_cmd;
	int				args_size;
	char			**argvs;
	int				redir_nbr;
	t_redir			*r;
	t_token_type	type;
}	t_cmd;

typedef struct s_red
{
	int				infile;
	int				outfile;
	int				err;
	int				in_heredoc;
	char			*filename_;
	int				**pipe_fd;
}	t_red;

typedef struct s_state
{
	char			**env_;
	char			**path;
	int				read_end;
	int				write_end;
}	t_state;

typedef struct s_data
{
	int				saved_stdout;
	int				saved_stdin;
	t_red			*redir;
	t_state			*state;
}	t_data;

/*
** Free_functions
*/

void		main_free(t_data *m, t_cmd *cmd);
void		free_path(char **path);
void		ft_freeptr(void *ptr);

/*
** Exec helpers
*/

int			is_builtin(t_cmd *cmd);
char		*find_path(char	*cmd, char **path);
int			pipe_all(t_cmd *cmd, t_data *m);
void		close_all_pipes(int **fd, int n, t_data *m);
void		init_m(t_data *m, t_state *state);

/*
** Error functions
*/

void		print_error(char *file_error);
void		check_valid_fd(t_data *m, char *file_error, int fd);
void		fork_failed(void);
void		not_valid_id(char *arg);
int			cmdnf_nsfile(t_cmd *cmd, t_data *m, char *possible_path);

/*
** Here_doc
*/

int			count(t_cmd *cmd, t_token_type type);
char		*envar_here_doc(char *buff, int i);
void		parse_here_doc(t_redir *r, t_data *m);

/*
** Main_exec
*/

void		restore_std(int saved_stdout, int saved_stdin);
int			dup_env_var(char **env);
char		**get_path(void);
void		wait_children(void);
char		**get_env_(char	**env_);

/*
** Error Functions
*/

void		setup_out(t_cmd *cmd, t_data *m, int j);
void		setup_in(t_cmd *cmd, t_data *m, int j);
void		error_retrieving_cd(void);
int			check_for_permission(t_cmd *cmd);

/*
** Utils
*/

int			env_count(void);
char		**dup_env(void);
void		print_sorted_env(char **sorted_env);
char		**realloc_new_env(int env_num, char *arg, char **env_pointer);
int			set_env_var(char *key, char *new_path);

/*
** main
*/

void		check_for_heredoc(t_data *m, t_cmd *cmd);
void		exec_multiple_cmd(t_cmd *cmd, t_data *m, t_state *state);
void		exec_simple_pipe(t_cmd *cmd, t_data *m, t_state *state);
void		exec_single_cmd(t_cmd *cmd, t_data *m);
int			execute_regular_cmd(t_cmd *cmd, t_data *m);
void		sigint_handler(int sig);
void		check_for_errors(t_cmd *cmd, t_data *m);
int			valid_envar(char c);

#endif
