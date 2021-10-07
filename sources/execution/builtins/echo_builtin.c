/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:06:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/23 11:14:50 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	check_n_option(char **args)
{
	int	i;

	if (args[2] == NULL)
		return ;
	i = 2;
	while (is_valid_option(args[i]) == 0)
	{
		i++;
		if (args[i] == NULL)
			return ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
}

int	echo_builtin(char **args)
{
	int	j;

	g_global->exit_status = 0;
	if (args[1] == NULL)
		ft_putstr_fd("\n", 1);
	else
	{
		if (is_valid_option(args[1]) == 0)
			check_n_option(args);
		else
		{
			j = 1;
			while (args[j] != NULL)
			{
				ft_putstr_fd(args[j], 1);
				if (args[j + 1] != NULL)
					ft_putstr_fd(" ", 1);
				j++;
			}
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
