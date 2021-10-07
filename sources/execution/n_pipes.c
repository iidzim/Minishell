/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:19:57 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/05 18:47:24 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd_path(t_cmd *cmd, t_data *m, int *p_fd)
{
	int		fd;
	char	*possible_path;

	check_for_errors(cmd, m);
	possible_path = find_path(cmd->argvs[0], m->state->path);
	if (possible_path == NULL)
		possible_path = ft_strdup(cmd->argvs[0]);
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
		if (cmdnf_nsfile(cmd, m, possible_path))
			exit(127);
	if (p_fd != NULL)
	{
		close (p_fd[0]);
		close (p_fd[1]);
	}
	if (execve (possible_path, cmd->argvs, g_global->env_var))
		exit(126);
}

int	exec_process(t_cmd *cmd, t_data *m, int *fd)
{
	g_global->pid = fork();
	if (g_global->pid < 0)
		fork_failed();
	if (g_global->pid == 0)
	{
		if (m->state->read_end != 0)
		{
			dup2(m->state->read_end, 0);
			close(m->state->read_end);
		}
		if (m->state->write_end != 1)
		{
			dup2(m->state->write_end, 1);
			close(m->state->write_end);
		}
		if (cmd->argvs != NULL && is_builtin(cmd))
			check_builtin(cmd, m);
		else
			exec_cmd_path(cmd, m, fd);
		exit(0);
	}
	return (1);
}

int	exec_pipe_cmd(t_cmd *cmd, t_data *m)
{
	int		i;

	i = 0;
	m->state->read_end = 0;
	pipe_all(cmd, m);
	while (i < cmd->nbr_cmd - 1)
	{
		pipe(m->redir->pipe_fd[i]);
		m->state->write_end = m->redir->pipe_fd[i][1];
		g_global->pid = exec_process(&cmd[i], &m[i], m->redir->pipe_fd[i]);
		close(m->state->write_end);
		if (m->state->read_end != 0)
			close (m->state->read_end);
		m->state->read_end = m->redir->pipe_fd[i][0];
		i++;
	}
	m->state->write_end = 1;
	g_global->pid = exec_process(&cmd[i], &m[i], NULL);
	return (1);
}

/*
**	exec_simple_pipe() execute commands with pipes only
*/

void	exec_simple_pipe(t_cmd *cmd, t_data *m, t_state *state)
{
	int		i;

	i = -1;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i], state);
	exec_pipe_cmd(cmd, m);
	g_global->pid = 0;
	close_all_pipes(m->redir->pipe_fd, cmd->nbr_cmd - 1, m);
	wait_children();
}
