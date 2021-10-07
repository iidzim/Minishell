/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:46:46 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/05 15:01:51 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *file_error)
{
	write (2, "minishell: ", 11);
	write(2, file_error, ft_strlen(file_error));
	perror(" ");
}

void	check_valid_fd(t_data *m, char *file_error, int fd)
{
	if (fd < 0)
	{
		m->redir->err = 1;
		write (2, "minishell: ", 11);
		write(2, file_error, ft_strlen(file_error));
		perror(" ");
		g_global->exit_status = 1;
	}
}

void	fork_failed(void)
{
	write(2, "Fork failed", 11);
	exit(EXIT_FAILURE);
}

void	not_valid_id(char *arg)
{
	write (2, "minishell: unset: `", 19);
	write (2, arg, ft_strlen(arg));
	write (2, "': not a valid identifier\n", 26);
	g_global->exit_status = 1;
}

int	cmdnf_nsfile(t_cmd *cmd, t_data *m, char *possible_path)
{
	if (m->state->path == NULL)
	{
		write (2, "minishell: ", 11);
		write (2, cmd->argvs[0], ft_strlen(cmd->argvs[0]));
		write (2, ": No such file or directory\n", 28);
		return (1);
	}
	else if (ft_strncmp(cmd->argvs[0], "./", 2))
	{
		write (2, "minishell: ", 11);
		write(2, possible_path, ft_strlen(possible_path));
		ft_putendl_fd(": command not found", 2);
		return (1);
	}
	return (0);
}
