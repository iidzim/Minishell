/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:18:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/06 11:16:44 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_env_(char	**env_)
{
	char	**env;
	int		i;

	i = -1;
	env = (char **)malloc(sizeof(char *) * (len(env_) + 1));
	if (env == NULL)
		exit(EXIT_FAILURE);
	while (++i < len(env_))
		env[i] = ft_strdup(env_[i]);
	env[i] = 0;
	return (env);
}

int	exec_proc(t_cmd *cmd, t_data *m, int *fd)
{
	g_global->pid = fork();
	if (g_global->pid == 0)
	{
		if (m->redir->infile && !m->redir->err)
			dup2(m->redir->infile, 0);
		else if (m->state->read_end != 0)
		{
			dup2(m->state->read_end, 0);
			close(m->state->read_end);
		}
		if (m->redir->outfile && !m->redir->err)
			dup2(m->redir->outfile, 1);
		else if (m->state->write_end != 1)
		{
			dup2(m->state->write_end, 1);
			close(m->state->write_end);
		}
		if (cmd->argvs != NULL && is_builtin(cmd))
			check_builtin(cmd, m);
		else
			exec_cmd_path(cmd, m, fd);
		exit (0);
	}
	return (1);
}

void	setup_all_redirections(t_cmd *cmd, t_data *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		j = -1;
		check_for_heredoc(&m[i], &cmd[i]);
		while (++j < cmd[i].redir_nbr)
		{
			if (cmd[i].r[j].type == less)
				setup_in(&cmd[i], &m[i], j);
			if ((cmd[i].r[j].type == great || cmd[i].r[j].type == greater) && \
				!m->redir->err)
				setup_out(&cmd[i], &m[i], j);
		}
	}
}

int	exec_pipe_red(t_cmd *cmd, t_data *m, t_state *state)
{
	int		i;

	i = -1;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i], state);
	pipe_all(cmd, m);
	setup_all_redirections(cmd, m);
	i = -1;
	m->state->read_end = 0;
	while (++i < cmd->nbr_cmd - 1)
	{
		pipe(m->redir->pipe_fd[i]);
		m->state->write_end = m->redir->pipe_fd[i][1];
		g_global->pid = exec_proc(&cmd[i], &m[i], m->redir->pipe_fd[i]);
		close(m->state->write_end);
		if (m->state->read_end != 0)
			close(m->state->read_end);
		m->state->read_end = m->redir->pipe_fd[i][0];
	}
	m->state->write_end = 1;
	g_global->pid = exec_proc(&cmd[i], &m[i], NULL);
	return (1);
}

void	exec_multiple_cmd(t_cmd *cmd, t_data *m, t_state *state)
{
	int		i;
	int		is_redir;

	i = 0;
	is_redir = 0;
	while (i < cmd->nbr_cmd)
	{
		if (cmd[i].redir_nbr != 0)
			is_redir = 1;
		i++;
	}
	if (!is_redir)
	{
		exec_simple_pipe(cmd, m, state);
		return ;
	}
	else
	{
		exec_pipe_red(cmd, m, state);
		close_all_pipes(m->redir->pipe_fd, cmd->nbr_cmd - 1, m);
		wait_children();
	}
	g_global->pid = 0;
}
