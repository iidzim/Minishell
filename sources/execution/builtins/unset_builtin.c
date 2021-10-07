/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:20:06 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/05 10:52:34 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	void	free_old_env(char **env_pointer)
{
	int	i;

	i = 0;
	while (env_pointer[i])
	{
		free(env_pointer[i]);
		env_pointer[i] = NULL;
		i++;
	}
	free (env_pointer);
	env_pointer = NULL;
}

char	**realloc_new_env(int env_num, char *arg, char **env_pointer)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (env_num + 2));
	if (!new_env)
		return (NULL);
	while (env_pointer[i])
	{
		new_env[i] = ft_strdup(env_pointer[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[env_num + 1] = 0;
	free_old_env(env_pointer);
	return (new_env);
}

char	**remove_env_by_key(int index, char **env_pointer)
{
	char			*next_env;
	char			*pfree;
	register int	i;

	i = index;
	if (i < len(env_pointer))
	{
		while (env_pointer[i + 1] != NULL)
		{
			next_env = ft_strdup(env_pointer[i + 1]);
			pfree = env_pointer[i];
			env_pointer[i] = next_env;
			free (pfree);
			i++;
		}
	}
	pfree = env_pointer[i];
	env_pointer[i] = 0;
	free (pfree);
	return (env_pointer);
}

/*
**  unset a bash environment variable
**  unset arg
**  unset arg1 arg2 *
*/

int	unset_builtin(char **args, t_data *m)
{
	int	i;
	int	env_index;
	int	env_index_;

	i = -1;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		env_index = find_env(args[i], g_global->env_var);
		env_index_ = find_env(args[i], m->state->env_);
		if (env_index_ != -1)
			m->state->env_ = remove_env_by_key(env_index_, m->state->env_);
		if (env_index != -1)
			g_global->env_var = remove_env_by_key(env_index, g_global->env_var);
		else
		{
			if (!is_valid_env_key(args[i]))
			{
				not_valid_id(args[i]);
				continue ;
			}
		}
	}
	return (1);
}
