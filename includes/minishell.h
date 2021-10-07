/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/05 19:25:09 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include "./exec.h"
# include "lexer.h"
# include "parser.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <curses.h>
# include <sys/stat.h>

typedef struct s_global
{
	char	**env_var;
	int		pid;
	int		exit_status;
}	t_global;

t_global	*g_global;

/*
** Helpers 
*/

int			find_env(char *key, char **env_pointer);
char		*get_env_var_by_key(char *key);
char		*return_value(const char *s, int c);
int			get_str_by_char(char *str, char c, int i);
int			is_valid_env_key(char *arg);
void		modify_env(char *arg, char *key);
void		exec_cmd_path(t_cmd *cmd, t_data *m, int *p_fd);
void		find_cmd_path(t_cmd *cmd, t_data *m);

/*
** builtins
*/

int			cd_builtin(char **arg);
int			echo_builtin(char **arg);
int			pwd_builtin(void);
void		add_to_env(char *arg, t_data *m);
int			env_builtin(t_data *m);
int			exit_builtin(char **args);
int			unset_builtin(char **args, t_data *m);
int			export_builtin(char **arg, t_data *m);
char		*add_char_to_word(char *word, char c);
char		*get_pwd(void);
char		*return_value(const char *s, int c);
int			error_path(const char *cmd, const char *path, int errnum);
void		error_exit(char *arg);
long long	atoi_exit(const char *str);

#endif
