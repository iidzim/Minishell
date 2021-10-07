/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:41 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/04 10:46:20 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** errors:
** greater than LONG_MIN   -9223372036854775808
** greater than LONG_MAX
** non numeric arg
** more then one arg
*/

void	error_exit(char *arg)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit (255);
}

long long	atoi_exit(const char *str)
{
	int					signe;
	unsigned long long	r;
	char				*error_tmp;

	error_tmp = (char *)str;
	signe = 1;
	r = 0;
	while (*str >= 9 && *str <= 32)
		str++;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + *str - '0';
		if (r > LLONG_MAX)
			error_exit(error_tmp);
		str++;
	}
	ft_putendl_fd("exit", 1);
	exit (r * signe);
}

void	exit_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '\0')
	{
		while (arg[i])
		{
			if (arg[0] == '-' || arg[0] == '+')
				i++;
			if (arg[i] < 48 || arg[i] > 57 )
			{
				ft_putendl_fd("exit", 1);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(arg, 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit (255);
			}
			i++;
		}	
	}
	atoi_exit(arg);
}

int	check_for_num_arg(char *args)
{
	int	i;
	int	is_alpha;

	i = 0;
	is_alpha = 0;
	while (args[i])
	{
		if (args[0] == '-' || args[0] == '+')
			i++;
		if (args[i] < 48 || args[i] > 57)
			is_alpha = 1;
		i++;
	}
	if (!is_alpha)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_global->exit_status = 1;
	}
	else
		error_exit(args);
	return (0);
}

int	exit_builtin(char **args)
{
	char	*trim_arg;

	trim_arg = ft_strtrim(args[1], " ");
	if (len(args) > 2)
		return (check_for_num_arg(trim_arg));
	else if (args[1])
	{
		if (!ft_strcmp(trim_arg, "-9223372036854775808"))
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		exit_number(trim_arg);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit (g_global->exit_status);
	}
	return (1);
}
