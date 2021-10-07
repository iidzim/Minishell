/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:31:05 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/05 19:11:32 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var_by_key(char *key)
{
	int		index;
	char	*value;
	int		i;

	value = NULL;
	index = 0;
	i = 0;
	if (!key)
		return (NULL);
	index = find_env(key, g_global->env_var);
	if (index == -1)
		return (NULL);
	value = return_value(g_global->env_var[index], '=');
	return (value);
}

void	setup_in(t_cmd *cmd, t_data *m, int cpt)
{
	int	fd;

	fd = open(cmd->r[cpt].filename, O_RDWR);
	if (fd < 0)
	{
		print_error(cmd->r[cpt].filename);
		m->redir->err = 1;
		return ;
	}
	else
		m->redir->infile = fd;
}

void	setup_out(t_cmd *cmd, t_data *m, int i)
{
	int	fd;

	fd = 0;
	if (cmd->r[i].type == great)
	{
		fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd < 0)
		{
			m->redir->err = 1;
			print_error(cmd->r[i].filename);
		}
	}
	else if (cmd->r[i].type == greater)
	{
		fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
		{
			m->redir->err = 1;
			print_error(cmd->r[i].filename);
		}
	}
	m->redir->outfile = fd;
}

static int	check_only_key(char *key)
{
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (g_global->env_var[++i])
	{
		if (!ft_strcmp(g_global->env_var[i], key))
			return (i);
	}
	return (-1);
}

int	find_env(char *key, char **env_pointer)
{
	int		index;
	char	*sub_env;
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (env_pointer[++i])
	{
		index = get_str_by_char(env_pointer[i], '=', 0);
		if (index == -1)
			index = ft_strlen(env_pointer[i]);
		else
		{
			sub_env = ft_substr(env_pointer[i], 0, index);
			if (sub_env != NULL && ft_strequ(key, sub_env))
			{
				free(sub_env);
				return (i);
			}
			free (sub_env);
		}
	}
	return (check_only_key(key));
}
