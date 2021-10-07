/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:56:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/04 19:48:20 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** env [without any options]
** is used to print environment variables
*/

static void	new_env(char *arg, char *key, t_data *m)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env(key, m->state->env_);
	if (i == -1)
	{
		i = 0;
		while (m->state->env_[i])
			i++;
		m->state->env_ = realloc_new_env(i, arg, m->state->env_);
	}
	else
	{
		i = find_env(key, m->state->env_);
		if (i == -1)
			return ;
		else
		{
			new_value = ft_strdup(arg);
			tmp = m->state->env_[i];
			m->state->env_[i] = new_value;
			free (tmp);
		}
	}
}

void	add_to_env(char *arg, t_data *m)
{
	int		i;
	char	*key;

	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=', 0);
	if (i == -1)
		return ;
	key = ft_substr(arg, 0, i);
	new_env(arg, key, m);
	free (key);
}

int	env_builtin(t_data *m)
{
	int	i;

	i = 0;
	g_global->exit_status = 0;
	while (m->state->env_[i] != NULL)
	{
		ft_putendl_fd(m->state->env_[i], 1);
		i++;
	}
	return (1);
}
