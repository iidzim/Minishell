/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:44:36 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/06 11:25:28 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_for_errors(t_cmd *cmd, t_data *m)
{
	if (!cmd->argvs)
		exit(g_global->exit_status);
	if (m->redir->err)
	{
		g_global->exit_status = 1;
		exit(g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "\0"))
	{
		write (2, "minishell: ", 11);
		ft_putendl_fd(": command not found", 2);
		exit (g_global->exit_status);
	}
}

int	check_for_permission(t_cmd *cmd)
{
	struct stat	sb;
	DIR			*dirp;

	dirp = opendir(cmd->argvs[0]);
	write (2, "minishell :", 11);
	write(2, cmd->argvs[0], ft_strlen(cmd->argvs[0]));
	if (dirp)
	{
		closedir(dirp);
		ft_putstr_fd(": is a directory\n", 2);
		return (126);
	}
	if (stat(cmd->argvs[0], &sb) == 0)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	if (!dirp)
		ft_putstr_fd(" Not a directory\n", 2);
	return (126);
}

void	find_cmd_path(t_cmd *cmd, t_data *m)
{
	char	*possible_path;
	int		fd;

	check_for_errors(cmd, m);
	possible_path = find_path (cmd->argvs[0], m->state->path);
	if (possible_path == NULL)
		possible_path = ft_strdup(cmd->argvs[0]);
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
		if (cmdnf_nsfile(cmd, m, possible_path))
			exit(127);
	if (execve (possible_path, cmd->argvs, g_global->env_var))
		exit(check_for_permission(cmd));
}

/*
** execute_regular_cmd() executes regular command, commands with 
** no redirections & no pipes
*/

int	execute_regular_cmd(t_cmd *cmd, t_data *m)
{
	pid_t	child_pid;

	if (is_builtin(cmd))
		return (check_builtin(cmd, m));
	else
	{
		g_global->pid = 0;
		child_pid = fork();
		if (child_pid < 0 )
			fork_failed();
		else if (child_pid == 0)
			find_cmd_path(cmd, m);
		wait_children();
		g_global->pid = 1;
		restore_std(m->saved_stdout, m->saved_stdin);
	}
	return (1);
}
