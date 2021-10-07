/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:28:20 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/06 13:26:44 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	setup_infiles(t_cmd *cmd, t_data *m, int i)
{
	int	fd;

	if (cmd->r[i].type == less)
	{
		fd = open(cmd->r[i].filename, O_RDWR);
		m->redir->infile = fd;
		check_valid_fd(m, cmd->r[i].filename, fd);
	}
	if (!m->redir->err)
	{
		if (dup2(m->redir->infile, 0) < 0)
		{
			printf("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
		close(m->redir->infile);
	}
}

void	setup_outfiles(t_cmd *cmd, t_data *m, int i)
{
	int	fd;

	if (cmd->r[i].type == great && !m->redir->err)
	{
		fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		m->redir->outfile = fd;
		check_valid_fd(m, cmd->r[i].filename, fd);
	}
	else if (cmd->r[i].type == greater && !m->redir->err)
	{
		fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		m->redir->outfile = fd;
		check_valid_fd(m, cmd->r[i].filename, fd);
	}
	if (!m->redir->err)
	{
		dup2(m->redir->outfile, 1);
		close(m->redir->outfile);
	}
}

int	setup_redirections(t_cmd *cmd, t_data *m)
{
	int	i;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == less)
			setup_infiles(cmd, m, i);
		if ((cmd->r[i].type == greater || cmd->r[i].type == great) && \
			!m->redir->err)
			setup_outfiles(cmd, m, i);
		i++;
	}
	return (1);
}

/*
**	exec_single_cmd() executes single commands , 
**	commands with redirections and no pipes.
*/

void	check_for_heredoc(t_data *m, t_cmd *cmd)
{
	int		i;
	char	*pfree;

	i = -1;
	if ((count(cmd, here_doc) == 0))
		return ;
	else
	{
		while (++i < cmd->redir_nbr)
		{
			if (cmd->r[i].type == here_doc)
			{
				parse_here_doc(&cmd->r[i], m);
				cmd->r[i].type = less;
				pfree = cmd->r[i].filename;
				cmd->r[i].filename = m->redir->filename_;
				free (pfree);
			}
		}
	}
}

void	exec_single_cmd(t_cmd *cmd, t_data *m)
{
	pid_t	child_pid;

	setup_redirections(cmd, m);
	if (is_builtin(cmd) && !m->redir->err)
	{
		check_builtin(cmd, m);
		restore_std(m->saved_stdout, m->saved_stdin);
		return ;
	}
	else
	{
		child_pid = fork();
		if (child_pid < 0)
			fork_failed();
		else if (child_pid == 0)
			find_cmd_path(cmd, m);
		else
			wait_children();
		restore_std(m->saved_stdout, m->saved_stdin);
	}
}
