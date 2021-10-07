/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:27:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/24 15:14:30 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	env_count(void)
{
	int	i;

	i = 0;
	while (g_global->env_var[i])
		i++;
	return (i);
}

void	print_sorted_env(char **sorted_env)
{
	int		i;
	int		j;
	char	equ_sign;

	i = -1;
	while (sorted_env[++i])
	{
		j = 0;
		equ_sign = 1;
		ft_putstr_fd("declare -x ", 1);
		while (sorted_env[i][j])
		{
			ft_putchar_fd(sorted_env[i][j], 1);
			if (sorted_env[i][j] == '=' && equ_sign)
			{
				ft_putchar_fd('"', 1);
				equ_sign = 0;
			}
			j++;
		}
		if (!equ_sign)
			ft_putendl_fd("\"", 1);
		else
			ft_putchar_fd('\n', 1);
	}
}

char	**dup_env(void)
{
	char	**dup;
	int		i;

	i = env_count();
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	dup[i] = 0;
	i--;
	while (i != -1)
	{
		dup[i] = g_global->env_var[i];
		i--;
	}
	return (dup);
}

void	modify_env(char *arg, char *key)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env(key, g_global->env_var);
	if (i == -1)
		return ;
	else
	{
		new_value = ft_strdup(arg);
		tmp = g_global->env_var[i];
		g_global->env_var[i] = new_value;
		free (tmp);
	}
}

int	get_str_by_char(char *str, char c, int i)
{
	char	*str2;
	int		ret;

	str2 = ft_strchr(str, c);
	if (!str2 && i == 0)
		return (-1);
	else if (!str2 && i == 1)
		return (0);
	else
		ret = (int)(str2 - str);
	return (ret);
}
